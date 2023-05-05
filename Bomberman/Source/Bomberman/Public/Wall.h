// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Wall.generated.h"

class UBoxComponent;

UCLASS()
class BOMBERMAN_API AWall : public AActor
{
	GENERATED_BODY()
	
public:	
	AWall();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Component")
	USceneComponent* SceneRoot = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* StaticMesh = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Component")
	UBoxComponent* BoxCollision = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool bIsIndestructible = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UParticleSystem* ParticleSystem = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	TSubclassOf<class APowerUp> SuperSpeedPowerUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	TSubclassOf<class APowerUp> InvinciblePowerUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	TSubclassOf<class APowerUp> MoreBombsPowerUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	TSubclassOf<class APowerUp> Death;

public:
	UFUNCTION(NetMulticast, Reliable)
	virtual void GetDamagedByBomb();

};
