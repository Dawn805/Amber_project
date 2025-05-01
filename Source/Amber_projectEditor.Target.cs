// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class Amber_projectEditorTarget : TargetRules
{
	public Amber_projectEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		bUseFastPDBLinking = false;
        	bUseAdaptiveUnityBuild = false;

		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_5;
		ExtraModuleNames.Add("Amber_project");
	}
}
