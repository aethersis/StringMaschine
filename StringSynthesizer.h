#pragma once
#include "KarplusString.h"
#include "ADSRKeyboard.h"
#include "LookupTables.h"

class StringSynthesizer
{
public:
	enum FollowType { None, Adsr, Key, Count };

	StringSynthesizer(uint8_t polyphony, float sampleRate, const LUTBank& lutBank);
	float update(float input = 0.f); // input is useful for making vocoder-like effects (in that case make generator return 0)
	void pressKey(uint8_t keyId, uint8_t velocity);
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

	FollowType followDynamicLevel = FollowType::None;
	FollowType followMasterVolume = FollowType::None;
	FollowType followTremoloDepth = FollowType::None;
	FollowType followTremoloFrequency = FollowType::None;
	FollowType followExcitationStrength = FollowType::None;
	FollowType followExcitationCutoff = FollowType::None;
	FollowType followDampingBrightness = FollowType::None;
	FollowType followDampingCoefficient = FollowType::None;

private:
	void handleKeyVelocity(float normalizedVelocity, uint8_t keyIndex);
	void handleKeyAdsr(uint8_t keyIndex);
	float m_dynamicLevel = 1;
	float m_trempoloDepth = 1;
	float m_tremoloFrequency = 1;
	float m_excitationStrength = 1;
	float m_excitationCutoff = 1;
	float m_dampingBrightness = 1;
	float m_dampingCoefficient = 1;

	Tremolo m_tremolo;
	std::vector<KarplusString> m_strings;
	float m_polyphony;
	float m_masterVolume;
	ADSRKeyboard m_keyboard;
};