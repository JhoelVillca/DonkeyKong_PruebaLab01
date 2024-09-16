// Copyright Epic Games, Inc. All Rights Reserved.

#include "DonkeyKongGameMode.h"
#include "DonkeyKongCharacter.h"
#include "Plataforma.h"
#include "CuboDisparador.h" // Asegúrate de incluir esto
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

        while (IDsSeleccionados.Num() < 6) {
            int32 RandomIndex = FMath::RandRange(0, Claves.Num() - 1);
            // Obtener el ID de la plataforma
            int32 PlataformaID = Claves[RandomIndex]; 
            if (!IDsSeleccionados.Contains(PlataformaID)) {
                IDsSeleccionados.Add(PlataformaID);
            }
        }

        // Activar el movimiento para las plataformas seleccionadas
        for (int32 ID : IDsSeleccionados) {
            if (PlataformasCreadas.Contains(ID) && ID % 2 == 0) {
                PlataformasCreadas[ID]->SetShouldMove(true);
            }
        }

        // Spawnear CuboDisparador en las plataformas seleccionadas
        TArray<ACuboDisparador*> CubosDisparadores; // Array para almacenar los CuboDisparador
        TSet<int32> IDsUsados; // Para almacenar IDs únicos

        for (int32 ID : IDsSeleccionados) {
            if (PlataformasCreadas.Contains(ID) && ID% 2 != 0) {
                APlataforma* PlataformaSeleccionada = PlataformasCreadas[ID];
                FVector UbicacionCubo = PlataformaSeleccionada->GetActorLocation() + FVector(0, 0, 100); // Ajusta la altura según sea necesario
                ACuboDisparador* NuevoCuboDisparador = GetWorld()->SpawnActor<ACuboDisparador>(ACuboDisparador::StaticClass(), UbicacionCubo, FRotator(0.0f, 0.0f, 0.0f));
                if (NuevoCuboDisparador) {
                    int32 CuboID;
                    do {
                        CuboID = FMath::RandRange(0, 1000); // Rango amplio para evitar colisiones
                    } while (IDsUsados.Contains(CuboID)); // Asegurarse de que el ID sea único

                    IDsUsados.Add(CuboID); // Agregar el ID a los usados
                    CubosDisparadores.Add(NuevoCuboDisparador); // Almacenar en el array

                    if (IDsUsados.Num() >= 3) {
                        break; // Salir del bucle una vez que tengamos 3 IDs únicos
                    }
                }
            }
        }
    }
    else {
       GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No hay suficientes plataformas creadas."));
    }
}