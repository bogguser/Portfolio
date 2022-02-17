#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TzFntastic/Turtle/Turtle.h"
#include "TurtleFactory.generated.h"

UCLASS()
class TZFNTASTIC_API ATurtleFactory : public AActor
{
	GENERATED_BODY()
	
public:	
	ATurtleFactory();

	UFUNCTION(BlueprintCallable)
	void SpawnTurtle();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;
	
	UPROPERTY(VisibleAnywhere)
	class UArrowComponent* TurtleSpawnPoint;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATurtle> TurtleSpawnClass;

	UPROPERTY(EditInstanceOnly)
	TArray<AActor*> PatrolPoints;
};
