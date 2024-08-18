// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Fish.h"

#include "Components/SphereComponent.h"
#include "Data/FishDataAsset.h"


// Sets default values
AFish::AFish()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = SphereComponent;

	SKM_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SKM_Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AFish::BeginPlay()
{
	Super::BeginPlay();

	if (!FishDataAsset) return;
	const int32 RandomID = FMath::RandRange(0, 2);
	SKM_Mesh->SetSkeletalMesh(FishDataAsset->AssetItems[RandomID].SKM_Fish);
	SKM_Mesh->PlayAnimation(FishDataAsset->AssetItems[RandomID].AnimFish, true);
}
