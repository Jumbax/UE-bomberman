// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BombermanPlayerState.generated.h"


UCLASS()
class BOMBERMAN_API ABombermanPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	virtual void StartTimer();
	virtual void StopTimer();

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
	int32 Minutes = 2;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
	int32 Seconds = 0;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
	TArray<int32> VictoriesCount = { 0, 0 };

protected:
	virtual void BeginPlay() override;

	UFUNCTION(NetMulticast, Reliable)
	virtual void SetTimer();

	FTimerHandle MemberTimerHandle;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
