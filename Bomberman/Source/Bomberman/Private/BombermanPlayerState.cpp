// Fill out your copyright notice in the Description page of Project Settings.


#include "BombermanPlayerState.h"
#include "BombermanController.h"
#include "Net/UnrealNetwork.h"

void ABombermanPlayerState::BeginPlay()
{
	if (GetLocalRole() == ROLE_SimulatedProxy)
	{
		ABombermanController* Controller = Cast<ABombermanController>(GetPlayerController());
		if (Controller)
		{
			Controller->SetVictoriesCountMenu(VictoriesCount[0], VictoriesCount[1]);
		}
	}
}

void ABombermanPlayerState::StartTimer()
{
	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &ABombermanPlayerState::SetTimer, 1.f, true);
}

void ABombermanPlayerState::StopTimer()
{
	GetWorldTimerManager().ClearTimer(MemberTimerHandle);
}

void ABombermanPlayerState::SetTimer_Implementation()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		if (Seconds > 0)
		{
			Seconds--;
		}
		else if (Seconds == 0)
		{
			Minutes--;
			Seconds = 59;
		}
	}
	
	if (GetLocalRole() == ROLE_SimulatedProxy)
	{
		ABombermanController* Controller = Cast<ABombermanController>(GetPlayerController());
		if (Controller)
		{
			Controller->SetTimer(Minutes, Seconds);
		}
	}
}


void ABombermanPlayerState::GetLifetimeReplicatedProps(TArray <FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABombermanPlayerState, Minutes);
	DOREPLIFETIME(ABombermanPlayerState, Seconds);
	DOREPLIFETIME(ABombermanPlayerState, VictoriesCount);
}