// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Menu.generated.h"

UCLASS()
class BOMBERMAN_API UMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	void SetPlayerPanelsVisibility(const int32 PlayersInGame);
	void SetTimerText(const int32 InMinutes, const int32 InSeconds);
	void SetVictoriesCountText(const int32 InPlayer1VictoriesCount, const int32 InPlayer2VictoriesCount);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UEditableText* Minutes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UEditableText* Seconds;
	
	TArray<class UCanvasPanel*> PlayerPanels;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UCanvasPanel* Player1Panel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UCanvasPanel* Player2Panel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UEditableText* Player1VictoriesCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UEditableText* Player2VictoriesCount;
};
