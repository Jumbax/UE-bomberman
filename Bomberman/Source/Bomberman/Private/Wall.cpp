// Fill out your copyright notice in the Description page of Project Settings.


#include "Wall.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PowerUp.h"

// Sets default values
AWall::AWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxCollision->SetupAttachment(RootComponent);
	BoxCollision->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel2);
	BoxCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BoxCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);
}

// Called when the game starts or when spawned
void AWall::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWall::GetDamagedByBomb_Implementation()
{
	if (!IsIndestructible)
	{

		if (GetLocalRole() == ROLE_SimulatedProxy)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystem, GetTransform(), true, EPSCPoolMethod::None, true);
		}

		if (GetLocalRole() == ROLE_Authority)
		{
			int CoinFlip = FMath::RandRange(0, 1);
			if (CoinFlip == 0)
			{
				Destroy();
				return;
			}

			int RandomNum = FMath::RandRange(0, static_cast<int>(EPowerUpType::Option5) - 1);
			FActorSpawnParameters SpawnParameters;
			FVector SpawnPoint = FVector(GetActorLocation().X + 100.f, GetActorLocation().Y + 100.f, GetActorLocation().Z);
			switch (RandomNum)
			{
			case 0:
				GetWorld()->SpawnActor<APowerUp>(SuperSpeedPowerUp, SpawnPoint, FRotator(0.f, 0.f, 0.f), SpawnParameters);
				break;
			case 1:
				GetWorld()->SpawnActor<APowerUp>(InvinciblePowerUp, SpawnPoint, FRotator(0.f, 0.f, 0.f), SpawnParameters);
				break;
			case 2:
				GetWorld()->SpawnActor<APowerUp>(MoreBombsPowerUp, SpawnPoint, FRotator(0.f, 0.f, 0.f), SpawnParameters);
				break;
			case 3:
				GetWorld()->SpawnActor<APowerUp>(Death, SpawnPoint, FRotator(0.f, 0.f, 0.f), SpawnParameters);
				break;
			}
		}

		Destroy();
	}
}

