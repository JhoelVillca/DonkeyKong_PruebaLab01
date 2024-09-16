// Fill out your copyright notice in the Description page of Project Settings.


#include "ProyectilBueno.h"

// Sets default values
AProyectilBueno::AProyectilBueno()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//malla para el proyectil
	mallaDeProyectilBueno = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mallaDeProyectilBueno"));
	//tamanio del proyectil
	mallaDeProyectilBueno->SetWorldScale3D(FVector(0.5f));
	RootComponent = mallaDeProyectilBueno;

	//buscar malla
	static ConstructorHelpers::FObjectFinder<UStaticMesh> mallaDeProyectilBuenoAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	//buscar material
	static	ConstructorHelpers::FObjectFinder<UMaterial> mallaDeProyectilMateria(TEXT("Material'/Game/StarterContent/Materials/M_Metal_Gold.M_Metal_Gold'"));
	//asignar malla
	mallaDeProyectilBueno->SetStaticMesh(mallaDeProyectilBuenoAsset.Object);
	//asignar material
	mallaDeProyectilBueno->SetMaterial(0,mallaDeProyectilMateria.Object);
	//componentes de movimiento
	mallaDeProyectilBueno->SetSimulatePhysics(false);
	mallaDeProyectilBueno->SetCollisionProfileName(TEXT("BlockAllDynamic"));

	//mas componentes de movimiento

	movimientoDeProyectil = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("movimientoDeProyctil"));
	ProjectileMovement = movimientoDeProyectil; // Asignar correctamente
	movimientoDeProyectil->UpdatedComponent = mallaDeProyectilBueno;
	movimientoDeProyectil->InitialSpeed = 900.0f;
	movimientoDeProyectil->MaxSpeed = 900.0f;
	movimientoDeProyectil->ProjectileGravityScale = 0.0f;

}
void AProyectilBueno::Initialize(const FVector& Direction)
{
	ProjectileMovement->Velocity = Direction * ProjectileMovement->InitialSpeed; // Asegúrate de que esto sea correcto
}

// Called when the game starts or when spawned
void AProyectilBueno::BeginPlay()
{
	Super::BeginPlay();

	mallaDeProyectilBueno->OnComponentHit.AddDynamic(this, &AProyectilBueno::OnHit);
	
}

// Called every frame
void AProyectilBueno::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}
void AProyectilBueno::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	/**
	 * Verifica si la colisión es con un actor diferente al personaje que la disparó.
	 * Si la colisión es con un actor diferente, se destruye la esfera.
	 */
	if (OtherActor != nullptr && OtherActor != this && OtherActor != GetOwner())
	{
		Destroy();
	}
}
