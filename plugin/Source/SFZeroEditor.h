#ifndef INCLUDED_SFZEROEDITOR_H
#define INCLUDED_SFZEROEDITOR_H

#include "JuceHeader.h"
#include "ClickableLabel.h"
#include "SFZeroAudioProcessor.h"

namespace sfzero_plugin
{
    class SFZeroEditor : public AudioProcessorEditor, public Timer, public ClickableLabel::ClickListener
    {
    public:
        SFZeroEditor(SFZeroAudioProcessor *ownerFilter);
        ~SFZeroEditor();
        
        void paint(Graphics &g) override;
        void resized() override;
        void labelClicked(Label *clickedLabel) override;
        void timerCallback() override;
        
    protected:
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
        
        ClickableLabel fileLabel;
        ClickableLabel pathLabel;
        ClickableLabel infoLabel;
        Viewport viewport;
        int showing, showingInfo;
        MidiKeyboardComponent midiKeyboard;
        ProgressBar *progressBar;
        
        SFZeroAudioProcessor *getProcessor() const { return static_cast<SFZeroAudioProcessor *>(getAudioProcessor()); }
        void chooseFile();
        void setFile(File *newFile);
        void updateFile(File *file);
        void showSoundInfo();
        void showVoiceInfo();
        void showVersion();
        void showPath();
        void showProgress();
        void hideProgress();
        void showSubsound();
    };
}


#endif // INCLUDED_SFZEROEDITOR_H
