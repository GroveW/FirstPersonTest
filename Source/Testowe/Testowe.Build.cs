// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Testowe : ModuleRules
{
	public Testowe(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
