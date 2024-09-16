// Copyright Epic Games, Inc. All Rights Reserved.

#include "DonkeyKongCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "ProyectilBueno.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"

ADonkeyKongCharacter::ADonkeyKongCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(-1000.f,0.f,75.f);
	CameraBoom->SetRelativeRotation(FRotator(0.f,180.f,0.f));

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 1.0f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	// Inicializar la clase del proyectil
	//static ConstructorHelpers::FClassFinder<AProyectilBueno> ProyectilAsset(TEXT("/Game/Path/To/Your/ProyectilBueno"));
	//if (ProyectilAsset.Succeeded())
	//{
	//	ProjectileClass = ProyectilAsset.Class;
	//}
}

//////////////////////////////////////////////////////////////////////////
// Input

void ADonkeyKongCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADonkeyKongCharacter::MoveRight);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &ADonkeyKongCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ADonkeyKongCharacter::TouchStopped);

	//para disparar

	PlayerInputComponent->BindAction("Disparar", IE_Pressed, this, &ADonkeyKongCharacter::Disparar);
}

void ADonkeyKongCharacter::MoveRight(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(0.f,-1.f,0.f), Value);
}

void ADonkeyKongCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void ADonkeyKongCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

void ADonkeyKongCharacter::Disparar(){
	//ProjectileClass = AProyectilBueno::StaticClass();


	ProjectileClass = AProyectilBueno::StaticClass();
	if (ProjectileClass)
	{
		//Obtener rotacio y ubicacion para ubicar el proyectil
		FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 100.0f; // Ajustar la distancia de spawn
		FRotator SpawnRotation = GetActorRotation();

		// Parmetros 
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		// Spawnear el proyectil
		AProyectilBueno* SpawnedProjectile = GetWorld()->SpawnActor<AProyectilBueno>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);

		if (SpawnedProjectile)
		{
			// Inicializar el proyectil con la direccin actual del personaje
			FVector ForwardDirection = GetActorForwardVector();
			SpawnedProjectile->Initialize(ForwardDirection);
		}
	}
}
