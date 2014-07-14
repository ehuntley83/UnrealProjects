#pragma once

class CityBlockBuilderWindow : public SCompoundWidget
{
private:
    int _buildingsPerX;
    int _buildingsPerY;

    float _alleyWidth;
    float _heightPercent;
    float _minSizePercent;
    float _spacing;

    void BuildingsPerXChanged(int32 value);
    TOptional<int32> GetBuildingsPerX() const;

    void BuildingsPerYChanged(int32 value);
    TOptional<int32> GetBuildingsPerY() const;

    void AlleyWidthChanged(float value);
    TOptional<float> GetAlleyWidth() const;

    void HeightPercentChanged(float value);
    TOptional<float> GetHeightPercent() const;

    void MinSizePercentChanged(float value);
    TOptional<float> GetMinSizePercent() const;

    void SpacingChanged(float value);
    TOptional<float> GetSpacing() const;

public:
    CityBlockBuilderWindow();

    SLATE_BEGIN_ARGS(CityBlockBuilderWindow)
    {
    }
    SLATE_END_ARGS()

    void Construct(const FArguments& args);
};