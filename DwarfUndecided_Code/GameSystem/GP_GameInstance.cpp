// (C) 2021 Changemaker Educations (FG20FT GP3 Team 8) - All Rights Reserved.


#include "GameSystem/GP_GameInstance.h"


UGP_GameInstance::UGP_GameInstance()
{
}

void UGP_GameInstance::Init()
{
	// Super:: doesn't work...?
	UGameInstance::Init();

	//Gold = 0;
}

void UGP_GameInstance::SetMouseSense(float Value)
{
	GameSettings.MouseSensitivity = Value;
}

void UGP_GameInstance::LoadComplete(const float LoadTime, const FString& MapName)
{
	Super::LoadComplete(LoadTime, MapName);
}

FGameSettings UGP_GameInstance::GetCurrentGameSettings() const
{
	return GameSettings;
}

void UGP_GameInstance::SetGameSettings(const FGameSettings& NewSettings)
{
	GameSettings = NewSettings;
}



#pragma region Scrapped
//void UGP_GameInstance::SetGameAct(EGameActProgression NextAct)
//{
//	if (NextAct >= EGameActProgression::MAX)
//	{
//		NextAct = static_cast<EGameActProgression>((int)EGameActProgression::MAX - 1);
//	}
//
//	const EGameActProgression PrevAct = CurrentAct;
//
//	CurrentAct = NextAct;
//
//	// If value has changed, report that.
//	if (CurrentAct != PrevAct)
//		OnGameActProgressed.Broadcast(CurrentAct);
//}
//
//void UGP_GameInstance::SetNextGameAct()
//{
//	EGameActProgression Next;
//	const int IntCurrentAct = (int)CurrentAct;
//	// Just in case we SOMEHOW manage to go beyond the
//	// bounds of the enum. We don't want undefined behavior.
//	if (IntCurrentAct >= (int)EGameActProgression::MAX - 1)
//	{
//		Next = EGameActProgression::MAX;
//	}
//	else
//	{
//		Next = static_cast<EGameActProgression>(IntCurrentAct + 1);
//	}
//
//	SetGameAct(Next);
//}
//
//void UGP_GameInstance::SetGameSubAct(EGameSubActProgression NextSubAct)
//{
//	if (NextSubAct >= EGameSubActProgression::SUBMAX)
//	{
//		NextSubAct = static_cast<EGameSubActProgression>((int)EGameSubActProgression::SUBMAX - 1);
//	}
//
//	const EGameSubActProgression PrevSubAct = CurrentSubAct;
//
//	CurrentSubAct = NextSubAct;
//
//	// If value has changed, report that.
//	if (CurrentSubAct != PrevSubAct)
//		OnGameSubActProgressed.Broadcast(CurrentSubAct, CurrentAct);
//}
//
//void UGP_GameInstance::SetNextGameSubAct()
//{
//	EGameSubActProgression Next;
//	const int IntCurrentSubAct = (int)CurrentSubAct;
//	// Just in case we SOMEHOW manage to go beyond the
//	// bounds of the enum. We don't want undefined behavior.
//	if (IntCurrentSubAct >= (int)EGameActProgression::MAX - 1)
//	{
//		Next = EGameSubActProgression::SUBMAX;
//	}
//	else
//	{
//		Next = static_cast<EGameSubActProgression>(IntCurrentSubAct + 1);
//	}
//
//	SetGameSubAct(Next);
//}

//int UGP_GameInstance::GetGold() const
//{
//	return Gold;
//}
//
//void UGP_GameInstance::SetGold(int NewGoldValue)
//{
//	const int OldGoldValue = Gold;
//	
//	if (NewGoldValue < 0)
//		Gold = 0;
//	else
//		Gold = NewGoldValue;
//
//	if (OldGoldValue != Gold && OnGoldChangedDelegate.IsBound())
//		OnGoldChangedDelegate.Broadcast(OldGoldValue, Gold);
//}
//
//void UGP_GameInstance::AddGold(int AddGoldValue)
//{
//	SetGold(GetGold() + AddGoldValue);
//}
#pragma endregion