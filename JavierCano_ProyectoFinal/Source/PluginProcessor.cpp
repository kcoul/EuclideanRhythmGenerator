/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

using namespace juce;

//==============================================================================
JavierCano_ProyectoFinalAudioProcessor::JavierCano_ProyectoFinalAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    //Activa el primero y desactivar el modo relativo
    euclideanRhythm[0].enabledButton.setToggleState(true, true);
    euclideanRhythm[0].midiTypeBox.setItemEnabled(2, false);

    //Cambiar valores por defecto

    for (int i = 0; i < ROWS_NUMBER; i++) {
        #pragma region setLookAndFeel
        float hue = (float)i / ROWS_NUMBER;

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
    }

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

    /*ScopedNoDenormals noDenormals;
    int totalNumInputChannels  = getTotalNumInputChannels();
    int totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }*/

    //Process MIDI messages
    for (int i = 0; i < getRowsNumber(); i++)
        euclideanRhythm[i].processMIDI(midiMessages);
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
}

void JavierCano_ProyectoFinalAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void JavierCano_ProyectoFinalAudioProcessor::timerCallback()
{
    //Actualizar el ritmo
    for (int i = 0; i < ROWS_NUMBER; i++)
        euclideanRhythm[i].updateVariables(floorf(beat));
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JavierCano_ProyectoFinalAudioProcessor();
}
