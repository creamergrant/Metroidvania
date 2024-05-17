// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class M : ModuleRules
{
	public M(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Paper2D", "EnhancedInput" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        PrivateIncludePaths.Add("../Source/M/Actors");
        PrivateIncludePaths.Add("../Source/M/Character");
        PrivateIncludePaths.Add("../Source/M/CombatComponents");
        PrivateIncludePaths.Add("../Source/M/Equipables");
        PrivateIncludePaths.Add("../Source/M/GameMode");
        PrivateIncludePaths.Add("../Source/M/GameState");
        PrivateIncludePaths.Add("../Source/M/Interacts");
        PrivateIncludePaths.Add("../Source/M/Interfaces");
        PrivateIncludePaths.Add("../Source/M/MovementComponents");
        PrivateIncludePaths.Add("../Source/M/Pickups");
        PrivateIncludePaths.Add("../Source/M/PlayerController");
        PrivateIncludePaths.Add("../Source/M/PlayerState");
        PrivateIncludePaths.Add("../Source/M/SaveGame");

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
