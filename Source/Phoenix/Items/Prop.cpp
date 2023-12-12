// Created by Bruce Crum.


#include "Phoenix/Items/Prop.h"

// Sets default values
AProp::AProp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SetActorTickEnabled(false);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;
	Mesh->CastShadow = true;
	Mesh->bOnlyOwnerSee = false;
	Mesh->bOwnerNoSee = false;

	SetRootComponent(Mesh);

	EquipableState = EEquipableState::Unequipped;
}

void AProp::SetEquipableState(EEquipableState NewState)
{
	EquipableState = NewState;
}

