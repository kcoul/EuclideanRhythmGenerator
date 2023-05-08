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

    for (int i = 0; i < ROWS_NUMBER; i++)
        addAndMakeVisible(audioProcessor.euclideanRhythm[i]);
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
        audioProcessor.euclideanRhythm[i++].setBounds(row);
}