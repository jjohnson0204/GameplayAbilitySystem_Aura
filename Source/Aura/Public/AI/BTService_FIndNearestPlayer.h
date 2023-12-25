// Copyright Light!!!!

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "BTService_FIndNearestPlayer.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UBTService_FIndNearestPlayer : public UBTService_BlueprintBase
{
	GENERATED_BODY()


protected:

	virtual void TickNode(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory,
		float DeltaSeconds
		) override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FBlackboardKeySelector TargetToFollowSelector;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FBlackboardKeySelector DistanceToTargetSelector;
};
