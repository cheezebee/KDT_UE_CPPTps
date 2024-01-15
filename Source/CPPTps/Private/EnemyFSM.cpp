// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFSM.h"
#include <Kismet/GameplayStatics.h>
#include "TpsPlayer.h"
#include "Enemy.h"
#include "AnimEnemy.h"

// Sets default values for this component's properties
UEnemyFSM::UEnemyFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}


// Called when the game starts
void UEnemyFSM::BeginPlay()
{
	Super::BeginPlay();

	// �÷��̾ ã��
	AActor* findActor = UGameplayStatics::GetActorOfClass(GetWorld(), ATpsPlayer::StaticClass());
	target = Cast<ATpsPlayer>(findActor);
	
	// ���� ���͸� ã��
	myActor = Cast<AEnemy>(GetOwner());

	// ������ �����Ǿ� �ִ� Anim Class ��������
	USkeletalMeshComponent* mesh = myActor->GetMesh();
	UAnimInstance* animInstance = mesh->GetAnimInstance();
	anim = Cast<UAnimEnemy>(animInstance);

	//anim = Cast<UAnimEnemy>(myActor->GetMesh()->GetAnimInstance());
}


// Called every frame
void UEnemyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ���࿡ Target �� ���ٸ� �Լ��� ������
	if (target == nullptr) return;

	switch (currState)
	{
	case EEnemyState::IDLE:
		UpdateIdle();
		break;
	case EEnemyState::MOVE:
		UpdateMove();
		break;
	case EEnemyState::ATTACK:
		UpdateAttack();
		break;
	case EEnemyState::ATTACK_DELAY:
		UpdateAttackDelay();
		break;
	case EEnemyState::DAMAGE:
		UpdateDamaged(DeltaTime);
		break;
	default:
		break;
	}
}

void UEnemyFSM::ChangeState(EEnemyState s)
{
	// �ٲ�� ���¸� �������
	UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EEnemyState"), true);
	if (enumPtr != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s -------> %s"),
			*enumPtr->GetNameStringByIndex((int32)currState),
			*enumPtr->GetNameStringByIndex((int32)s));
	}	

	// ���� ���¸� ����
	currState = s;

	// �ִϸ��̼� ���� ����
	anim->state = currState;
	
	// ���� �ð��� �ʱ�ȭ
	currTime = 0;

	switch (currState)
	{
	case EEnemyState::IDLE:

		break;
	case EEnemyState::MOVE:

		break;
	case EEnemyState::ATTACK:
	{
		// �ٷ� ���� �����ϰ� ����ð��� attackDelayTime ���� ����
		currTime = attackDelayTime;
		// ű, ��ġ �������� ����
		int32 rand = FMath::RandRange(0, 1);
		anim->attackType = (EAttackType)rand;
	}
		break;
	case EEnemyState::DIE:
		myActor->Destroy();
		break;
	default:
		break;
	}
}

void UEnemyFSM::UpdateIdle()
{
	// 1. �÷��̾���� �Ÿ��� ������.
	FVector dir = target->GetActorLocation() - myActor->GetActorLocation();
	float dist = dir.Length();
	// 2. ���࿡ �Ÿ��� �������� ���� ������ (�÷��̾ �Ѿư� �� �ִ� ����)
	if (dist < traceRange)
	{
		// 3. ���� ���¸� MOVE �� �ٲ���
		ChangeState(EEnemyState::MOVE);
	}
}

void UEnemyFSM::UpdateMove()
{
	// 1. �÷��̾ ���ϴ� ������ ������
	FVector dir = target->GetActorLocation() - myActor->GetActorLocation();
	
	// 2. �� �������� ��������. 
	myActor->AddMovementInput(dir.GetSafeNormal());

	// 3. �÷��̾���� �Ÿ��� ���� �������� ������
	float dist = dir.Length();
	if (dist < attackRange)
	{
		// 4. ���� ���¸� ATTACK �� �ٲ���
		ChangeState(EEnemyState::ATTACK);	
	}	
}

void UEnemyFSM::UpdateAttack()
{
	ChangeState(EEnemyState::ATTACK_DELAY);
}

void UEnemyFSM::UpdateAttackDelay()
{
	// 1. �ð��� �帣�� �Ѵ�.
	currTime += GetWorld()->DeltaTimeSeconds;
	// 2. ���࿡ Attack Delay �ð��� ������
	if (currTime > attackDelayTime)
	{
		// �÷������ �Ÿ�
		float dist = FVector::Distance(target->GetActorLocation(), myActor->GetActorLocation());
		// �� �Ÿ��� ���ݹ���- > ��¥ ����
		if (dist < attackRange)
		{
			// 3. ���� ���·� ����
			ChangeState(EEnemyState::ATTACK);
		}
		// �������� -> �̵� 
		else if (dist < traceRange)
		{
			ChangeState(EEnemyState::MOVE);
		}
		// �� �ܴ� -> ���
		else
		{
			ChangeState(EEnemyState::IDLE);
		}

		// 4. ����ð� �ʱ�ȭ
		currTime = 0;
	}
}

void UEnemyFSM::UpdateDamaged(float deltaTime)
{
	// damageDelayTime ��ٷȴٰ�
	currTime += deltaTime;
	if (currTime > damageDelayTime)
	{
		// IDLE ���·� ��ȯ
		ChangeState(EEnemyState::IDLE);
	}
}

