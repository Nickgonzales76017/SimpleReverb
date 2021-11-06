/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginParameter.h"
#define _USE_MATH_DEFINES
#include <cmath>

//==============================================================================
/**
*/
class SimpleReverbAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    SimpleReverbAudioProcessor();
    ~SimpleReverbAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
        
    juce::AudioProcessorValueTreeState apvts { *this, nullptr, "Parameters", createParameterLayout() };
    
      StringArray waveformItemsUI = {
        "Sine",
        "Triangle",
        "Sawtooth (rising)",
        "Sawtooth (falling)",
        "Square",
        "Square with sloped edges"
    };

    enum waveformIndex {
        waveformSine = 0,
        waveformTriangle,
        waveformSawtooth,
        waveformInverseSawtooth,
        waveformSquare,
        waveformSquareSlopedEdges,
    };

    //======================================

    float lfoPhase;
    float inverseSampleRate;
    float twoPi;

    float lfo (float phase, int waveform);

    //======================================

    PluginParametersManager parameters;

    PluginParameterLinSlider paramDepth;
    PluginParameterLinSlider paramFrequency;
    PluginParameterComboBox paramWaveform;

private:
    juce::dsp::Reverb::Parameters params;
    juce::dsp::Reverb leftReverb, rightReverb; 
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleReverbAudioProcessor)
};
