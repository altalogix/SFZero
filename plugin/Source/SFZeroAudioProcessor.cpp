#include "SFZeroAudioProcessor.h"
#include "SFZeroEditor.h"

namespace sfzero_plugin
{
    
    SFZeroAudioProcessor::SFZeroAudioProcessor() : loadProgress(0.0), loadThread(this)
    {
        formatManager.registerBasicFormats();
        
        for (int i = 0; i < 128; ++i)
        {
            synth.addVoice(new sfzero::Voice());
        }
    }
    
    SFZeroAudioProcessor::~SFZeroAudioProcessor() {}
    const String SFZeroAudioProcessor::getName() const { return JucePlugin_Name; }
    int SFZeroAudioProcessor::getNumParameters() { return 0; }
    float SFZeroAudioProcessor::getParameter(int /*index*/) { return 0.0f; }
    void SFZeroAudioProcessor::setParameter(int /*index*/, float /*newValue*/) {}
    const String SFZeroAudioProcessor::getParameterName(int /*index*/) { return String::empty; }
    const String SFZeroAudioProcessor::getParameterText(int /*index*/) { return String::empty; }
    
    void SFZeroAudioProcessor::setSfzFile(File *newSfzFile)
    {
        sfzFile = *newSfzFile;
        loadSound();
    }
    
    void SFZeroAudioProcessor::setSfzFileThreaded(File *newSfzFile)
    {
        loadThread.stopThread(2000);
        sfzFile = *newSfzFile;
        loadThread.startThread();
    }
    
    bool SFZeroAudioProcessor::acceptsMidi() const
    {
#if JucePlugin_WantsMidiInput
        return true;
        
#else
        return false;
#endif
    }
    
    bool SFZeroAudioProcessor::producesMidi() const
    {
#if JucePlugin_ProducesMidiOutput
        return true;
        
#else
        return false;
#endif
    }
    
    int SFZeroAudioProcessor::getNumPrograms() { return 1; }
    int SFZeroAudioProcessor::getCurrentProgram() { return 0; }
    void SFZeroAudioProcessor::setCurrentProgram(int /*index*/) {}
    const String SFZeroAudioProcessor::getProgramName(int /*index*/) { return String::empty; }
    void SFZeroAudioProcessor::changeProgramName(int /*index*/, const String & /*newName*/) {}
    void SFZeroAudioProcessor::prepareToPlay(double _sampleRate_, int /*samplesPerBlock*/)
    {
        synth.setCurrentPlaybackSampleRate(_sampleRate_);
        keyboardState.reset();
    }
    
    void SFZeroAudioProcessor::releaseResources()
    {
        // When playback stops, you can use this as an opportunity to free up any
        // spare memory, etc.
        keyboardState.reset();
    }
    
    void SFZeroAudioProcessor::processBlock(AudioSampleBuffer &buffer, MidiBuffer &midiMessages)
    {
        int numSamples = buffer.getNumSamples();
        
        keyboardState.processNextMidiBuffer(midiMessages, 0, numSamples, true);
        buffer.clear();
        synth.renderNextBlock(buffer, midiMessages, 0, numSamples);
    }
    
    bool SFZeroAudioProcessor::hasEditor() const
    {
        return true; // (change this to false if you choose to not supply an editor)
    }
    
    AudioProcessorEditor *SFZeroAudioProcessor::createEditor() { return new SFZeroEditor(this); }
    
    void SFZeroAudioProcessor::getStateInformation(MemoryBlock &destData)
    {
        auto obj = new DynamicObject();
        obj->setProperty("sfzFilePath", sfzFile.getFullPathName());
        auto sound = getSound();
        if (sound)
        {
            int subsound = sound->selectedSubsound();
            if (subsound != 0)
                obj->setProperty("subsound", subsound);
        }
        
        MemoryOutputStream out(destData, false);
        JSON::writeToStream(out, var(obj));
    }
    
    void SFZeroAudioProcessor::setStateInformation(const void *data, int sizeInBytes)
    {
        MemoryInputStream in(data, sizeInBytes, false);
        var state = JSON::parse(in);
        var pathVar = state["sfzFilePath"];
        if (pathVar.isString())
        {
            auto sfzFilePath = pathVar.toString();
            if (!sfzFilePath.isEmpty())
            {
                File file(sfzFilePath);
                setSfzFile(&file);
                auto sound = getSound();
                if (sound)
                {
                    var subsoundVar = state["subsound"];
                    if (subsoundVar.isInt())
                        sound->useSubsound(int(subsoundVar));
                }
            }
        }
    }
    
    sfzero::Sound *SFZeroAudioProcessor::getSound()
    {
        SynthesiserSound *sound = synth.getSound(0);
        
        return dynamic_cast<sfzero::Sound *>(sound);
    }
    
    int SFZeroAudioProcessor::numVoicesUsed() { return synth.numVoicesUsed(); }
    
    String SFZeroAudioProcessor::voiceInfoString() { return synth.voiceInfoString(); }
    
    void SFZeroAudioProcessor::loadSound(Thread *thread)
    {
        loadProgress = 0.0;
        synth.clearSounds();
        
        if (!sfzFile.existsAsFile())
        {
            return;
        }
        
        sfzero::Sound *sound;
        auto extension = sfzFile.getFileExtension();
        if ((extension == ".sf2") || (extension == ".SF2"))
        {
            sound = new sfzero::SF2Sound(sfzFile);
        }
        else
        {
            sound = new sfzero::Sound(sfzFile);
        }
        sound->loadRegions();
        sound->loadSamples(&formatManager, &loadProgress, thread);
        if (thread && thread->threadShouldExit())
        {
            delete sound;
            return;
        }
        
        synth.addSound(sound);
    }
    
    SFZeroAudioProcessor::LoadThread::LoadThread(SFZeroAudioProcessor *processorIn)
    : Thread("SFZLoad"), processor(processorIn)
    {
    }
    
    void SFZeroAudioProcessor::LoadThread::run() { processor->loadSound(this); }
}

AudioProcessor *JUCE_CALLTYPE createPluginFilter() { return new sfzero_plugin::SFZeroAudioProcessor(); }

