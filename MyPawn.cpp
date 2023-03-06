#include "MyPawn.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MyHUD.h"
#include "Components/CanvasPanelSlot.h"
#include "Engine.h"


AMyHUD* Hud{};
UImage* MyImage{};
UCanvasPanelSlot* ImageSlot{};

AMyPawn::AMyPawn()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	Hud = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (Hud)
	{
		MyImage = Hud->MyUserWidget->MyImage;
		ImageSlot = Cast<UCanvasPanelSlot>(Hud->MyUserWidget->MyImage->Slot);
		MyImage->SetColorAndOpacity(FLinearColor(FVector4(0, 0, 0, .4f)));
	}
}


void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bMousePressed)
	{
		LastPos = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
		ImageSlot->SetSize(LastPos - FirstPos);
	}
}

void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindKey(EKeys::LeftMouseButton, IE_Pressed, this, &AMyPawn::MousePressed);
	PlayerInputComponent->BindKey(EKeys::LeftMouseButton, IE_Released, this, &AMyPawn::MouseReleased);
}

void AMyPawn::MousePressed()
{
	if (Hud)
	{
		bMousePressed = true;
		FirstPos = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
		ImageSlot->SetPosition(FirstPos);

		FHitResult HitResult;
		GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursorByChannel(
			ETraceTypeQuery::TraceTypeQuery1, false, HitResult);

		if (HitResult.bBlockingHit)
		{
			Point1 = HitResult.Location;
			FVector P = Point1;
			P.Z = 0;
			Point1 = P;
		}
	}
}


void AMyPawn::MouseReleased()
{
	if (Hud)
	{
		bMousePressed = false;
		FHitResult HitResult;
		GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursorByChannel(
			ETraceTypeQuery::TraceTypeQuery1, false, HitResult);

		if (HitResult.bBlockingHit)
		{
			Point4 = HitResult.Location;
			FVector P = Point4;
			P.Z = 0;
			Point4 = P;
		}
		Point2 = FVector(Point1.X, Point4.Y, 0);
		Point3 = FVector(Point4.X, Point1.Y, 0);


		ImageSlot->SetPosition(FVector2D::ZeroVector);
		ImageSlot->SetSize(FVector2D::ZeroVector);

		DrawDebugBox(GetWorld(), (Point1 + Point2 + Point3 + Point4) / 4.f,
		             FVector(FMath::Abs(Point1.X - Point3.X), FMath::Abs(Point3.Y - Point4.Y), 100) / 2.f,
		             FColor::Emerald, false, 3);
	}
}
