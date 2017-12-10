#include "SFZeroEditorList.h"
#include "SFZeroFolders.h"
#include "SFZeroAudioProcessor.h"

enum
{
  hMargin = 12,
  vMargin = 12,
  labelHeight = 25,
  progressBarHeight = 30,
  keyboardHeight = 54,
};

sfzero::SFZeroEditorList::SFZeroEditorList(SFZeroAudioProcessor *ownerFilter)
: AudioProcessorEditor(ownerFilter), fileLabel(String::empty, "File... (click here to choose)"), pathLabel(String::empty),
showingInfo(showingSoundInfo), midiKeyboard(ownerFilter->keyboardState, MidiKeyboardComponent::horizontalKeyboard),
progressBar(nullptr)
{
  isAU = SystemStats::isRunningInAppExtensionSandbox();
  
#ifdef JUCE_MAC
  Font fileFont("Helvetica", 22.0, Font::bold);
  Font labelFont("Helvetica", 15.0, Font::plain);
#else
  Font fileFont("Ariel", 22.0, Font::bold);
  Font labelFont("Ariel", 15.0, Font::plain);
#endif
  
  //File folder("/temp");
  groupFolder = SFZeroFolders::GetGroupFolder();
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
  fileTree = new SFZeroFileList(*directoryList);
  fileTree->setLookAndFeel(&lookAndFeel);
  //fileTree->setRootItemVisible(true);
  addAndMakeVisible(fileTree);
  fileTree->addListener(this);
  
  addAndMakeVisible(&midiKeyboard);
  midiKeyboard.setOctaveForMiddleC(4);
  
  addAndMakeVisible(&fileLabel);
  fileLabel.setFont(fileFont);
  fileLabel.setColour(Label::textColourId, Colours::grey);
  fileLabel.addClickListener(this);
  
  addAndMakeVisible(&pathLabel);
  pathLabel.setFont(labelFont);
  pathLabel.setColour(Label::textColourId, Colours::grey);
  pathLabel.addClickListener(this);
  
  addAndMakeVisible(&infoLabel);
  infoLabel.setFont(labelFont);
  infoLabel.setJustificationType(Justification::topLeft);
  infoLabel.addClickListener(this);

  startTimer(200);
  
  File sfzFile = ownerFilter->getSfzFile();
  if (sfzFile != File::nonexistent)
  {
    updateFile(&sfzFile);
    showSoundInfo();
    auto sound = ownerFilter->getSound();
    if (sound && (sound->numSubsounds() > 1))
    {
      showSubsound();
    }
  }
  else
  {
    showVersion();
  }
  setSize(500, 300);
}

sfzero::SFZeroEditorList::~SFZeroEditorList(){
  filelistThread->stopThread(1000);
  delete filelistThread;
  delete directoryList;
  delete fileTree;
  delete progressBar;
  delete fileFilter;
}

void sfzero::SFZeroEditorList::paint(Graphics &g) { g.fillAll(Colours::grey); }

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

void sfzero::SFZeroEditorList::labelClicked(Label *clickedLabel)
{
  if (clickedLabel == &fileLabel)
  {
    chooseFile();
  }
  else if (clickedLabel == &pathLabel)
  {
    if (showing == showingSubsound)
    {
      auto processor = getProcessor();
      auto sound = processor->getSound();
      if (sound)
      {
        PopupMenu menu;
        int selectedSubsound = sound->selectedSubsound();
        int numSubsounds = sound->numSubsounds();
        for (int i = 0; i < numSubsounds; ++i)
        {
          menu.addItem(i + 1, sound->subsoundName(i), true, (i == selectedSubsound));
        }
        int result = menu.show();
        if (result != 0)
        {
          sound->useSubsound(result - 1);
          showSubsound();
        }
      }
    }
    else if (showing == showingVersion)
    {
      showPath();
    }
    else
    {
      showVersion();
    }
  }
  else if (clickedLabel == &infoLabel)
  {
    if (showingInfo == showingSoundInfo)
    {
      showVoiceInfo();
    }
    else
    {
      showSoundInfo();
    }
  }
}

void sfzero::SFZeroEditorList::timerCallback()
{
  if (showing == showingProgress)
  {
    auto processor = getProcessor();
    if (processor->loadProgress >= 1.0)
    {
      auto sound = processor->getSound();
      if (sound && (sound->numSubsounds() > 1))
      {
        showSubsound();
      }
      else
      {
        showPath();
      }
      showSoundInfo();
    }
  }
  
  if (showingInfo == showingVoiceInfo)
  {
    showVoiceInfo();
  }
}

