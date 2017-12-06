#include <cassert>
#include <algorithm>
#include "KarplusString.h"
#include "AllPassFilter.h"

KarplusString::KarplusString(unsigned int delaySize, float sampleRate, const LUTBank &lutBank)
	: m_buffer(std::vector<float>(delaySize, 0.f)),
	m_headIndex(delaySize - 1U),
	m_tailIndex(0),
	m_currentLength(delaySize),
	m_sampleRate(sampleRate),
	m_beingPlucked(false),
	m_lowpassFilter(44100),
	m_highpassFilter(sampleRate),
	m_excitationStrength(1.f),
	m_oscillator(44100, lutBank)
{
	m_highpassFilter.setFrequency(1.f); // 1Hz high-pass for DC offset cancellation in feedback loop
	setFrequency(55.f);
	setExcitationSource(LUTBank::Waveform::Sine);
	setExcitationType(ExcitationType::Momentary);
}

float KarplusString::update(float input, float envelope, float tremolo)
{
	if (m_oscillator.getWaveform() != LUTBank::Waveform::None)
	{
		input = 0.f;
	}
	if (m_beingPlucked && m_excitationType == ExcitationType::Continuous)
	{
		
		input += m_oscillator.generate();
		if (m_oscillator.getWaveform() != LUTBank::Waveform::None)
		{
			input *= m_continuousLevelScaleFactor;
		}
		input = m_lowpassFilter.process(input);
	}

	auto output = m_buffer[m_tailIndex];
	output = m_fractionalDelay.process(output);

	auto feedback = output;
	feedback = m_highpassFilter.process(feedback); //remove DC offset
	feedback = m_dampingFilter.process(feedback);

	m_buffer[m_headIndex] = input*envelope*tremolo + feedback;

	m_headIndex = (m_headIndex + 1) % m_buffer.size();
	m_tailIndex = (m_tailIndex + 1) % m_buffer.size();
	m_currentIndex = (m_currentIndex + 1) % (unsigned int)m_currentLength;

	output = m_dynamicLevelFilter.process(output);
	
	return output;
}

void KarplusString::pluck(bool on)
{
	m_beingPlucked = on;

	if (m_beingPlucked)
	{
		std::fill(m_buffer.begin(), m_buffer.end(), 0.f);
		m_dampingFilter.reset();
		m_highpassFilter.reset();
	}
	if (m_excitationType == ExcitationType::Momentary && on)
	{
		//fill buffer from tail to head 
		for (int i = m_tailIndex; i < m_tailIndex + (int)m_currentLength; ++i)
		{
			m_buffer[i%m_buffer.size()] = m_excitationStrength * m_oscillator.generate();
		}

		//don't forget to update fractional delay to avoid detuning and noisy artifacts
		m_fractionalDelay.process(m_lowpassFilter.process(m_excitationStrength  * m_oscillator.generate()));
	}
}

void KarplusString::setFrequency(float desiredFrequency)
{
	m_dampingFilter.setDampedStringFrequency(desiredFrequency);
	m_dynamicLevelFilter.setFrequency(desiredFrequency);
	m_oscillator.setFrequency(desiredFrequency);
	m_frequency = desiredFrequency;

	m_currentLength = m_sampleRate / desiredFrequency - .5f;
	float integerPart = 0.f;
	float fractionalPart = modf(m_currentLength, &integerPart);
	m_fractionalDelay.setSize(fractionalPart);

	assert(integerPart <= m_buffer.size());


	m_headIndex = (m_tailIndex + static_cast<int>(m_currentLength)) % m_buffer.size();


	m_continuousLevelScaleFactor = 1.f / powf(m_frequency, 1.f / 3.15f) * m_excitationStrength;

}

void KarplusString::setExcitationSource(LUTBank::Waveform waveform)
{
	m_oscillator.setWaveform(waveform);
}

void KarplusString::setDampingCoefficient(float dampingCoefficient)
{
	m_dampingFilter.setDampingCoefficient(dampingCoefficient);
}

void KarplusString::setDampingBrightness(float dampingBrightness)
{
	m_dampingFilter.setDampingBrightness(dampingBrightness);
}

void KarplusString::setDynamicLevel(float dynamicLevel)
{
	m_dynamicLevelFilter.setLevel(dynamicLevel);
}

void KarplusString::setExcitationType(ExcitationType excitationType)
{
	m_excitationType = excitationType;
}

void KarplusString::setExcitationStrength(float strength)
{
	m_excitationStrength = strength;
}

void KarplusString::setExcitationCutoff(float cutoff)
{
	m_lowpassFilter.setFrequency(cutoff);
}