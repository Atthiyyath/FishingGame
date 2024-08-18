// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuoyancyComponent.h"
#include "Throwable.generated.h"

class AWater;
class UProjectileMovementComponent;
class USphereComponent;
class AFishingCharacter;

UCLASS()
class FISHING_API AThrowable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AThrowable();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USphereComponent> SphereComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBuoyancyComponent> BuoyancyComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	void OnReleased(FVector ForwardVector, AFishingCharacter* Character);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	virtual void BeginOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

private:
	TObjectPtr<AFishingCharacter> CharacterOwner;
	TObjectPtr<AWater> Water;
	
	UPROPERTY(EditDefaultsOnly)
	float SpeedValue = 1000.f;

	UPROPERTY(EditDefaultsOnly)
	float InitTimeFishBites = 3.f;

	bool IsBobberFloating = false;
};
