// Fill out your copyright notice in the Description page of Project Settings.


#include "ReferneceStudy.h"

// Sets default values
AReferneceStudy::AReferneceStudy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AReferneceStudy::BeginPlay()
{
	Super::BeginPlay();

	int32 number = 10;

	Test testClass;
	testClass.height = 180.0f;
	testClass.age = 27;


	int32 size = sizeof(testClass);

	ValueTypeFunc(testClass);
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay number : %d"), p);

	PointTypeFunc(&testClass);
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay number : %d"), number);

	ReferenceTypeFunc(testClass)
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay number : %d"), number);
}

// Called every frame
void AReferneceStudy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AReferneceStudy::ValueTypeFunc(int32 n, Test nt)
{
	n = 100;
	UE_LOG(LogTemp, Warning, TEXT("ValueTypeFunc n : %d"), n);

	t.age=50;
	t.height=200;
}

void AReferneceStudy::PointTypeFunc(int32 *p, Test* pt)

{
	*p= 200;
	UE_LOG(LogTemp, Warning, TEXT("ValueTypeFunc p : %d"), p);	//ÁÖ¼Ò°ª
	UE_LOG(LogTemp, Warning, TEXT("ValueTypeFunc *p : %d"), *p); //200

	pt->age = 10;
	pt->height = 220; 
}

void AReferneceStudy::ReferenceTypeFunc(int32& r, Test& rt)
{
	r=300;
	UE_LOG(LogTemp, Warning, TEXT("ReferenceTypeFunc r : %d"), r);	//
	UE_LOG(LogTemp, Warning, TEXT("ReferenceTypeFunc r : %d"), &r); //

	rt.age = 100;
	rt.height = 140;
}

