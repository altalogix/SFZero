#include "SFZeroEditorBase.h"
#include "SFZeroAudioProcessor.h"
#include "SFZeroFolders.h"

sfzero::SFZeroEditorBase::SFZeroEditorBase(SFZeroAudioProcessor *ownerFilter)
: AudioProcessorEditor(ownerFilter), fileLabel(String::empty, "File... (click here to choose)"), pathLabel(String::empty),
showingInfo(showingSoundInfo), midiKeyboard(ownerFilter->keyboardState, MidiKeyboardComponent::horizontalKeyboard),
progressBar(nullptr)
{
  isAU = SystemStats::isRunningInAppExtensionSandbox();
  groupFolder = SFZeroFolders::GetGroupFolder();
  
  fileFont.setHeight(22.0);
  fileFont.setStyleFlags(Font::bold);
  labelFont.setHeight(15.0);
  labelFont.setStyleFlags(Font::plain);
#ifdef JUCE_MAC
  fileFont.setTypefaceName("Helvetica");
  labelFont.setTypefaceName("Helvetica");
#else
  fileFont.setTypefaceName("Ariel");
  labelFont.setTypefaceName("Ariel");
#endif
  
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
  
  startTimer(200);
  auto processor = getProcessor();
  File sfzFile = processor->getSfzFile();
  if (sfzFile != File::nonexistent)
  {
    updateFile(&sfzFile);
    showSoundInfo();
    auto sound = processor->getSound();
    if (sound && (sound->numSubsounds() > 1))
    {
      showSubsound();
    }
  }
  else
  {
    showVersion();
  }
}

sfzero::SFZeroEditorBase::~SFZeroEditorBase() {
  delete progressBar;
}

void sfzero::SFZeroEditorBase::labelClicked(Label *clickedLabel)
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

void sfzero::SFZeroEditorBase::timerCallback()
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

void sfzero::SFZeroEditorBase::chooseFile()
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

void sfzero::SFZeroEditorBase::setFile(const File *newFile)
{
#ifdef JUCE_IOS
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
#endif
  
  auto processor = getProcessor();
  
  processor->setSfzFileThreaded(newFile);
  
  updateFile(newFile);
  showProgress();
}

void sfzero::SFZeroEditorBase::updateFile(const File *file)
{
  fileLabel.setText(file->getFileName(), dontSendNotification);
  fileLabel.setColour(Label::textColourId, Colours::black);
  showPath();
}

void sfzero::SFZeroEditorBase::showSoundInfo()
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

void sfzero::SFZeroEditorBase::showVoiceInfo()
{
  auto processor = getProcessor();
  
  infoLabel.setText(processor->voiceInfoString(), dontSendNotification);
  showingInfo = showingVoiceInfo;
}

void sfzero::SFZeroEditorBase::showVersion()
{
  auto date = Time::getCompilationDate();
  auto str = String::formatted("SFZero beta %d.%d.%d", date.getYear(), date.getMonth(), date.getDayOfMonth());
  pathLabel.setText(str, dontSendNotification);
  pathLabel.setColour(Label::textColourId, Colours::grey);
  hideProgress();
  showing = showingVersion;
}

void sfzero::SFZeroEditorBase::showPath()
{
  auto processor = getProcessor();
  File file = processor->getSfzFile();
  
  pathLabel.setText(file.getParentDirectory().getFullPathName(), dontSendNotification);
  pathLabel.setColour(Label::textColourId, Colours::grey);
  hideProgress();
  showing = showingPath;
}

void sfzero::SFZeroEditorBase::showSubsound()
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

void sfzero::SFZeroEditorBase::showProgress()
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

void sfzero::SFZeroEditorBase::hideProgress()
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
