#include "SFZeroEditorList.h"
#include "SFZeroFolders.h"
#include "SFZeroAudioProcessor.h"

sfzero::SFZeroEditorList::SFZeroEditorList(SFZeroAudioProcessor *ownerFilter) : SFZeroEditorBase(ownerFilter){
  File localFolder (File::getSpecialLocation (File::userDocumentsDirectory));
  //File folder = getSharedResourceFolder().getParentDirectory().getChildFile("Documents");
  if(isAU)
    browseFolder = groupFolder;
  else
    browseFolder = localFolder;
  fileFilter=new WildcardFileFilter("*.sf2;*.sfz;*.SF2;*.SFZ", "*", "Soundfonts");
  filelistThread = new TimeSliceThread("File List");
  directoryList = new DirectoryContentsList (fileFilter, *filelistThread);
  directoryList->setDirectory(browseFolder, true, true);
  filelistThread->startThread (3);
  fileTree = new FileTreeComponent(*directoryList);
  fileTree->setLookAndFeel(&lookAndFeel);
  //fileTree->setRootItemVisible(true);
  addAndMakeVisible(fileTree);
  fileTree->addListener(this);
  
  addAndMakeVisible(&infoLabel);
  infoLabel.setFont(labelFont);
  infoLabel.setJustificationType(Justification::topLeft);
  infoLabel.addClickListener(this);
  setSize(500, 300);
}

sfzero::SFZeroEditorList::~SFZeroEditorList(){
  filelistThread->stopThread(1000);
  delete filelistThread;
  delete directoryList;
  delete fileTree;
  delete fileFilter;
}

void sfzero::SFZeroEditorList::paint(Graphics &g){
  g.fillAll(Colours::grey);
}

void sfzero::SFZeroEditorList::resized()
{
  Rectangle<int> area (getLocalBounds());
  area.removeFromTop(vMargin);
  area.removeFromBottom(vMargin);
  area.removeFromLeft(hMargin);
  area.removeFromRight(hMargin);
  fileLabel.setBounds(area.removeFromTop(labelHeight));
  pathLabel.setBounds(area.removeFromTop(labelHeight));
  infoLabel.setBounds(area.removeFromTop(labelHeight));
  midiKeyboard.setBounds (area.removeFromBottom (keyboardHeight));
  fileTree->setBounds(area);
}

File sfzero::SFZeroEditorList::getSharedResourceFolder()
{
  File bundle = File::getSpecialLocation (File::invokedExecutableFile).getParentDirectory();
  
  // macOS uses Contents/MacOS structrue, iOS bundle structure is flat
#if JUCE_MAC
  bundle = bundle.getParentDirectory().getParentDirectory();
#endif
  
  // appex is in a PlugIns folder inside the parent bundle
  if (SystemStats::isRunningInAppExtensionSandbox())
    bundle = bundle.getParentDirectory().getParentDirectory();
  
#if JUCE_MAC
  bundle = bundle.getChildFile ("Resources");
#endif
  
  return bundle;
}

void sfzero::SFZeroEditorList::selectionChanged(){}
void sfzero::SFZeroEditorList::fileClicked (const File& file, const MouseEvent& e){}
void sfzero::SFZeroEditorList::fileDoubleClicked (const File& file){
  String ext = file.getFileExtension();
  if(ext==".sf2" || ext==".SF2" || ext==".sfz" || ext==".SFZ")
    setFile(&file);
}
void sfzero::SFZeroEditorList::browserRootChanged (const File& newRoot){}
