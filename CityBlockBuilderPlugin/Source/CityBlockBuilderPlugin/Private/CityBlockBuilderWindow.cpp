#include "CityBlockBuilderPluginPch.h"
#include "CityBlockBuilderWindow.h"

#define LOCTEXT_NAMESPACE "CityBlockBuilderPluginWindow"

CityBlockBuilderWindow::CityBlockBuilderWindow() :
_buildingsPerX(1),
_buildingsPerY(1),
_alleyWidth(100),
_heightPercent(50),
_minSizePercent(50),
_spacing(10),
_boundsActor(NULL)
{
}

void CityBlockBuilderWindow::Construct(const FArguments& args)
{
    TSharedRef<SVerticalBox> vertBox = SNew(SVerticalBox);

    ChildSlot
        [
            vertBox
        ];

    vertBox->AddSlot()
        .AutoHeight()
        [
            SNew(SHorizontalBox)
            + SHorizontalBox::Slot()
            .VAlign(VAlign_Center)
            [
                SNew(STextBlock).Text(this, &CityBlockBuilderWindow::GetBoundsActorName)
                .ColorAndOpacity(this, &CityBlockBuilderWindow::GetBoundsActorColorAndOpacity)
            ]
            + SHorizontalBox::Slot()
            .VAlign(VAlign_Center)
            [
                SAssignNew(_boundsActorDropdown, SComboButton)
                .ContentPadding(0)
                .ForegroundColor(this, &CityBlockBuilderWindow::GetBoundsActorForeground)
                .OnGetMenuContent(this, &CityBlockBuilderWindow::GetBoundsActorContent)
                .ButtonStyle(FEditorStyle::Get(), "ToggleButton")
                .ButtonContent()
                [
                    SNew(SHorizontalBox)
                    + SHorizontalBox::Slot()
                    .AutoWidth()
                    .VAlign(VAlign_Center)
                    [
                        SNew(SImage).Image(FEditorStyle::GetBrush("GenericViewButton"))
                    ]
                    + SHorizontalBox::Slot()
                    .VAlign(VAlign_Center)
                    .Padding(2, 0, 0, 0)
                    [
                        SNew(STextBlock).Text(this, &CityBlockBuilderWindow::GetBoundsActorName)
                    ]
                ]
            ]
        ];

    vertBox->AddSlot()
        .AutoHeight()
        [
            SNew(SHorizontalBox)
            + SHorizontalBox::Slot()
            .VAlign(VAlign_Center)
            [
                SNew(STextBlock).Text(LOCTEXT("BuildingXName", "Buildings X"))
            ]
            + SHorizontalBox::Slot()
            .VAlign(VAlign_Center)
            [
                SNew(SNumericEntryBox<int32>)
                .AllowSpin(true)
                .MinValue(1)
                .MaxValue(30)
                .MinSliderValue(1)
                .MaxSliderValue(30)
                .Value(this, &CityBlockBuilderWindow::GetBuildingsPerX)
                .OnValueChanged(this, &CityBlockBuilderWindow::BuildingsPerXChanged)
            ]
        ];

    vertBox->AddSlot()
        .AutoHeight()
        [
            SNew(SHorizontalBox)
            + SHorizontalBox::Slot()
            .VAlign(VAlign_Center)
            [
                SNew(STextBlock).Text(LOCTEXT("BuildingYName", "Buildings Y"))
            ]
            + SHorizontalBox::Slot()
            .VAlign(VAlign_Center)
            [
                SNew(SNumericEntryBox<int32>)
                .AllowSpin(true)
                .MinValue(1)
                .MaxValue(30)
                .MinSliderValue(1)
                .MaxSliderValue(30)
                .Value(this, &CityBlockBuilderWindow::GetBuildingsPerY)
                .OnValueChanged(this, &CityBlockBuilderWindow::BuildingsPerYChanged)
            ]
        ];

    vertBox->AddSlot()
        .AutoHeight()
        [
            SNew(SHorizontalBox)
            + SHorizontalBox::Slot()
            .VAlign(VAlign_Center)
            [
                SNew(STextBlock).Text(LOCTEXT("AlleyWidthName", "Alley Width"))
            ]
            + SHorizontalBox::Slot()
            .VAlign(VAlign_Center)
            [
                SNew(SNumericEntryBox<float>)
                .AllowSpin(true)
                .MinValue(1).MaxValue(1000)
                .MinSliderValue(1).MaxSliderValue(1000)
                .Value(this, &CityBlockBuilderWindow::GetAlleyWidth)
                .OnValueChanged(this, &CityBlockBuilderWindow::AlleyWidthChanged)
            ]
        ];

    vertBox->AddSlot()
        .AutoHeight()
        [
            SNew(SHorizontalBox)
            + SHorizontalBox::Slot()
            .VAlign(VAlign_Center)
            [
                SNew(STextBlock).Text(LOCTEXT("HeightPercentName", "Heignt Percent"))
            ]
            + SHorizontalBox::Slot()
            .VAlign(VAlign_Center)
            [
                SNew(SNumericEntryBox<float>)
                .AllowSpin(true)
                .MinValue(0).MaxValue(100)
                .MinSliderValue(0).MaxSliderValue(100)
                .Value(this, &CityBlockBuilderWindow::GetHeightPercent)
                .OnValueChanged(this, &CityBlockBuilderWindow::HeightPercentChanged)
            ]
        ];

    vertBox->AddSlot()
        .AutoHeight()
        [
            SNew(SHorizontalBox)
            + SHorizontalBox::Slot()
            .VAlign(VAlign_Center)
            [
                SNew(STextBlock).Text(LOCTEXT("MinSizePercentName", "Min Size Percent"))
            ]
            + SHorizontalBox::Slot()
            .VAlign(VAlign_Center)
            [
                SNew(SNumericEntryBox<float>)
                .AllowSpin(true)
                .MinValue(0).MaxValue(100)
                .MinSliderValue(0).MaxSliderValue(100)
                .Value(this, &CityBlockBuilderWindow::GetMinSizePercent)
                .OnValueChanged(this, &CityBlockBuilderWindow::MinSizePercentChanged)
            ]
        ];

    vertBox->AddSlot()
        .AutoHeight()
        [
            SNew(SHorizontalBox)
            + SHorizontalBox::Slot()
            .VAlign(VAlign_Center)
            [
                SNew(STextBlock).Text(LOCTEXT("SpacingName", "Spacing"))
            ]
            + SHorizontalBox::Slot()
            .VAlign(VAlign_Center)
            [
                SNew(SNumericEntryBox<float>)
                .AllowSpin(true)
                .MinValue(0).MaxValue(1000)
                .MinSliderValue(0).MaxSliderValue(1000)
                .Value(this, &CityBlockBuilderWindow::GetSpacing)
                .OnValueChanged(this, &CityBlockBuilderWindow::SpacingChanged)
            ]
        ];
}

