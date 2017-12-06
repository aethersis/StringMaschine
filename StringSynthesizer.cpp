#include "StringSynthesizer.h"
StringSynthesizer::StringSynthesizer(uint8_t polyphony, float sampleRate, const LUTBank& lutBank)
	: m_strings(16, KarplusString(sampleRate / 10, sampleRate, lutBank)),
	m_keyboard(16, sampleRate),
	m_polyphony(16),
	m_tremolo(lutBank),
	m_masterVolume(1)
{
}

float StringSynthesizer::update(float input)
{
	float output = 0.f;
	uint8_t idx = 0;
	m_keyboard.tick();
	auto tremoloSample = m_tremolo.process();
	for (uint8_t idx=0; idx<m_polyphony; ++idx)
	{
		handleKeyAdsr(idx);
		output += m_strings[idx].update(input, 1.f, tremoloSample) * m_keyboard.getCurrentGain(idx);
	}

	return m_masterVolume * output / m_polyphony;
}

void StringSynthesizer::pressKey(uint8_t keyId, uint8_t velocity)
{
	const float normalizedVelocity = velocity / 127.f;
	const float tuningBaseTone = 440.f;
	auto frequency = (tuningBaseTone / 32.f) * powf(2,((keyId - 9) / 12.f));
	auto keyIndex = m_keyboard.pressKey(keyId);

	m_strings[keyIndex].setFrequency(frequency);

	handleKeyVelocity(normalizedVelocity, keyIndex);

	m_strings[keyIndex].pluck(true);
}

void StringSynthesizer::releaseKey(uint8_t keyId)
{
	auto key = m_keyboard.releaseKey(keyId);
	m_strings[key % (int)m_polyphony].pluck(false);
}

void StringSynthesizer::setDampingCoefficient(float dampingCoefficient)
{
	m_dampingCoefficient = dampingCoefficient;
	for (auto& string : m_strings)
	{
		string.setDampingCoefficient(dampingCoefficient);
	}
}

void StringSynthesizer::setDampingBrightness(float dampingBrightness)
{
	m_dampingBrightness = dampingBrightness;
	for (auto& string : m_strings)
	{
		string.setDampingBrightness(dampingBrightness);
	}
}

void StringSynthesizer::setDynamicLevel(float dynamicLevel)
{
	m_dynamicLevel = dynamicLevel;
	for (auto& string : m_strings)
	{
		string.setDynamicLevel(dynamicLevel);
	}
}

void StringSynthesizer::setTremoloDepth(float depth)
{
	m_trempoloDepth = depth;
	m_tremolo.setAmplitude(depth);
}

void StringSynthesizer::setTremoloFrequency(float frequency)
{
	m_tremoloFrequency = frequency;
	m_tremolo.setFrequency(frequency);
}

void StringSynthesizer::setTremoloWaveform(LUTBank::Waveform waveform)
{
	m_tremolo.setWaveform(waveform);
}

void StringSynthesizer::setExcitationType(ExcitationType excitationType)
{
	for (auto& string : m_strings)
	{
		string.setExcitationType(excitationType);
	}
}

void StringSynthesizer::setExcitationStrength(float strength)
{
	m_excitationStrength = strength;
	for (auto& string : m_strings)
	{
		string.setExcitationStrength(strength);
	}
}

void StringSynthesizer::setExcitationCutoff(float cutoff)
{
	m_excitationCutoff = cutoff;
	for (auto& string : m_strings)
	{
		string.setExcitationCutoff(cutoff);
	}
}

void StringSynthesizer::setExcitationResonance(float resonance)
{

}

void StringSynthesizer::setExcitationSource(LUTBank::Waveform source)
{
	for (auto& string : m_strings)
	{
		string.setExcitationSource(source);
	}
}

void StringSynthesizer::setAttack(float attack)
{
	m_keyboard.setAttack(attack);
}

void StringSynthesizer::setDecay(float decay)
{
	m_keyboard.setDecay(decay);
}

void StringSynthesizer::setSustain(float sustain)
{
	m_keyboard.setSustain(sustain);
}

void StringSynthesizer::setRelease(float release)
{
	m_keyboard.setRelease(release);
}

void StringSynthesizer::setMasterVolume(float volume)
{
	m_masterVolume = volume;
}

void StringSynthesizer::handleKeyVelocity(float normalizedVelocity, uint8_t keyIndex)
{
	if (followDynamicLevel == FollowType::Key)
	{
		m_strings[keyIndex].setDynamicLevel(m_dynamicLevel * normalizedVelocity);
	}
	if (followTremoloDepth == FollowType::Key)
	{
		m_tremolo.setAmplitude(m_trempoloDepth * normalizedVelocity);
	}
	if (followTremoloFrequency == FollowType::Key)
	{
		m_tremolo.setFrequency(m_tremoloFrequency * normalizedVelocity);
	}
	if (followExcitationStrength == FollowType::Key)
	{
		m_strings[keyIndex].setExcitationStrength(m_excitationStrength * normalizedVelocity);
	}
	if (followExcitationCutoff == FollowType::Key)
	{
		m_strings[keyIndex].setExcitationCutoff(m_excitationCutoff * normalizedVelocity);
	}
	if (followDampingBrightness == FollowType::Key)
	{
		m_strings[keyIndex].setDampingBrightness(m_excitationCutoff * normalizedVelocity);
	}
	if (followDampingCoefficient == FollowType::Key)
	{
		m_strings[keyIndex].setDampingCoefficient(m_excitationCutoff * normalizedVelocity);
	}
}

void StringSynthesizer::handleKeyAdsr(uint8_t keyIndex)
{
	float adsrState = m_keyboard.getCurrentGain(keyIndex);

	if (followDynamicLevel == FollowType::Adsr)
	{
		m_strings[keyIndex].setDynamicLevel(m_dynamicLevel * adsrState);
	}
	if (followTremoloDepth == FollowType::Adsr)
	{
		m_tremolo.setAmplitude(m_trempoloDepth * adsrState);
	}
	if (followTremoloFrequency == FollowType::Adsr)
	{
		m_tremolo.setFrequency(m_tremoloFrequency * adsrState);
	}
	if (followExcitationStrength == FollowType::Adsr)
	{
		m_strings[keyIndex].setExcitationStrength(m_excitationStrength * adsrState);
	}
	if (followExcitationCutoff == FollowType::Adsr)
	{
		m_strings[keyIndex].setExcitationCutoff(m_excitationCutoff * adsrState);
	}
	if (followDampingBrightness == FollowType::Adsr)
	{
		m_strings[keyIndex].setDampingBrightness(m_excitationCutoff * adsrState);
	}
	if (followDampingCoefficient == FollowType::Adsr)
	{
		m_strings[keyIndex].setDampingCoefficient(m_excitationCutoff * adsrState);
	}
}