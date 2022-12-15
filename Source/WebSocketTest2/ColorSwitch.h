// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ColorSwitch.generated.h"

class UMaterialInstanceDynamic;
class UWebSocketGameInstance;

UCLASS()
class WEBSOCKETTEST2_API AColorSwitch : public AActor
{
	GENERATED_BODY()
		UStaticMeshComponent* FirstActorMesh;
		UStaticMeshComponent* fam;
	
public:	
	// Sets default values for this actor's properties
	AColorSwitch();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Learning About Components")
		class UStaticMeshComponent* mouse;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Learning About Components")
		class UStaticMeshComponent* keyboard;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Learning About Components")
		class UStaticMeshComponent* r;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UMaterialInstanceDynamic* material;
	UMaterialInstanceDynamic* material1;
	UWebSocketGameInstance* GameInstance;
};
