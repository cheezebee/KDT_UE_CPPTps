// Fill out your copyright notice in the Description page of Project Settings.


#include "TpsGameInstance.h"

#include "Inventory.h"

UTpsGameInstance::UTpsGameInstance()
{
	ConstructorHelpers::FObjectFinder<UDataTable> tempData(TEXT("/Script/Engine.DataTable'/Game/Blueprints/Inventory/ItemTable.ItemTable'"));
	if (tempData.Succeeded())
	{
		UDataTable* data = tempData.Object;

		// ���� (���� ����)
		TArray<FName> rowNames = data->GetRowNames();
		for (int i = 0; i < rowNames.Num(); i++)
		{
			// �� ���� �����͸� ��������
			FItemData* itemData = data->FindRow<FItemData>(rowNames[i], TEXT(""));
			// �츮�� ���� Array �� ��Ƴ���
			defineItem.Add(*itemData);			
		}
	}
}

void UTpsGameInstance::Init()
{
	Super::Init();

	////LoadClass()
	//// ������ ���� - Database �� �ִ� ���� �о ����)
	//UDataTable* data = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/Blueprints/Inventory/ItemTable.ItemTable'"));
	//// ���� (���� ����)
	//TArray<FName> rowNames = data->GetRowNames();
	//for (int i = 0; i < rowNames.Num(); i++)
	//{
	//	// �� ���� �����͸� ��������
	//	FItemData* itemData = data->FindRow<FItemData>(rowNames[i], TEXT(""));
	//	// �츮�� ���� Array �� ��Ƴ���
	//	defineItem.Add(*itemData);
	//}
}