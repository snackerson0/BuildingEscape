// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "engine/World.h"
#include <Components/ActorComponent.h>
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/PrimitiveComponent.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	
	FindInputComponent();
	FindPhysicsHandle();
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	HoldingGrabbableObject();

	
}

void UGrabber::HoldingGrabbableObject()
{
	if(!PhysicsHandle) {return;}
	if (PhysicsHandle->GrabbedComponent)
	{
		FVector PlayerLocation;
		FRotator PlayerRotation;
		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerLocation, PlayerRotation);
		FVector LineTraceEnd = PlayerLocation + PlayerRotation.Vector() * distance;
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}
}

void UGrabber::BindPlayerInput()
{
	PlayersInput->BindAction("Grab",IE_Pressed,this, &UGrabber::Grab);
	PlayersInput->BindAction("Grab",IE_Released,this, &UGrabber::GrabRelease);
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp,Warning,TEXT("grab was pressed"))
	if(!PhysicsHandle){return;}
		auto HitResult = LineTrace();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();
	auto ActorRotation = ComponentToGrab->RelativeRotation;
	if(ActorHit)
	PhysicsHandle->GrabComponentAtLocationWithRotation(ComponentToGrab,NAME_None,ActorHit->GetActorLocation(),ActorRotation);
}

void UGrabber::GrabRelease()
{
	UE_LOG(LogTemp,Warning,TEXT("grab was Released"))
	if(!PhysicsHandle){return;}
		PhysicsHandle->ReleaseComponent();
}
void UGrabber::FindInputComponent()
{
	PlayersInput = GetOwner()->FindComponentByClass<UInputComponent>();
	if(PlayersInput){
		UE_LOG(LogTemp, Warning, TEXT("Input Component Found"))
		BindPlayerInput();
	}
	else 
		UE_LOG(LogTemp, Error, TEXT("Input Component not Found"))
		
}

void UGrabber::FindPhysicsHandle()
{
PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
if(PhysicsHandle)
UE_LOG(LogTemp, Warning, TEXT("Physics handle found on %s"),*GetOwner()->GetName())
else
UE_LOG(LogTemp, Error, TEXT("Physics handle not found on %s"),*GetOwner()->GetName())
}

FHitResult UGrabber::LineTrace()
{
	FVector PlayerLocation;
	FRotator PlayerRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerLocation,PlayerRotation);
	FVector LineTraceEnd = PlayerLocation + PlayerRotation.Vector() * distance;
	 FCollisionQueryParams CollisionParams (FName(TEXT("")),false,GetOwner());
	if (GetWorld()->LineTraceSingleByObjectType(hit,PlayerLocation,LineTraceEnd,FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),CollisionParams))
	UE_LOG(LogTemp,Warning, TEXT("hit object %s"), *(hit.GetActor()->GetName()))
	return hit;
	
}