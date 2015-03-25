// Copyright 1998-2015 Nishant Naveen. All Rights Reserved.
namespace UnrealBuildTool.Rules
{
	public class TextRenderPlugin : ModuleRules
	{
        public TextRenderPlugin(TargetInfo Target)
		{
			PublicIncludePaths.AddRange
            (
				new string[] 
                {
                    "TextRenderPlugin/Public",					
				}
            );

			PrivateIncludePaths.AddRange
            (
				new string[] 
                {
                    "TextRenderPlugin/Private",				
				}                
            );

            PublicDependencyModuleNames.AddRange(
                new string[]
				{
					"Core",
					"CoreUObject",
                    "Engine",
                    "InputCore",
				}
            );

			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
                    "Slate"
				});

			//DynamicallyLoadedModuleNames.AddRange(
			//	new string[]
			//	{
			//	});
		}
	}
}