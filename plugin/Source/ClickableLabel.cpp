#include "ClickableLabel.h"

namespace sfzero_plugin
{
    ClickableLabel::ClickableLabel(const String &componentName, const String &labelText) : Label(componentName, labelText) {}
    void ClickableLabel::addClickListener(ClickListener *listener) { clickListeners.add(listener); }
    void ClickableLabel::removeClickListener(ClickListener *listener) { clickListeners.remove(listener); }
    void ClickableLabel::mouseUp(const MouseEvent &e)
    {
        bool goodClick = e.mouseWasClicked() && contains(e.getPosition()) && !e.mods.isPopupMenu();
        
        if (goodClick)
        {
            BailOutChecker checker(this);
            clickListeners.callChecked(checker, &ClickListener::labelClicked, this);
        }
    }
}
