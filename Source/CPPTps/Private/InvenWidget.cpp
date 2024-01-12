// Fill out your copyright notice in the Description page of Project Settings.


#include "InvenWidget.h"
#include "Inventory.h"
#include "InvenItem.h"
#include <Components/CanvasPanel.h>
#include <Components/CanvasPanelSlot.h>
#include <Components/Image.h>

void UInvenWidget::NativeConstruct()
{
	Super::NativeConstruct();

	itemFactory = LoadClass<UInvenItem>(nullptr, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/Inventory/BP_InvenItem.BP_InvenItem_C'"));
}

void UInvenWidget::RefreshInven(TArray<FItemData> myItems)
{
	// myItems ������ŭ InvenItem ����
	for (int i = 0; i < myItems.Num(); i++)
	{
		// InvenItem ����
		UInvenItem* item = CreateWidget<UInvenItem>(GetWorld(), itemFactory);

		// ** invenPanel ���̰� ���� ��ġ���� ��������!! **
		
		// �κ��丮�� ������ item �� ������
		invenPanel->AddChild(item);

		// �κ��丮�̿��� item �� ��ġ ���
		FVector2D pos;
		pos.X = (i % 5) * 100;
		pos.Y = (i / 5) * 100;
		UCanvasPanelSlot* panelSlot = Cast<UCanvasPanelSlot>(item->Slot);
		panelSlot->SetPosition(pos);	

		// �̹��� ����
		item->thumbnail->SetBrushFromTexture(myItems[i].thumbnail);
	}
}
