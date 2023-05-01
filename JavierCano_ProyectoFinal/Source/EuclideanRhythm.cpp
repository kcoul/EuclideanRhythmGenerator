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
using namespace std;

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
	addAndMakeVisible(stepsSlider);
	addAndMakeVisible(pulsesSlider);
	addAndMakeVisible(rotateSlider);
	addAndMakeVisible(pitchSlider);
	addAndMakeVisible(midiType);
	addAndMakeVisible(velocitySlider);
	addAndMakeVisible(gateSlider);
	addAndMakeVisible(probabilitySlider);
	addAndMakeVisible(channelSlider);
#pragma endregion

#pragma region setStyle
	enabled.setButtonText("Enabled");
	random.setButtonText("Randomize");
	mute.setButtonText("M");
	solo.setButtonText("S");

	const int textEntryBoxWidth = 100, textEntryBoxHeight = 30;

	stepsSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	stepsSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textEntryBoxWidth, textEntryBoxHeight);
	stepsSlider.setNumDecimalPlacesToDisplay(0);
	stepsSlider.setRange(Range<double>(1, 32), 1);
	stepsSlider.setValue(13, dontSendNotification);
	stepsSlider.setTextValueSuffix(" steps");
	stepsSlider.addListener(this);

	pulsesSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	pulsesSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textEntryBoxWidth, textEntryBoxHeight);
	pulsesSlider.setNumDecimalPlacesToDisplay(0);
	pulsesSlider.setRange(Range<double>(1, 32), 1);
	pulsesSlider.setValue(5, dontSendNotification);
	pulsesSlider.setTextValueSuffix(" pulses");
	pulsesSlider.addListener(this);

	rotateSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	rotateSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textEntryBoxWidth, textEntryBoxHeight);
	rotateSlider.setNumDecimalPlacesToDisplay(0);
	rotateSlider.setRange(Range<double>(0, 360), 0);
	rotateSlider.setTextValueSuffix("d rotated");

	pitchSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	pitchSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textEntryBoxWidth, textEntryBoxHeight);
	pitchSlider.setNumDecimalPlacesToDisplay(0);
	pitchSlider.setRange(Range<double>(0, 127), 1);
	pitchSlider.setTextValueSuffix(" pitch");

	midiType.addItem("Absolute", 1);
	midiType.addItem("Relative", 2);
	midiType.addItem("Incoming MIDI", 3);
	midiType.addItem("Random Range", 4);
	midiType.setSelectedId(1);

	velocitySlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	velocitySlider.setTextBoxStyle(Slider::TextBoxBelow, false, textEntryBoxWidth, textEntryBoxHeight);
	velocitySlider.setNumDecimalPlacesToDisplay(0);
	velocitySlider.setRange(Range<double>(0, 127), 1);
	velocitySlider.setTextValueSuffix(" velocity");

	gateSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	gateSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textEntryBoxWidth, textEntryBoxHeight);
	gateSlider.setNumDecimalPlacesToDisplay(0);
	gateSlider.setRange(Range<double>(0, 127), 1);
	gateSlider.setTextValueSuffix(" gate");

	probabilitySlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	probabilitySlider.setTextBoxStyle(Slider::TextBoxBelow, false, textEntryBoxWidth, textEntryBoxHeight);
	probabilitySlider.setNumDecimalPlacesToDisplay(2);
	probabilitySlider.setRange(Range<double>(0, 100), 0);
	probabilitySlider.setTextValueSuffix("% probability");

	channelSlider.setSliderStyle(Slider::SliderStyle::IncDecButtons);
	channelSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textEntryBoxWidth, textEntryBoxHeight);
	channelSlider.setNumDecimalPlacesToDisplay(0);
	channelSlider.setRange(Range<double>(0, 32), 1);
	channelSlider.setTextValueSuffix(" channel");
#pragma endregion

	setLookAndFeel(&lookAndFeel);
}

EuclideanRhythm::~EuclideanRhythm()
{
	setLookAndFeel(nullptr);
}

