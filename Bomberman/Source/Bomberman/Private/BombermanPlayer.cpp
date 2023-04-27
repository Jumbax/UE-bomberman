// Fill out your copyright notice in the Description page of Project Settings.


#include "BombermanPlayer.h"
#include "Bomb.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Net/UnrealNetwork.h"

ABombermanPlayer::ABombermanPlayer()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.0f; // The camera follows at this distance behind the character	
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	bReplicates = true;
}

void ABombermanPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	BombsNum = StartingBombsNum;
}

void ABombermanPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		EnhancedInputComponent->BindAction(DropBombAction, ETriggerEvent::Completed, this, &ABombermanPlayer::DropBomb);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABombermanPlayer::Move);
	}
}

void ABombermanPlayer::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ABombermanPlayer::DropBomb_Implementation(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		if (BombsNum > 0)
		{
			FActorSpawnParameters SpawnParameters;
			FVector SpawnPoint = FVector(GetActorLocation().X, GetActorLocation().Y, 8.5f);
			GetWorld()->SpawnActor<ABomb>(Bomb, SpawnPoint, FRotator(0.f, 0.f, 0.0), SpawnParameters);
			BombsNum--;
			GetWorldTimerManager().SetTimer(ReChargeBombTimerHandle, this, &ABombermanPlayer::AddBomb, ReChargeBombTime, false);
		}
	}
}

void ABombermanPlayer::AddBomb()
{
	if (BombsNum >= MaxBombsNum)
	{
		GetWorldTimerManager().ClearTimer(ReChargeBombTimerHandle);
		return;
	}
	BombsNum++;
}

void ABombermanPlayer::ActiveSuperSpeedPowerUp(const float Duration)
{
	GetCharacterMovement()->MaxWalkSpeed = 1000.f;
	GetWorldTimerManager().SetTimer(SuperSpeedTimerHandle, this, &ABombermanPlayer::DeactiveSuperSpeedPowerUp, Duration, false);
}

void ABombermanPlayer::DeactiveSuperSpeedPowerUp()
{
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetWorldTimerManager().ClearTimer(SuperSpeedTimerHandle);
}

void ABombermanPlayer::ActiveInvinciblePowerUp(const float Duration)
{
	IsInvincible = true;
	GetWorldTimerManager().SetTimer(InvincibleTimerHandle, this, &ABombermanPlayer::DeactiveInvinciblePowerUp, Duration, false);
}

void ABombermanPlayer::DeactiveInvinciblePowerUp()
{
	IsInvincible = false;
	GetWorldTimerManager().ClearTimer(InvincibleTimerHandle);
}

void ABombermanPlayer::ActiveMoreBombsPowerUp()
{
	BombsNum += 3;
}

void ABombermanPlayer::Death()
{
	
}
