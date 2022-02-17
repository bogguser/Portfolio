
#include "TurtleFactory.h"

#include "Components/ArrowComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "TzFntastic/Turtle/Turtle.h"

ATurtleFactory::ATurtleFactory()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	SetRootComponent(MeshComponent);

	TurtleSpawnPoint = CreateDefaultSubobject<UArrowComponent>("TankSpawnPoint");
	TurtleSpawnPoint->SetupAttachment(GetRootComponent());

}

void ATurtleFactory::SpawnTurtle()
{
	if(TurtleSpawnClass == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ATurtleFactory::SpawnTurtle: TurtleSpawnClass != nullptr) !"));
		return;
	}
	const FTransform SpawnTransform(TurtleSpawnPoint->GetComponentRotation(),TurtleSpawnPoint->GetComponentLocation());
	auto NewTurtle = Cast<ATurtle>(UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), TurtleSpawnClass,SpawnTransform,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn, this));
 	
	NewTurtle->PatrolPoints = PatrolPoints;
	UGameplayStatics::FinishSpawningActor(NewTurtle, SpawnTransform);
	NewTurtle->SpawnParticle->Activate();
	NewTurtle->SpawnAudio->Activate();
}


void ATurtleFactory::BeginPlay()
{
	Super::BeginPlay();
	
}


