#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CreateTurtleButtons.generated.h"

UCLASS()
class TZFNTASTIC_API UCreateTurtleButtons : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
};
