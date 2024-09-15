// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
// Declaración anticipada de APlataforma
class APlataforma; // Cambiado de incluir a declaración anticipada
#include "DonkeyKongGameMode.generated.h"

UCLASS(minimalapi)
class ADonkeyKongGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADonkeyKongGameMode();

	int e;

private:
	FVector PosPlataforma;
	TMap<int32, APlataforma*> PlataformasCreadas; 

protected:
	virtual void BeginPlay() override;
};



