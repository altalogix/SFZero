#ifndef INCLUDED_SFZEROEDITORLIST_H
#define INCLUDED_SFZEROEDITORLIST_H

#include "JuceHeader.h"
#include "ClickableLabel.h"
#include "SFZeroAudioProcessor.h"
#include "SFZeroFileList.h"
#include "SFZeroFileBrowserLookAndFeel.h"

namespace sfzero
{
  
  class SFZeroEditorList : public AudioProcessorEditor, public Timer, public ClickableLabel::ClickListener, public FileBrowserListener
  {
  public:
    SFZeroEditorList(SFZeroAudioProcessor *ownerFilter);
    ~SFZeroEditorList();
    
    void paint(Graphics &g) override;
    void resized() override;
    void labelClicked(Label *clickedLabel) override;
    void timerCallback() override;
    /** Callback when the user selects a different file in the browser. */
    void selectionChanged() override;
    /** Callback when the user clicks on a file in the browser. */
    void fileClicked (const File& file, const MouseEvent& e) override;
    /** Callback when the user double-clicks on a file in the browser. */
    void fileDoubleClicked (const File& file) override;
    /** Callback when the browser's root folder changes. */
    void browserRootChanged (const File& newRoot) override;
    
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
    DirectoryContentsList *directoryList;
    TimeSliceThread *filelistThread;
    int showing, showingInfo;
    MidiKeyboardComponent midiKeyboard;
    ProgressBar *progressBar;
    SFZeroFileList *fileTree;
    SFZeroFileBrowserLookAndFeel lookAndFeel;
    File getSharedResourceFolder();
    bool isAU;
    File browseFolder;
    File groupFolder;
    WildcardFileFilter* fileFilter;
    
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


#endif // INCLUDED_SFZEROEDITORLIST_H
