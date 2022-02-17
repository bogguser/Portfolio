#include "Turtle.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"

ATurtle::ATurtle()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	BodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>("BodyMesh");
	BodyMesh->SetupAttachment(GetRootComponent());

	SpawnParticle = CreateDefaultSubobject<UParticleSystemComponent>("SpawnParticle");
	SpawnParticle->SetupAttachment(BodyMesh);

	SpawnAudio = CreateDefaultSubobject<UAudioComponent>("SpawnAudio");
	SpawnAudio->SetupAttachment(SpawnParticle);

	WalkParticle = CreateDefaultSubobject<UParticleSystemComponent>("WalkParticle");
	WalkParticle->SetupAttachment(BodyMesh);

	WalkAudio = CreateDefaultSubobject<UAudioComponent>("WalkAudio");
	WalkAudio->SetupAttachment(WalkParticle);

	FinishParticle = CreateDefaultSubobject<UParticleSystemComponent>("FinishParticle");
	FinishParticle->SetupAttachment(BodyMesh);

	FinishAudio = CreateDefaultSubobject<UAudioComponent>("FinishAudio");
	FinishAudio->SetupAttachment(FinishParticle);

}

void ATurtle::ProccesMovement(float DeltaTime, float MovementScale)
{
	FVector CurrentLocationForward = GetActorLocation();
	FVector ForwardVectorForward = GetActorForwardVector();
	FVector NewLocationForward = CurrentLocationForward + ForwardVectorForward * MoveSpeed * MovementScale * DeltaTime;
	SetActorLocation(NewLocationForward);
}

void ATurtle::ProccesRotation(float DeltaTime, const FRotator& TargetRotation)
{
	FRotator NewRotation = FMath::RInterpConstantTo(GetActorRotation(), TargetRotation,DeltaTime, RotationSpeed);
	NewRotation.Pitch = GetActorRotation().Pitch;
	NewRotation.Roll = GetActorRotation().Roll;
	SetActorRotation(NewRotation);
}

void ATurtle::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATurtle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATurtle::ProccesMovementBack(float DeltaTime, float MovementScale)
{
	FVector CurrentLocationForward = GetActorLocation();
	FVector ForwardVectorForward = GetActorForwardVector();
	FVector NewLocationForward = CurrentLocationForward - ForwardVectorForward * MoveSpeed * MovementScale * DeltaTime;
	SetActorLocation(NewLocationForward);
}

