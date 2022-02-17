#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TzFntastic/Turtle/Turtle.h"
#include "TurtleAIController.generated.h"


UCLASS()
class TZFNTASTIC_API ATurtleAIController : public AAIController
{
	GENERATED_BODY()
public:
	ATurtleAIController();
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaSeconds) override;
public:
	void ProccessMovement();
	void PausedFalse();
	void PausedTrue();
	void FinishWalk();

protected:
	UPROPERTY()
	ATurtle* Turtle;

	UPROPERTY(EditAnywhere)
	float MovementAcceptRadius = 15.f;

	UPROPERTY(EditDefaultsOnly)
	float TurtleWait = 1.f;

	int32 CurrentPatrolPointIndex = 0;

	int32 PatrolNum;

private:
	FTimerHandle TimerHandle;
	bool IsPause = false;
	bool IsBack = false;
	bool IsFinish = false;
};



