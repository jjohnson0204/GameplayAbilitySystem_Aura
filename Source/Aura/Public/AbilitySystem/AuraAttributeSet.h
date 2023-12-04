// Copyright Light!!!!

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AuraAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UAuraAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Declare the variable
	// Health
	UPROPERTY(BlueprintReadOnly, Replicated = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health ;
	UPROPERTY(BlueprintReadOnly, Replicated = OnRep_MaxHealth, Category = "Vital Attributes")
	FGameplayAttributeData MaxHealth ;

	//Mana
	UPROPERTY(BlueprintReadOnly, Replicated = OnRep_Mana, Category = "Vital Attributes")
	FGameplayAttributeData Mana ;
	UPROPERTY(BlueprintReadOnly, Replicated = OnRep_MaxMana, Category = "Vital Attributes")
	FGameplayAttributeData MaxMana ;

	// Create RepNotify that excepts the old value
	//Health
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	//Mana
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
};
