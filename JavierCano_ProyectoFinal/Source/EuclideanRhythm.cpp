/*
  ==============================================================================

    EuclideanRhythm.cpp
    Created: 26 Apr 2023 2:24:53pm
    Author:  usuario_local

  ==============================================================================
*/

#include <JuceHeader.h>
#include "EuclideanRhythm.h"

using namespace juce;

//==============================================================================
EuclideanRhythm::EuclideanRhythm()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    #pragma region addAndMakeVisible
    addAndMakeVisible(enabled);
    addAndMakeVisible(mute);
    addAndMakeVisible(solo);
    addAndMakeVisible(steps);
    addAndMakeVisible(pulse);
    addAndMakeVisible(rotate);
    addAndMakeVisible(pitch);
    addAndMakeVisible(midiType);
    addAndMakeVisible(velocity);
    addAndMakeVisible(gate);
    addAndMakeVisible(probability);
    addAndMakeVisible(channel);
    #pragma endregion

    steps.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    steps.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 30);
    steps.setNumDecimalPlacesToDisplay(0);
    //knob.setMouseDragSensitivity(getLocalBounds().getWidth()); //Hacer setter
    setLookAndFeel(&lookAndFeel);
}

EuclideanRhythm::~EuclideanRhythm()
{
    setLookAndFeel(nullptr);
}

void EuclideanRhythm::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background
    
    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    //g.setColour (juce::Colours::white);
    //g.setFont (14.0f);
    //g.drawText ("EuclideanRhythm", getLocalBounds(),
    //            juce::Justification::centred, true);   // draw some placeholder text
}

void EuclideanRhythm::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    Rectangle<int> area = getLocalBounds();
    int width = area.getWidth() / 10;
    int height = area.getHeight() / 3;
    Rectangle<int> toggleArea = area.removeFromLeft(width);

    #pragma region setBounds
    enabled.setBounds(toggleArea.removeFromTop(height));
    mute.setBounds(toggleArea.removeFromTop(height));
    solo.setBounds(toggleArea.removeFromTop(height));
    steps.setBounds(area.removeFromLeft(width));
    pulse.setBounds(area.removeFromLeft(width));
    rotate.setBounds(area.removeFromLeft(width));
    pitch.setBounds(area.removeFromLeft(width));
    midiType.setBounds(area.removeFromLeft(width));
    velocity.setBounds(area.removeFromLeft(width));
    gate.setBounds(area.removeFromLeft(width));
    probability.setBounds(area.removeFromLeft(width));
    channel.setBounds(area.removeFromLeft(width));
    #pragma endregion
}

void EuclideanRhythm::randomize()
{
}
