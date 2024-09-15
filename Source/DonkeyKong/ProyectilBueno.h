// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//para agregarle movimientos
#include "GameFramework/ProjectileMovementComponent.h"
#include "DonkeyKongCharacter.h"
#include "ProyectilBueno.generated.h"
UCLASS()
class DONKEYKONG_API AProyectilBueno : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProyectilBueno();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//void 

private:

	//declaracion de malla para mi proyectil 
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* mallaDeProyectilBueno;

	//declaracion de movimiento del proyectil
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* movimientoDeProyectil;
};
