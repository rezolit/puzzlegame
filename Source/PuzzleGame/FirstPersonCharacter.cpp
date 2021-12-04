// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPersonCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AFirstPersonCharacter::AFirstPersonCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Camera
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(RootComponent);
	FirstPersonCamera->bUsePawnControlRotation = true;

	SprintAdditionalSpeed = 300.0f;
}

// Called when the game starts or when spawned
void AFirstPersonCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFirstPersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



// Called to bind functionality to input
void AFirstPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForward", this, &AFirstPersonCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AFirstPersonCharacter::MoveRight);

	InputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AFirstPersonCharacter::Jump);
	InputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &AFirstPersonCharacter::StopJumping);

	InputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &AFirstPersonCharacter::Sprint);
	InputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &AFirstPersonCharacter::StopSprinting);

	InputComponent->BindAxis("LookUp", this, &AFirstPersonCharacter::LookUp);
	InputComponent->BindAxis("LookHorizontal", this, &AFirstPersonCharacter::LookHorizontal);
}

void AFirstPersonCharacter::MoveForward(float Axis)
{
	ACharacter::AddMovementInput(GetActorForwardVector(), Axis);
}

void AFirstPersonCharacter::MoveRight(float Axis)
{
	ACharacter::AddMovementInput(GetActorRightVector(), Axis);
}

void AFirstPersonCharacter::Jump()
{
	if (CanJumping) {
		ACharacter::Jump();
	}
}

void AFirstPersonCharacter::StopJumping()
{
	if (CanJumping)
	{
		ACharacter::StopJumping();
	}
}

void AFirstPersonCharacter::Sprint()
{
	GetCharacterMovement()->MaxWalkSpeed += SprintAdditionalSpeed;
}

void AFirstPersonCharacter::StopSprinting()
{
	GetCharacterMovement()->MaxWalkSpeed -= SprintAdditionalSpeed;
}

void AFirstPersonCharacter::LookUp(float Axis)
{
	AddControllerPitchInput(Axis);
}

void AFirstPersonCharacter::LookHorizontal(float Axis)
{
	AddControllerYawInput(Axis);
}

