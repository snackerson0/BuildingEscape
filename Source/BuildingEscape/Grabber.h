// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
GENERATED_BODY()
	//public attributes 
public:
	UPROPERTY(EditAnywhere)
	float distance = 100.f;
	//private attributes
private:
	FHitResult hit;
	UPhysicsHandleComponent *PhysicsHandle=nullptr;
	FVector LineTraceEnd;
public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	

	///Private functions
private:
	UInputComponent *PlayersInput = nullptr;
	void BindPlayerInput();
	void Grab();
	void GrabRelease();
	void FindInputComponent();
	void FindPhysicsHandle();
	FHitResult LineTrace();
	void HoldingGrabbableObject();
};

