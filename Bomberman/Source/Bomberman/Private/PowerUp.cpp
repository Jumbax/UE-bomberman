// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUp.h"
#include "BombermanPlayer.h"
#include "Components/BoxComponent.h"

APowerUp::APowerUp()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>("SceneRoot");
	RootComponent = SceneRoot;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(RootComponent);
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	BoxCollision->SetupAttachment(RootComponent);
	BoxCollision->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel3);
	BoxCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BoxCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	bReplicates = true;
}

void APowerUp::BeginPlay()
{
	Super::BeginPlay();
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &APowerUp::OnOverlapBegin);
}

void APowerUp::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABombermanPlayer* Player = Cast<ABombermanPlayer>(OtherActor);
	if (Player)
	{
		switch (Type)
		{
		case Option1:
			Player->ActiveSuperSpeedPowerUp(SuperSpeedDuration);
			break;
		case Option2:
			Player->ActiveInvinciblePowerUp(InvincibleDuration);
			break;
		case Option3:
			Player->ActiveMoreBombsPowerUp();
			break;
		case Option4:
			Player->Death();
			break;
		}

		Destroy();
	}
}
