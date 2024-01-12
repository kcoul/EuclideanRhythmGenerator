/*
  ==============================================================================

	EuclideanRhythm.cpp
	Created: 26 Apr 2023 2:24:53pm
	Author:  usuario_local

  ==============================================================================
*/

#include "EuclideanRhythm.h"

using namespace juce;

int EuclideanRhythm::soloedRhythms = 0;

//==============================================================================
EuclideanRhythm::EuclideanRhythm(AudioProcessorValueTreeState& vts, int i) : valueTreeState(vts), id(i)
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
	addAndMakeVisible(relativePitchSlider);
	addAndMakeVisible(randomMinPitchSlider);
	addAndMakeVisible(randomMaxPitchSlider);
	addAndMakeVisible(midiTypeBox);
	addAndMakeVisible(velocitySlider);
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
	stepsSlider.setRange(Range<double>(1, 32), 1);
	stepsSlider.setTextValueSuffix(" steps");
	stepsSlider.addListener(this);

	pulsesSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	pulsesSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textEntryBoxWidth, textEntryBoxHeight);
	pulsesSlider.setRange(Range<double>(1, 32), 1);
	pulsesSlider.setTextValueSuffix(" pulses");
	pulsesSlider.addListener(this);

	rotateSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	rotateSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textEntryBoxWidth, textEntryBoxHeight);
	rotateSlider.setRange(Range<double>(0, 360), 0);
	rotateSlider.setTextValueSuffix("d rotated");

	pitchSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	pitchSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textEntryBoxWidth, textEntryBoxHeight);
	pitchSlider.setRange(Range<double>(0, 127), 1);
	pitchSlider.setTextValueSuffix(" pitch");

	relativePitchSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	relativePitchSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textEntryBoxWidth, textEntryBoxHeight);
	relativePitchSlider.setRange(Range<double>(-24, 24), 1);
	relativePitchSlider.setTextValueSuffix(" pitch");

	randomMinPitchSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
	randomMinPitchSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textEntryBoxWidth, textEntryBoxHeight);
	randomMinPitchSlider.setRange(Range<double>(0, 127), 1);
	randomMinPitchSlider.setTextValueSuffix(" min pitch");
	randomMinPitchSlider.addListener(this);
	randomMaxPitchSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
	randomMaxPitchSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textEntryBoxWidth, textEntryBoxHeight);
	randomMaxPitchSlider.setRange(Range<double>(0, 127), 1);
	randomMaxPitchSlider.setTextValueSuffix(" max pitch");
	randomMaxPitchSlider.addListener(this);

	midiTypeBox.addItem("Absolute", 1);
	midiTypeBox.addItem("Relative", 2);
	midiTypeBox.addItem("Random Range", 3);
	midiTypeBox.setSelectedId(1);

	velocitySlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	velocitySlider.setTextBoxStyle(Slider::TextBoxBelow, false, textEntryBoxWidth, textEntryBoxHeight);
	velocitySlider.setRange(Range<double>(0, 127), 1);
	velocitySlider.setTextValueSuffix(" velocity");

	probabilitySlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	probabilitySlider.setTextBoxStyle(Slider::TextBoxBelow, false, textEntryBoxWidth, textEntryBoxHeight);
	probabilitySlider.setRange(Range<double>(0, 100), 0);
	probabilitySlider.setTextValueSuffix("% probability");

	channelSlider.setSliderStyle(Slider::SliderStyle::IncDecButtons);
	channelSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textEntryBoxWidth, textEntryBoxHeight);
	channelSlider.setRange(Range<double>(1, 16), 1);
	channelSlider.setTextValueSuffix(" channel");
	#pragma endregion

	#pragma region attachments
	enabledAttachment.reset(new ButtonAttachment(valueTreeState, "enabled" + std::to_string(id), enabledButton));
	random.onClick = [this]() { randomize(); };
	muteAttachment.reset(new ButtonAttachment(valueTreeState, "mute" + std::to_string(id), muteButton));
	soloAttachment.reset(new ButtonAttachment(valueTreeState, "solo" + std::to_string(id), soloButton));

	stepsAttachment.reset(new SliderAttachment(valueTreeState, "steps" + std::to_string(id), stepsSlider));
	pulsesAttachment.reset(new SliderAttachment(valueTreeState, "pulses" + std::to_string(id), pulsesSlider));
	rotateAttachment.reset(new SliderAttachment(valueTreeState, "rotate" + std::to_string(id), rotateSlider));
	pitchAttachment.reset(new SliderAttachment(valueTreeState, "pitch" + std::to_string(id), pitchSlider));
	relativePitchAttachment.reset(new SliderAttachment(valueTreeState, "relativePitch" + std::to_string(id),
		relativePitchSlider));
	randomMinPitchAttachment.reset(new SliderAttachment(valueTreeState, "randomMinPitch" + std::to_string(id),
		randomMinPitchSlider));
	randomMaxPitchAttachment.reset(new SliderAttachment(valueTreeState, "randomMaxPitch" + std::to_string(id),
		randomMaxPitchSlider));
	midiTypeAttachment.reset(new ComboBoxAttachment(valueTreeState, "midiType" + std::to_string(id), midiTypeBox));
	velocityAttachment.reset(new SliderAttachment(valueTreeState, "velocity" + std::to_string(id), velocitySlider));
	probabilityAttachment.reset(new SliderAttachment(valueTreeState, "probability" + std::to_string(id),
		probabilitySlider));
	channelAttachment.reset(new SliderAttachment(valueTreeState, "channel" + std::to_string(id), channelSlider));
	#pragma endregion

	setLookAndFeel(&lookAndFeel);

	currentBeat = previousBeat = -1;

	//Para asegurarnos que el contador de solos no falle
	solo = false;
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
	int width = area.getWidth() /  9;
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
	Rectangle<int> pitchArea = area.removeFromLeft(width);
	pitchSlider.setBounds(pitchArea);
	relativePitchSlider.setBounds(pitchArea);
	randomMinPitchSlider.setBounds(pitchArea.removeFromLeft(width / 2));
	randomMaxPitchSlider.setBounds(pitchArea.removeFromLeft(width / 2));
	midiTypeBox.setBounds(area.removeFromLeft(width));
	velocitySlider.setBounds(area.removeFromLeft(width));
	probabilitySlider.setBounds(area.removeFromLeft(width));
	channelSlider.setBounds(area.removeFromLeft(width));
	#pragma endregion
}

