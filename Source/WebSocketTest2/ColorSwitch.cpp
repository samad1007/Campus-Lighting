// Fill out your copyright notice in the Description page of Project Settings.


#include "ColorSwitch.h"
#include "Components/StaticMeshComponent.h"
#include "WebSocketGameInstance.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"
// Sets default values
AColorSwitch::AColorSwitch()
{
	/*
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mouse = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FirstActorMesh"));
	SetRootComponent(mouse);
	keyboard = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("fam"));
	//SetRootComponent(keyboard);
	keyboard->SetupAttachment(mouse);
	*/
	r = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("root"));
	SetRootComponent(r);
	mouse = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FirstActorMesh"));
	//SetRootComponent(mouse);
	mouse->SetupAttachment(r);
	keyboard = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("fam"));
	keyboard->SetupAttachment(r);
}

// Called when the game starts or when spawned
void AColorSwitch::BeginPlay()
{
	Super::BeginPlay();
	material = UMaterialInstanceDynamic::Create(mouse->GetMaterial(0), NULL);
	material1 = UMaterialInstanceDynamic::Create(keyboard->GetMaterial(0), NULL);

	mouse->SetMaterial(0, material);
	keyboard->SetMaterial(0, material1);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, material->GetName());
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, material1->GetName());

}

// Called every frame
void AColorSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	//UMaterialInstanceDynamic* material = UMaterialInstanceDynamic::Create(sphere->GetMaterial(0), NULL);
	//if (GameInstance) {
		//UE_LOG(LogTemp, Warning, TEXT("MoveForward: %f"), GameInstance->WebSocket->OnMessage());
	//}
	GameInstance = Cast<UWebSocketGameInstance>(GetGameInstance());

	if (GameInstance)
	{
		if (GameInstance->Socket->IsConnected())
		{
			if (GameInstance->key == 1.0f) {

				//UE_LOG(LogTemp, Warning, TEXT("key: %f"), GameInstance->key);
				material1->SetVectorParameterValue(FName(TEXT("color")), FLinearColor(0.0f, 1.0f, 0.0f));
			}
			else {
				material1->SetVectorParameterValue(FName(TEXT("color")), FLinearColor(1.0f, 0.0f, 0.0f));
			}
			if (GameInstance->mouse == 1.0f) {

				//UE_LOG(LogTemp, Warning, TEXT("mouse: %f"), GameInstance->mouse);
				material->SetVectorParameterValue(FName(TEXT("color")), FLinearColor(0.0f, 1.0f, 0.0f));
			}
			else {
				material->SetVectorParameterValue(FName(TEXT("color")), FLinearColor(1.0f, 0.0f, 0.0f));
			}
		}
		else {
			material->SetVectorParameterValue(FName(TEXT("color")), FLinearColor(1.0f, 1.0f, 1.0f));
			material1->SetVectorParameterValue(FName(TEXT("color")), FLinearColor(1.0f, 1.0f, 1.0f));
		}
	}
}

