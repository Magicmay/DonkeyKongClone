// Fill out your copyright notice in the Description page of Project Settings.

#include "../DonkeyKong.h"
#include "DKLadder.h"

#include "../Enemies/DKEnemy.h"
#include "../Enemies/DKBarrel.h"
#include "../Enemies/DKSimpleEnemy.h"

#include "DonkeyKongCharacter.h"


// Sets default values
ADKLadder::ADKLadder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	LadderVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("LadderVolume"));
	LadderVolume->AttachTo(RootComponent);

	LadderEnd = CreateDefaultSubobject<UBoxComponent>(TEXT("LadderEnd"));
	LadderEnd->AttachTo(RootComponent);

	LadderBegin = CreateDefaultSubobject<UBoxComponent>(TEXT("LadderBegin"));
	LadderBegin->AttachTo(RootComponent);

	EnemyClimbUpVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("EnemyMoveVolume"));
	EnemyClimbUpVolume->AttachTo(RootComponent);

	EnemyClimbDownVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("EnemyClimbDownVolume"));
	EnemyClimbDownVolume->AttachTo(RootComponent);

	LadderEnd->OnComponentBeginOverlap.AddDynamic(this, &ADKLadder::LadderEnd_OnBeginOverlap);
	LadderBegin->OnComponentBeginOverlap.AddDynamic(this, &ADKLadder::LadderBegin_OnBeginOverlap);

	EnemyClimbUpVolume->OnComponentBeginOverlap.AddDynamic(this, &ADKLadder::EnemyClimbUpVolume_OnBeginOverlap);
	EnemyClimbDownVolume->OnComponentBeginOverlap.AddDynamic(this, &ADKLadder::EnemyClimbDownVolume_OnBeginOverlap);
}

// Called when the game starts or when spawned
void ADKLadder::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADKLadder::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ADKLadder::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	LadderBegin->SetRelativeLocation(BeginLocation);
	LadderEnd->SetRelativeLocation(EndLocation);
	EnemyClimbUpVolume->SetRelativeLocation(EnemyClimbUpVolumeLocation);
	EnemyClimbDownVolume->SetRelativeLocation(EnemyClimbDownVolumeLocation);
}

void ADKLadder::LadderEnd_OnBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ADonkeyKongCharacter* MyChar = Cast<ADonkeyKongCharacter>(OtherActor))
	{
		if (MyChar->GetClimbingDirection() > 0)
		{
			FVector DropLocation = GetActorLocation() + EndLocation;
			MyChar->ClimbFinish(DropLocation, this);
		}
	}

	if (ADKEnemy* Enemy = Cast<ADKEnemy>(OtherActor))
	{
		Enemy->ClimbStop(this);
	}
}

void ADKLadder::LadderBegin_OnBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ADonkeyKongCharacter* MyChar = Cast<ADonkeyKongCharacter>(OtherActor))
	{
		if (MyChar->GetClimbingDirection() < 0)
		{
			FVector DropLocation = GetActorLocation() + BeginLocation;
			MyChar->ClimbFinish(DropLocation, this);
		}
	}

	if (ADKEnemy* Enemy = Cast<ADKEnemy>(OtherActor))
	{
		Enemy->ClimbStop(this);
	}
}

void ADKLadder::EnemyClimbUpVolume_OnBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ADKEnemy* Enemy = Cast<ADKEnemy>(OtherActor))
	{
		float chance = FMath::FRandRange(0, 1);
		float test = Enemy->GetChanceToClimb();
		if (chance > test)
			return;

		Enemy->ClimbUp(this);
	}
}

void ADKLadder::EnemyClimbDownVolume_OnBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ADKEnemy* Enemy = Cast<ADKEnemy>(OtherActor))
	{
		float chance = FMath::FRandRange(0, 1);
		float test = Enemy->GetChanceToClimb();
		if (chance > test)
			return;

		Enemy->ClimbDown(this);
	}
}