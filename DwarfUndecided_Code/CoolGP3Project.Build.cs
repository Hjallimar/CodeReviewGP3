// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CoolGP3Project : ModuleRules
{
	public CoolGP3Project(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG", "Slate", "SlateCore" });

		PublicIncludePaths.Add("CoolGP3Project");
	}
}
