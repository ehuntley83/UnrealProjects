#pragma once

class CityBlockBuilderWindow : public SCompoundWidget
{
public:
    CityBlockBuilderWindow();

    SLATE_BEGIN_ARGS(CityBlockBuilderWindow)
    {
    }
    SLATE_END_ARGS()

    void Construct(const FArguments& args);
};