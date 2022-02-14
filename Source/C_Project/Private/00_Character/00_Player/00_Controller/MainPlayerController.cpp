// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/00_Player/00_Controller/MainPlayerController.h"
#include "98_Widget/00_Player/MainWidget.h"
#include "00_Character/00_Player/PlayerCharacter.h"

void AMainPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	if (MainWidgetObject != nullptr)
	{
		MainWidget = CreateWidget<UMainWidget>(this, MainWidgetObject);
		if (MainWidget != nullptr)
		{
			MainWidget->AddToViewport();

			APlayerCharacter* player = Cast<APlayerCharacter>(aPawn);
			if (player != nullptr)
			{
				player->OnChangedHP.AddUniqueDynamic(MainWidget, &UMainWidget::UpdateHPPercent);
				player->OnChangedSP.AddUniqueDynamic(MainWidget, &UMainWidget::UpdateSPPercent);

				player->OnChangedHP.Broadcast(player->GetStatusComponent());
				player->OnChangedSP.Broadcast(player->GetStatusComponent());
			}

		}

		if (LockOnWidgetObject != nullptr)
		{
			LockOnWidget = CreateWidget<UUserWidget>(this, LockOnWidgetObject);
			if (LockOnWidget != nullptr)
			{
				LockOnWidget->SetDesiredSizeInViewport(FVector2D(50, 50));
				LockOnWidget->SetVisibility(ESlateVisibility::Hidden);
				LockOnWidget->AddToViewport();
			}
		}
	}
}
