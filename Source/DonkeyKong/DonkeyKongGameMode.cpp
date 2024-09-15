// Copyright Epic Games, Inc. All Rights Reserved.

#include "DonkeyKongGameMode.h"
#include "DonkeyKongCharacter.h"
#include "Plataforma.h"
#include "CoreMinimal.h"
#include "Kismet/KismetMathLibrary.h" // para tener algunas funciones matematicas
#include "UObject/ConstructorHelpers.h"

ADonkeyKongGameMode::ADonkeyKongGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ADonkeyKongGameMode::BeginPlay()
{
    Super::BeginPlay();

    int z = -551;
    e = FMath::RandRange(3, 5);
    float AEZ = 10.0f;
    float CEY = 414.0f;
    float tam = -551;

    int32 PlataformaIDCounter = 0; //Contar IDs
    // Spawnear las plataformas de con un numero random de componentes
    for(int i = 0; i < 5; i++) {
        for (int j = 0; j < e; j++) {
            APlataforma* newPlataforma = nullptr;
            if (j == 0 || j + 1 == e) {
                z *= -1;
                newPlataforma = GetWorld()->SpawnActor<APlataforma>(APlataforma::StaticClass(),
                    FVector(1207, CEY - j * 551, (504.0f - FMath::Tan(FMath::DegreesToRadians(AEZ)) * z / 2) + i * 460.0f), FRotator(0.0f, 0.0f, AEZ));
            } else {
                newPlataforma = GetWorld()->SpawnActor<APlataforma>(APlataforma::StaticClass(),
                    FVector(1207, CEY - j * 551, 504.0f + i * 460.0f), FRotator(0.0f, 0.0f, 0.0f));
            }

            if (newPlataforma) {
                // Agregar la plataforma al TMap
                PlataformasCreadas.Add(PlataformaIDCounter, newPlataforma); 
                PlataformaIDCounter++; 
            } 
        }
        tam *= -1;
        CEY += tam;
        AEZ *= -1;
    }
    // Seleccionar 3 plataformas aleatorias
    if (PlataformasCreadas.Num() > 3) {
        // Para almacenar IDs únicos
        TSet<int32> IDsSeleccionados; 
        TArray<int32> Claves; 
        // Obtener las claves del TMap
        PlataformasCreadas.GetKeys(Claves); 

        while (IDsSeleccionados.Num() < 3) {
            int32 RandomIndex = FMath::RandRange(0, Claves.Num() - 1);
            // Obtener el ID de la plataforma
            int32 PlataformaID = Claves[RandomIndex]; 
            if (!IDsSeleccionados.Contains(PlataformaID)) {
                IDsSeleccionados.Add(PlataformaID);
                //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Plataforma seleccionada con ID: %d"), PlataformaID));
            }
        }

        // Activar el movimiento para las plataformas seleccionadas
        for (int32 ID : IDsSeleccionados) {
            if (PlataformasCreadas.Contains(ID)) {
                PlataformasCreadas[ID]->SetShouldMove(true);
              
            }
        }
    }
    else {
       GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No hay suficientes plataformas creadas."));
    }
}