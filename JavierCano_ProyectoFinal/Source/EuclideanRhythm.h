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
class EuclideanRhythm  : public juce::Component
{
public:
    EuclideanRhythm();
    ~EuclideanRhythm() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::LookAndFeel_V4 lookAndFeel;

    juce::Slider knob;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EuclideanRhythm)
};
