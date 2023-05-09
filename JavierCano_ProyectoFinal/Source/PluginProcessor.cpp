/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

using namespace juce;

AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
{
    AudioProcessorValueTreeState::ParameterLayout parameters;

    for (int i = 0; i < ROWS_NUMBER; i++) {
        parameters.add(std::make_unique<AudioParameterBool>
            ("enabled" + std::to_string(i), "Fila " + std::to_string(i + 1) + ": Enabled", false));
        parameters.add(std::make_unique<AudioParameterBool>
            ("mute" + std::to_string(i), "Fila " + std::to_string(i + 1) + ": Mute", false));
        parameters.add(std::make_unique<AudioParameterBool>
            ("solo" + std::to_string(i), "Fila " + std::to_string(i + 1) + ": Solo", false));
        parameters.add(std::make_unique<AudioParameterInt>
            ("steps" + std::to_string(i), "Fila " + std::to_string(i + 1) + ": Steps", 1, 32, 8));
        parameters.add(std::make_unique<AudioParameterInt>
            ("pulses" + std::to_string(i), "Fila " + std::to_string(i + 1) + ": Pulses", 1, 32, 3));
        parameters.add(std::make_unique<AudioParameterFloat>
            ("rotate" + std::to_string(i), "Fila " + std::to_string(i + 1) + ": Rotate", 
                NormalisableRange<float>(0.0f, 360.0f, 0.01f), 0));
        parameters.add(std::make_unique<AudioParameterInt>
            ("pitch" + std::to_string(i), "Fila " + std::to_string(i + 1) + ": Pitch", 0, 127, 60));
        parameters.add(std::make_unique<AudioParameterInt>
            ("relativePitch" + std::to_string(i), "Fila " + std::to_string(i + 1) + ": Relative pitch", -24, 24, 0));
        parameters.add(std::make_unique<AudioParameterInt>
            ("randomMinPitch" + std::to_string(i), "Fila " + std::to_string(i + 1) + ": Random min pitch", 0, 127, 60));
        parameters.add(std::make_unique<AudioParameterInt>
            ("randomMaxPitch" + std::to_string(i), "Fila " + std::to_string(i + 1) + ": Random max pitch", 0, 127, 60));
        parameters.add(std::make_unique<AudioParameterInt>
            ("midiType" + std::to_string(i), "Fila " + std::to_string(i + 1) + ": MidiType", 1, 4, 1));
        parameters.add(std::make_unique<AudioParameterInt>
            ("velocity" + std::to_string(i), "Fila " + std::to_string(i + 1) + ": Velocity", 0, 127, 127));
        parameters.add(std::make_unique<AudioParameterFloat>
            ("probability" + std::to_string(i), "Fila " + std::to_string(i + 1) + ": Probability", 
                NormalisableRange<float>(0.0f, 100.0f, 0.01), 100.0f));
        parameters.add(std::make_unique<AudioParameterInt>
            ("channel" + std::to_string(i), "Fila " + std::to_string(i + 1) + ": Channel", 1, 16, 1));
    }

    return parameters;
}

//==============================================================================
JavierCano_ProyectoFinalAudioProcessor::JavierCano_ProyectoFinalAudioProcessor()
    : parameters(*this, &undoManager, "PARAMETERS", createParameterLayout())
