// Fill out your copyright notice in the Description page of Project Settings.

#include "Bomb.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Wall.h"

ABomb::ABomb()
{
	PrimaryActorTick.bCanEverTick = true;
	SceneRoot = CreateDefaultSubobject<USceneComponent>("SceneRoot");
	RootComponent = SceneRoot;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMesh->SetupAttachment(RootComponent);
	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereCollision->SetupAttachment(RootComponent);
	SphereCollision->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	SphereCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	SphereCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);

	bReplicates = true;
}

void ABomb::BeginPlay()
{
	Super::BeginPlay();
	StartTimer();
}

void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABomb::StartTimer()
{
	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &ABomb::Explode, ExplodingTime, false);
}

void ABomb::Explode_Implementation()
{	
	if (GetLocalRole() == ROLE_SimulatedProxy)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystem, GetTransform(), true, EPSCPoolMethod::None, true);
	}	

	if (GetLocalRole() == ROLE_Authority)
	{
		Exploding = true;

		TArray<AActor*> ActorsToCollidingWith;
		TArray< TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		//ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1));
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel2));
		TArray<AActor*> ActorToIgnore;
		ActorToIgnore.Add(Cast<AActor>(this));
		UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetActorLocation(), ExplodingRadius, ObjectTypes, nullptr, ActorToIgnore, ActorsToCollidingWith);
	
		for (AActor* Actor : ActorsToCollidingWith)
		{
			if (ABomb* OtherBomb = Cast<ABomb>(Actor))
			{
				if (!OtherBomb->Exploding)
				{
					OtherBomb->Explode();
				}
			}
			else if (AWall* Wall = Cast<AWall>(Actor))
			{
				Wall->GetDamagedByBomb();
			}
		}
	}

	GetWorldTimerManager().ClearTimer(MemberTimerHandle);
	Destroy();
}