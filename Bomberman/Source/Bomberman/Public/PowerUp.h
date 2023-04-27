// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerUp.generated.h"

UENUM(BlueprintType)
enum EPowerUpType
{
	Option1 UMETA(DisplayName = "SuperSpeed"),
	Option2 UMETA(DisplayName = "Invinsible"),
	Option3 UMETA(DisplayName = "MoreBombs"),
	Option4 UMETA(DisplayName = "Death"),
	Option5 UMETA(DisplayName = "None")
};

UCLASS()
class BOMBERMAN_API APowerUp : public AActor
{
	GENERATED_BODY()
	
public:
	APowerUp();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Component")
	USceneComponent* SceneRoot = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* StaticMesh = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Component")
	class UBoxComponent* BoxCollision = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	TEnumAsByte<EPowerUpType> Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float Duration = 0.f;

	UFUNCTION(Category = "Collision")
		virtual void OnOverlapBegin(
			UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION(Category = "Collision")
		virtual void OnOverlapEnd(
			UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);
};
