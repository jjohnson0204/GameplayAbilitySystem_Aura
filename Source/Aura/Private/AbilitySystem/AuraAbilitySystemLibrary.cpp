// Copyright Light!!!!


#include "AbilitySystem/AuraAbilitySystemLibrary.h"

#include "AbilitySystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	//Get the widget controller and return to the caller
	//Call from within a widget
	//Get player controller
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		//Get the Hud
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(PC->GetHUD()))
		{
			//Access Player State
			AAuraPlayerState* PS = PC->GetPlayerState<AAuraPlayerState>();
			//Access Ability System Component
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			// Access Attribute Set
			UAttributeSet* AS = PS->GetAttributeSet();
			/**
			 * With the PC, PS, ASC and AS you have the Parms for FWidgetControllerParams
			 */
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			//return controller
			return AuraHUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}