void sfzero::SFZeroEditorList::chooseFile()
{
#ifdef JUCE_IOS
  FileChooser chooser("Select an SFZ file...", File::getSpecialLocation (File::userDocumentsDirectory), "*.sfz;*.SFZ;*.sf2;*.SF2");
#else
  FileChooser chooser("Select an SFZ file...", File::nonexistent, "*.sfz;*.SFZ;*.sf2;*.SF2");
#endif
  if (chooser.browseForFileToOpen())
  {
    File sfzFile(chooser.getResult());
    setFile(&sfzFile);
  }
}

void sfzero::SFZeroEditorList::setFile(const File *newFile)
{
  bool result=false;
  if(!isAU){
    if(true){
      File parentDir = newFile->getParentDirectory();
      juce::String dest=groupFolder.getFullPathName()+"/"+parentDir.getFileName();
      result=parentDir.copyDirectoryTo(dest);
    }
    else{
      juce::String dest=groupFolder.getFullPathName()+"/"+newFile->getFileName();
      result=newFile->copyFileTo(File(dest));
    }
  }
  auto processor = getProcessor();
  
  processor->setSfzFileThreaded(newFile);
  
  updateFile(newFile);
  showProgress();
}

void sfzero::SFZeroEditorList::updateFile(const File *file)
{
  fileLabel.setText(file->getFileName(), dontSendNotification);
  fileLabel.setColour(Label::textColourId, Colours::black);
  showPath();
}

void sfzero::SFZeroEditorList::showSoundInfo()
{
  auto processor = getProcessor();
  auto sound = processor->getSound();
  
  if (sound)
  {
    String info;
    auto& errors = sound->getErrors();
    if (errors.size() > 0)
    {
      info << errors.size() << " errors: \n";
      info << errors.joinIntoString("\n");
      info << "\n";
    }
    else
    {
      info << "no errors.\n\n";
    }
    auto& warnings = sound->getWarnings();
    if (warnings.size() > 0)
    {
      info << warnings.size() << " warnings: \n";
      info << warnings.joinIntoString("\n");
    }
    else
    {
      info << "no warnings.\n";
    }
    infoLabel.setText(info, dontSendNotification);
  }
  showingInfo = showingSoundInfo;
}

void sfzero::SFZeroEditorList::showVoiceInfo()
{
  auto processor = getProcessor();
  
  infoLabel.setText(processor->voiceInfoString(), dontSendNotification);
  showingInfo = showingVoiceInfo;
}

void sfzero::SFZeroEditorList::showVersion()
{
  auto date = Time::getCompilationDate();
  auto str = String::formatted("SFZero beta %d.%d.%d", date.getYear(), date.getMonth(), date.getDayOfMonth());
  pathLabel.setText(str, dontSendNotification);
  pathLabel.setColour(Label::textColourId, Colours::grey);
  hideProgress();
  showing = showingVersion;
}

void sfzero::SFZeroEditorList::showPath()
{
  auto processor = getProcessor();
  File file = processor->getSfzFile();
  
  pathLabel.setText(file.getParentDirectory().getFullPathName(), dontSendNotification);
  pathLabel.setColour(Label::textColourId, Colours::grey);
  hideProgress();
  showing = showingPath;
}

void sfzero::SFZeroEditorList::showSubsound()
{
  auto processor = getProcessor();
  auto sound = processor->getSound();
  
  if (sound == nullptr)
  {
    return;
  }
  
  pathLabel.setText(sound->subsoundName(sound->selectedSubsound()), dontSendNotification);
  pathLabel.setColour(Label::textColourId, Colours::black);
  hideProgress();
  showing = showingSubsound;
}

void sfzero::SFZeroEditorList::showProgress()
{
  auto processor = getProcessor();
  
  pathLabel.setVisible(false);
  infoLabel.setVisible(false);
  progressBar = new ProgressBar(processor->loadProgress);
  addAndMakeVisible(progressBar);
  int marginedWidth = getWidth() - 2 * hMargin;
  progressBar->setBounds(hMargin, vMargin + labelHeight, marginedWidth, progressBarHeight);
  showing = showingProgress;
}

void sfzero::SFZeroEditorList::hideProgress()
{
  if (progressBar == nullptr)
  {
    return;
  }
  
  removeChildComponent(progressBar);
  delete progressBar;
  progressBar = nullptr;
  
  pathLabel.setVisible(true);
  infoLabel.setVisible(true);
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
