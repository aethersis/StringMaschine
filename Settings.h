#pragma once
#include <limits>
#include <cstdint>

// Main sound settings. Feel free to modify them
using Sample = int16_t;                         // Used throught the synthesizer, typically to store sound. Use int8_t for 8 bit synthesis (chiptune :D)
												// The bigger the type, the higher the quality but MUCH more CPU/memory intensive

using LargeTypeUnsigned = uint32_t;             // Used for phase accumulators. Must be greater size than Sample

using LargeType = int32_t;                      // Used for normalization. Must be greater size than Sample

constexpr uint32_t g_sampleRate = 44100;        // Sampling frequency - i.e. 44100 is CD Quality. The higher the better quality.

constexpr uint8_t  g_lookupTableSizeBits = 12;   // Size of table (in bits) which stores samples. The lower, the more chiptune-like sound
												 // The higher, the better quality - especially for low frequencies

constexpr uint8_t  g_filterPrecissionBits = 16; // Number of bits used for filter precission. Cannot be higher than number of bits per Sample

constexpr uint8_t  g_polyphony = 24;             // Limit of polyphony. Sets maximum number of active voices in keyboard class. 

												// Don't touch the values below. They are calculated automatically.
constexpr uint16_t          g_lookupTableSize = 1 << g_lookupTableSizeBits;
constexpr float             g_pi = 3.14159265353897f;
constexpr auto              g_bitResolution = 8 * sizeof(Sample);
constexpr auto              g_outputTypeMax = std::numeric_limits<Sample>::max();
constexpr auto              g_phaseAccumulatorMax = std::numeric_limits<LargeTypeUnsigned>::max();
constexpr auto              g_phaseAccumulatorBits = 8 * sizeof(LargeTypeUnsigned);
constexpr LargeTypeUnsigned g_alphaFrequencyMultiplier = 2.f * g_pi * g_sampleRate;
constexpr auto              g_bitsInByte = 8;

static_assert(sizeof(LargeTypeUnsigned) > sizeof(Sample), "LargeTypeUnsigned must be greater than OutputType");
static_assert(sizeof(LargeType) > sizeof(Sample), "LargeType must be greater than OutputType");
static_assert(std::numeric_limits<LargeTypeUnsigned>::min() == 0, "LargeTypeUnsigned must be unsigned");
static_assert(std::numeric_limits<LargeType>::min() < 0, "LargeType must be signed");
static_assert(g_filterPrecissionBits <= 8 * sizeof(Sample), "Filter precission bits must be smaller or equal than bits per sample");
static_assert(g_lookupTableSizeBits > 2 && g_lookupTableSizeBits <= 8 * sizeof(Sample), "Lookup table size must be greater than 4 and smaller than size of Sample type");
