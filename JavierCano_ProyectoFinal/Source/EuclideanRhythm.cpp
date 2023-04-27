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
    addAndMakeVisible(random);
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

    #pragma region setStyle
    enabled.setButtonText("Enabled");
    random.setButtonText("Randomize");
    mute.setButtonText("M");
    solo.setButtonText("S");

    const int textEntryBoxWidth = 100, textEntryBoxHeight = 30;

    steps.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    steps.setTextBoxStyle(Slider::TextBoxBelow, false, textEntryBoxWidth, textEntryBoxHeight);
    steps.setNumDecimalPlacesToDisplay(0);
    steps.setRange(Range<double>(1, 32), 1);
    steps.setValue(4, dontSendNotification);
    steps.setTextValueSuffix(" steps");
    steps.addListener(this);

    pulse.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    pulse.setTextBoxStyle(Slider::TextBoxBelow, false, textEntryBoxWidth, textEntryBoxHeight);
    pulse.setNumDecimalPlacesToDisplay(0);
    pulse.setRange(Range<double>(1, 32), 1);
    pulse.setValue(1, dontSendNotification);
    pulse.setTextValueSuffix(" pulses");
    pulse.addListener(this);

    rotate.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    rotate.setTextBoxStyle(Slider::TextBoxBelow, false, textEntryBoxWidth, textEntryBoxHeight);
    rotate.setNumDecimalPlacesToDisplay(0);
    rotate.setRange(Range<double>(1, 360), 0);
    rotate.setTextValueSuffix("d rotated");

    pitch.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    pitch.setTextBoxStyle(Slider::TextBoxBelow, false, textEntryBoxWidth, textEntryBoxHeight);
    pitch.setNumDecimalPlacesToDisplay(0);
    pitch.setRange(Range<double>(0, 127), 1);
    pitch.setTextValueSuffix(" pitch");

    velocity.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    velocity.setTextBoxStyle(Slider::TextBoxBelow, false, textEntryBoxWidth, textEntryBoxHeight);
    velocity.setNumDecimalPlacesToDisplay(0);
    velocity.setRange(Range<double>(0, 127), 1);
    velocity.setTextValueSuffix(" velocity");

    gate.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gate.setTextBoxStyle(Slider::TextBoxBelow, false, textEntryBoxWidth, textEntryBoxHeight);
    gate.setNumDecimalPlacesToDisplay(0);
    gate.setRange(Range<double>(0, 127), 1);
    gate.setTextValueSuffix(" gate");

    probability.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    probability.setTextBoxStyle(Slider::TextBoxBelow, false, textEntryBoxWidth, textEntryBoxHeight);
    probability.setNumDecimalPlacesToDisplay(2);
    probability.setRange(Range<double>(0, 100), 0);
    probability.setTextValueSuffix("% probability");

    channel.setSliderStyle(Slider::SliderStyle::IncDecButtons);
    channel.setTextBoxStyle(Slider::TextBoxBelow, false, textEntryBoxWidth, textEntryBoxHeight);
    channel.setNumDecimalPlacesToDisplay(0);
    channel.setRange(Range<double>(0, 32), 1);
    channel.setTextValueSuffix(" channel");
    #pragma endregion
    
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
    // clear the background
    g.fillAll (lookAndFeel.getCurrentColourScheme()
        .getUIColour(LookAndFeel_V4::ColourScheme::windowBackground));   
    
    // draw an outline around the component
    g.setColour (lookAndFeel.getCurrentColourScheme()
        .getUIColour(LookAndFeel_V4::ColourScheme::outline));
    g.drawRect (getLocalBounds(), 1);
}

void EuclideanRhythm::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    Rectangle<int> area = getLocalBounds();
    int width = area.getWidth() / 10;
    int height = area.getHeight() / 4;
    Rectangle<int> toggleArea = area.removeFromLeft(width);

    #pragma region setBounds
    enabled.setBounds(toggleArea.removeFromTop(height));
    random.setBounds(toggleArea.removeFromTop(height));
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

void EuclideanRhythm::sliderValueChanged(Slider* slider)
{
    if ((slider == &steps || slider == &pulse) && steps.getValue() < pulse.getValue())
        pulse.setValue(steps.getValue());
}

void EuclideanRhythm::randomize()
{
}
