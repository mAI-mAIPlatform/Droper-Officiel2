// Copyright (c) 2026 mCompany. All Rights Reserved.

using UnrealBuildTool;

public class Droper : ModuleRules
{
	public Droper(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"PhysicsCore",
			"ChaosVehicles",
			"Niagara",
			"UMG",
			"Slate",
			"SlateCore",
			"OnlineSubsystem",
			"OnlineSubsystemUtils",
			"AIModule",
			"GameplayTasks",
			"GameplayTags",
			"NavigationSystem",
			"NetCore"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"AnimGraphRuntime",
			"MediaAssets",
			"ReplicationGraph"
		});

		// Enable IWYU (Include-What-You-Use)
		bEnforceIWYU = true;

		// Multithreading & async loading support
		bUseUnity = false;
	}
}
