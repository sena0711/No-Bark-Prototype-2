// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class NO_BARK_PROTOTYPE2_API APickup : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APickup();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	/** Return the mesh for the Pickup**/
	FORCEINLINE class UStaticMeshComponent* GetPickupMesh() const { return PickupMesh; }

	/** Return theif the pickup is Active**/
	UFUNCTION(BlueprintPure, Category = "Pickup")
		bool IsPickupActive();

	/** Allow other classess to safely change if pickup is active**/
	UFUNCTION(BlueprintCallable, Category = "Pickup")
		void SetActive(bool NewPickupState);


	/** function to call when the piciup is collected**/
	UFUNCTION(BlueprintNativeEvent)
		void WasCollected();
	/**Virtual function can be overrideen by any child classes**/
	virtual void WasCollected_Implementation();

	/** the mesh for the Pickup**/
	UPROPERTY(EditAnywhere, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* PickupMesh;

protected:

	bool bIsActive;
};
