#pragma once

#include "CoreMinimal.h"
#include "MyUserWidget.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

UCLASS()
class STRATEGY_API AMyHUD : public AHUD
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> Widget;

public:
	UMyUserWidget* MyUserWidget{};
};
