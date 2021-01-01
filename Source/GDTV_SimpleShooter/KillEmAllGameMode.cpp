// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "ShooterAIController.h"
#include "GameFramework/Controller.h"

void AKillEmAllGameMode::PawnKilled(APawn* DeadPawn)
{
    Super::PawnKilled(DeadPawn);

    UE_LOG(LogTemp, Warning, TEXT("A Pawn is Dead!!!"));

    APlayerController* PlayerController = Cast<APlayerController>(DeadPawn->GetController());

    if(PlayerController != nullptr)
    {
        EndGame(false);
    }

    for(AShooterAIController* AIController : TActorRange<AShooterAIController>(GetWorld()))
    {
        if(!AIController->isDead())
        {
            return;
        }
    }

    EndGame(true);
   
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
    for(AShooterAIController* AIController : TActorRange<AShooterAIController>(GetWorld()))
    {
        if(!AIController->isDead())
        {
            AIController->GameEnded();
        }
    }
    
    for(AController* Controller : TActorRange<AController>(GetWorld()))
    {
        bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
    }
}
