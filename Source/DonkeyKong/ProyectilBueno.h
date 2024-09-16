// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//para agregarle movimientos
#include "GameFramework/ProjectileMovementComponent.h"
#include "ProyectilBueno.generated.h"

UCLASS()
class DONKEYKONG_API AProyectilBueno : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProyectilBueno();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	UProjectileMovementComponent* ProjectileMovement;

	void Initialize(const FVector& Direction);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	//declaracion de malla para mi proyectil 
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* mallaDeProyectilBueno;

	//declaracion de movimiento del proyectil
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* movimientoDeProyectil;
};
