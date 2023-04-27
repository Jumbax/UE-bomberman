// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu.h"
#include "Components/EditableText.h"

void UMenu::SetTimer(int32 InMinutes, int32 InSeconds)
{
	Minutes->SetText(FText::AsNumber(InMinutes));
	Seconds->SetText(FText::AsNumber(InSeconds));
}

void UMenu::SetLifesCount(int32 PlayerID, int32 InLifes)
{
	if (PlayerID == 0)
	{
		Player1Lifes->SetText(FText::AsNumber(InLifes));
	}
	else
	{
		Player2Lifes->SetText(FText::AsNumber(InLifes));
	}
}