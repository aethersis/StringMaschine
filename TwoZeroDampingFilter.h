#pragma once
#include "IFilter.h"

class TwoZeroDampingFilter : public IFilter
{
public:
	TwoZeroDampingFilter();
	void setDampingCoefficient(float dampingCoefficient);
	void setDampingBrightness(float dampingBrightness);
	void setDampedStringFrequency(float frequency);
	void reset();
	float process(float input);

private:
	float m_dampingCoefficient;
	float m_dampingBrightness;
	float m_previous, m_pastPrevious; 
	float m_stringFrequency;
};