#ifndef INCLUDED_CLICKABLELABEL_H
#define INCLUDED_CLICKABLELABEL_H

#include "JuceHeader.h"

namespace sfzero_plugin
{
    class ClickableLabel : public Label
    {
    public:
        ClickableLabel(const String &componentName = String::empty, const String &labelText = String::empty);
        
        class JUCE_API ClickListener
        {
        public:
            virtual ~ClickListener() {}
            virtual void labelClicked(Label *clickedLabel) = 0;
        };
        
        void addClickListener(ClickListener *listener);
        void removeClickListener(ClickListener *listener);
        
    protected:
        ListenerList<ClickListener> clickListeners;
        
        void mouseUp(const MouseEvent &e) override;
    };
}


#endif // INCLUDED_CLICKABLELABEL_H
