// Copyright Epic Games, Inc. All Rights Reserved.
#include "Components/PointLightComponent.h"
#include "WebSocketTest2Character.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "WebSocketGameInstance.h"


#include "MyTriggerBox.h"
//////////////////////////////////////////////////////////////////////////
// AWebSocketTest2Character
class LightSwitchBoth;
AWebSocketTest2Character::AWebSocketTest2Character()
{
	/*
	// Set size for collision capsule
	TriggerCapsule = GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);


	// bind trigger events
	TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &AUnrealCPPCharacter::OnOverlapBegin);
	TriggerCapsule->OnComponentEndOverlap.AddDynamic(this, &AUnrealCPPCharacter::OnOverlapEnd);

	*/
	// set current light switch to null

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AWebSocketTest2Character::NotifyServer()
{
	UWebSocketGameInstance* GameInstance = Cast<UWebSocketGameInstance>(GetGameInstance());

	Light = Cast<ALightSwitchBoth>(UGameplayStatics::GetActorOfClass(GetWorld(), Actortospawn));
	//ALightSwitchBoth* lightBulb = Cast<ALightSwitchBoth>(GetActor());
	//AActor* LightCast;
	/*
	ALightSwitchBoth* lightSwit = Cast<ALightSwitchBoth>(lightBulb);
	lightSwit->PointLight2 = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight1"));
		//= CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight1"));
	lightSwit->PointLight2->SetVisibility(true);*/
	AMyTriggerBox* tbox = Cast<AMyTriggerBox>(tb);
	
	if (GameInstance)
	{
		if (GameInstance->Socket->IsConnected())
		{
			
			//if (tbox->box_flag == true) {
				GameInstance->Socket->Send("{\"action\":\"sendmessage\",\"message\":\"Pressed E Key\"}");
				flag = 0;
			//}
			//LightSwitchBoth->PointLight2;
		}
	}
}

void AWebSocketTest2Character::NotifyServer2()
{
	UWebSocketGameInstance* GameInstance = Cast<UWebSocketGameInstance>(GetGameInstance());
	
	if (GameInstance)
	{
		if (GameInstance->Socket->IsConnected())
		{
			GameInstance->Socket->Send("{\"action\":\"sendmessage\",\"message\":\"on1\"}");
			
		}
	}
}




//Latest functions

/*
void AWebSocketTest2Character::ToggleFlashLight()
{
	//LightSwitchBoth->ToggleFlashLight();
}

void AWebSocketTest2Character::ToggleLightSwitch()
{
	LightSwitchBoth = GetWorld()->SpawnActor<ALightSwitchBoth>(ALightSwitchBoth::StaticClass());
	LightSwitchBoth->AttachFlashLight(GetOwner());
}
*/
void AWebSocketTest2Character::Action()
{
}


void AWebSocketTest2Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AWebSocketTest2Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AWebSocketTest2Character::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AWebSocketTest2Character::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AWebSocketTest2Character::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AWebSocketTest2Character::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AWebSocketTest2Character::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AWebSocketTest2Character::OnResetVR);
	PlayerInputComponent->BindAction("NotifyServer", IE_Pressed, this, &AWebSocketTest2Character::NotifyServer);
	PlayerInputComponent->BindAction("NotifyServer1", IE_Pressed, this, &AWebSocketTest2Character::NotifyServer2);


	/*
	PlayerInputComponent->BindAction("ToggleFlashLight", IE_Pressed, this, &AWebSocketTest2Character::ToggleFlashLight);
	PlayerInputComponent->BindAction("ToggleLightSwitch", IE_Pressed, this, &AWebSocketTest2Character::ToggleLightSwitch);
	*/



}


void AWebSocketTest2Character::OnResetVR()
{
	// If WebSocketTest2 is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in WebSocketTest2.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AWebSocketTest2Character::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AWebSocketTest2Character::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AWebSocketTest2Character::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AWebSocketTest2Character::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AWebSocketTest2Character::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AWebSocketTest2Character::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}


