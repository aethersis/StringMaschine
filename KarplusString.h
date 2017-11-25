#pragma once
#include <vector>
#include <functional>
#include <memory>
#include "IFilter.h"
#include "FractionalDelayFilter.h"
#include "OneZeroDampingFilter.h"
#include "TwoZeroDampingFilter.h"
#include "DynamicLevelLowpassFilter.h"
#include "LowpassFilter.h"
#include "HighPassFilter.h"
#include "Tremolo.h"

enum ExcitationType { Momentary, Continuous };
enum DampingType { Constant, Exponential };

class KarplusString
{
public:
	KarplusString(unsigned int delaySize, float sampleRate, const LUTBank& lutBank);
	float update(float input = 0.f, float envelope = 1.f, float tremolo = 1.f); // input is useful for making vocoder-like effects (in that case make generator return 0)
	void pluck(bool onOrOff);

	//setters
	void setFrequency(float desiredFrequency);

	void setDampingCoefficient(float dampingCoefficient);
	void setDampingBrightness(float dampingBrightness);

	void setDynamicLevel(float dynamicLevel);

	void setExcitationType(ExcitationType excitationType);
	void setExcitationStrength(float strength);
	void setExcitationCutoff(float cutoff);
	void setExcitationSource(LUTBank::Waveform source);

private:
	Oscillator m_oscillator;
	ExcitationType m_excitationType;

	FractionalDelayFilter m_fractionalDelay;
	TwoZeroDampingFilter m_dampingFilter;
	DynamicLevelLowpassFilter m_dynamicLevelFilter;
	LowpassFilter m_lowpassFilter;
	HighpassFilter m_highpassFilter;

	bool m_beingPlucked;

	float m_sampleRate;
	float m_currentLength;
	float m_frequency;
	float m_continuousLevelScaleFactor;
	float m_excitationStrength;

	unsigned int m_pluckLength;
	unsigned int m_pluckTimer;
	unsigned int m_currentIndex;

	size_t m_headIndex;
	size_t m_tailIndex;	

	std::vector<float> m_buffer;
};