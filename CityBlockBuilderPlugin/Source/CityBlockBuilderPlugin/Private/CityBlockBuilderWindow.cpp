#include "CityBlockBuilderPluginPch.h"
#include "CityBlockBuilderWindow.h"

#define LOCTEXT_NAMESPACE "CityBlockBuilderPluginWindow"

CityBlockBuilderWindow::CityBlockBuilderWindow() :
_buildingsPerX(1),
_buildingsPerY(1),
_alleyWidth(100),
_heightPercent(50),
_minSizePercent(50),
_spacing(10)
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