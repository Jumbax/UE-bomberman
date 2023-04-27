// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BombermanController.generated.h"

UCLASS()
class BOMBERMAN_API ABombermanController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Menu")
	class UMenu* MenuHUD;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu")
	TSubclassOf<class UMenu> MenuHUDClass;
};
