#include "CityBlockBuilderPluginPch.h"
#include "Module.h"
#include "CityBlockBuilderWindow.h"

IMPLEMENT_MODULE(Module, CityBlockBuilderPlugin);
DEFINE_LOG_CATEGORY(ModuleLog)

#define LOCTEXT_NAMESPACE "CityBlockBuilderPlugin"

const FName CityBlockBuilderWindowTabName(TEXT("CityBlockBuilderWindowTab"));

Module::Module()
{
}

void Module::StartupModule()
{
    // Consider the Extender to be a way to "batch" changes to the Unreal Engine UI
    TSharedPtr<FExtender> extender = MakeShareable(new FExtender);

    // We want to extend the Menu which contains the WindowLocalTabSpawners subsection
    extender->AddMenuExtension(
        "WindowLocalTabSpawners", 
        EExtensionHook::After,          // Call our extension delegate after the menu loads
        NULL, 
        FMenuExtensionDelegate::CreateRaw(this, &Module::CreateWindowMenu));

    // Get a reference to the level editor and add the extender
    FLevelEditorModule& levelEditor = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
    levelEditor.GetMenuExtensibilityManager()->AddExtender(extender);

    // Register our tab with the Global Tab Manager by providing a logical name and creation delegate
    // The Global Tab Manager contains the level editor itself as well. Technically, the editor's tab manager
    // is not completely instantiated at the point that modules are able to be loaded which is why we
    // have to create our tab as a Global child.
    // A future release of Unreal will allow a hook into the instantiated editor tab manager
    FGlobalTabmanager::Get()->RegisterTabSpawner(CityBlockBuilderWindowTabName, FOnSpawnTab::CreateRaw(this, &Module::CreateTab))
        .SetDisplayName(FText::FromString(TEXT("City Block Builder Window")));
}

void Module::ShutdownModule()
{

}

void Module::CreateWindowMenu(FMenuBuilder& menuBuilder)
{
    menuBuilder.AddMenuEntry(
        LOCTEXT("OpenWindow", "City Block Builder Window"),
        LOCTEXT("OpenWindowToolTip", "Opens the City Block Builder Window"),
        FSlateIcon(),
        FUIAction(FExecuteAction::CreateRaw(this, &Module::OpenPluginWindow))
        );
}

void Module::OpenPluginWindow()
{
    FGlobalTabmanager::Get()->InvokeTab(CityBlockBuilderWindowTabName);
}

TSharedRef<SDockTab> Module::CreateTab(const FSpawnTabArgs& args)
{
    // The Slate UI system uses operator overloading liberally
    //  Chained method invocations indicate setting properties on the parent Slate object
    //  Square brackets indicate child Slate objects
    return 
        SNew(SDockTab)
        .Label(LOCTEXT("TabTitle", "City Block Builder Window"))
        .TabRole(ETabRole::MajorTab)
        .ContentPadding(5)
        [
            SNew(SBorder)
            .Padding(4)
            .BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
            [
                SNew(CityBlockBuilderWindow)
            ]
        ];
}