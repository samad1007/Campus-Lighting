// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WebSocketGameInstance.h"
#include "LightSwitchBoth.generated.h"

UCLASS()
class WEBSOCKETTEST2_API ALightSwitchBoth : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightSwitchBoth();

    /** point light component */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Switch Components")
        class UPointLightComponent* PointLight2;

    /** sphere component */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Switch Components")
        class USphereComponent* Sphere1;

  
 

    /** the desired intensity for the light */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Switch Variables")
        float DesiredIntensity;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    UWebSocketGameInstance* GameInstance;
    FString str;
    int flag;

    void AttachFlashLight(AActor* Player);
    /*
    void ToggleFlashLight();
    bool LightState= false;
    */

};
