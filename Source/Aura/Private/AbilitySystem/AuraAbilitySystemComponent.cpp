// Copyright Light!!!!


#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);
}

void UAuraAbilitySystemComponent::EffectApplied(
	UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayEffectSpec& EffectSpec,
	FActiveGameplayEffectHandle ActiveEffectHandle)
{
	//Broadcast the gameplay tag to the widget
	//Tag container
	FGameplayTagContainer TagContainer;
	//Get tag
	EffectSpec.GetAllAssetTags(TagContainer);
	//Broadcast to widget
	EffectAssetTags.Broadcast(TagContainer);
	
}
