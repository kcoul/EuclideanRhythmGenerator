/*
  ==============================================================================

    EuclideanRhythm.h
    Created: 26 Apr 2023 2:24:53pm
    Author:  usuario_local

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
typedef juce::AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;
typedef juce::AudioProcessorValueTreeState::ComboBoxAttachment ComboBoxAttachment;

//==============================================================================
/*
*/
class EuclideanRhythm : public juce::Component, juce::Slider::Listener
{
public:
    EuclideanRhythm(juce::AudioProcessorValueTreeState& vts, int i);
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
    juce::Slider pitchSlider;
    juce::Slider relativePitchSlider;
    juce::Slider randomMinPitchSlider;
    juce::Slider randomMaxPitchSlider;
    juce::ComboBox midiTypeBox;
    juce::Slider velocitySlider;
    juce::Slider probabilitySlider;
    juce::Slider channelSlider;

    juce::LookAndFeel_V4 lookAndFeel;

    juce::Random randomGenerator;

    virtual void sliderValueChanged(juce::Slider* slider);

    void randomize();

    enum MidiType { ABSOLUTE, RELATIVE, INPUT, RANDOM };

    void processMIDI(juce::MidiBuffer& incomingMidiMessages, juce::MidiBuffer& generatedBuffer);

    void updateVariables(float beat);
    bool getBeat(int beat);

private:
    int id;

    std::vector<bool> rhythm;

    int currentBeat, previousBeat;

    bool enabled;
    bool mute;
    bool solo;
    static int soloedRhythms;

    int steps;
    int pulses;
    float rotate;
    int pitch;
    int referencePitch;
    int relativePitch;
    int randomMinPitch;
    int randomMaxPitch;
    MidiType midiType;
    juce::uint8 velocity;
    float probability;
    int channel;

    std::unique_ptr<ButtonAttachment> enabledAttachment;
    std::unique_ptr<ButtonAttachment> muteAttachment;
    std::unique_ptr<ButtonAttachment> soloAttachment;
    
    std::unique_ptr<SliderAttachment> stepsAttachment;
    std::unique_ptr<SliderAttachment> pulsesAttachment;
    std::unique_ptr<SliderAttachment> rotateAttachment;
    std::unique_ptr<SliderAttachment> pitchAttachment;
    std::unique_ptr<SliderAttachment> relativePitchAttachment;
    std::unique_ptr<SliderAttachment> randomMinPitchAttachment;
    std::unique_ptr<SliderAttachment> randomMaxPitchAttachment;
    std::unique_ptr<ComboBoxAttachment> midiTypeAttachment;
    std::unique_ptr<SliderAttachment> velocityAttachment;
    std::unique_ptr<SliderAttachment> probabilityAttachment;
    std::unique_ptr<SliderAttachment> channelAttachment;

    juce::AudioProcessorValueTreeState& valueTreeState;

    std::vector<bool> bresenhamAlgorithm(int steps, int pulses);

    void getReferencePitch();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EuclideanRhythm)
};
