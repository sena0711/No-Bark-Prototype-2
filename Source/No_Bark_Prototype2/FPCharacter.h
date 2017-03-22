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
	virtual void Tick(float DeltaSeconds) override;

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


	/** Spring Arm Component  */
	UPROPERTY(EditAnywhere, Category = "SpringArm")
		class USpringArmComponent* SpringArm;

	/** Location on gun mesh where light should spawn. */
	UPROPERTY(EditAnywhere, Category = "PickupMesh")
		class USphereComponent* CollectionSphere;


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


	/**
	Function to update the character's power
	* @param PowerChange This is the amount to change the power by, and it can be positive or negative.
	*/


	/**Current power level of our character */
	UPROPERTY(EditAnywhere, Category = "Power")
		float CharacterPower;

	UPROPERTY(EditAnywhere, Category = "Power")
		bool LightStatus;

	/** Accessor function for initial power */
	UFUNCTION(BlueprintPure, Category = "Power")
		float GetInitialPower();

	/** Accessor function for current power */
	UFUNCTION(BlueprintPure, Category = "Power")
		float GetCurrentPower();

	/** Accessor function for current power */
	UFUNCTION(BlueprintPure, Category = "Power")
		bool GetLightStatus();

	/**
	Function to update the character's power
	* @param PowerChange This is the amount to change the power by, and it can be positive or negative.
	*/
	UFUNCTION(BlueprintCallable, Category = "Power")
		void UpdatePower(float PowerChange);


	protected:
		// Called to bind functionality to input
		virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

		/** Called when we press a key to collect any pickups inside the CollectionSphere */
		UFUNCTION(BlueprintCallable, Category = "Pickups")
			void CollectPickups();

		/**The starting power level of our character */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
			float InitialPower;

		/** Multiplier for character speed */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
			float LightFactor;

		/** Speed when power level = 0 */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
			float BaseFactor;

		UFUNCTION(BlueprintImplementableEvent, Category = "Power")
			void PowerChangeEffect();

		/**The rate at which the character loses power */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
			float LightingTime;



public:
	///** Returns Mesh1P subobject **/
	//FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	///** Returns FirstPersonCameraComponent subobject **/
	//FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
	/** Returns GetCollectionSphere subobject **/
	FORCEINLINE class USphereComponent* GetCollectionSphere() const { return CollectionSphere; }

};
