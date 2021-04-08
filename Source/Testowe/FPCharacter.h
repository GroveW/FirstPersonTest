// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Container.h"

#include "FPCharacter.generated.h"

UCLASS()
class TESTOWE_API AFPCharacter : public ACharacter
{
	GENERATED_BODY()

	const int MAX_MINIONS = 5;
	int MinionsSpawned = 0;

public:
	// Sets default values for this character's properties
	AFPCharacter();

	UFUNCTION(BlueprintCallable)
	FVector FindClosestContainerOfType(NeededObjectType ContainerType, FVector ActorPosition);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnFire();
	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APawn> MinionToSpawn;

	UPROPERTY(EditDefaultsOnly)
	float MinionSpawningDistance = 300.0f;

	struct ContainerRepresentation
	{
		NeededObjectType Type;
		FVector Position;
	
		ContainerRepresentation(NeededObjectType Type, FVector Pos)
		{
			this->Type = Type;
			this->Position = Pos;
		}
	};

	TArray<ContainerRepresentation*> Containers;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
