// Copyright Light!!!!


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"


AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraEffectActor::ApplyEffectToTarget(
	AActor* Target,
	TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* TargetAbilitySystemComponent =
		UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
	if (TargetAbilitySystemComponent == nullptr) return;

	check(GameplayEffectClass);
	/**
	 * Handle that wraps a FGameplayEffectContext or subclass,
	 * to allow it to be polymorphic and replicate properly
	 */
	FGameplayEffectContextHandle EffectContextHandle =
		TargetAbilitySystemComponent->MakeEffectContext();
	/** Sets the object this effect was created from. */
	EffectContextHandle.AddSourceObject(this);
	/** Allows blueprints to generate a GameplayEffectSpec
	 * once and then reference it by handle,
	 * to apply it multiple times/multiple targets. */
	FGameplayEffectSpecHandle EffectSpecHandle =
		TargetAbilitySystemComponent->MakeOutgoingSpec(
			GameplayEffectClass,
			1.f,
			EffectContextHandle
	);
	TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}
