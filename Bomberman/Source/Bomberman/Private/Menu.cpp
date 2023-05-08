// Fill out your copyright notice in the Description page of Project Settings.

#include "Menu.h"
#include "Components/EditableText.h"
#include "Components/CanvasPanel.h"

void UMenu::NativeConstruct()
{
	PlayerPanels.Add(Player1Panel);
	PlayerPanels.Add(Player2Panel);
}

void UMenu::SetPlayerPanelsVisibility(const int32 PlayersInGame)
{
	for (size_t i = 0; i < PlayersInGame; i++)
	{
		PlayerPanels[i]->SetVisibility(ESlateVisibility::Visible);
	}
}


void UMenu::SetTimerText(const int32 InMinutes, const int32 InSeconds)
{
	if (InSeconds <= 9)
	{
		FString SecondsStr = TEXT("0");
		SecondsStr.AppendInt(InSeconds);
		Seconds->SetText(FText::FromString(SecondsStr));
		return;
	}

	Minutes->SetText(FText::AsNumber(InMinutes));
	Seconds->SetText(FText::AsNumber(InSeconds));
}

void UMenu::SetVictoriesCountText(const int32 InPlayer1VictoriesCount, const int32 InPlayer2VictoriesCount)
{
	Player1VictoriesCount->SetText(FText::AsNumber(InPlayer1VictoriesCount));
	Player2VictoriesCount->SetText(FText::AsNumber(InPlayer2VictoriesCount));
}