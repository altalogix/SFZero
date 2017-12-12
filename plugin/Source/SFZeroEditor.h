#ifndef INCLUDED_SFZEROEDITOR_H
#define INCLUDED_SFZEROEDITOR_H

#include "JuceHeader.h"
#include "ClickableLabel.h"
#include "SFZeroAudioProcessor.h"
#include "SFZeroEditorBase.h"

namespace sfzero
{
  class SFZeroEditor : public SFZeroEditorBase
  {
  public:
    SFZeroEditor(SFZeroAudioProcessor *ownerFilter);
    ~SFZeroEditor();

    void paint(Graphics &g) override;
    void resized() override;

  protected:
    Viewport viewport;
  };
}

#endif // INCLUDED_SFZEROEDITOR_H
