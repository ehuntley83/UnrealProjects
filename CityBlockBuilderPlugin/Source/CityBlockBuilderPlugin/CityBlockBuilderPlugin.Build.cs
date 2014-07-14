using UnrealBuildTool;

public class CityBlockBuilderPlugin : ModuleRules
{
    public CityBlockBuilderPlugin(TargetInfo target)
    {
        PrivateIncludePaths.AddRange(new[] { "CityBlockBuilderPlugin/Private" });

        PrivateDependencyModuleNames.AddRange(
            new[] 
            {
                "Engine",
                "UnrealEd",
                "InputCore",
                "Core",
                "Slate",
                "SlateCore",
                "EditorStyle",
                "CoreUObject",
                "LevelEditor"
            });
    }
}