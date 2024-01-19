// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Manager.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Engine/World.h>

// Sets default values
AEnemy_Manager::AEnemy_Manager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//
	ConstructorHelpers::FClassFinder<AEnemy>temp(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/BP_Enemy.BP_Enemy'"));
	if (temp.Succeeded())
	{
		enemyFactory = temp.Class;
	}
}

// Called when the game starts or when spawned
void AEnemy_Manager::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> tempActor;
	//SpawnPos ���� ã�ƿ���
	//UGameplayStatics ��Ŭ���
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),AActor::StaticClass(), tempActor);
	//
	for(int32 i = 0; i < tempActor.Num(); i++)
	{ 
		/*if (tempActor[i]->GetName().Contains(TEXT("Spawn")) == false)continue;
		allSpawnPos.Add(tempActor[i]);*/

		
		// ���࿡ �̸��� Spawn�� ���ԵǾ� �ִٸ�
		if(tempActor[i]->GetActorLabel().Contains(TEXT("Spawn")))
		{
			// allSpawnPos�� �߰�����
			allSpawnPos.Add(tempActor[i]);

		}
			
	}

	
}

// Called every frame
void AEnemy_Manager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	currTime += DeltaTime;
	if (currTime > createTime)
	{
		//���ʴ� ���� (��ġ ; spawn pos �߿� �ϳ�)
		//��Ŭ���
		//int32 rand = FMath::RandRange(0,allSpawnPos.Num()-1);
		GetWorld()->SpawnActor<AEnemy>
		(enemyFactory, 
		allSpawnPos[spawnIdx]->GetActorLocation(),
		FRotator());
	}

	//ù��° ���� ���
	spawnIdx++;
	if (spawnIdx == allSpawnPos.Num())
	{
		spawnIdx = 0;
	}

	//�ι�° ���� ���
	//spawnIdx++;
	//spawnIdx %= allSpawnPos.Num();
	//����° ���� ���
	//spawnIdx = (spawnIdx +1) % allSpawnPos.Num();
	
	//����ð� �ʱ�ȭ
	currTime = 0;
}

