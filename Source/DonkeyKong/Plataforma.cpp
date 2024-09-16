// Fill out your copyright notice in the Description page of Project Settings.


#include "Plataforma.h"

// Sets default values
APlataforma::APlataforma()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// Inicialización de mallaDePlataforma 

	mallaDePlataforma = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mallaDePlataforma"));
	mallaDePlataforma->SetRelativeScale3D(FVector(1.0f, 1.25f/3.0f, 1.0f));
	RootComponent = mallaDePlataforma;

	// Busca el objeto, es decir la dirección 

	static ConstructorHelpers::FObjectFinder<UStaticMesh>mallaDePlataformaAsset(TEXT("StaticMesh'/Game/Geometry/MisMallas/PlataformaMalla/MallaDePlataforma.MallaDePlataforma'"));
	if (mallaDePlataformaAsset.Succeeded()) {

		// Asignar la malla
		mallaDePlataforma->SetStaticMesh(mallaDePlataformaAsset.Object);

		// Para el material
		static ConstructorHelpers::FObjectFinder<UMaterial>mallaDePlataformaMateria(TEXT("Material'/Game/Geometry/MisMallas/PlataformaMalla/rojito.rojito'"));
		if (mallaDePlataformaMateria.Succeeded()) {

			MaterialDinamico = UMaterialInstanceDynamic::Create(mallaDePlataformaMateria.Object, mallaDePlataforma);
			mallaDePlataforma->SetMaterial(0, MaterialDinamico);
			MaterialDinamico->SetVectorParameterValue(TEXT("BaseColor"), FLinearColor(0.5f, 0.0f, 0.125f, 1.0f));
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("No se encontro el material, por favor asegurese de haberlo importado "));
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("/Game/Geometry/MisMallas"));
		}
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Malla No Encontrada, por favor, asegúrese de tenerlo"));
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("/Game/Geometry/MisMallas"));
	}
}

// Called when the game starts or when spawned
void APlataforma::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlataforma::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bShouldMove) {
		float velocidadMovPlataforma = 1.0f;
		float distanciaMovPlataforma = 100.0f;
		float tiempoMovPlataforma = GetWorld()->GetTimeSeconds();

		FVector NewLocation = GetActorLocation();

		NewLocation.Z += FMath::Sin(tiempoMovPlataforma * velocidadMovPlataforma) * distanciaMovPlataforma * DeltaTime;

		SetActorLocation(NewLocation);
	}
}

void APlataforma::oscilar(float DeltaTime, float nume) {
	//ADonkeyKongGameMode* GameMode = Cast<ADonkeyKongGameMode>(GetWorld()->GetAuthGameMode());
	//if (GameMode) {
	//	int valorEntero = GameMode->e; // Acceder a la variable e
	//	float provB = static_cast<float>(valorEntero); // Convertir el entero a float
	//	if (siORnot(nume, provB)) {
	//		
	// 			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Se mueve"));
	//	}
	//	else {
	//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No se mueve"));
//
	//	}
	//}
}

/*
bool APlataforma::siORnot(float numee, float probabilidadDePlataforma) {
	if (numee < (probabilidadDePlataforma*5/100)) {
		return true;
	}
	else {
		return false;
	}
}*/

