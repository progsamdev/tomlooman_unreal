using UnrealBuildTool;

public class Projectiles: ModuleRules
{
    public Projectiles(ReadOnlyTargetRules Target) : base(Target)
    {
        PrivateDependencyModuleNames.AddRange(new string[] {"Core", "CoreUObject", "Engine"});
    }
}
