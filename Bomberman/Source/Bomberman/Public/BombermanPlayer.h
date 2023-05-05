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
	virtual void BeginPlay();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Move(const FInputActionValue& Value);
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION(Server, Reliable)
	void DropBomb(const FInputActionValue& Value);
	
	virtual void AddBomb();

	FTimerHandle ReChargeBombTimerHandle;
	FTimerHandle SuperSpeedTimerHandle;
	FTimerHandle InvincibleTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	int32 StartingBombsNum = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	int32 MaxBombsNum = 3;
	
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite, Category = "Settings")
	int32 BombsNum = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float ReChargeBombTime = 3.f;
	
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite, Category = "Settings")
	bool bIsInvincible = false;

	UPROPERTY(Replicated, BlueprintReadOnly)
	bool bIsDead = false;

public:
	ABombermanPlayer();

	UFUNCTION(Server, Reliable)
	virtual void Death();

	bool IsDead() const { return bIsDead; }
	bool IsInvincible() const { return bIsInvincible; }
	virtual void ActiveSuperSpeedPowerUp(const float Duration);
	virtual void DeactiveSuperSpeedPowerUp();
	virtual void ActiveInvinciblePowerUp(const float Duration);
	virtual void DeactiveInvinciblePowerUp();
	virtual void ActiveMoreBombsPowerUp();

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
