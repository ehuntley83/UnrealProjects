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
_boundsActor(NULL),
_alleySpace(AlleySpace::NoAlley)
{
}

void CityBlockBuilderWindow::Construct(const FArguments& args)
{
    // What we're doing here is using Slate to create a vertical box within our window
    // then creating many horizontal boxes within that vertical box to contain our
    // properties. Most of them consist of a label to the left and a value selector to
    // the right. Each horizontal box is in a new Slot within the parent vertical box.
    // The labels and selectors are in Slots in each horizontal box.
    // Data binding between the values in the property selectors and our class is done
    // through delegates which set the private property values.
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
                SNew(STextBlock)
                .Text(this, &CityBlockBuilderWindow::GetBoundsActorName)
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
                SNew(STextBlock)
                .Text(LOCTEXT("AlleySpaceName", "Alley Space"))
            ]
            + SHorizontalBox::Slot()
                .VAlign(VAlign_Center)
                [
                    SNew(SComboButton)
                    .ContentPadding(0)
                    .OnGetMenuContent(this, &CityBlockBuilderWindow::GetAlleySpaceContent)
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
                            SNew(STextBlock).Text(this, &CityBlockBuilderWindow::GetAlleySpaceText)
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

    vertBox->AddSlot()
        .AutoHeight()
        [
            SNew(SButton)
            .Text(FString(TEXT("Build")))
            .OnClicked(this, &CityBlockBuilderWindow::DoBuild)
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
            FText::FromString(i->GetName()),    // Menu text
            FText::FromString(i->GetName()),    // Tooltip text
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

FString CityBlockBuilderWindow::GetAlleySpaceText() const
{
    if (_alleySpace == AlleySpace::NoAlley)
        return FString::Printf(TEXT("No alley"));

    if (_alleySpace == AlleySpace::XAlley)
        return FString::Printf(TEXT("X Alley"));

    if (_alleySpace == AlleySpace::YAlley)
        return FString::Printf(TEXT("Y Alley"));

    return FString::Printf(TEXT("Error"));
}

void CityBlockBuilderWindow::SelectAlleySpace(AlleySpace::E space)
{
    _alleySpace = space;
}

bool CityBlockBuilderWindow::IsAlleySpaceSelected(AlleySpace::E space) const
{
    return _alleySpace == space;
}

TSharedRef<SWidget> CityBlockBuilderWindow::GetAlleySpaceContent()
{
    FMenuBuilder menu(true, NULL);

    menu.AddMenuEntry(
        FText::FromString(TEXT("No Alley")),    // Menu text
        FText::FromString(TEXT("No Alley")),    // Tooltip text
        FSlateIcon(),
        FUIAction(
            FExecuteAction::CreateSP(this, &CityBlockBuilderWindow::SelectAlleySpace, AlleySpace::NoAlley),
            FCanExecuteAction(),
            FIsActionChecked::CreateSP(this, &CityBlockBuilderWindow::IsAlleySpaceSelected, AlleySpace::NoAlley)
        ),
        NAME_None,
        EUserInterfaceActionType::ToggleButton
        );

    menu.AddMenuEntry(
        FText::FromString(TEXT("X Alley")),    // Menu text
        FText::FromString(TEXT("X Alley")),    // Tooltip text
        FSlateIcon(),
        FUIAction(
            FExecuteAction::CreateSP(this, &CityBlockBuilderWindow::SelectAlleySpace, AlleySpace::XAlley),
            FCanExecuteAction(),
            FIsActionChecked::CreateSP(this, &CityBlockBuilderWindow::IsAlleySpaceSelected, AlleySpace::XAlley)
        ),
        NAME_None,
        EUserInterfaceActionType::ToggleButton
        );

    menu.AddMenuEntry(
        FText::FromString(TEXT("Y Alley")),    // Menu text
        FText::FromString(TEXT("Y Alley")),    // Tooltip text
        FSlateIcon(),
        FUIAction(
            FExecuteAction::CreateSP(this, &CityBlockBuilderWindow::SelectAlleySpace, AlleySpace::YAlley),
            FCanExecuteAction(),
            FIsActionChecked::CreateSP(this, &CityBlockBuilderWindow::IsAlleySpaceSelected, AlleySpace::YAlley)
        ),
        NAME_None,
        EUserInterfaceActionType::ToggleButton
        );

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
    
    for (const FWorldContext& WorldContext : GEngine->GetWorldContexts())
    {
      if (WorldContext.WorldType == EWorldType::PIE)
        return WorldContext.World();
        
      if (WorldContext.WorldType == EWorldType::Editor)
        world = WorldContext.World();
    }

    return world;
}

void CityBlockBuilderWindow::CreateBrush(FVector position, FVector size)
{
    // This method will take a position and size and create a new cube brush.
    // It is called by the DoBuild method when creating all the randow builings.
    // Placing BSP brushes is not optimal, as they take a while to generate and place
    // but this could be extended to placing static meshes.
    UWorld* world = GetWorld();

    UCubeBuilder* cubeBuilder = Cast<UCubeBuilder>(GEditor->FindBrushBuilder (UCubeBuilder::StaticClass()));

    cubeBuilder-> X = size.X;
    cubeBuilder->Y = size.Y;
    cubeBuilder->Z = size.Z;
    cubeBuilder->Build(world);

    world->GetDefaultBrush()->SetActorLocation(position);
    GEditor->RedrawLevelEditingViewports();
    GEditor->Exec(world, TEXT("BRUSH ADD"));
}

FReply CityBlockBuilderWindow::DoBuild()
{
    // This is the real meat and potatoes of the plugin that generates a number of cube brushes
    // within the preferred sizes and alignments
    if (_boundsActor == NULL)
        return FReply::Handled();

    FVector boundsSize = _boundsActor->GetComponentsBoundingBox().GetExtent();
    FVector boundsPosition = _boundsActor->GetActorLocation();
    FVector boundsMin = boundsPosition - boundsSize;
    boundsSize *= 2;

    float xBuildingBounds = (boundsSize.X - (_alleySpace == AlleySpace::XAlley ? _alleyWidth : 0)) / (float)_buildingsPerX;
    float yBuildingBounds = (boundsSize.Y - (_alleySpace == AlleySpace::YAlley ? _alleyWidth : 0)) / (float)_buildingsPerY;

    float alleyPivot = 0;
    if (_alleySpace == AlleySpace::XAlley)
        alleyPivot = _buildingsPerX / 2.f;
    else if (_alleySpace == AlleySpace::YAlley)
        alleyPivot = _buildingsPerY / 2.f;

    FVector position, size;
    for (int x = 0; x < _buildingsPerX; x++)
    {
        for (int y = 0; y < _buildingsPerY; y++)
        {
            size.X = FMath::FRandRange(xBuildingBounds * (_minSizePercent / 100.f), xBuildingBounds) - _spacing;
            size.Y = FMath::FRandRange(yBuildingBounds * (_minSizePercent / 100.f), yBuildingBounds) - _spacing;
            size.Z = FMath::FRandRange(boundsSize.Z * (_minSizePercent / 100.f), boundsSize.Z);

            position.X = boundsMin.X + (xBuildingBounds * x) + _spacing + (size.X / 2.f);
            position.Y = boundsMin.Y + (yBuildingBounds * y) + _spacing + (size.Y / 2.f);
            position.Z = boundsMin.Z + (size.Z / 2.f);

            if (_alleySpace == AlleySpace::XAlley && x >= alleyPivot)
                position.X += _alleyWidth;
            else if (_alleySpace == AlleySpace::YAlley && y >= alleyPivot)
                position.Y += _alleyWidth;

            CreateBrush(position, size);
        }
    }

    return FReply::Handled();
}