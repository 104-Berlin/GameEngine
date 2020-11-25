#include "Engine.h"

using namespace Engine;

EWidget::EWidget()
    :   EObject("Widget"),
        fPosition(this, "Position"),
        fSize(this, "Size")

{

}

EWidget::EWidget(const EVec2& position, const EVec2& size)
    : EWidget()
{
    fPosition.SetValue(position);
    fSize.SetValue(size);
}