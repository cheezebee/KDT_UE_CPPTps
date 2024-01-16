// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimPlayer.h"

void UAnimPlayer::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// ���� �پ��ִ� Pawn �� ��������
	APawn* pawn = TryGetPawnOwner();
	if (pawn != nullptr)
	{
		// ���� �չ���
		FVector forward = pawn->GetActorForwardVector();
		// �̵� ����
		FVector moveDir = pawn->GetVelocity();
		// forward �� moveDir �� ���� = cos(�� ���Ͱ� �̷�� ��) 
		// �� ���� 0���� ũ�� �� ����, 0���� ������ �� ����
		dirF = FVector::DotProduct(forward, moveDir);
		//dirF = forward.Dot(moveDir);

		// ���� ������ ����
		FVector right = pawn->GetActorRightVector();
		// right �� moveDir �� ���� = cos(�� ���Ͱ� �̷�� ��) 
		// �� ���� 0���� ũ�� ������ ����, 0���� ������ ���� ����
		dirR = FVector::DotProduct(right, moveDir);
		UE_LOG(LogTemp, Warning, TEXT("dot : %f"), dirR);
	}
}
