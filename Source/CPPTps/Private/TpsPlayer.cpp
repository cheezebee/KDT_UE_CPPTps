// Fill out your copyright notice in the Description page of Project Settings.


#include "TpsPlayer.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Kismet/GameplayStatics.h>
#include <InputMappingContext.h>
#include <InputAction.h>
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>

// Sets default values
ATpsPlayer::ATpsPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// imc default ���� �о����
	ConstructorHelpers::FObjectFinder<UInputMappingContext> tempImc(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMC_Default.IMC_Default'"));
	if (tempImc.Succeeded())
	{
		imcDefault = tempImc.Object;
	}

	// ia_jump ���� �о����
	ConstructorHelpers::FObjectFinder<UInputAction> tempIAJump(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Jump.IA_Jump'"));
	if (tempIAJump.Succeeded())
	{
		ia_Jump = tempIAJump.Object;
	}

	// Skeletal Mesh �о����
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin'"));
	
	if (tempMesh.Succeeded())
	{
		// Mesh �� Skeletal Mesh ����
		//USkeletalMeshComponent* mesh = GetMesh();
		GetMesh()->SetSkeletalMesh(tempMesh.Object);
	}

	// Mesh �� ��ġ ���� ȸ������ ����
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));	
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0)); // Pitch, Yaw, Roll

	//Spring Arm ������Ʈ ����
	arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("ARM"));
	// arm �� rootComponent �� �ڽ�
	arm->SetupAttachment(RootComponent);
	// arm ��ġ�� �ٲ���
	arm->SetRelativeLocation(FVector(0, 70, 90));

	// Camera ������Ʈ ����
	cam = CreateDefaultSubobject<UCameraComponent>(TEXT("CAM"));
	// cam �� arm �� �ڽ����� ����
	cam->SetupAttachment(arm);
}

// Called when the game starts or when spawned
void ATpsPlayer::BeginPlay()
{
	Super::BeginPlay();

	// �����̴� �ӷ��� moveSpeed �� ����
	GetCharacterMovement()->MaxWalkSpeed = moveSpeed;

	// Controller �� ȸ������ ���� ���� ����
	bUseControllerRotationYaw = true;
	arm->bUsePawnControlRotation = true;

	// ī�޶� ��/�� ȸ���� �� ���� (min, max ����)
	APlayerController* playerCon = GetWorld()->GetFirstPlayerController();
	playerCon->PlayerCameraManager->ViewPitchMin = -60;
	playerCon->PlayerCameraManager->ViewPitchMax = 60;

	/*APlayerCameraManager* camManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	camManager->ViewPitchMin = -60;
	camManager->ViewPitchMax = 60;*/

	// ���� Ƚ�� ����
	JumpMaxCount = 3;

	// APlayerController ��������
	APlayerController* playerController = Cast<APlayerController>(GetController());
	//subSystem �� ��������	
	auto subSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());
	// imcDefault �߰� ����
	subSystem->AddMappingContext(imcDefault, 0);
}

// Called every frame
void ATpsPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
		
	MoveAction();

	// RotateAction();	
}

// Called to bind functionality to input
void ATpsPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (input)
	{
		input->BindAction(ia_Jump, ETriggerEvent::Started, this, &ATpsPlayer::EnhancedJump);
	}

	
	// A, D
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &ATpsPlayer::InputHorizontal);

	// W, S
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &ATpsPlayer::InputVertical);

	// ���콺 �¿� ������ �� 
	PlayerInputComponent->BindAxis(TEXT("MouseX"), this, &ATpsPlayer::InputMouseX);
	// ���콺 ���� ������ ��
	PlayerInputComponent->BindAxis(TEXT("MouseY"), this, &ATpsPlayer::InputMouseY);

	// �����̽��� ������ �� 
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ATpsPlayer::InputJump);
}

void ATpsPlayer::MoveAction()
{
	//// p = p0 + vt
	//FVector p0 = GetActorLocation();
	//FVector dir = GetActorRightVector() * moveInput.Y +
	//	GetActorForwardVector() * moveInput.X;
	//// dir �� ũ�⸦ 1�� �����.
	//dir.Normalize();
	//// vt ��ŭ ��������
	//FVector vt = dir * moveSpeed * DeltaTime;
	//// ���� �̵��ؾ� �ϴ� ��ġ
	//FVector p = p0 + vt;
	//SetActorLocation(p);

	FVector dir = GetActorRightVector() * moveInput.Y +
		GetActorForwardVector() * moveInput.X;
	// dir �� ũ�⸦ 1�� �����.
	dir.Normalize();

	// dir �������� ��������
	AddMovementInput(dir);
}

void ATpsPlayer::RotateAction()
{
	// ���� ȸ�� yaw (z��) �� ����
	SetActorRotation(FRotator(0, mx, 0));
	// spring arm �� ȸ�� pitch (y��) �� ����
	arm->SetRelativeRotation(FRotator(my, 0, 0));
}

void ATpsPlayer::InputHorizontal(float value)
{
	moveInput.Y = value;
}

void ATpsPlayer::InputVertical(float value)
{
	moveInput.X = value;
}

void ATpsPlayer::InputMouseX(float value)
{
	AddControllerYawInput(value);

	// ��, �� ȸ���ϴ� ���� ����
	//mx += value;

}

void ATpsPlayer::InputMouseY(float value)
{
	AddControllerPitchInput(value);
	// ��, �� ȸ���ϴ� ���� ����
	//my += value;
}

void ATpsPlayer::InputJump()
{
	//Jump();
}

void ATpsPlayer::EnhancedJump()
{
	Jump();
}

