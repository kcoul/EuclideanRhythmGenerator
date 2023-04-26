/*
  ==============================================================================

    EuclideanRhythm.h
    Created: 26 Apr 2023 2:24:53pm
    Author:  usuario_local

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

enum KnobsIDs {

};

//==============================================================================
/*
*/
class EuclideanRhythm  : public juce::Component
{
public:
    EuclideanRhythm();
    ~EuclideanRhythm() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    juce::LookAndFeel_V4 lookAndFeel;

    void randomize();

    enum MidiType { ABSOLUTE, RELATIVE, INPUT, RANDOM };
private:
    juce::ToggleButton enabled;

    juce::ToggleButton mute;
    juce::ToggleButton solo;
    
    juce::Slider steps;
    juce::Slider pulse;
    juce::Slider rotate;
    juce::Slider speed;
    juce::Slider pitch;
    juce::ComboBox midiType;
    juce::Slider velocity;
    juce::Slider gate;
    juce::Slider probability;

    juce::ComboBox channel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EuclideanRhythm)
};
