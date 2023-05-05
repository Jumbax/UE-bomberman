// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GM_GameMode.generated.h"

UCLASS()
class BOMBERMAN_API AGM_GameMode : public AGameMode
{
	GENERATED_BODY()

protected:
	AGM_GameMode();
	virtual void BeginPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Players")
	TArray<class ABombermanController*> BombermanControllers;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Players")
	TArray<class ABombermanPlayerState*> BombermanPlayersState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Players")
	TArray<FVector> SpawnLocations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Players")
	int32 PlayersInGame = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Players")
	TSubclassOf<APawn> BombermanPlayerClass = nullptr;

	class UBombermanGameInstance* BombermanGameInstance = nullptr;

public:
	virtual void SetGameWinner();
};
