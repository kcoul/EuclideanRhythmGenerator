/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <vector>

using namespace std;
using namespace juce;

//==============================================================================
JavierCano_ProyectoFinalAudioProcessorEditor::JavierCano_ProyectoFinalAudioProcessorEditor
    (JavierCano_ProyectoFinalAudioProcessor& p) : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (720, 480);
    setResizable(true, false);

    for (int i = 0; i < ROWS_NUMBER; i++) {
        if (i == 0) //Activa el primero
            euclideanRhythm[i].enabled.setToggleState(true, true);

        #pragma region setLookAndFeel
        float hue = (float) i / ROWS_NUMBER;

        euclideanRhythm[i].lookAndFeel.getCurrentColourScheme().setUIColour
            (LookAndFeel_V4::ColourScheme::windowBackground, Colour(hue, .05f, .2f, 1.0f));

        euclideanRhythm[i].lookAndFeel.getCurrentColourScheme().setUIColour
            (LookAndFeel_V4::ColourScheme::widgetBackground, Colour(hue, .05f, .2f, 1.0f));

        euclideanRhythm[i].lookAndFeel.getCurrentColourScheme().setUIColour
            (LookAndFeel_V4::ColourScheme::menuBackground, Colour(hue, .05f, .2f, 1.0f));

        euclideanRhythm[i].lookAndFeel.getCurrentColourScheme().setUIColour
            (LookAndFeel_V4::ColourScheme::outline, Colour(hue, .6f, .95f, 1.0f));

        euclideanRhythm[i].lookAndFeel.getCurrentColourScheme().setUIColour
            (LookAndFeel_V4::ColourScheme::defaultText, Colour(hue, .05f, .2f, 1.0f));

        euclideanRhythm[i].lookAndFeel.getCurrentColourScheme().setUIColour
            (LookAndFeel_V4::ColourScheme::defaultFill, Colour(hue, .05f, .2f, 1.0f));

        euclideanRhythm[i].lookAndFeel.getCurrentColourScheme().setUIColour
            (LookAndFeel_V4::ColourScheme::highlightedText, Colour(hue, .05f, .2f, 1.0f));

        euclideanRhythm[i].lookAndFeel.getCurrentColourScheme().setUIColour
            (LookAndFeel_V4::ColourScheme::highlightedFill, Colour(hue, .05f, .2f, 1.0f));

        euclideanRhythm[i].lookAndFeel.getCurrentColourScheme().setUIColour
            (LookAndFeel_V4::ColourScheme::menuText, Colour(hue, .05f, .2f, 1.0f));

        /**< A colour to use to fill the slider's background. */
        euclideanRhythm[i].lookAndFeel.setColour(Slider::backgroundColourId, 
            Colour(hue, .3f, .04f, 1.0f));

        /**< The colour to draw the thumb with. It's up to the look
            and feel class how this is used. */
        euclideanRhythm[i].lookAndFeel.setColour(Slider::thumbColourId, 
            Colour(hue, .9f, 1.0f, 1.0f));

        /**< The colour to draw the groove that the thumb moves along. */
        euclideanRhythm[i].lookAndFeel.setColour(Slider::trackColourId, 
            Colour(hue, .3f, .6f, 1.0f));

        /**< For rotary sliders, this colour fills the outer curve. */
        euclideanRhythm[i].lookAndFeel.setColour(Slider::rotarySliderFillColourId, 
            Colour(hue, .3f, .6f, 1.0f));

        /**< For rotary sliders, this colour is used to draw the outer curve's outline. */
        euclideanRhythm[i].lookAndFeel.setColour(Slider::rotarySliderOutlineColourId, 
            Colour(hue, .7f, .1f, 1.0f));

        /**< The colour for the text in the text-editor box used for editing the value. */
        euclideanRhythm[i].lookAndFeel.setColour(Slider::textBoxTextColourId, 
            Colour(hue, .0f, .0f, 1.0f));

        /**< The background colour for the text-editor box. */
        euclideanRhythm[i].lookAndFeel.setColour(Slider::textBoxBackgroundColourId, 
            Colour(hue, .0f, 1.0f, 1.0f));

        /**< The text highlight colour for the text-editor box. */
        euclideanRhythm[i].lookAndFeel.setColour(Slider::textBoxHighlightColourId, 
            Colour(hue, .1f, 1.0f, 1.0f));

        /**< The colour to use for a border around the text-editor box. */
        euclideanRhythm[i].lookAndFeel.setColour(Slider::textBoxOutlineColourId, 
            Colour(hue, .7f, .1f, 1.0f));
        #pragma endregion
        
        addAndMakeVisible(euclideanRhythm[i]);
    }
}

JavierCano_ProyectoFinalAudioProcessorEditor::~JavierCano_ProyectoFinalAudioProcessorEditor()
{
}

//==============================================================================
void JavierCano_ProyectoFinalAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void JavierCano_ProyectoFinalAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    Rectangle<int> area = getLocalBounds();
    RectangleList<int> rows = RectangleList<int>();
    int rowHeight = area.getHeight() / ROWS_NUMBER;

    for(int i = 0; i < ROWS_NUMBER; i++)
        rows.add(area.removeFromTop(rowHeight));

    int i = 0;
    for (auto row : rows)
        euclideanRhythm[i++].setBounds(row);
}
