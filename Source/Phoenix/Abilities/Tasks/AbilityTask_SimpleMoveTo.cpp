// Created by Bruce Crum.


#include "Phoenix/Abilities/Tasks/AbilityTask_SimpleMoveTo.h"

#include "NavigationSystem.h"

UAbilityTask_SimpleMoveTo::UAbilityTask_SimpleMoveTo()
{
	bTickingTask = false;

	MoveRequestID = FAIRequestID::InvalidRequest;
	MoveRequest = FAIMoveRequest();
	OwnerController = nullptr;
}

UAbilityTask_SimpleMoveTo* UAbilityTask_SimpleMoveTo::SimpleMoveTo(UGameplayAbility* OwningAbility, AController* Controller, AActor* GoalActor, const FVector& GoalLocation, const float AcceptanceRadius)
{
	const auto MyObj = NewAbilityTask<UAbilityTask_SimpleMoveTo>(OwningAbility, NAME_None);

	if (Controller != nullptr)
	{
		FAIMoveRequest MoveReq;

		if (GoalActor != nullptr)
		{
			MoveReq.SetGoalActor(GoalActor);
		}
		else
		{
			MoveReq.SetGoalLocation(GoalLocation);
		}

		MoveReq.SetAcceptanceRadius(AcceptanceRadius);
		MoveReq.SetUsePathfinding(true);

		MyObj->SetUp(Controller, MoveReq);
	}

	return MyObj;
}

void UAbilityTask_SimpleMoveTo::Activate()
{
	Super::Activate();
	
	PerformMove();
}

void UAbilityTask_SimpleMoveTo::PerformMove()
{
	// This is an entire copy/paste of AI Move To as AI Move To only works with AI controllers, I need something that works for standard controllers.

	auto PFComp = OwnerController ? OwnerController->FindComponentByClass<UPathFollowingComponent>() : nullptr;
	if (PFComp == nullptr)
	{
		PFComp = NewObject<UPathFollowingComponent>(OwnerController);
		PFComp->RegisterComponentWithWorld(OwnerController->GetWorld());
		PFComp->Initialize();
	}

	if (const auto NavSys = OwnerController ? FNavigationSystem::GetCurrent<UNavigationSystemV1>(OwnerController->GetWorld()) : nullptr)
	{
		const bool bAlreadyAtGoal = PFComp->HasReached(MoveRequest.GetGoalLocation(), EPathFollowingReachMode::OverlapAgent);

		// script source, keep only one move request at time
		if (PFComp->GetStatus() != EPathFollowingStatus::Idle)
		{
			PFComp->AbortMove(*NavSys, FPathFollowingResultFlags::ForcedScript | FPathFollowingResultFlags::NewRequest
				, FAIRequestID::AnyRequest, bAlreadyAtGoal ? EPathFollowingVelocityMode::Reset : EPathFollowingVelocityMode::Keep);
		}

		// script source, keep only one move request at time
		if (PFComp->GetStatus() != EPathFollowingStatus::Idle)
		{
			PFComp->AbortMove(*NavSys, FPathFollowingResultFlags::ForcedScript | FPathFollowingResultFlags::NewRequest);
		}

		if (bAlreadyAtGoal)
		{
			PFComp->RequestMoveWithImmediateFinish(EPathFollowingResult::Success);
		}
		else
		{
			const FVector AgentNavLocation = OwnerController->GetNavAgentLocation();
			if (const ANavigationData* NavData = NavSys->GetNavDataForProps(OwnerController->GetNavAgentPropertiesRef(), AgentNavLocation))
			{
				const FPathFindingQuery Query(OwnerController, *NavData, AgentNavLocation, MoveRequest.GetGoalLocation());
				const FPathFindingResult Result = NavSys->FindPathSync(Query);
				if (Result.IsSuccessful())
				{
					Result.Path->SetGoalActorObservation(*MoveRequest.GetGoalActor(), 100.0f);
					MoveRequestID = PFComp->RequestMove(MoveRequest, Result.Path);
					if (MoveRequestID != FAIRequestID::InvalidRequest)
					{
						PFComp->OnRequestFinished.AddUObject(this, &ThisClass::OnRequestFinished);
					}
				}
				else if (PFComp->GetStatus() != EPathFollowingStatus::Idle)
				{
					PFComp->RequestMoveWithImmediateFinish(EPathFollowingResult::Invalid);
				}
			}
		}
	}
}

void UAbilityTask_SimpleMoveTo::OnRequestFinished(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	if (RequestID == MoveRequestID)
	{
		// reset request Id, FinishMoveTask doesn't need to update path following's state
		MoveRequestID = FAIRequestID::InvalidRequest;

		if (bUseContinuousTracking && MoveRequest.IsMoveToActorRequest() && Result.IsSuccess())
		{
			GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ThisClass::PerformMove);
		}
		else
		{
			FinishMoveTask(Result.Code);
		}
	}
}

void UAbilityTask_SimpleMoveTo::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);

	if (MoveRequestID.IsValid())
	{
		if (const auto PFComp = OwnerController ? OwnerController->FindComponentByClass<UPathFollowingComponent>() : nullptr)
		{
			if (PFComp->GetStatus() != EPathFollowingStatus::Idle)
			{
				PFComp->AbortMove(*this, FPathFollowingResultFlags::OwnerFinished, MoveRequestID);
			}
		}
	}
}

void UAbilityTask_SimpleMoveTo::SetUp(AController* InController, const FAIMoveRequest& InMoveRequest)
{
	OwnerController = InController;
	MoveRequest = InMoveRequest;
}

void UAbilityTask_SimpleMoveTo::FinishMoveTask(EPathFollowingResult::Type InResult)
{
	if (MoveRequestID.IsValid())
	{
		if (const auto PFComp = OwnerController ? OwnerController->FindComponentByClass<UPathFollowingComponent>() : nullptr)
		{
			if (PFComp->GetStatus() != EPathFollowingStatus::Idle)
			{
				PFComp->AbortMove(*this, FPathFollowingResultFlags::OwnerFinished, MoveRequestID);
			}
		}
	}

	MoveResult = InResult;
	EndTask();

	if (InResult == EPathFollowingResult::Invalid)
	{
		OnRequestFailed.Broadcast();
	}
	else
	{
		OnMoveFinished.Broadcast(InResult, OwnerController);
	}
}