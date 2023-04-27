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
class EuclideanRhythm  : public juce::Component, juce::Slider::Listener
{
public:
    EuclideanRhythm();
    ~EuclideanRhythm() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    juce::ToggleButton enabled;
    juce::TextButton random;
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
    juce::Slider channel;

    juce::LookAndFeel_V4 lookAndFeel;

    virtual void sliderValueChanged(juce::Slider* slider);

    void randomize();

    enum MidiType { ABSOLUTE, RELATIVE, INPUT, RANDOM };

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EuclideanRhythm)
};
