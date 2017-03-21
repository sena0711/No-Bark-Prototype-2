// Fill out your copyright notice in the Description page of Project Settings.

#include "No_Bark_Prototype2.h"
#include "FPCGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "BatteryPickup.h"
#include "FPCharacter.h"




AFPCGameMode::AFPCGameMode()
{// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/MyFPCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	//base decay rate
	DecayRate = 0.01f;
}

void AFPCGameMode::BeginPlay()
{
	Super::BeginPlay();


	// set the score to beat
	AFPCharacter* MyCharacter = Cast<AFPCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (MyCharacter)
	{
		PowerToWin = (MyCharacter->GetInitialPower())*1.25f;
	}

	/*if (HUDWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}*/


}

void AFPCGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Check that we are using the battery collector character
	AFPCharacter* MyCharacter = Cast<AFPCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

	if (MyCharacter)
	{
		//// If our power is greater than needed to win, set the game's state to Won
		//if (MyCharacter->GetCurrentPower() > PowerToWin)
		//{
		//	SetCurrentState(EBatteryPlayState::EWon);
		//}
		// if the character's power is positive
		if (MyCharacter->GetCurrentPower() > 0)
		{

			// decrease the character's power using the decay rate
			MyCharacter->UpdatePower(-DeltaTime*DecayRate*(MyCharacter->GetInitialPower()));
		}
		else
		{
			SetCurrentState(EBatteryPlayState::EGameOver);
		}

	}

}

float AFPCGameMode::GetPowerToWin() const
{
	return PowerToWin;
}

EBatteryPlayState AFPCGameMode::GetCurrentState() const
{
	return CurrentState;
}

void AFPCGameMode::SetCurrentState(EBatteryPlayState NewState)
{
	//set current state
	CurrentState = NewState;
	// handle the new current state
	HandleNewState(CurrentState);

}

void AFPCGameMode::HandleNewState(EBatteryPlayState NewState)
{
	switch (NewState)
	{
		// If the game is playing
	case EBatteryPlayState::EPlaying:
	{

	}
	break;
	// If we've won the game
	case EBatteryPlayState::EWon:
	{

	}
	break;
	// If we've lost the game
	case EBatteryPlayState::EGameOver:
	{

		// block player input
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (PlayerController)
		{
			PlayerController->SetCinematicMode(true, false, false, true, true);
		}
		// ragdoll the character
		ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
		if (MyCharacter)
		{
			MyCharacter->GetMesh()->SetSimulatePhysics(true);
			MyCharacter->GetMovementComponent()->MovementState.bCanJump = false;
		}
	}
	break;
	// Unknown/default state
	default:
	case EBatteryPlayState::EUnknown:
	{
		// do nothing
	}
	break;
	}

}
