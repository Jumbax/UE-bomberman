// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUp.h"
#include "BombermanPlayer.h"
#include "Components/BoxComponent.h"

// Sets default values
APowerUp::APowerUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

// Called when the game starts or when spawned
void APowerUp::BeginPlay()
{
	Super::BeginPlay();
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &APowerUp::OnOverlapBegin);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &APowerUp::OnOverlapEnd);
}

// Called every frame
void APowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
			Player->ActiveSuperSpeedPowerUp(Duration);
			break;
		case Option2:
			Player->ActiveInvinciblePowerUp(Duration);
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

void APowerUp::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	
}
