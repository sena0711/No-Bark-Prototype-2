// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "FPCharacter.generated.h"
class UInputComponent;
UCLASS()
class NO_BARK_PROTOTYPE2_API AFPCharacter : public ACharacter
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	AFPCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Pawn mesh: 1st person view  */
	UPROPERTY(EditAnywhere, Category = Mesh)
		class USkeletalMeshComponent* Mesh1P;

	/** torchlight mesh: 1st person view*/
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where light should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USceneComponent* FP_MuzzleLocation;

	/** First person camera */
	UPROPERTY(EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FirstPersonCameraComponent;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class ALightOnly> LightClass;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector LightOffset;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	//**Sound**//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* FireSound;

	/** Fires a projectile. */
	UFUNCTION()
		void TriggerLight();
	/**
	* Called via input to turn at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	UFUNCTION()
		void TurnAtRate(float Rate);

	/**
	* Called via input to turn look up/down at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	UFUNCTION()
		void LookUpAtRate(float Rate);

	/** Handles moving forward/backward */
	UFUNCTION()
		void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	UFUNCTION()
		void MoveRight(float Val);

	/**
	* Lighting components.
	*/
	/** point light component */
	UPROPERTY(EditAnywhere, Category = "Switch Components")
		class USpotLightComponent* SpotLight1;

	/** sphere component */
	UPROPERTY(EditAnywhere, Category = "Switch Components")
		class USphereComponent* Sphere1;

	/** called when something enters the sphere component */
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/** called when something leaves the sphere component */
	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/** Toggles the light component's visibility*/
	UFUNCTION()
		void ToggleLight();

	/** the desired intensity for the light */
	UPROPERTY(EditAnywhere, Category = "Switch Variables")
		float DesiredIntensity;

	/** the desired intensity for the light */
	UPROPERTY(EditAnywhere, Category = "Switch Variables")
		float SphereRadius;

public:
	///** Returns Mesh1P subobject **/
	//FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	///** Returns FirstPersonCameraComponent subobject **/
	//FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	
};
