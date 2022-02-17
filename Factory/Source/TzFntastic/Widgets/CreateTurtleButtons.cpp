#include "CreateTurtleButtons.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

void UCreateTurtleButtons::NativeConstruct()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(),0);
	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PC, this, EMouseLockMode::LockAlways);
	PC->bShowMouseCursor = true;
}


