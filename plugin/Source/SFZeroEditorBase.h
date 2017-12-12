#ifndef INCLUDED_SFZEROEDITORBASE_H
#define INCLUDED_SFZEROEDITORBASE_H

#include "JuceHeader.h"
#include "ClickableLabel.h"
#include "SFZeroAudioProcessor.h"

namespace sfzero
{
  class SFZeroEditorBase : public AudioProcessorEditor, public Timer, public ClickableLabel::ClickListener
  {
  public:
    SFZeroEditorBase(SFZeroAudioProcessor *ownerFilter);
    ~SFZeroEditorBase();
    
    void labelClicked(Label *clickedLabel) override;
    void timerCallback() override;
    
  protected:
    // layout parameters
    enum
    {
      hMargin = 12,
      vMargin = 12,
      labelHeight = 25,
      progressBarHeight = 30,
      keyboardHeight = 54,
    };
    
    // pathLabel options.
    enum
    {
      showingVersion,
      showingPath,
      showingProgress,
      showingSubsound,
    };
    
    // infoLabel options.
    enum
    {
      showingSoundInfo,
      showingVoiceInfo,
    };
    
    Font fileFont;
    Font labelFont;
    ClickableLabel fileLabel;
    ClickableLabel pathLabel;
    ClickableLabel infoLabel;
    Viewport viewport;
    int showing, showingInfo;
    MidiKeyboardComponent midiKeyboard;
    ProgressBar *progressBar;
    bool isAU;
    File groupFolder;
    
    SFZeroAudioProcessor *getProcessor() const { return static_cast<SFZeroAudioProcessor *>(getAudioProcessor()); }
    void chooseFile();
    void setFile(const File *newFile);
    void updateFile(const File *file);
    void showSoundInfo();
    void showVoiceInfo();
    void showVersion();
    void showPath();
    void showProgress();
    void hideProgress();
    void showSubsound();
  };
}


#endif // INCLUDED_SFZEROEDITORBASE_H