#ifndef JucePlugin_PreferredChannelConfigurations
     , AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    for (int i = 0; i < ROWS_NUMBER; i++)
        euclideanRhythm.push_back(std::make_unique<EuclideanRhythm>(parameters, i));

    //Desactivar el modo relativo para el primero
    euclideanRhythm[0]->midiTypeBox.setItemEnabled(2, false);

    #pragma region setLookAndFeel
    for (int i = 0; i < ROWS_NUMBER; i++) {
        float hue = (float)i / ROWS_NUMBER;

        euclideanRhythm[i]->lookAndFeel.getCurrentColourScheme().setUIColour
        (LookAndFeel_V4::ColourScheme::windowBackground, Colour(hue, .05f, .2f, 1.0f));

        euclideanRhythm[i]->lookAndFeel.getCurrentColourScheme().setUIColour
        (LookAndFeel_V4::ColourScheme::widgetBackground, Colour(hue, .05f, .2f, 1.0f));

        euclideanRhythm[i]->lookAndFeel.getCurrentColourScheme().setUIColour
        (LookAndFeel_V4::ColourScheme::menuBackground, Colour(hue, .05f, .2f, 1.0f));

        euclideanRhythm[i]->lookAndFeel.getCurrentColourScheme().setUIColour
        (LookAndFeel_V4::ColourScheme::outline, Colour(hue, .6f, .95f, 1.0f));

        euclideanRhythm[i]->lookAndFeel.getCurrentColourScheme().setUIColour
        (LookAndFeel_V4::ColourScheme::defaultText, Colour(hue, .05f, .2f, 1.0f));

        euclideanRhythm[i]->lookAndFeel.getCurrentColourScheme().setUIColour
        (LookAndFeel_V4::ColourScheme::defaultFill, Colour(hue, .05f, .2f, 1.0f));

        euclideanRhythm[i]->lookAndFeel.getCurrentColourScheme().setUIColour
        (LookAndFeel_V4::ColourScheme::highlightedText, Colour(hue, .05f, .2f, 1.0f));

        euclideanRhythm[i]->lookAndFeel.getCurrentColourScheme().setUIColour
        (LookAndFeel_V4::ColourScheme::highlightedFill, Colour(hue, .05f, .2f, 1.0f));

        euclideanRhythm[i]->lookAndFeel.getCurrentColourScheme().setUIColour
        (LookAndFeel_V4::ColourScheme::menuText, Colour(hue, .05f, .2f, 1.0f));

        /**< A colour to use to fill the slider's background. */
        euclideanRhythm[i]->lookAndFeel.setColour(Slider::backgroundColourId,
            Colour(hue, .3f, .04f, 1.0f));

        /**< The colour to draw the thumb with. It's up to the look
            and feel class how this is used. */
        euclideanRhythm[i]->lookAndFeel.setColour(Slider::thumbColourId,
            Colour(hue, .9f, 1.0f, 1.0f));

        /**< The colour to draw the groove that the thumb moves along. */
        euclideanRhythm[i]->lookAndFeel.setColour(Slider::trackColourId,
            Colour(hue, .3f, .6f, 1.0f));

        /**< For rotary sliders, this colour fills the outer curve. */
        euclideanRhythm[i]->lookAndFeel.setColour(Slider::rotarySliderFillColourId,
            Colour(hue, .3f, .6f, 1.0f));

        /**< For rotary sliders, this colour is used to draw the outer curve's outline. */
        euclideanRhythm[i]->lookAndFeel.setColour(Slider::rotarySliderOutlineColourId,
            Colour(hue, .7f, .1f, 1.0f));

        /**< The colour for the text in the text-editor box used for editing the value. */
        euclideanRhythm[i]->lookAndFeel.setColour(Slider::textBoxTextColourId,
            Colour(hue, .0f, .0f, 1.0f));

        /**< The background colour for the text-editor box. */
        euclideanRhythm[i]->lookAndFeel.setColour(Slider::textBoxBackgroundColourId,
            Colour(hue, .0f, 1.0f, 1.0f));

        /**< The text highlight colour for the text-editor box. */
        euclideanRhythm[i]->lookAndFeel.setColour(Slider::textBoxHighlightColourId,
            Colour(hue, .1f, 1.0f, 1.0f));

        /**< The colour to use for a border around the text-editor box. */
        euclideanRhythm[i]->lookAndFeel.setColour(Slider::textBoxOutlineColourId,
            Colour(hue, .7f, .1f, 1.0f));
    }
    #pragma endregion

    Timer::startTimerHz(60);

    beat = 0;
}

JavierCano_ProyectoFinalAudioProcessor::~JavierCano_ProyectoFinalAudioProcessor()
{
    Timer::stopTimer();
}

