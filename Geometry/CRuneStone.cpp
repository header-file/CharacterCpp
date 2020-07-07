#include "CRuneStone.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "DestructibleComponent.h"
#include "Components/BoxComponent.h"
#include "Classes/Materials/Material.h"
#include "Classes/Materials/MaterialInstanceDynamic.h"
#include "Player/CPlayer.h"

ACRuneStone::ACRuneStone()
{
 	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UDestructibleComponent>("Mesh");
	RootComponent = Mesh;

	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	Box->SetupAttachment(Mesh);

	ConstructorHelpers::FObjectFinder<UMaterial> material(L"Material'/Game/InfinityBladeIceLands/Environments/Ice/EX_Env_Ice_1/Materials/M_Rune_Stone_1.M_Rune_Stone_1'");
	if (material.Succeeded()) Material = material.Object;
}

void ACRuneStone::BeginPlay()
{
	Super::BeginPlay();
	
	bPurified = false;

	Box->OnComponentBeginOverlap.AddDynamic(this, &ACRuneStone::OnBeginOverlap);

	MaterialDynamic = UMaterialInstanceDynamic::Create(Material, this);
	for (int i = 0; i < Mesh->GetNumMaterials(); i++)
		Mesh->SetMaterial(i, MaterialDynamic);

	Player = Cast<ACPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void ACRuneStone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Player->GetCasting())
	{
		FLinearColor color;
		color.R = 1.0f;
		color.G = ColorChange;
		color.B = ColorChange;
		color.A = 1.0f;

		ColorChange += 0.002f;

		MaterialDynamic->SetVectorParameterValue("Temp", color);
	}

	if (ColorChange >= 1.0f)
		bPurified = true;
}

void ACRuneStone::OnBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
}

