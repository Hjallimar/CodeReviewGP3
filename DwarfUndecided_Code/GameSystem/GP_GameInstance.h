// (C) 2021 Changemaker Educations (FG20FT GP3 Team 8) - All Rights Reserved.

// AUTHOR: Justus Hörberg

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameSystem/GameSettings.h"
#include "GP_GameInstance.generated.h"

#pragma region Scrapped1
///* This enum denotes the stage of the game the player is currently at. */
//UENUM()
//enum EGameActProgression
//{
//	StartOfGame = 0, // The very first stage the game is in when the map loads. (Player cannot open shop)
//	FollowingMomsNote, // The tutorial stage (the prologue). (Player cannot open shop)
//
//	// All chapters work similarly to each other, in how work days play out and whatnot. What differs is the type of events that occur, or if there's a storyline that's supposed to take place, etc.
//	Chapter1, // The first chapter of the game.
//
//	FinalChapter, // The final chapter of the game. (Is called "FINAL"Chapter as an abstract capper in case we don't know how many chapters there will be.)
//
//	MAX // IS NOT USED FOR STORY PROGRESSION!!! Serves only as a bound-definition for iterators.
//};
//
///* This enum denotes the substage of a game act - not every GameActProgression has to follow this formula, but still there regardless. */
//UENUM()
//enum EGameSubActProgression
//{
//	PreWorkDay = 0, // The state at which the player starts the day. 
//	WorkDay,
//	PostWorkDay,
//
//	SUBMAX // IS NOT USED FOR SUB-STORY PROGRESSION!!! Serves only as a bound-definition for iterators.
//};
//
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameActChanged, EGameActProgression, CurrentAct);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGameSubActChanged, EGameSubActProgression, CurrentSubAct, EGameActProgression, CurrentAct);
#pragma endregion

/**
 * 
 */
UCLASS()
class COOLGP3PROJECT_API UGP_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UGP_GameInstance();
	virtual void Init() override;

	virtual void LoadComplete(const float LoadTime, const FString& MapName) override;

	// :)
	UPROPERTY()
	bool bHardMode = false;

	const float HardModeMinTime = 25.f;
	const float HardModeMaxTime = 35.f;

protected:

	UPROPERTY()
	/* The settings for this game. */
	FGameSettings GameSettings;

public:
	/* Returns a const pointer to the game settings contained by this GameInstance. Used for retrieving values without creating new structs. */
	const FGameSettings* const GetGameSettings() const { return &GameSettings; }

	FGameSettings GetCurrentGameSettings() const;
	void SetGameSettings(const FGameSettings& NewSettings);
	void SetMouseSense(float Value);



#pragma region Scrapped2
//	/* Sets the current act of the game. */
//	void SetGameAct(EGameActProgression NextAct);
//
//	/* Advances the game act to the next in the enum. */
//	void SetNextGameAct();
//
//	/* Sets the current act of the game. */
//	void SetGameSubAct(EGameSubActProgression NextSubAct);
//
//	/* Advances the game sub-act to the next in the enum. */
//	void SetNextGameSubAct();
//
//	/* Delegate that gets called everytime the game act changes. */
//	FOnGameActChanged OnGameActProgressed;
//
//	/* Delegate that gets called everytime the game sub-act changes. */
//	FOnGameSubActChanged OnGameSubActProgressed;
//
//protected:
//	/* The current game act. */
//	EGameActProgression CurrentAct;
//
//	/* The current game sub-act. */
//	EGameSubActProgression CurrentSubAct;
#pragma endregion
};
