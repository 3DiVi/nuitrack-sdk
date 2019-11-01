// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class Nuitrack: ModuleRules
{
	public Nuitrack(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

		string LibraryPath = ModuleDirectory + "/Nuitrack";

		PublicIncludePaths.Add(LibraryPath + "/include");
		
		Definitions.Add("NUITRACK_NO_EXCEPTIONS");
		
		if (Target.Platform == UnrealTargetPlatform.Android)
		{
			string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
			AdditionalPropertiesForReceipt.Add(new ReceiptProperty("AndroidPlugin",
					Path.Combine(PluginPath, "VicoVR_APL.xml")));
            
			PublicLibraryPaths.Add(LibraryPath + "/lib/android");

			PublicAdditionalLibraries.Add("middleware");
			PublicAdditionalLibraries.Add("nuitrack");

			Definitions.Add("WITH_NUITRACK");
		}
	}
}
