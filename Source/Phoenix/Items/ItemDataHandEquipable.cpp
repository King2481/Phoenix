// Created by Bruce Crum.


#include "Phoenix/Items/ItemDataHandEquipable.h"
#include "Phoenix/Items/Prop.h"
#include "Phoenix/Characters/Equipable.h"

UItemDataHandEquipable::UItemDataHandEquipable()
{
	AssociatedProp = nullptr;
	SpawnedProp = nullptr;
	EquippedSocketName = NAME_None;
	UnequippedSocketName = NAME_None;
}

void UItemDataHandEquipable::OnEquip(AActor* EquippingActor)
{
	if (SpawnedProp)
	{
		OnUnequip(EquippingActor);
	}

	FActorSpawnParameters Params;
	Params.Owner = EquippingActor;
	Params.Instigator = Cast<APawn>(EquippingActor);

	if (AssociatedProp != nullptr)
	{
		if (UWorld* World = EquippingActor->GetWorld())
		{
			if (SpawnedProp = World->SpawnActor<AProp>(AssociatedProp.LoadSynchronous(), FTransform::Identity, Params))
			{
				if (const auto EquipableInterface = Cast<IEquipable>(EquippingActor))
				{
					// TODO: Handle what default state the weapon should attach to.
					SpawnedProp->AttachToComponent(IEquipable::Execute_GetEquipableAttachMesh(EquippingActor), FAttachmentTransformRules::SnapToTargetIncludingScale, UnequippedSocketName);
				}
			}
		}
	}
}

void UItemDataHandEquipable::OnUnequip(AActor* UnequippingActor)
{
	if (SpawnedProp)
	{
		SpawnedProp->Destroy();
		SpawnedProp = nullptr;
	}
}