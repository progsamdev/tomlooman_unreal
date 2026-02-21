// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"

// Sets default values
ARogueCharacter::ARogueCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetupComponents();
}

// Called when the game starts or when spawned
void ARogueCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ARogueCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARogueCharacter::Move(const FInputActionValue& InValue)
{
	FVector2D InputValue = InValue.Get<FVector2D>();
	//FVector MoveDirection = FVector(InputValue.X, InputValue.Y, 0.0f);

	FRotator ControlRotation = GetControlRotation();
	ControlRotation.Pitch = 0.0f; // Ignore pitch for movement direction

	AddMovementInput(ControlRotation.Vector(), InputValue.X);	 
	FVector RightDirection = ControlRotation.RotateVector(FVector::RightVector);
	AddMovementInput(RightDirection, InputValue.Y);

}

void ARogueCharacter::Look(const FInputActionInstance& InValue)
{
	FVector2D InputValue = InValue.GetValue().Get<FVector2D>();
	AddControllerYawInput(InputValue.X);
	AddControllerPitchInput(InputValue.Y);
} 

// Called to bind functionality to input
void ARogueCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedInputCmp = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInputCmp->BindAction(Input_Move, ETriggerEvent::Triggered, this, &ARogueCharacter::Move);	
	EnhancedInputCmp->BindAction(Input_Look, ETriggerEvent::Triggered, this, &ARogueCharacter::Look);
}

void ARogueCharacter::SetupComponents()
{
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(GetRootComponent());
	SpringArmComp->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

}



