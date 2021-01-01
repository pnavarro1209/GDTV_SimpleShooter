// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"


#include "ShooterCharacter.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AShooterAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

bool AShooterAIController::isDead() const
{
    AShooterCharacter* ControlledPawn = Cast<AShooterCharacter>(GetPawn());

    if(ControlledPawn != nullptr)
    {
        return ControlledPawn->IsDead();
    }
    else
    {
        return true;
    }
}

void AShooterAIController::GameEnded()
{
    if(EnemyAI != nullptr)
    {
        GetBlackboardComponent()->SetValueAsBool(TEXT("IsGameOver"), true);
    }
}

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();

    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if(EnemyAI != nullptr)
    {
        RunBehaviorTree(EnemyAI);
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
        GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
        GetBlackboardComponent()->ClearValue(TEXT("IsGameOver"));
    }
}


