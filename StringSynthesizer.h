#pragma once
#include "KarplusString.h"
#include "ADSRKeyboard.h"
#include "LookupTables.h"

class StringSynthesizer
{
public:
	StringSynthesizer(uint8_t polyphony, float sampleRate, const LUTBank& lutBank);
	float update(float input = 0.f); // input is useful for making vocoder-like effects (in that case make generator return 0)
	void pressKey(uint8_t keyId);
	void releaseKey(uint8_t keyId);

	void setDampingCoefficient(float dampingCoefficient);
	void setDampingBrightness(float dampingBrightness);

	void setDynamicLevel(float dynamicLevel);

	void setExcitationType(ExcitationType excitationType);
	void setExcitationStrength(float strength);
	void setExcitationCutoff(float cutoff);
	void setExcitationResonance(float resonance);
	void setExcitationSource(LUTBank::Waveform source);

	void setTremoloDepth(float depth);
	void setTremoloFrequency(float frequency);
	void setTremoloWaveform(LUTBank::Waveform waveform);

	void setAttack(float attack);
	void setDecay(float decay);
	void setSustain(float sustain);
	void setRelease(float release);

	void setMasterVolume(float volume);

private:
	Tremolo m_tremolo;
	std::vector<KarplusString> m_strings;
	float m_polyphony;
	float m_masterVolume;
	ADSRKeyboard m_keyboard;
};