// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bomb.generated.h"


UCLASS()
class BOMBERMAN_API ABomb : public AActor
{
	GENERATED_BODY()
	
public:
	ABomb();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void StartTimer();

	UFUNCTION(NetMulticast, Reliable)
	virtual void Explode();

	FTimerHandle MemberTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float ExplodingTime = 3.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float ExplodingRadius = 300.f;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Component")
	USceneComponent* SceneRoot = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* StaticMesh = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Component")
	class USphereComponent* SphereCollision = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UParticleSystem* ParticleSystem = nullptr;

	bool Exploding = false;
};
