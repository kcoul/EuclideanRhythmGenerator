/*
  ==============================================================================

    EuclideanRhythm.h
    Created: 26 Apr 2023 2:24:53pm
    Author:  usuario_local

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class EuclideanRhythm : public juce::Component, juce::Slider::Listener
{
public:
    EuclideanRhythm();
    ~EuclideanRhythm() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    juce::ToggleButton enabledButton;
    juce::TextButton random;
    juce::ToggleButton muteButton;
    juce::ToggleButton soloButton;

    juce::Slider stepsSlider;
    juce::Slider pulsesSlider;
    juce::Slider rotateSlider;
    juce::Slider speedSlider;
    juce::Slider pitchSlider;
    juce::ComboBox midiType;
    juce::Slider velocitySlider;
    juce::Slider gateSlider;
    juce::Slider probabilitySlider;
    juce::Slider channelSlider;

    juce::LookAndFeel_V4 lookAndFeel;

    virtual void sliderValueChanged(juce::Slider* slider);

    void randomize();

    enum MidiType { ABSOLUTE, RELATIVE, INPUT, RANDOM };

    void processMIDI(juce::MidiBuffer& midiMessages);

    void updateVariables(int beat);
    bool getBeat(int beat);

private:
    std::vector<bool> bresenhamAlgorithm(int steps, int pulses);

    std::vector<bool> rhythm;

    int currentBeat, previousBeat;

    bool enabled;
    bool mute;
    bool solo;
    /*float steps;
    float pulse;
    float rotate;
    float speed;
    float pitch;
    int midiType;
    float velocity;
    float gate;
    float probability;
    int channel;*/

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EuclideanRhythm)
};
