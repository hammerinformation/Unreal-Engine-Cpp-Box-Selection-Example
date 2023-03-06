#include "MyHUD.h"

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();

	if (Widget)
	{
		MyUserWidget = CreateWidget<UMyUserWidget>(GetWorld(), Widget);

		if (MyUserWidget)
		{
			MyUserWidget->AddToViewport();
		}
	}
}
