// Fill out your copyright notice in the Description page of Project Settings.


#include "Container.h"

// Sets default values
AContainer::AContainer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
}

// Called when the game starts or when spawned
void AContainer::BeginPlay()
{
	Super::BeginPlay();

	switch (NeededObject)
	{
	case NeededObjectType::OBJ_RED:
		StaticMesh->SetMaterial(0, RedMaterial);
		break;
	case NeededObjectType::OBJ_GREEN:
		StaticMesh->SetMaterial(0, GreenMaterial);
		break;
	case NeededObjectType::OBJ_BLUE:
		StaticMesh->SetMaterial(0, BlueMaterial);
		break;
	}
}

// Called every frame
void AContainer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

