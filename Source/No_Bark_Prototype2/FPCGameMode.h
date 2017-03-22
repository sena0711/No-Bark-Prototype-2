// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "FPCGameMode.generated.h"

/**
 * 
 */
//enum to store the current state of gameplay
UENUM(BlueprintType)
enum class EBatteryPlayState
{
	EPlaying,
	EGameOver,
	EWon,
	EUnknown
};

UCLASS()
class NO_BARK_PROTOTYPE2_API AFPCGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	// Sets default values for this Gamemode's properties
	AFPCGameMode();

	virtual void Tick(float DeltaTime) override;

	/** Returns power needed to win - needed for the HUD */
	UFUNCTION(BlueprintPure, Category = "Power")
		float GetPowerToWin() const;

	UFUNCTION(BlueprintPure, Category = "Power")
		float GetGameScore() const;
	UFUNCTION(BlueprintPure, Category = "Power")
		float GetTimeTicking() const;

	virtual void BeginPlay() override;

	/** Returns the current playing state */
	UFUNCTION(BlueprintPure, Category = "Power")
		EBatteryPlayState GetCurrentState() const;

	/** Sets a new playing state */
	void SetCurrentState(EBatteryPlayState NewState);

protected:
	/**The rate at which the character loses power */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		float DecayRate;
	/**The rate at which the character loses power */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		float RechargeRate;
	/**The rate at which the character loses power */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		float TimeTicking;
	/**The rate at which the character loses power */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		float GameScore;

	/**The power needed to win the game */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		float PowerToWin;

	/** The Widget class to use for our HUD screen */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		TSubclassOf<class UUserWidget> HUDWidgetClass;

	/** The instance of the HUD */
	UPROPERTY()
		class UUserWidget* CurrentWidget;


private:
	/**Keeps track of the current playing state */
	EBatteryPlayState CurrentState;

	TArray<class ASpawnVolume*> SpawnVolumeActors;

	/**Handle any function calls that rely upon changing the playing state of our game */
	void HandleNewState(EBatteryPlayState NewState);

};