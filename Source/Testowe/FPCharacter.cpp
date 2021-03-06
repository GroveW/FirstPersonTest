// Fill out your copyright notice in the Description page of Project Settings.


#include "FPCharacter.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AFPCharacter::AFPCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFPCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> ContainerActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AContainer::StaticClass(), ContainerActors);

	for (auto containerActor : ContainerActors)
	{
		auto container = Cast<AContainer>(containerActor);
		Containers.Add(new ContainerRepresentation(container->GetNeededObjectType(), containerActor->GetActorLocation()));
	}
}

// Called every frame
void AFPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Spawn", IE_Pressed, this, &AFPCharacter::OnFire);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AFPCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AFPCharacter::LookUpAtRate);
}

void AFPCharacter::OnFire()
{
	if (MinionsSpawned < MAX_MINIONS)
	{
		FVector SpawnPosition = GetActorLocation() + GetActorForwardVector() * MinionSpawningDistance;
		FRotator MinionRotation = FRotator(0.0f, 0.0f, 0.0f);
		AActor* p = GetWorld()->SpawnActor(MinionToSpawn, &SpawnPosition, &MinionRotation);
		Cast<APawn>(p)->SpawnDefaultController();

		MinionsSpawned++;
	}
}

void AFPCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AFPCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AFPCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * GetWorld()->GetDeltaSeconds());
}

void AFPCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * GetWorld()->GetDeltaSeconds());
}

void AFPCharacter::BlockInput(bool Block)
{
	if (Block)
		UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	else
		UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

FVector AFPCharacter::FindClosestContainerOfType(NeededObjectType ContainerType, FVector ActorPosition)
{
	float smallestDistance = 100000.0f;
	FVector targetPosition;

	for (auto container : Containers)
	{
		float newDistance = FVector::Dist(container->Position, ActorPosition);
		if (container->Type == ContainerType && newDistance < smallestDistance)
		{
			targetPosition = container->Position;
			smallestDistance = newDistance;
		}
	}

	return targetPosition;
}