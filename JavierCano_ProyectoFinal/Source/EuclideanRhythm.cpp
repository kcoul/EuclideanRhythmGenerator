/*
  ==============================================================================

	EuclideanRhythm.cpp
	Created: 26 Apr 2023 2:24:53pm
	Author:  usuario_local

  ==============================================================================
*/

#include "EuclideanRhythm.h"

using namespace juce;
using namespace std;

//==============================================================================
EuclideanRhythm::EuclideanRhythm()
{
	// In your constructor, you should add any child components, and
	// initialise any special settings that your component needs.

	#pragma region addAndMakeVisible
	addAndMakeVisible(enabledButton);
	addAndMakeVisible(random);
	addAndMakeVisible(muteButton);
	addAndMakeVisible(soloButton);
	addAndMakeVisible(stepsSlider);
	addAndMakeVisible(pulsesSlider);
	addAndMakeVisible(rotateSlider);
	addAndMakeVisible(pitchSlider);
	addAndMakeVisible(midiTypeBox);
	addAndMakeVisible(velocitySlider);
	addAndMakeVisible(gateSlider);
	addAndMakeVisible(probabilitySlider);
	addAndMakeVisible(channelSlider);
	#pragma endregion

	#pragma region setStyle
	enabledButton.setButtonText("Enabled");
	random.setButtonText("Randomize");
	muteButton.setButtonText("M");
	soloButton.setButtonText("S");

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
	pitchSlider.setValue(72, dontSendNotification);
	pitchSlider.setTextValueSuffix(" pitch");

	midiTypeBox.addItem("Absolute", 1);
	midiTypeBox.addItem("Relative", 2);
	midiTypeBox.addItem("Incoming MIDI", 3);
	midiTypeBox.addItem("Random Range", 4);
	midiTypeBox.setSelectedId(1);

	velocitySlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	velocitySlider.setTextBoxStyle(Slider::TextBoxBelow, false, textEntryBoxWidth, textEntryBoxHeight);
	velocitySlider.setNumDecimalPlacesToDisplay(0);
	velocitySlider.setRange(Range<double>(0, 127), 1);
	velocitySlider.setValue(127, dontSendNotification);
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
	probabilitySlider.setValue(100, dontSendNotification);
	probabilitySlider.setTextValueSuffix("% probability");

	channelSlider.setSliderStyle(Slider::SliderStyle::IncDecButtons);
	channelSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textEntryBoxWidth, textEntryBoxHeight);
	channelSlider.setNumDecimalPlacesToDisplay(0);
	channelSlider.setRange(Range<double>(1, 16), 1);
	channelSlider.setTextValueSuffix(" channel");
	#pragma endregion

	setLookAndFeel(&lookAndFeel);

	currentBeat = previousBeat = -1;
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
	enabledButton.setBounds(toggleArea.removeFromTop(height));
	random.setBounds(toggleArea.removeFromTop(height));
	muteButton.setBounds(toggleArea.removeFromTop(height));
	soloButton.setBounds(toggleArea.removeFromTop(height));
	stepsSlider.setBounds(area.removeFromLeft(width));
	pulsesSlider.setBounds(area.removeFromLeft(width));
	rotateSlider.setBounds(area.removeFromLeft(width));
	pitchSlider.setBounds(area.removeFromLeft(width));
	midiTypeBox.setBounds(area.removeFromLeft(width));
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
	//Excepcion aqui en Reaper
	if (!enabled || mute)
		return;

	MidiBuffer processedBuffer;

	MidiBuffer::Iterator it(midiMessages);
	MidiMessage currentMessage;
	int samplePosition;
	while (it.getNextEvent(currentMessage, samplePosition)) {
		//DBG("Incoming MIDI: " + currentMessage.getDescription());
		/*if (currentMessage.isNoteOnOrOff()) {
			MidiMessage transposedMessage = currentMessage;
			transposedMessage.setNoteNumber(50);
			processedBuffer.addEvent(transposedMessage, samplePosition);
		}*/
		
		processedBuffer.addEvent(currentMessage, samplePosition);
	}
	
	if (currentBeat != previousBeat) { 
		previousBeat = currentBeat;

		if (getBeat(currentBeat % (int) stepsSlider.getValue())) {
			MidiMessage newMessage = MidiMessage::noteOn(channel, pitch, velocity);
			
			processedBuffer.addEvent(newMessage, ++samplePosition);
		}
	}

	midiMessages.swapWith(processedBuffer); //Peligro de que processed buffer se borre?
}

void EuclideanRhythm::updateVariables(int beat)
{
	rhythm = bresenhamAlgorithm(stepsSlider.getValue(), pulsesSlider.getValue());

	currentBeat = beat;

	enabled = enabledButton.getToggleStateValue().getValue();
	mute = muteButton.getToggleStateValue().getValue();
	solo = soloButton.getToggleStateValue().getValue();

	steps = stepsSlider.getValue();
	pulse = pulsesSlider.getValue();
	rotate = rotateSlider.getValue();
	speed = speedSlider.getValue();
	pitch = pitchSlider.getValue();
	midiType = (MidiType) (midiTypeBox.getSelectedId() - 1);
	velocity = (uint8) velocitySlider.getValue();
	gate = gateSlider.getValue();
	probability = probabilitySlider.getValue();
	channel = channelSlider.getValue();
}

bool EuclideanRhythm::getBeat(int beat)
{
	return rhythm[beat];
}

vector<bool> EuclideanRhythm::bresenhamAlgorithm(int steps, int pulses)
{
	float slope = (float) pulses / steps; 
	vector<bool> rhythm;
	int previous = -1;
	for (int i = 0; i < steps; i++) {
		int current = floorf(i * slope);
		rhythm.push_back(previous != current);
		previous = current;
	}
	return rhythm;
}
