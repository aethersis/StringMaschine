#pragma once
#include "IFilter.h"

class DynamicLevelLowpassFilter : public IFilter
{
public:
	DynamicLevelLowpassFilter();
	float process(float input) override;
	void setLevel(float level);
	void setFrequency(float cutoff);

private:
	float m_previousInput, m_previousOutput;
	float m_b0, m_a0;
	float m_level, m_levelAttenuation;
};