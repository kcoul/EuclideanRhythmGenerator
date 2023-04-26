/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

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

    rowsNumber = 4;
    for (int i = 0; i < rowsNumber; i++) {
        euclideanRhythm.emplace_back();
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

    for(int i = 0; i < rowsNumber; i++)
        rows.add(area.removeFromTop(area.getHeight() / rowsNumber));

    int i = 0;
    for (auto row : rows)
        euclideanRhythm[i++].setBounds(row);
}
