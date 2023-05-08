// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BombermanController.generated.h"

UCLASS()
class BOMBERMAN_API ABombermanController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Menu")
	class UMenu* MenuHUD = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Menu")
	class UScoreboard* ScoreboardHUD = nullptr;

	virtual void SetTimer(const int32 Minutes, const int32 Seconds);

	UFUNCTION(Client, Reliable)
	virtual void SpawnScoreboard();
	
	UFUNCTION(Client, Reliable)
	virtual void SetVictoriesCountScoreboard(const int32 Player1VictoriesCount, const int32 Player2VictoriesCount);
	
	UFUNCTION(Client, Reliable)
	virtual void SetVictoriesCountMenu(const int32 Player1VictoriesCount, const int32 Player2VictoriesCount);
	
	UFUNCTION(Client, Reliable)
	virtual void SetWinningPlayer(const int32 PlayerID);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu")
	TSubclassOf<class UMenu> MenuHUDClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu")
	TSubclassOf<class UScoreboard> ScoreboardHUDClass = nullptr;
};
