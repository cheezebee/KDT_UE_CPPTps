// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

#include "Components/SphereComponent.h"
#include <GameFramework/ProjectileMovementComponent.h>
#include <Kismet/KismetSystemLibrary.h>

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// �浹ü
	compSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SPHERE"));
	SetRootComponent(compSphere);
	compSphere->SetSphereRadius(13);
	compSphere->SetCollisionProfileName(TEXT("BlockAll"));

	// ���
	compMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	compMesh->SetupAttachment(RootComponent);
	compMesh->SetRelativeScale3D(FVector(0.26f));
	compMesh->SetCollisionProfileName(TEXT("NoCollision"));

	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (tempMesh.Succeeded())
	{
		compMesh->SetStaticMesh(tempMesh.Object);
	}

	ConstructorHelpers::FObjectFinder<UMaterial> tempMat(TEXT("/Script/Engine.Material'/Engine/EditorMaterials/Cascade/CASC_RenderNormal_MAT.CASC_RenderNormal_MAT'"));
	if (tempMat.Succeeded())
	{
		compMesh->SetMaterial(0, tempMat.Object);
	}

	// �߻�ü ������ �����ϴ� ������Ʈ
	compProjectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("PROJECTILE"));
	// ������ ������Ʈ ����
	compProjectile->SetUpdatedComponent(compSphere);
	// �ʱ� �ӷ�, �ִ� �ӷ�
	compProjectile->InitialSpeed = 1500;
	compProjectile->MaxSpeed = 1500;
	// ƨ��� �Ұ�����
	compProjectile->bShouldBounce = true;
	// �󸶳� �� ƨ��� �Ұ�����
	compProjectile->Bounciness = 0.6f;
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	 
	SetLifeSpan(2);

	//UKismetSystemLibrary::K2_SetTimer(this, TEXT("AutoDestroy"), 2, false);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	//// 1. �ð��� �帣�� ����
	//currTime += DeltaTime;
	//// 2. 2�ʰ� ������
	//if (currTime > 2)
	//{
	//	// 3. ���� �ı�����
	//	Destroy();
	//}
}

void ABullet::AutoDestroy()
{
	Destroy();
}