void EuclideanRhythm::sliderValueChanged(Slider* slider)
{
	if ((slider == &stepsSlider || slider == &pulsesSlider) && stepsSlider.getValue() < pulsesSlider.getValue())
		pulsesSlider.setValue(stepsSlider.getValue());

	else if (slider == &randomMaxPitchSlider && randomMaxPitchSlider.getValue() < randomMinPitchSlider.getValue())
		randomMinPitchSlider.setValue(randomMaxPitchSlider.getValue());

	else if (slider == &randomMinPitchSlider && randomMaxPitchSlider.getValue() < randomMinPitchSlider.getValue())
		randomMaxPitchSlider.setValue(randomMinPitchSlider.getValue());
}

void EuclideanRhythm::randomize()
{
	int randomSteps = randomGenerator.nextInt(32) + 1;
	stepsSlider.setValue(randomSteps, dontSendNotification);
	pulsesSlider.setValue(randomGenerator.nextInt(randomSteps) + 1, dontSendNotification);
	pitchSlider.setValue(randomGenerator.nextInt(128), dontSendNotification);
	velocitySlider.setValue(randomGenerator.nextInt(128), dontSendNotification);
}

void EuclideanRhythm::processMIDI(MidiBuffer& incomingMidiMessages, MidiBuffer& generatedBuffer)
{
	if (!enabled || soloedRhythms > 0 && !solo || mute)
		return;

	if (currentBeat != previousBeat) { 
		previousBeat = currentBeat;

		if (randomGenerator.nextFloat() * 100 < probability && getBeat(currentBeat % (int) stepsSlider.getValue())) {
			int newPitch = pitch;

			switch (midiType) {
			case RELATIVE:
				newPitch = referencePitch + relativePitch;
				break;
			case RANDOM:
				newPitch = randomGenerator.nextInt(randomMaxPitch - randomMinPitch + 1) + randomMinPitch;
				break;
			}

			MidiMessage newMessage = MidiMessage::noteOn(channel, newPitch, velocity);
			
			generatedBuffer.addEvent(newMessage, 0);
		}
	}
}

void EuclideanRhythm::updateVariables(float beat)
{
	#pragma region getValue
	rhythm = bresenhamAlgorithm(stepsSlider.getValue(), pulsesSlider.getValue());

	enabled = enabledButton.getToggleStateValue().getValue();
	mute = muteButton.getToggleStateValue().getValue();
	if (!solo) {
		if(solo = soloButton.getToggleStateValue().getValue())
			soloedRhythms++;
	}
	else {
		if (!(solo = soloButton.getToggleStateValue().getValue()))
			soloedRhythms--;
	}

	steps = stepsSlider.getValue();
	pulses = pulsesSlider.getValue();
	rotate = rotateSlider.getValue();
	pitch = pitchSlider.getValue();
	relativePitch = relativePitchSlider.getValue();
	randomMinPitch = randomMinPitchSlider.getValue();
	randomMaxPitch = randomMaxPitchSlider.getValue();
	midiType = (MidiType) (midiTypeBox.getSelectedId() - 1);
	velocity = (uint8) velocitySlider.getValue();
	probability = probabilitySlider.getValue();
	channel = channelSlider.getValue();

	if (midiType == RELATIVE)
		getReferencePitch();
	#pragma endregion

	#pragma region setVisible
	pitchSlider.setVisible(false);
	relativePitchSlider.setVisible(false);
	randomMinPitchSlider.setVisible(false);
	randomMaxPitchSlider.setVisible(false);

	switch (midiType) {
	default:
		pitchSlider.setVisible(true);
		break;
	case RELATIVE:
		relativePitchSlider.setVisible(true);
		break;
	case RANDOM:
		randomMinPitchSlider.setVisible(true);
		randomMaxPitchSlider.setVisible(true);
		break;
	}
	#pragma endregion

	currentBeat = floorf(beat + rotate / 360 * steps);
}

bool EuclideanRhythm::getBeat(int beat)
{
	return rhythm[beat];
}

std::vector<bool> EuclideanRhythm::bresenhamAlgorithm(int steps, int pulses)
{
	float slope = (float) pulses / steps; 
	std::vector<bool> rhythm;
	int previous = -1;
	for (int i = 0; i < steps; i++) {
		int current = floorf(i * slope);
		rhythm.push_back(previous != current);
		previous = current;
	}
	return rhythm;
}

void EuclideanRhythm::getReferencePitch()
{
	int i = id - 1;

	while (i > 0 && (int) valueTreeState.getParameterAsValue("midiType" + std::to_string(i)).getValue() - 1 != ABSOLUTE)
		i--;

	referencePitch = (int) valueTreeState.getParameterAsValue("pitch" + std::to_string(i)).getValue();
}
