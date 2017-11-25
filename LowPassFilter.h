#pragma once
#include "IFilter.h"

class LowpassFilter : public IFilter
{
public:
	LowpassFilter(float sampleRate);
	float process(float input) override;
	void setFrequency(float cutoff);

private:
	float m_sampleRate;
	float m_previousOutput;
	float m_alpha;
};

class MoogLowPass : public IFilter
{
public:
	MoogLowPass(float sampleRate = 44100.f, float cutoff = 20000.f, float resonance = 0.f)
		: m_sampleRate(sampleRate)
	{
		res = resonance;
		setCutoff(cutoff);
		setResonance(resonance);

		input = in1 = in2 = in3 = in4 = out4 =
			out1 = out2 = out3 = out4 = inputGain = 0.f;
	}

	void setCutoff(float cutoff)
	{
		f = cutoff / (float)m_sampleRate * 1.16f;
		inputGain = 0.35013f * (f*f) * (f*f);
		setResonance(res);
	}

	void setResonance(float resonance)
	{
		fb = 4.f * resonance * (1.f - 0.15f * f * f);
		res = resonance;
	}

	float process(float input) override
	{
		input -= out4 * fb;
		input *= inputGain;

		out1 = input + in1 * 0.3f + (1.f - f) * out1;
		in1 = input;

		out2 = out1 + in2 * 0.3f + (1.f - f) * out2;
		in2 = out1;

		out3 = out2 + in3 * 0.3f + (1.f - f) * out3;
		in3 = out2;

		out4 = out3 + in4 * 0.3f + (1.f - f) * out4;
		in4 = out3;

		return out4;
	}

private:
	float m_sampleRate;
	float f;
	float fb;
	float input;
	float inputGain;
	float in1, in2, in3, in4;
	float out1, out2, out3, out4;
	float res;
};