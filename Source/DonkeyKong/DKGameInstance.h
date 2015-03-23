// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "DKGameInstance.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDKOnBothPlayersZeroLifes);

/**
 * 
 */
UCLASS()
class DONKEYKONG_API UDKGameInstance : public UGameInstance
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditAnywhere, Category = "Debug")
		bool bStartTwoPlayers;

	/* With how many lifes players will start. */
	UPROPERTY(EditAnywhere, Category = "Config")
		int32 StartingLifes;

	/* Name of starting level */
	UPROPERTY(EditAnywhere, Category = "Config")
		FName StartingLevel;

	/* Current count of players lifes. */
	UPROPERTY(BlueprintReadWrite, Category = "Player")
		TArray<int32> PlayerLifes;

	/* Level which player reached */
	UPROPERTY(BlueprintReadWrite, Category = "Player")
		TArray<FName> CurrentLevel;

	////////////////////////
	////Score

	/* Current Highest score. */
	UPROPERTY(BlueprintReadOnly, Category = "Score")
		int32 HighestScore;
	
	/* Total Score Accumulated during game duration. */
	UPROPERTY(BlueprintReadWrite, Category = "Score")
		TArray<int32> TotalGameScore;
	
	////Score
	////////////////////////

public:
	/* Called when both players are out of lifes. */
	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Game Events")
		FDKOnBothPlayersZeroLifes OnBothPlayersZeroLifes;

	/* Index of current player. */
	UPROPERTY(BlueprintReadOnly, Category = "Player Info")
		int32 CurrentPlayerIndex;

	/* Number of players in current game. EditAnywhere, for editor debug. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 PlayerNumber;
public:
	UDKGameInstance(const FObjectInitializer& ObjectInitializer);
	/** UGameInstance overrides - BEGIN */
	virtual void Init() override;
	/* UGameInstance overrides - END **/
	
	/* Adds score to current player. */
	void AddScore(int32 ScoreIn);
	
	/* 
		Subtracts one life, from current player. 
		return true if any lifes remain.
	*/
	void SubtractPlayerLife();

	inline int32 GetPlayerLifes(int32 PlayerIndex) { return PlayerLifes[CurrentPlayerIndex]; }
	
	/* Resets game instance to default values */
	void ResetCurrentGame();

	/* Checks if any player have any lifes remaining */
	bool AreAnyLifesRemaining();

	/* Starts game with only one player */
	UFUNCTION(BlueprintCallable, Category = "Player")
		void StartOnePlayer();

	/* Starts game with two players */
	UFUNCTION(BlueprintCallable, Category = "Player")
		void StartTwoPlayers();

	/* Called to create new game from either StartOnePlayer or StartTwoPlayers */
	void CreateGame();
};
