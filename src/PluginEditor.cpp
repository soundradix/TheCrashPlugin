/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

using namespace juce;

//==============================================================================
TheCrashPluginAudioProcessorEditor::TheCrashPluginAudioProcessorEditor (TheCrashPluginAudioProcessor& p)
    : AudioProcessorEditor (&p),
      audioProcessor (p)
{
    crashFromProcessor.setButtonText ("Crash From Processor");
    crashFromEditor.setButtonText ("Crash From Editor");
    addAndMakeVisible (crashFromEditor);
    addAndMakeVisible (crashFromProcessor);
    
    crashFromEditor.onClick = [] {
        int* ptr = nullptr;
        auto result = 7 / *ptr;
    };

    crashFromProcessor.onClick = [this] {
        audioProcessor.shouldCrash = true;
    };

    setSize (400, 300);
}

TheCrashPluginAudioProcessorEditor::~TheCrashPluginAudioProcessorEditor()
{
}

//==============================================================================
void TheCrashPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void TheCrashPluginAudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced (2);
    crashFromProcessor.setBounds (area.removeFromTop (getHeight() * 0.5));
    crashFromEditor.setBounds (area.removeFromTop (getHeight() * 0.5));
}
