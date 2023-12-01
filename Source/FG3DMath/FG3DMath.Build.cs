// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FG3DMath : ModuleRules
{
	public FG3DMath(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}
