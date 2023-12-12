// Created by Bruce Crum.


#include "Phoenix/World/Placeable/PlaceableBase.h"

// Sets default values
APlaceableBase::APlaceableBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SetActorTickEnabled(false);
}