//==============================================================================
const String JavierCano_ProyectoFinalAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool JavierCano_ProyectoFinalAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool JavierCano_ProyectoFinalAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool JavierCano_ProyectoFinalAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double JavierCano_ProyectoFinalAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int JavierCano_ProyectoFinalAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int JavierCano_ProyectoFinalAudioProcessor::getCurrentProgram()
{
    return 0;
}

void JavierCano_ProyectoFinalAudioProcessor::setCurrentProgram (int index)
{
}

const String JavierCano_ProyectoFinalAudioProcessor::getProgramName (int index)
{
    return {};
}

void JavierCano_ProyectoFinalAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void JavierCano_ProyectoFinalAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

    /*for (int i = 0; i < ROWS_NUMBER; i++) {
        euclideanRhythm[i]->enabledButton.setToggleState(*parameters.getRawParameterValue("enabled" + std::to_string(i)), false);
        euclideanRhythm[i]->muteButton.setToggleState(*parameters.getRawParameterValue("mute" + std::to_string(i)), false);
        euclideanRhythm[i]->soloButton.setToggleState(*parameters.getRawParameterValue("solo" + std::to_string(i)), false);
        euclideanRhythm[i]->stepsSlider.setValue(*parameters.getRawParameterValue("steps" + std::to_string(i)));
        euclideanRhythm[i]->pulsesSlider.setValue(*parameters.getRawParameterValue("pulses" + std::to_string(i)));
        euclideanRhythm[i]->rotateSlider.setValue(*parameters.getRawParameterValue("rotate" + std::to_string(i)));
        euclideanRhythm[i]->pitchSlider.setValue(*parameters.getRawParameterValue("pitch" + std::to_string(i)));
        euclideanRhythm[i]->midiTypeBox.setSelectedId(*parameters.getRawParameterValue("midiType" + std::to_string(i)));
        euclideanRhythm[i]->velocitySlider.setValue(*parameters.getRawParameterValue("velocity" + std::to_string(i)));
        euclideanRhythm[i]->probabilitySlider.setValue(*parameters.getRawParameterValue("probability" + std::to_string(i)));
        euclideanRhythm[i]->channelSlider.setValue(*parameters.getRawParameterValue("channel" + std::to_string(i)));
    }*/
}

void JavierCano_ProyectoFinalAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool JavierCano_ProyectoFinalAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void JavierCano_ProyectoFinalAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    getCurrentDAWBeat();

    //Process MIDI messages
    MidiBuffer generatedBuffer;
    for (int i = 0; i < ROWS_NUMBER; i++)
        euclideanRhythm[i]->processMIDI(midiMessages, generatedBuffer);
    midiMessages.swapWith(generatedBuffer);
}

void JavierCano_ProyectoFinalAudioProcessor::getCurrentDAWBeat()
{
    //Acceder al tiempo del DAW
    AudioPlayHead* playHead = getPlayHead();
    if (playHead != nullptr) {
        auto playPosition = playHead->getPosition();

        if (playPosition != nullopt) {
            auto playPositionInQuarterNotes = playPosition->getPpqPosition();

            if (playPositionInQuarterNotes != nullopt)
                beat = *playPositionInQuarterNotes;
        }
    }
}

//==============================================================================
bool JavierCano_ProyectoFinalAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* JavierCano_ProyectoFinalAudioProcessor::createEditor()
{
    pluginEditor = new JavierCano_ProyectoFinalAudioProcessorEditor(*this);
    return pluginEditor;
}

//==============================================================================
void JavierCano_ProyectoFinalAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.

    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void JavierCano_ProyectoFinalAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

    std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(parameters.state.getType()))
            parameters.replaceState(ValueTree::fromXml(*xmlState));
}

void JavierCano_ProyectoFinalAudioProcessor::timerCallback()
{
    //Actualizar el ritmo
    for (int i = 0; i < ROWS_NUMBER; i++)
        euclideanRhythm[i]->updateVariables(beat);
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JavierCano_ProyectoFinalAudioProcessor();
}
