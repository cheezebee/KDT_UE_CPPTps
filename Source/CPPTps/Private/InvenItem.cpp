// Fill out your copyright notice in the Description page of Project Settings.


#include "InvenItem.h"

// ���콺 (����/������) ������ (���콺�����Ͱ� �� ���� ���� ��)
FReply UInvenItem::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	onHover.ExecuteIfBound(this);

	//UE_LOG(LogTemp, Warning, TEXT("item name : %s"), *itemData.name);

	return Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);
}

void UInvenItem::InitItem(FItemData data, int32 idx, UObject* InObject, const FName& InFunctionName)
{
	itemData = data;
	idxInInven = idx;

	// onHover �� InObject �� �����ϴ� �Լ� InFunctionName �� ���
	onHover.BindUFunction(InObject, InFunctionName);
}


