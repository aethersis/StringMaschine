#pragma once

class IFilter
{
public:
	virtual ~IFilter() = default;
	virtual float process(float input) = 0;
};