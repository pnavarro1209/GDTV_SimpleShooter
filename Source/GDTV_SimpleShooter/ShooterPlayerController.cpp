// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void AShooterPlayerController::EndGameUI()
{
    StopMovement();

    UUserWidget* EndScreen = CreateWidget(this, EndScreenClass);

    EndScreen->AddToViewport();
}

void AShooterPlayerController::OpenHUD()
{
    HUDWidget = CreateWidget(this, HUDClass);

    if(HUDWidget != nullptr)
    {
        HUDWidget->AddToViewport();
    }
}

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    HUDWidget->RemoveFromViewport();
    
    if(bIsWinner)
    {
        UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
        
        if(WinScreen != nullptr)
        {
            WinScreen->AddToViewport();
        }
    }
    else
    {
        UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
        
        if(LoseScreen != nullptr)
        {
            LoseScreen->AddToViewport();
        }
    }

    GetWorldTimerManager().SetTimer(RestartTimer, this, &AShooterPlayerController::EndGameUI, RestartTime);
}

void AShooterPlayerController::BeginPlay()
{
    Super::BeginPlay();
}
