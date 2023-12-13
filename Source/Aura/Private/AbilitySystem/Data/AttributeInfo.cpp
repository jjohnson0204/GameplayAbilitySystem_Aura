// Copyright Light!!!!


#include "AbilitySystem/Data/AttributeInfo.h"

FAuraAttributeInfo UAttributeInfo::FindAttributeInfoForTag(
	const FGameplayTag& AttributeTag
	, bool bLogNotFound) const
{
	for (const FAuraAttributeInfo& Info : AttributeInformation)
	{
		if (Info.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return Info;
		}
	}

	// we never found the array
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error,
			TEXT("Can't find Info for the AttributeTag [%s] on AttributeInfo [%s]."),
			*AttributeTag.ToString(),
			*GetNameSafe(this)
		);
	}

	return FAuraAttributeInfo();
}
