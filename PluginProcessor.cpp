/*
==============================================================================

This file was auto-generated!

It contains the basic framework code for a JUCE plugin processor.

==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginGui.h"


//==============================================================================
StringMaschineAudioProcessor::StringMaschineAudioProcessor() :
	m_lutBank(),
	m_karplusString(16, 44100, m_lutBank)
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", AudioChannelSet::stereo(), true)
#endif
	),
#endif

{
}

StringMaschineAudioProcessor::~StringMaschineAudioProcessor()
{
}

//==============================================================================
const String StringMaschineAudioProcessor::getName() const
{
	return JucePlugin_Name;
}

bool StringMaschineAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
	return true;
#else
	return false;
#endif
}

bool StringMaschineAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
	return true;
#else
	return false;
#endif
}

double StringMaschineAudioProcessor::getTailLengthSeconds() const
{
	return 0.0;
}

int StringMaschineAudioProcessor::getNumPrograms()
{
	return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
				// so this should be at least 1, even if you're not really implementing programs.
}

int StringMaschineAudioProcessor::getCurrentProgram()
{
	return 0;
}

void StringMaschineAudioProcessor::setCurrentProgram(int index)
{
}

const String StringMaschineAudioProcessor::getProgramName(int index)
{
	return{};
}

void StringMaschineAudioProcessor::changeProgramName(int index, const String& newName)
{
}

//==============================================================================
void StringMaschineAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	// Use this method as the place to do any pre-playback
	// initialisation that you need..
}

void StringMaschineAudioProcessor::releaseResources()
{
	// When playback stops, you can use this as an opportunity to free up any
	// spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool StringMaschineAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
	ignoreUnused(layouts);
	return true;
#else
	// This is the place where you check if the layout is supported.
	// In this template code we only support mono or stereo.
	if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
		&& layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void StringMaschineAudioProcessor::processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	const int totalNumInputChannels = getTotalNumInputChannels();
	const int totalNumOutputChannels = getTotalNumOutputChannels();

	// In case we have more outputs than inputs, this code clears any output
	// channels that didn't contain input data, (because these aren't
	// guaranteed to be empty - they may contain garbage).
	// This is here to avoid people getting screaming feedback
	// when they first compile a plugin, but obviously you don't need to keep
	// this code if your algorithm always overwrites all the output channels.
	for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());

	auto input = buffer.getReadPointer(0);
	auto output1 = buffer.getWritePointer(0);
	auto output2 = buffer.getWritePointer(1);

	int time;
	MidiMessage m;
	float volume;
	for (MidiBuffer::Iterator i(midiMessages); i.getNextEvent(m, time);)
	{
		auto key = m.getNoteNumber();
		if (m.isNoteOn())
		{
			volume = m.getVelocity() / 127.f;
			m_karplusString.pressKey(key);
		}
		else if (m.isNoteOff())
		{
			volume = 0;
			m_karplusString.releaseKey(key);
		}
	}

	for (auto i = 0; i < buffer.getNumSamples(); ++i)
	{
		output1[i] = m_karplusString.update(input[i]);
		output2[i] = output1[i];
	}
	// ..do something to the data...
}

//==============================================================================
bool StringMaschineAudioProcessor::hasEditor() const
{
	return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* StringMaschineAudioProcessor::createEditor()
{
	return new PluginGui(*this);
}

//==============================================================================
void StringMaschineAudioProcessor::getStateInformation(MemoryBlock& destData)
{
	// You should use this method to store your parameters in the memory block.
	// You could do that either as raw data, or use the XML or ValueTree classes
	// as intermediaries to make it easy to save and load complex data.
}

void StringMaschineAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
	// You should use this method to restore your parameters from this memory block,
	// whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
	return new StringMaschineAudioProcessor();
}