void EuclideanRhythm::paint(Graphics& g)
{
	/* This demo code just fills the component's background and
	   draws some placeholder text to get you started.

	   You should replace everything in this method with your own
	   drawing code..
	*/
	// clear the background
	g.fillAll(lookAndFeel.getCurrentColourScheme()
		.getUIColour(LookAndFeel_V4::ColourScheme::windowBackground));

	// draw an outline around the component
	g.setColour(lookAndFeel.getCurrentColourScheme()
		.getUIColour(LookAndFeel_V4::ColourScheme::outline));
	g.drawRect(getLocalBounds(), 1);
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
	stepsSlider.setBounds(area.removeFromLeft(width));
	pulsesSlider.setBounds(area.removeFromLeft(width));
	rotateSlider.setBounds(area.removeFromLeft(width));
	pitchSlider.setBounds(area.removeFromLeft(width));
	midiType.setBounds(area.removeFromLeft(width));
	velocitySlider.setBounds(area.removeFromLeft(width));
	gateSlider.setBounds(area.removeFromLeft(width));
	probabilitySlider.setBounds(area.removeFromLeft(width));
	channelSlider.setBounds(area.removeFromLeft(width));
#pragma endregion
}

void EuclideanRhythm::sliderValueChanged(Slider* slider)
{
	if ((slider == &stepsSlider || slider == &pulsesSlider) && stepsSlider.getValue() < pulsesSlider.getValue())
		pulsesSlider.setValue(stepsSlider.getValue());
}

void EuclideanRhythm::randomize()
{
}

void EuclideanRhythm::processMIDI(MidiBuffer& midiMessages)
{
	MidiBuffer processedBuffer;

	MidiBuffer::Iterator it(midiMessages);
	MidiMessage currentMessage;
	int samplePosition;
	while (it.getNextEvent(currentMessage, samplePosition)) {
		DBG("Incoming MIDI: " + currentMessage.getDescription());
		if (currentMessage.isNoteOnOrOff()) {
			MidiMessage transposedMessage = currentMessage;
			transposedMessage.setNoteNumber(50);
			processedBuffer.addEvent(transposedMessage, samplePosition);
		}
	}

	midiMessages.swapWith(processedBuffer); //Peligro de que processed buffer se borre?
}

void EuclideanRhythm::calculateRhythm()
{
	vector<bool> rhythmBeats = toussaintAlgorithm(stepsSlider.getValue(), pulsesSlider.getValue());

#ifdef _DEBUG
	//Mostrar ritmo por la salida de Visual Studio
	string rhythm = "";
	for (bool beat : rhythmBeats) {
		rhythm.push_back(beat ? 'x' : '.');
		rhythm.push_back(' ');
	}
	DBG("[" + rhythm + "]");
#endif
}

vector<int> EuclideanRhythm::euclidAlgorithm(int steps, int pulses)
{
	vector<int> euclidSequence;
	euclidSequence.push_back(pulses);

	while (pulses > 0) {
		//int q = steps / pulses;
		int r = steps % pulses;

		if(r != 0)
			euclidSequence.push_back(r);

		steps = pulses;
		pulses = r;
	}

	return euclidSequence;
}

vector<bool> EuclideanRhythm::toussaintAlgorithm(int steps, int pulses)
{
	//Fuente: Toussaint's algorithm (https://en.wikipedia.org/wiki/Euclidean_rhythm#Summary_of_algorithm)
	int width = steps;
	int height = 1;

	//Empezamos con una matriz en la que todos los pulsos se dan primero y el resto se queda vacia
	vector<vector<bool>> beatsDistribution(steps, vector<bool>(steps, false));
	for (int i = 0; i < pulses; i++)
		beatsDistribution[0][i] = true;

	//Algoritmo de Euclid para minimizar el apelotonamiento
	vector<int> euclidSequence = euclidAlgorithm(steps, pulses);

	for (int i = 0; i < euclidSequence.size(); i++) {
		//Cortamos y bajamos los ultimos tiempos de la matriz hasta que no se puedan bajar mas
		for (int y = 0; y <= i; y++)
			for (int x = 0; x < euclidSequence[i]; x++)
				beatsDistribution[height + y][x] = beatsDistribution[y][width - 1 - x];

		if (i + 1 < euclidSequence.size()) {
			width -= euclidSequence[i];
			height = steps / width;
			if (steps % width != 0)
				height++;
		}
	}

	//Reconstruccion del rimto
	vector<bool> rhythmBeats;
	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
			rhythmBeats.push_back(beatsDistribution[y][x]);
	rhythmBeats.resize(steps);

	return rhythmBeats;
}
