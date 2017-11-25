#pragma once
#include <array>
#include <vector>
#include "ADSR.h"

class ADSRKeyboard
{
public:
	ADSRKeyboard(uint8_t polyphony, float sampleRate) : m_pressedCount(0), m_polyphony(polyphony), m_keys(polyphony, 0), m_envelopes(polyphony, ADSR(sampleRate)), m_currentVoice(0) {}

	uint8_t pressKey(uint8_t keyId)
	{
		auto voice = m_currentVoice;
		if (m_keys[m_currentVoice] == 0)
		{
			++m_pressedCount;
		}
		m_keys[m_currentVoice] = keyId;
		m_envelopes[m_currentVoice].trigger(true);
		m_currentVoice = (m_currentVoice + 1) % m_polyphony;
		return voice;
	}

	uint8_t releaseKey(uint8_t keyId)
	{
		for (uint8_t i = 0; i < m_polyphony; ++i)
		{
			if (m_keys[i] == keyId)
			{
				--m_pressedCount;
				m_envelopes[i].trigger(false);
				m_keys[i] = 0;
				//m_currentVoice = (i + 1) % m_polyphony;
				return i;
			}
		}
		return 0;
	}

	const uint8_t& operator[](uint8_t idx) const
	{
		return m_keys[idx];
	}

	const float getCurrentGain(uint8_t idx)
	{
		return m_envelopes[idx].get();
	}

	void tick()
	{
		for (uint8_t i = 0U; i < m_polyphony; ++i)
		{
			m_envelopes[i].tick();
		}
	}

	void setAttack(float attackTimeMsec)
	{
		for (uint8_t i = 0U; i < m_polyphony; ++i)
		{
			m_envelopes[i].setAttack(attackTimeMsec);
		}
	}

	void setDecay(float decayTimeMsec)
	{
		for (uint8_t i = 0U; i < m_polyphony; ++i)
		{
			m_envelopes[i].setDecay(decayTimeMsec);
		}
	}

	void setRelease(float releaseTimeMsec)
	{
		for (uint8_t i = 0U; i < m_polyphony; ++i)
		{
			m_envelopes[i].setRelease(releaseTimeMsec);
		}
	}

	void setSustain(float sustainLevel)
	{
		for (uint8_t i = 0U; i < m_polyphony; ++i)
		{
			m_envelopes[i].setSustainLevel(sustainLevel);
		}
	}

	uint8_t getPressedCount()
	{
		return m_pressedCount;
	}

protected:
	uint8_t m_polyphony;
	uint8_t m_currentVoice;
	uint8_t m_pressedCount;
	std::vector<uint8_t> m_keys;
	std::vector<ADSR> m_envelopes;
};