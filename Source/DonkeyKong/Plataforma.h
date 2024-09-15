// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DonkeyKongGameMode.h"
#include "Plataforma.generated.h"

UCLASS()
class DONKEYKONG_API APlataforma : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlataforma();

	// Método para establecer si la plataforma debe moverse
	void SetShouldMove(bool bMove) { bShouldMove = bMove; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Declaración de malla estática
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* mallaDePlataforma;

	UPROPERTY(VisibleAnywhere)
	UMaterialInstanceDynamic* MaterialDinamico;

	// Para el movimiento
	float velocidad;
	float distancia;
	float tiempo;
	FVector MoviendoPlataforma;

	// Función para que se mueva
	void oscilar(float DeltaTime, float nume);
	bool bShouldMove = false;
};
