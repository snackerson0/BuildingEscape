// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!PressurePlate) {return;}
	if(TotalMassOnPressurePlate()>TriggerMass)
		OnOpenRequest.Broadcast();
	else
	{
		OnCloseRequest.Broadcast();
	}
	
}





float UOpenDoor::TotalMassOnPressurePlate()
{
	if (!PressurePlate){return 0.f;}
	float TotalMass=0;
	TArray <AActor *> OverlappingActors;
	PressurePlate->GetOverlappingActors( OverlappingActors);
	for (auto Actorptr : OverlappingActors)
	{
		TotalMass += Actorptr->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return TotalMass;
}

