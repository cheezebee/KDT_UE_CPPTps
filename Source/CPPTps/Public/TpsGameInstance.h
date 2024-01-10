// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TpsGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CPPTPS_API UTpsGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	virtual void Init() override;
	
public:
	// ������ ������ ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<struct FItemData> defineItem;


};
