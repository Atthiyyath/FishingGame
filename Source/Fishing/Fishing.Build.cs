// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Fishing : ModuleRules
{
	public Fishing(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput", "Water", "FCTween" });
    }
}
