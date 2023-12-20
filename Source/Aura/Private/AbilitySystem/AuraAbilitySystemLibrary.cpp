// Copyright Light!!!!


#include "AbilitySystem/AuraAbilitySystemLibrary.h"

#include "AbilitySystemComponent.h"
#include "Game/AuraGameModeBase.h"
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

UAttributeMenuWidgetController* UAuraAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
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
			return AuraHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

void UAuraAbilitySystemLibrary::InitializeDefaultAttributes(
	const UObject* WorldContextObject,
	ECharacterClass CharacterClass,
	float Level,
	UAbilitySystemComponent* ASC)
{
	const AAuraGameModeBase* AuraGameMode = Cast<AAuraGameModeBase>(
		UGameplayStatics::GetGameMode(WorldContextObject)
	);
	if (AuraGameMode == nullptr) return;

	AActor* AvatarActor = ASC->GetAvatarActor();
	
	UCharacterClassInfo* CharacterClassInfo = AuraGameMode->CharacterClassInfo;
	const FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

	//Primary
	FGameplayEffectContextHandle PrimaryAttributesContextHandle	= ASC->MakeEffectContext();
	PrimaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(
		ClassDefaultInfo.PrimaryAttributes,
		Level,
		PrimaryAttributesContextHandle
	);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());

	//Secondary
	FGameplayEffectContextHandle SecondaryAttributesContextHandle	= ASC->MakeEffectContext();
	SecondaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(
		CharacterClassInfo->SecondaryAttributes,
		Level,
		SecondaryAttributesContextHandle
	);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpecHandle.Data.Get());

	//Vital
	FGameplayEffectContextHandle VitalAttributesContextHandle	= ASC->MakeEffectContext();
	VitalAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle VitalAttributesSpecHandle = ASC->MakeOutgoingSpec(
		CharacterClassInfo->VitalAttributes,
		Level,
		VitalAttributesContextHandle
	);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributesSpecHandle.Data.Get());
}
