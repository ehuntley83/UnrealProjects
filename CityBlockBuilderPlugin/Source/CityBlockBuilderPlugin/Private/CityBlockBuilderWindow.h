#pragma once

struct AlleySpace
{
    enum E
    {
        NoAlley,
        XAlley,
        YAlley
    };
};

class CityBlockBuilderWindow : public SCompoundWidget
{
private:
    TSharedPtr<SComboButton> _boundsActorDropdown;

    ATriggerBox* _boundsActor;

    AlleySpace::E _alleySpace;

    int _buildingsPerX;
    int _buildingsPerY;

    float _alleyWidth;
    float _heightPercent;
    float _minSizePercent;
    float _spacing;

    FString GetBoundsActorName() const;
    FSlateColor GetBoundsActorColorAndOpacity() const;
    FSlateColor GetBoundsActorForeground() const;
    bool IsActorSelected(ATriggerBox* actor);
    void SelectBoundsActor(ATriggerBox* actor);
    TSharedRef<SWidget> GetBoundsActorContent();

    FString GetAlleySpaceText() const;
    void SelectAlleySpace(AlleySpace::E space);
    bool IsAlleySpaceSelected(AlleySpace::E space) const;
    TSharedRef<SWidget> GetAlleySpaceContent();

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

    UWorld* GetWorld();

public:
    CityBlockBuilderWindow();

    SLATE_BEGIN_ARGS(CityBlockBuilderWindow)
    {
    }
    SLATE_END_ARGS()

    void Construct(const FArguments& args);
};