using UnrealBuildTool;
using System;
using System.IO;
using System.Collections.Generic;

public class NuitrackModule : ModuleRules
{
    public NuitrackModule(ReadOnlyTargetRules Target) : base(Target)
    {
        // We neeed to depend on Core in order to implement our game module in the next step
        PublicDependencyModuleNames.AddRange(new string[] { "Core" });
        bAddDefaultIncludePaths = false;

        string LibraryPath = ModuleDirectory + "/lib/";
        string LibraryPrefix = "";
        string LibraryExtension = "";

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            LibraryPath += "win64/";
            LibraryExtension = ".lib";
        }
        else if (Target.Platform == UnrealTargetPlatform.Win32)
        {
            LibraryPath += "win32/";
            LibraryExtension = ".lib";
        }
        else if (Target.Platform == UnrealTargetPlatform.Android)
        {
            PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
            LibraryPath += "android/"; // "android-arm64/"
            LibraryPrefix = "lib";
            LibraryExtension = ".so";

            PublicDefinitions.Add("NUITRACK_NO_EXCEPTIONS");

            string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
            AdditionalPropertiesForReceipt.Add(new ReceiptProperty("AndroidPlugin",
                    Path.Combine(PluginPath, "VicoVR_APL.xml")));
        }
        else
        {
            Console.Error.WriteLine("NuitrackModule does not support this target platform");
            Environment.Exit(1);
        }

        PublicIncludePaths.Add(ModuleDirectory + "/include");

        var Libraries = new List<string> { "middleware", "nuitrack" };
        foreach (string LibraryName in Libraries)
        {
            PublicAdditionalLibraries.Add(LibraryPath + LibraryPrefix + LibraryName + LibraryExtension);
        }
    }
}
