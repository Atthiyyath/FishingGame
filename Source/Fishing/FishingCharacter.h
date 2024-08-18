// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Public/Interface/InteractInterface.h"
#include "FishingCharacter.generated.h"

class AThrowable;
class AFishingHUD;
class AFishingPlayerController;

UCLASS(Blueprintable)
class AFishingCharacter : public ACharacter, public IInteractInterface
{
	GENERATED_BODY()

public:
	AFishingCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	virtual void Interact_Implementation(UStaticMeshComponent* StaticMesh) override;

	UFUNCTION()
	void ThrowBobber();
	
	UFUNCTION()
	void OnThrowableItemReleased();
	/*void OnAnimationEnded(UAnimMontage* Montage, bool bInterrupted);*/

	FOnMontageEnded EndDelegate;
	
protected:
	virtual void BeginPlay() override;
	
	TObjectPtr<AFishingPlayerController> PlayerController;
	TObjectPtr<AFishingHUD> FishingHUD;
	
private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	// Equipable Item
	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> EquipItem;

	// Throwable Item
	UPROPERTY(EditDefaultsOnly, Category = "Throw Item")
	TSubclassOf<AThrowable> ThrowableItemClass;

	UPROPERTY()
	TObjectPtr<AThrowable> ThrowableItem;

	UPROPERTY(EditDefaultsOnly, Category = "Throw Item")
	TObjectPtr<UAnimMontage> ThrowMontage;

	bool IsInFishingArea = false;
	bool IsItemEquipped = false;
	bool IsFishingAnimationActive = false;
	float HoldTime = 0.f;
	bool IsPlayerCaughtFish = false;
	bool StartFishingTime = false;
	
public:
	float FishingTime = 0.f;
	
	FORCEINLINE TObjectPtr<AFishingHUD> GetHUD() const {return FishingHUD;}
	FORCEINLINE bool GetIsInFishingArea() const {return IsInFishingArea;}
	FORCEINLINE void SetIsInFishingArea(bool IsInArea) {IsInFishingArea = IsInArea;}
	FORCEINLINE bool GetIsEquipFishingRod() const {return IsItemEquipped;}
	FORCEINLINE bool GetIsFishingAnimationActive() const {return IsFishingAnimationActive;}
	FORCEINLINE void SetIsFishingAnimationActive(bool IsInFishing) {IsFishingAnimationActive = IsInFishing;}
	FORCEINLINE float GetHoldTime() const {return HoldTime;}
	FORCEINLINE void SetHoldTime(float value) {HoldTime = value;}
	FORCEINLINE bool GetPlayerCaughtFish() const {return IsPlayerCaughtFish;}
	FORCEINLINE void SetPlayerCaughtFish(bool IsCaught) {IsPlayerCaughtFish = IsCaught;}
	FORCEINLINE bool GetStartFishingTime() const {return StartFishingTime;}
	FORCEINLINE void SetStartFishingTime(bool IsTimeActive) {StartFishingTime = IsTimeActive;}
	FORCEINLINE AThrowable* GetBobber() const {return ThrowableItem;}
};

