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
	//SpawnPos 들을 찾아오자
	//UGameplayStatics 인클루드
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),AActor::StaticClass(), tempActor);
	//
	for(int32 i = 0; i < tempActor.Num(); i++)
	{ 
		/*if (tempActor[i]->GetName().Contains(TEXT("Spawn")) == false)continue;
		allSpawnPos.Add(tempActor[i]);*/

		
		// 만약에 이름에 Spawn이 포함되어 있다면
		if(tempActor[i]->GetActorLabel().Contains(TEXT("Spawn")))
		{
			// allSpawnPos에 추가하자
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
		//에너니 생성 (위치 ; spawn pos 중에 하나)
		//인클루드
		//int32 rand = FMath::RandRange(0,allSpawnPos.Num()-1);
		GetWorld()->SpawnActor<AEnemy>
		(enemyFactory, 
		allSpawnPos[spawnIdx]->GetActorLocation(),
		FRotator());
	}

	//첫번째 스폰 방법
	spawnIdx++;
	if (spawnIdx == allSpawnPos.Num())
	{
		spawnIdx = 0;
	}

	//두번째 스폰 방법
	//spawnIdx++;
	//spawnIdx %= allSpawnPos.Num();
	//세번째 스폰 방법
	//spawnIdx = (spawnIdx +1) % allSpawnPos.Num();
	
	//현재시간 초기화
	currTime = 0;
}

