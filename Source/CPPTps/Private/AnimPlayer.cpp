// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimPlayer.h"

void UAnimPlayer::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// ���� �پ��ִ� Pawn �� ��������
	APawn* pawn = TryGetPawnOwner();
	if (pawn != nullptr)
	{
		moveSpeed = pawn->GetVelocity().Length();
	}
}
