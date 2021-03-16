// PluginEditor - UI
#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class TheCrashPluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    TheCrashPluginAudioProcessorEditor (TheCrashPluginAudioProcessor&);
    ~TheCrashPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TheCrashPluginAudioProcessor& audioProcessor;

    juce::TextButton crashFromEditor, crashFromProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TheCrashPluginAudioProcessorEditor)
};
