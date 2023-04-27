// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "BombermanPlayer.generated.h"

UCLASS()
class BOMBERMAN_API ABombermanPlayer : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* DropBombAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bomb, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ABomb> Bomb;

protected:
	void Move(const FInputActionValue& Value);
	UFUNCTION(Server, Reliable)
	void DropBomb(const FInputActionValue& Value);
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay();
	virtual void AddBomb();

	FTimerHandle ReChargeBombTimerHandle;
	FTimerHandle SuperSpeedTimerHandle;
	FTimerHandle InvincibleTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	int32 StartingBombsNum = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	int32 MaxBombsNum = 3;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Settings")
	int32 BombsNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float ReChargeBombTime = 3.f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Settings")
	bool IsInvincible = false;

public:
	ABombermanPlayer();

	//UFUNCTION(Server, Reliable)
	virtual void Death();
	//UFUNCTION(NetMulticast, Reliable)
	virtual void ActiveSuperSpeedPowerUp(const float Duration);
	//UFUNCTION(Server, Reliable)
	virtual void DeactiveSuperSpeedPowerUp();
	//UFUNCTION(Server, Reliable)
	virtual void ActiveInvinciblePowerUp(const float Duration);
	//UFUNCTION(Server, Reliable)
	virtual void DeactiveInvinciblePowerUp();
	//UFUNCTION(Server, Reliable)
	virtual void ActiveMoreBombsPowerUp();

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
