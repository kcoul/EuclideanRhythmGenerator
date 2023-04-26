/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "EuclideanRhythm.h"

#define ROWS_NUMBER 4

//==============================================================================
/**
*/
class JavierCano_ProyectoFinalAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    JavierCano_ProyectoFinalAudioProcessorEditor (JavierCano_ProyectoFinalAudioProcessor&);
    ~JavierCano_ProyectoFinalAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JavierCano_ProyectoFinalAudioProcessor& audioProcessor;

    EuclideanRhythm euclideanRhythm[ROWS_NUMBER];

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JavierCano_ProyectoFinalAudioProcessorEditor)
};
