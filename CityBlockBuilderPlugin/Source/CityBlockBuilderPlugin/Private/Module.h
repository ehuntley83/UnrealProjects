#pragma once

DECLARE_LOG_CATEGORY_EXTERN(ModuleLog, Log, All)

class Module : public IModuleInterface
{
private:
    void CreateWindowMenu(FMenuBuilder& menuBuilder);
    void OpenPluginWindow();
    TSharedRef<SDockTab> CreateTab(const FSpawnTabArgs& args);

public:
    Module();

    virtual void StartupModule() OVERRIDE;
    virtual void ShutdownModule() OVERRIDE;
};