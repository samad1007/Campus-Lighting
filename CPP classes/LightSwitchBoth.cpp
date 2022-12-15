// Fill out your copyright notice in the Description page of Project Settings.
#include "Components/PointLightComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SceneComponent.h"
#include "WebSocketGameInstance.h"
#include "WebSocketsModule.h"
#include "WebSocketTest2.h"
#include "LightSwitchBoth.h"
#include "WebSocketTest2Character.h"
#include "Containers/UnrealString.h"
using namespace std;
class UWebSocketGameInstance;

// Sets default values
ALightSwitchBoth::ALightSwitchBoth()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    DesiredIntensity = 3000.0f;

    PointLight2 = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight1"));
    PointLight2->Intensity = DesiredIntensity;
    //PointLight1->bVisible = true;
    RootComponent = PointLight2;

    /*Sphere1 = CreateDefaultSubobject<USphereComponent>(TEXT("Light Sphere Component"));
    //Sphere1 = CreateDefaultSubobject<USphereComponent>(this, TEXT("Sphere1"));
    Sphere1->InitSphereRadius(250.0f);
    Sphere1->SetupAttachment(RootComponent);

    Sphere1->OnComponentBeginOverlap.AddDynamic(this, &ALightSwitchBoth::OnOverlapBegin);       // set up a notification for when this component overlaps something
    Sphere1->OnComponentEndOverlap.AddDynamic(this, &ALightSwitchBoth::OnOverlapEnd);       // set up a notification for when this component overlaps something
    */   
}


// Called when the game starts or when spawned
void ALightSwitchBoth::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALightSwitchBoth::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GameInstance = Cast<UWebSocketGameInstance>(GetGameInstance());

	if (GameInstance)
	{
        if (GameInstance->Socket->IsConnected())
        {
            str = FString(GameInstance->msg);
            FString button="";
            for (int i = 0; i < str.Len(); i++) {

                // convert str[i] to uppercase
                char ch = tolower(str[i]);
                button += ch;
            }

            if (button == "on") {

                //UE_LOG(LogTemp, Warning, TEXT("key: %f"), GameInstance->key);
                //PointLight1->ToggleVisibility();
                PointLight2->SetVisibility(true);
                
            }
            
            else if(button=="off") {
                PointLight2->SetVisibility(false);
            }
            /*
            if (GameInstance->sent == "off1") {
                if(PointLight1->IsVisible())
                //UE_LOG(LogTemp, Warning, TEXT("key: %f"), GameInstance->key);
                //PointLight1->ToggleVisibility();
                PointLight1->SetVisibility(false);

            }

            else {
                PointLight1->SetVisibility(true);
            }
           */

           
         
        }
	}
   
}
/*
void ALightSwitchBoth::ToggleFlashLight()
{
    if (LightState) {
        LightState = false;
        PointLight2->SetVisibility(false);
    }
    else {
        LightState = true;
        PointLight2->SetVisibility(true);
    }
}

void ALightSwitchBoth::AttachFlashLight(AActor* Player)
{
    USceneComponent* SceneComponent = Player->FindComponentByClass<USceneComponent>();
    if (SceneComponent != nullptr) {
        this->AttachToComponent(SceneComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("hand_r_Socket"));
        UE_LOG(LogTemp, Warning, TEXT("Spawning FlashLight"));
    }
}
*/

/*

void ALightSwitchBoth::OnOverlapBegin_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
   
    if (OtherActor && (OtherActor != this) && OtherComp)
    ToggleLight(); 
}


void ALightSwitchBoth::OnOverlapEnd_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
   
    if (OtherActor && (OtherActor != this) && OtherComp)
    {
        ToggleLight();
    }
}
*/
    
/*
void ALightSwitchBoth::ToggleLight()
{
    PointLight1->ToggleVisibility();
}
*/

