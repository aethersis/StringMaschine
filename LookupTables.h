#pragma once
#include <algorithm>
#include <random>
#include <memory>
#include <array>

struct LUTBank
{
public:
	static const int lookupTableSize = 44100;
	enum class Waveform {Sine, Sawtooth, Noise, Triangle, Square, None}; 
	float sineLut[lookupTableSize], noiseLut[lookupTableSize], triangleLut[lookupTableSize], squareLut[lookupTableSize], sawtoothLut[lookupTableSize], emptyLut[lookupTableSize];

	LUTBank();

	const float* getLutPointer(Waveform waveform) const;
	
private:
	
	void generateSineLut(float *lut);

	void generateSawtoothLut(float *lut);

	void generateTriangleLut(float *lut);

	void generateSquareLut(float *lut);

	void generateNoiseLut(float *lut);

	void generateEmptyLut(float *lut);
};
