#ifndef INCLUDED_SFZEROEDITORLIST_H
#define INCLUDED_SFZEROEDITORLIST_H

#include "JuceHeader.h"
#include "ClickableLabel.h"
#include "SFZeroAudioProcessor.h"
#include "SFZeroFileBrowserLookAndFeel.h"
#include "SFZeroEditorBase.h"

namespace sfzero
{
  
  class SFZeroEditorList : public SFZeroEditorBase, public FileBrowserListener
  {
  public:
    SFZeroEditorList(SFZeroAudioProcessor *ownerFilter);
    ~SFZeroEditorList();
    
    void paint(Graphics &g) override;
    void resized() override;
    /** Callback when the user selects a different file in the browser. */
    void selectionChanged() override;
    /** Callback when the user clicks on a file in the browser. */
    void fileClicked (const File& file, const MouseEvent& e) override;
    /** Callback when the user double-clicks on a file in the browser. */
    void fileDoubleClicked (const File& file) override;
    /** Callback when the browser's root folder changes. */
    void browserRootChanged (const File& newRoot) override;
    
  protected:
    DirectoryContentsList *directoryList;
    TimeSliceThread *filelistThread;
    FileTreeComponent *fileTree;
    SFZeroFileBrowserLookAndFeel lookAndFeel;
    File getSharedResourceFolder();
    File browseFolder;
    WildcardFileFilter* fileFilter;
    
  };
}


#endif // INCLUDED_SFZEROEDITORLIST_H
