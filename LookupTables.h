#pragma once
#include <algorithm>
#include <random>
#include <memory>
#include <array>
#include "Settings.h"

struct LUTBank
{
public:
	enum class Waveform {Sine, Sawtooth, Noise, Triangle, Square, None}; 
	Sample sineLut[g_lookupTableSize], noiseLut[g_lookupTableSize], triangleLut[g_lookupTableSize], squareLut[g_lookupTableSize], sawtoothLut[g_lookupTableSize], emptyLut[g_lookupTableSize];

	LUTBank();

	const Sample* getLutPointer(Waveform waveform) const;
	
private:
	
	void generateSineLut(Sample *lut);

	void generateSawtoothLut(Sample *lut);

	void generateTriangleLut(Sample *lut);

	void generateSquareLut(Sample *lut);

	void generateNoiseLut(Sample *lut);

	void generateEmptyLut(Sample *lut);
};
