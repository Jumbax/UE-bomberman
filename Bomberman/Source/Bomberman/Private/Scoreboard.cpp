// Fill out your copyright notice in the Description page of Project Settings.


#include "Scoreboard.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UScoreboard::NativeConstruct()
{
	Player1TrophyImages.Add(Player1Trophy1);
	Player1TrophyImages.Add(Player1Trophy2);
	Player1TrophyImages.Add(Player1Trophy3);
	Player1TrophyImages.Add(Player1Trophy4);
	Player1TrophyImages.Add(Player1Trophy5);

	Player2TrophyImages.Add(Player2Trophy1);
	Player2TrophyImages.Add(Player2Trophy2);
	Player2TrophyImages.Add(Player2Trophy3);
	Player2TrophyImages.Add(Player2Trophy4);
	Player2TrophyImages.Add(Player2Trophy5);
}								  

void UScoreboard::SetVictoriesCountText(const int32 InPlayer1VictoriesCount, const int32 InPlayer2VictoriesCount)
{
	if (InPlayer1VictoriesCount > 0)
	{
		for (size_t i = 0; i < InPlayer1VictoriesCount; i++)
		{
			Player1TrophyImages[i]->SetVisibility(ESlateVisibility::Visible);
		}
	}

	if (InPlayer2VictoriesCount > 0)
	{
		for (size_t i = 0; i < InPlayer2VictoriesCount; i++)
		{
			Player2TrophyImages[i]->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void UScoreboard::SetWinningPlayerText(const int32 PlayerID)
{
	FString PlayerWinnerName;
	if (PlayerID == 0)
	{
		PlayerWinnerName = TEXT("Player 1 Win");
	}
	else if (PlayerID == 1)
	{
		PlayerWinnerName = TEXT("Player 2 Win");
	}
	PlayerWinner_Txt->SetText(FText::FromString(PlayerWinnerName));
	PlayerWinner_Txt->SetVisibility(ESlateVisibility::Visible);
}