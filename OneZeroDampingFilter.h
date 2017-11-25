#pragma once
#include "IFilter.h"

class OneZeroDampingFilter : public IFilter
{
public:
	OneZeroDampingFilter();
	void setDampingCoefficient(float dampingCoefficient);
	void setDampingBrightness(float dampingBrightness);
	void setDampedStringFrequency(float frequency);
	float process(float input);

private:
	float m_dampingCoefficient;
	float m_dampingBrightness;
	float m_previous; 
	float m_stringFrequency;
};