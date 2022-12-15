// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "IWebSocket.h"
#include "WebSocketGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class WEBSOCKETTEST2_API UWebSocketGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	void Init() override;
	void Shutdown() override;
	TSharedPtr<IWebSocket> Socket;
	int32 i;
	float key, mouse;
	FString msg,sent;


};
