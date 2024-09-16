// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProyectilBueno.h" // Asegúrate de incluir este encabezado
#include "CuboDisparador.generated.h"

UCLASS()
class DONKEYKONG_API ACuboDisparador : public AActor
{
	GENERATED_BODY()
	
public:	
	// Establece los valores predeterminados para las propiedades de este actor
	ACuboDisparador();

protected:
	// Llamado cuando el juego comienza o cuando se genera
	virtual void BeginPlay() override;

public:	
	// Llamado cada frame
	virtual void Tick(float DeltaTime) override;

private:
	// Declaración del componente de malla estática
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ComponenteMallaCubo; // Cambiado a español y más amigable

	// Clase del proyectil
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<AProyectilBueno> ClaseProyectil; // Cambiado a español

	// Temporizador para controlar el disparo
	FTimerHandle TemporizadorDisparo; // Cambiado a español

	// Método para disparar el proyectil
	void DispararProyectil(); // Agregado
};
