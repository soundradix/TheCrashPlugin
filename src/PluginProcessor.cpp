/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TheCrashPluginAudioProcessor::TheCrashPluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

TheCrashPluginAudioProcessor::~TheCrashPluginAudioProcessor()
{
}

//==============================================================================
const juce::String TheCrashPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TheCrashPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TheCrashPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TheCrashPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TheCrashPluginAudioProcessor::getTailLengthSeconds() const
{
#if JucePlugin_Enable_ARA
    double tail;
    if (getTailLengthSecondsForARA (tail))
        return tail;
#endif

    return 0.0;
}

int TheCrashPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TheCrashPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TheCrashPluginAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String TheCrashPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void TheCrashPluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void TheCrashPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void TheCrashPluginAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TheCrashPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void TheCrashPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;

    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        if (shouldCrash)
        {
            auto* ugly = buffer.getWritePointer (std::numeric_limits<int>::max(), std::numeric_limits<int>::max());
            *ugly = 0.5f;
        }
    }
}

//==============================================================================
bool TheCrashPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* TheCrashPluginAudioProcessor::createEditor()
{
    return new TheCrashPluginAudioProcessorEditor (*this);
}

//==============================================================================
void TheCrashPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
#if JucePlugin_Enable_ARA
    if (isBoundToARA())
    {
        // When using ARA, all model state is stored in the ARA archives,
        // and the state here in the plug-in instance is limited to
        // view configuration data or other editor settings or remains empty.
    }
    else
#endif
    {
        // You should use this method to store your parameters in the memory block.
        // You could do that either as raw data, or use the XML or ValueTree classes
        // as intermediaries to make it easy to save and load complex data.
    }
}

void TheCrashPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
#if JucePlugin_Enable_ARA
    if (isBoundToARA())
    {
        // When using ARA, all model state is stored in the ARA archives,
        // and the state here in the plug-in instance is limited to
        // view configuration data or other editor settings or remains empty.
    }
    else
#endif
    {
        // You should use this method to restore your parameters from this memory block,
        // whose contents will have been created by the getStateInformation() call.
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TheCrashPluginAudioProcessor();
}
