#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemRow.generated.h"

USTRUCT(BlueprintType)
struct FItemIconRow : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* ItemIcon;
};
