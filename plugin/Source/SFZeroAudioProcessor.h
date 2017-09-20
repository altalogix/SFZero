#ifndef INCLUDED_SFZEROAUDIOPROCESSOR_H
#define INCLUDED_SFZEROAUDIOPROCESSOR_H

#include "JuceHeader.h"

class Sound;

namespace sfzero_plugin
{
    class SFZeroAudioProcessor : public AudioProcessor
    {
    public:
        SFZeroAudioProcessor();
        ~SFZeroAudioProcessor();
        
        bool silenceInProducesSilenceOut(void) const override { return false; }
        double getTailLengthSeconds(void) const override { return 0; }
        void prepareToPlay(double sampleRate, int samplesPerBlock) override;
        void releaseResources() override;
        void processBlock(AudioSampleBuffer &buffer, MidiBuffer &midiMessages) override;
        
        AudioProcessorEditor *createEditor() override;
        bool hasEditor() const override;
        
        const String getName() const override;
        
        int getNumParameters() override;
        
        float getParameter(int index) override;
        void setParameter(int index, float newValue) override;
        
        const String getParameterName(int index) override;
        const String getParameterText(int index) override;
        
        void setSfzFile(File *newSfzFile);
        void setSfzFileThreaded(File *newSfzFile);
        
        File getSfzFile() { return (sfzFile); }
        bool acceptsMidi() const override;
        bool producesMidi() const override;
        
        int getNumPrograms() override;
        int getCurrentProgram() override;
        void setCurrentProgram(int index) override;
        const String getProgramName(int index) override;
        void changeProgramName(int index, const String &newName) override;
        
        void getStateInformation(MemoryBlock &destData) override;
        void setStateInformation(const void *data, int sizeInBytes) override;
        
        MidiKeyboardState keyboardState;
        double loadProgress;
        
        sfzero::Sound *getSound();
        int numVoicesUsed();
        String voiceInfoString();
        
    protected:
        
        class LoadThread : public Thread
        {
        public:
            LoadThread(SFZeroAudioProcessor *processor);
            void run() override;
            
        protected:
            SFZeroAudioProcessor *processor;
        };
        friend class LoadThread;
        
        File sfzFile;
        sfzero::Synth synth;
        AudioFormatManager formatManager;
        LoadThread loadThread;
        
        void loadSound(Thread *thread = nullptr);
        
    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SFZeroAudioProcessor);
    };
}


#endif // INCLUDED_SFZEROAUDIOPROCESSOR_H