FString CityBlockBuilderWindow::GetBoundsActorName() const
{
    if (_boundsActor == NULL)
        return FString::Printf(TEXT("No Actor Selected"));

    return _boundsActor->GetName();
}

FSlateColor CityBlockBuilderWindow::GetBoundsActorColorAndOpacity() const
{
    if (_boundsActor == NULL)
        return FLinearColor(1, 0, 0);

    return FLinearColor(1, 1, 1);
}

FSlateColor CityBlockBuilderWindow::GetBoundsActorForeground() const
{
    if (_boundsActorDropdown->IsHovered())
        return FEditorStyle::GetSlateColor("InvertedForeground");

    return FEditorStyle::GetSlateColor("DefaultForeground");
}

bool CityBlockBuilderWindow::IsActorSelected(ATriggerBox* actor)
{
    return actor == _boundsActor;
}

void CityBlockBuilderWindow::SelectBoundsActor(ATriggerBox* actor)
{
    _boundsActor = actor;
}

TSharedRef<SWidget> CityBlockBuilderWindow::GetBoundsActorContent()
{
    UWorld* world = GetWorld();
    FMenuBuilder menu(true, NULL);

    for (TActorIterator<ATriggerBox> i(world); i; ++i)
    {
        menu.AddMenuEntry(
            FText::FromString(i->GetName()),
            FText::FromString(i->GetName()),
            FSlateIcon(),
            FUIAction(
                FExecuteAction::CreateSP(this, &CityBlockBuilderWindow::SelectBoundsActor, *i),
                FCanExecuteAction(),
                FIsActionChecked::CreateSP(this, &CityBlockBuilderWindow::IsActorSelected, *i)
            ),
            NAME_None,
            EUserInterfaceActionType::ToggleButton);
    }

    return menu.MakeWidget();
}

void CityBlockBuilderWindow::BuildingsPerXChanged(int32 value)
{
    _buildingsPerX = value;
}

TOptional<int32> CityBlockBuilderWindow::GetBuildingsPerX() const
{
    return _buildingsPerX;
}

void CityBlockBuilderWindow::BuildingsPerYChanged(int32 value)
{
    _buildingsPerY = value;
}

TOptional<int32> CityBlockBuilderWindow::GetBuildingsPerY() const
{
    return _buildingsPerY;
}

void CityBlockBuilderWindow::AlleyWidthChanged(float value)
{
    _alleyWidth = value;
}

TOptional<float> CityBlockBuilderWindow::GetAlleyWidth() const
{
    return _alleyWidth;
}

void CityBlockBuilderWindow::HeightPercentChanged(float value)
{
    _heightPercent = value;
}

TOptional<float> CityBlockBuilderWindow::GetHeightPercent() const
{
    return _heightPercent;
}

void CityBlockBuilderWindow::MinSizePercentChanged(float value)
{
    _minSizePercent = value;
}

TOptional<float> CityBlockBuilderWindow::GetMinSizePercent() const
{
    return _minSizePercent;
}

void CityBlockBuilderWindow::SpacingChanged(float value)
{
    _spacing = value;
}

TOptional<float> CityBlockBuilderWindow::GetSpacing() const
{
    return _spacing;
}

UWorld* CityBlockBuilderWindow::GetWorld()
{
    UWorld* world = NULL;
    const TArray<FWorldContext>& contexts = GEngine->GetWorldContexts();
    for (int32 i = 0; i < contexts.Num(); i++)
    {
        if (contexts[i].WorldType == EWorldType::PIE)
            return contexts[i].World();
        
        if (contexts[i].WorldType == EWorldType::Editor)
            world = contexts[i].World();
    }

    return world;
}