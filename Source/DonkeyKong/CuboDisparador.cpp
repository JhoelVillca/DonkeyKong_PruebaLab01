// Fill out your copyright notice in the Description page of Project Settings.


#include "CuboDisparador.h"
#include "ProyectilBueno.h" // Asegúrate de incluir esto
#include "Engine/World.h"
#include "TimerManager.h"
#include "Engine/Engine.h" // Para GEngine

// Constructor
ACuboDisparador::ACuboDisparador()
{
	PrimaryActorTick.bCanEverTick = true; // Eliminar el punto extra aquí

	// Inicializar el componente de malla
	ComponenteMallaCubo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ComponenteMallaCubo"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MallaCuboAsset(TEXT("StaticMesh'/Game/Geometry/Meshes/1M_Cube.1M_Cube'")); // Ruta de la malla
	if (MallaCuboAsset.Succeeded())
	{
		ComponenteMallaCubo->SetStaticMesh(MallaCuboAsset.Object);
	}
	RootComponent = ComponenteMallaCubo; // Establecer el componente de malla como raíz

	// Asignar la clase del proyectil
	static ConstructorHelpers::FClassFinder<AProyectilBueno> ProyectilAsset(TEXT("Class'/Script/DonkeyKong.ProyectilBueno'")); // Cambia la ruta al C++ de tu proyectil
	if (ProyectilAsset.Succeeded())
	{
		ClaseProyectil = ProyectilAsset.Class; // Cambiado a español
	}
}

// Llamado cuando el juego comienza o cuando se genera
void ACuboDisparador::BeginPlay()
{
	Super::BeginPlay();

	// Iniciar el temporizador para disparar el proyectil cada 3 segundos
	GetWorld()->GetTimerManager().SetTimer(TemporizadorDisparo, this, &ACuboDisparador::DispararProyectil, 3.0f, true); // Cambiado a español
}

// Llamado cada frame
void ACuboDisparador::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Método para disparar el proyectil
void ACuboDisparador::DispararProyectil()
{
	if (ClaseProyectil) // Cambiado a español
	{
		FVector UbicacionSpawn = GetActorLocation(); // Cambiado a español
		FRotator RotacionSpawn = GetActorRotation(); // Cambiado a español

		// Proyectil hacia -Y
		FVector UbicacionSpawnNegY = UbicacionSpawn + FVector(0, -100, 0); // Ajusta la distancia según sea necesario
		AProyectilBueno* ProyectilNegY = GetWorld()->SpawnActor<AProyectilBueno>(ClaseProyectil, UbicacionSpawnNegY, RotacionSpawn); // Cambiado a español
		if (ProyectilNegY)
		{
			FVector DireccionNegY = FVector(0, -1, 0); // Dirección hacia -Y
			ProyectilNegY->Initialize(DireccionNegY); // Cambiado a español
		}

		// Proyectil hacia +Y
		FVector UbicacionSpawnPosY = UbicacionSpawn + FVector(0, 100, 0); // Ajusta la distancia según sea necesario
		AProyectilBueno* ProyectilPosY = GetWorld()->SpawnActor<AProyectilBueno>(ClaseProyectil, UbicacionSpawnPosY, RotacionSpawn); // Cambiado a español
		if (ProyectilPosY)
		{
			FVector DireccionPosY = FVector(0, 1, 0); // Dirección hacia +Y
			ProyectilPosY->Initialize(DireccionPosY); // Cambiado a español
		}
	}
}
