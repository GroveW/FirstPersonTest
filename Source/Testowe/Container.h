// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Container.generated.h"

UENUM(BlueprintType)
enum class NeededObjectType : uint8
{
	OBJ_RED,
	OBJ_GREEN,
	OBJ_BLUE
};

UCLASS()
class TESTOWE_API AContainer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AContainer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly)
	NeededObjectType NeededObject;

	UPROPERTY(EditDefaultsOnly)
	UMaterial* RedMaterial;

	UPROPERTY(EditDefaultsOnly)
	UMaterial* GreenMaterial;

	UPROPERTY(EditDefaultsOnly)
	UMaterial* BlueMaterial;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
