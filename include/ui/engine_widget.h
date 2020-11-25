#pragma once

namespace Engine {

    class EWidget : public EObject
    {
    private:
        EProperty<EVec2>    fPosition;
        EProperty<EVec2>    fSize;
    public:
        EWidget();
        EWidget(const EVec2& position, const EVec2& size);
        
    };

}