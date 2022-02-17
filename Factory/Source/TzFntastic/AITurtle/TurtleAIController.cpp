#include "TurtleAIController.h"

#include "Components/AudioComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnitConversion.h"
#include "Particles/ParticleSystemComponent.h"
#include "TzFntastic/Turtle/Turtle.h"

ATurtleAIController::ATurtleAIController()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

void ATurtleAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATurtleAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(Turtle != nullptr)
	{
		if(Turtle->NumTurtle == 1)
		{
			if(PatrolNum != 0)
			{
				ProccessMovement();
			}
		}
		if(Turtle->NumTurtle == 2)
		{
			if(PatrolNum != 0)
			{
				if(!IsPause)
				{
					ProccessMovement();
				}
			}
		}
		if(Turtle->NumTurtle == 3)
		{
			if(PatrolNum != 0)
			{
				 if(!IsBack)
				 {
				 	ProccessMovement();
				 }
				 else if (IsBack)
				 {
				 	Turtle->ProccesMovementBack(DeltaSeconds);;
				 }
			}
			
		}
		if(PatrolNum == 0)
		{
			if(!IsFinish)
			{
				FinishWalk();
			}
		}
	}
		
}

void ATurtleAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	Turtle = GetPawn<ATurtle>();
	PatrolNum = Turtle->PatrolPoints.Num();
	if(Turtle->NumTurtle == 2||Turtle->NumTurtle == 3)
	{
		if(PatrolNum != 0)
		{
			GetWorldTimerManager().SetTimer(TimerHandle, this, &ATurtleAIController::PausedFalse,TurtleWait,false, 0.f);
		}
	}
}


void ATurtleAIController::ProccessMovement()
{
	if(Turtle->PatrolPoints.Num() == 0)
	{
		return;
	}

	auto PatrolPoint = Turtle->PatrolPoints[CurrentPatrolPointIndex];
	auto Deltatime = GetWorld()->GetDeltaSeconds();
	auto TargetRotation = UKismetMathLibrary::FindLookAtRotation(Turtle->GetActorLocation(), PatrolPoint->GetActorLocation());
	Turtle->ProccesRotation(Deltatime, TargetRotation);

	if(FMath::IsNearlyEqual(Turtle->GetActorRotation().Yaw,TargetRotation.Yaw, 2.f))
	{
		Turtle->ProccesMovement(Deltatime);
		Turtle->WalkParticle->Activate();
		Turtle->WalkAudio->Activate();

		if(FVector::DistSquared2D(Turtle->GetActorLocation(), PatrolPoint->GetActorLocation()) <= MovementAcceptRadius * MovementAcceptRadius)
		{
			CurrentPatrolPointIndex++;
			PatrolNum--;
			if(!Turtle->PatrolPoints.IsValidIndex(CurrentPatrolPointIndex))
			{
				CurrentPatrolPointIndex = 0;
			}
		}
	}
}

void ATurtleAIController::PausedFalse()
{
	if(PatrolNum == 0)
	{
		return;
	}
	if(Turtle->NumTurtle == 2)
	{
		if(IsPause)
		{
			IsPause = false;
		}
	}
	if(Turtle->NumTurtle == 3)
	{
		if(IsBack)
		{
			IsBack = false;
		}
	}
	GetWorldTimerManager().ClearTimer(TimerHandle);
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATurtleAIController::PausedTrue,TurtleWait,false, 1.f);
}

void ATurtleAIController::PausedTrue()
{
	if(PatrolNum == 0)
	{
		return;
	}
	if(Turtle->NumTurtle == 2)
	{
		if(!IsPause)
		{
			IsPause = true;
		}
	}
	if(Turtle->NumTurtle == 3)
	{
		if(!IsBack)
		{
			IsBack = true;
		}
	}
	GetWorldTimerManager().ClearTimer(TimerHandle);
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATurtleAIController::PausedFalse,TurtleWait,false, 0.5f);
}

void ATurtleAIController::FinishWalk()
{
	Turtle->WalkParticle->Complete();
	Turtle->FinishParticle->Activate();
	Turtle->FinishAudio->Activate();
	Turtle->BodyMesh->Stop();
	IsFinish = true;
}

