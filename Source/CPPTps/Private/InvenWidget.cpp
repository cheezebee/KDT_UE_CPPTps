// Fill out your copyright notice in the Description page of Project Settings.


#include "InvenWidget.h"
#include "Inventory.h"
#include "InvenItem.h"
#include <Components/CanvasPanel.h>
#include <Components/CanvasPanelSlot.h>
#include <Components/Image.h>
#include <Kismet/GameplayStatics.h>
#include "TpsPlayer.h"

void UInvenWidget::NativeConstruct()
{
	Super::NativeConstruct();

	itemFactory = LoadClass<UInvenItem>(nullptr, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/Inventory/BP_InvenItem.BP_InvenItem_C'"));

	// �÷��̾ ã��
	player = Cast<ATpsPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), ATpsPlayer::StaticClass()));
}

void UInvenWidget::RefreshInven(TArray<FItemData> myItems)
{
	// ������ �پ��ִ� InvenItem ��� ����
	for (int32 i = 0; i < allItemWidget.Num(); i++)
	{
		allItemWidget[i]->RemoveFromParent();
	}
	allItemWidget.Empty();

	// myItems ������ŭ InvenItem ����
	for (int i = 0; i < myItems.Num(); i++)
	{
		CreateItem(myItems[i], i);
	}
}

void UInvenWidget::CreateItem(FItemData itemData, int32 i)
{
	// InvenItem ����
	UInvenItem* item = CreateWidget<UInvenItem>(GetWorld(), itemFactory);

	// itemData �� ������� item �� �˷�����
	item->InitItem(itemData, i, player, TEXT("OnHoverItem"));

	// ������� item widget �� array ������ ����
	allItemWidget.Add(item);

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
	item->thumbnail->SetBrushFromTexture(itemData.thumbnail);
}
