#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Turtle.generated.h"

UCLASS()
class TZFNTASTIC_API ATurtle : public APawn
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USceneComponent* SceneComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USkeletalMeshComponent* BodyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UParticleSystemComponent* SpawnParticle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UAudioComponent*  SpawnAudio;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UParticleSystemComponent* WalkParticle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UAudioComponent*  WalkAudio;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UParticleSystemComponent* FinishParticle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UAudioComponent*  FinishAudio;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> PatrolPoints;

	UPROPERTY(EditAnywhere)
	int NumTurtle = 1;
	
public:	
	ATurtle();
	virtual void Tick(float DeltaTime) override;
	void ProccesMovement(float DeltaTime ,float MovementScale = 1.f);
	void ProccesRotation(float DeltaTime ,const FRotator& TargetRotation);
	void ProccesMovementBack(float DeltaTime ,float MovementScale = 1.f);
protected:
	
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	float MoveSpeed = 100.f;
	UPROPERTY(EditAnywhere)
	float RotationSpeed = 100.f;
};
