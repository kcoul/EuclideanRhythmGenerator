/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "EuclideanRhythm.h"

#define ROWS_NUMBER 4

class JavierCano_ProyectoFinalAudioProcessorEditor;

//==============================================================================
/**
*/
class JavierCano_ProyectoFinalAudioProcessor : public juce::AudioProcessor, public juce::Timer
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    JavierCano_ProyectoFinalAudioProcessor();
    ~JavierCano_ProyectoFinalAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    std::vector<std::unique_ptr<EuclideanRhythm>> euclideanRhythm;

    void timerCallback() override;

private:
    //==============================================================================
    JavierCano_ProyectoFinalAudioProcessorEditor* pluginEditor = nullptr;

    float beat;

    juce::AudioProcessorValueTreeState parameters;
    juce::UndoManager undoManager;

    void getCurrentDAWBeat();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JavierCano_ProyectoFinalAudioProcessor)
};
