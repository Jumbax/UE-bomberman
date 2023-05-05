// Fill out your copyright notice in the Description page of Project Settings.


#include "Wall.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PowerUp.h"

AWall::AWall()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxCollision->SetupAttachment(RootComponent);
	BoxCollision->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel2);
	BoxCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BoxCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);

	bReplicates = true;
}

void AWall::BeginPlay()
{
	Super::BeginPlay();
}

void AWall::GetDamagedByBomb_Implementation()
{
	if (!bIsIndestructible)
	{

		if (GetLocalRole() == ROLE_SimulatedProxy)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystem, GetTransform(), true, EPSCPoolMethod::None, true);
		}

		if (GetLocalRole() == ROLE_Authority)
		{
			const int CoinFlip = FMath::RandRange(0, 1);
			
			if (CoinFlip == 0)
			{
				Destroy();
				return;
			}

			const int RandomNum = FMath::RandRange(0, static_cast<int>(EPowerUpType::Option5) - 1);
			const FVector SpawnPoint = FVector(GetActorLocation().X + 100.f, GetActorLocation().Y + 100.f, GetActorLocation().Z);
			
			switch (RandomNum)
			{
			case 0:
				GetWorld()->SpawnActor<APowerUp>(SuperSpeedPowerUp, SpawnPoint, FRotator(0.f, 0.f, 0.f));
				break;
			case 1:
				GetWorld()->SpawnActor<APowerUp>(InvinciblePowerUp, SpawnPoint, FRotator(0.f, 0.f, 0.f));
				break;
			case 2:
				GetWorld()->SpawnActor<APowerUp>(MoreBombsPowerUp, SpawnPoint, FRotator(0.f, 0.f, 0.f));
				break;
			case 3:
				GetWorld()->SpawnActor<APowerUp>(Death, SpawnPoint, FRotator(0.f, 0.f, 0.f));
				break;
			}
		}

		Destroy();
	}
}

