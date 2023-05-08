// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_GameMode.h"
#include "BombermanController.h"
#include "BombermanGameInstance.h"
#include "BombermanPlayer.h"
#include "BombermanPlayerState.h"

AGM_GameMode::AGM_GameMode()
{
	SpawnLocations.Add(FVector(1900.f, 500.f, 96.f));
	SpawnLocations.Add(FVector(300.f, 3300.f, 96.f));
}

void AGM_GameMode::BeginPlay()
{
	BombermanGameInstance = Cast<UBombermanGameInstance>(GetGameInstance());
}

void AGM_GameMode::PostLogin(APlayerController* NewPlayer)
{
	APawn* Player = Cast<APawn>(GetWorld()->SpawnActor<ABombermanPlayer>(BombermanPlayerClass, SpawnLocations[0], FRotator(0, 0, 0)));
	NewPlayer->Possess(Player);

	SpawnLocations.RemoveAt(0);
	BombermanControllers.Add(Cast<ABombermanController>(NewPlayer));
	BombermanPlayersState.Add(Cast<ABombermanPlayerState>(Player->GetPlayerState()));

	if (BombermanControllers.Num() == PlayersInGame)
	{
		for (size_t i = 0; i < BombermanPlayersState.Num(); i++)
		{
			for (size_t j = 0; j < BombermanGameInstance->VictoriesCount.Num(); j++)
			{
				BombermanPlayersState[i]->VictoriesCount[j] = BombermanGameInstance->VictoriesCount[j];
			}
		}

		for (ABombermanPlayerState* BombermanPlayerState : BombermanPlayersState)
		{
			BombermanPlayerState->StartTimer();
		}
	}

}

void AGM_GameMode::SetGameWinner()
{
	for (size_t i = 0; i < BombermanControllers.Num(); i++)
	{
		ABombermanPlayer* Player = Cast<ABombermanPlayer>(BombermanControllers[i]->GetPawn());
		if (Player)
		{
			if (!Player->IsDead())
			{
				BombermanGameInstance->VictoriesCount[i]++;
			}

			BombermanPlayersState[i]->StopTimer();
		}
	}

	for (ABombermanController* BombermanController : BombermanControllers)
	{
		BombermanController->SpawnScoreboard();
		BombermanController->SetVictoriesCountMenu(BombermanGameInstance->VictoriesCount[0], BombermanGameInstance->VictoriesCount[1]);
		BombermanController->SetVictoriesCountScoreboard(BombermanGameInstance->VictoriesCount[0], BombermanGameInstance->VictoriesCount[1]);
	}

	bool ResetGame = false;

	for (ABombermanPlayerState* BombermanPlayerState : BombermanPlayersState)
	{
		if (BombermanGameInstance->VictoriesCount[0] >= 5)
		{
			Cast<ABombermanController>(BombermanPlayerState->GetOwningController())->SetWinningPlayer(0);
			ResetGame = true;
		}
		else if (BombermanGameInstance->VictoriesCount[1] >= 5)
		{
			Cast<ABombermanController>(BombermanPlayerState->GetOwningController())->SetWinningPlayer(1);
			ResetGame = true;
		}	
	}

	if (ResetGame)
	{
		for (size_t i = 0; i < BombermanControllers.Num(); i++)
		{
			BombermanGameInstance->VictoriesCount[i] = 0;
		}
	}

	RestartGame();
}