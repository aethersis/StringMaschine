#pragma once
#include "IFilter.h"

class HighpassFilter : public IFilter
{
public:
	HighpassFilter(float sampleRate);
	float process(float input) override;
	void setFrequency(float cutoff);
	void reset();

private:
	float m_sampleRate;
	float m_previousOutput, m_previousInput;
	float m_alpha;
};