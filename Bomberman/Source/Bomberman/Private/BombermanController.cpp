// Fill out your copyright notice in the Description page of Project Settings.


#include "BombermanController.h"
#include "Blueprint/UserWidget.h"
#include "BombermanGameInstance.h"
#include "Menu.h"
#include "Scoreboard.h"

void ABombermanController::BeginPlay()
{
	if (GetLocalRole() == ROLE_AutonomousProxy)
	{
		MenuHUD = CreateWidget<UMenu>(this, MenuHUDClass);
		if (MenuHUD)
		{
			MenuHUD->AddToPlayerScreen();
		}
		ScoreboardHUD = CreateWidget<UScoreboard>(this, ScoreboardHUDClass);
	}
}

void ABombermanController::SetTimer(const int32 Minutes, const int32 Seconds)
{
	if (MenuHUD)
	{
		MenuHUD->SetTimerText(Minutes, Seconds);
	}
}

void ABombermanController::SpawnScoreboard_Implementation()
{
	if (GetLocalRole() == ROLE_AutonomousProxy)
	{
		if (ScoreboardHUD)
		{
			ScoreboardHUD->AddToPlayerScreen();
		}
	}
}

void ABombermanController::SetVictoriesCountScoreboard_Implementation(int32 Player1VictoriesCount, int32 Player2VictoriesCount)
{
	if (GetLocalRole() == ROLE_AutonomousProxy)
	{
		if (ScoreboardHUD)
		{
			ScoreboardHUD->SetVictoriesCountText(Player1VictoriesCount, Player2VictoriesCount);
		}

	}
}

void ABombermanController::SetVictoriesCountMenu_Implementation(int32 Player1VictoriesCount, int32 Player2VictoriesCount)
{
	if (GetLocalRole() == ROLE_AutonomousProxy)
	{
		if (MenuHUD)
		{
			MenuHUD->SetVictoriesCountText(Player1VictoriesCount, Player2VictoriesCount);
		}
	}
}

void ABombermanController::SetWinningPlayer_Implementation(const int32 PlayerID)
{
	if (GetLocalRole() == ROLE_AutonomousProxy)
	{
		if (MenuHUD)
		{
			ScoreboardHUD->SetWinningPlayerText(PlayerID);
		}
	}
}