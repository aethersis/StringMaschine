#pragma once
#include <cstdint>
#include <cmath>

enum class AdsrState { Attack, Decay, Sustain, Release, Shutdown };

class ADSR
{
public:
	ADSR(float sampleRate) : m_currentState(AdsrState::Release),
		m_attackTco(expf(-1.5)),
		m_releaseTco(expf(-4.95)),
		m_currentGain(0),
		m_sustainLevel(1.f),
		m_sampleRate(sampleRate)
	{
		setAttack(1);
		setDecay(1);
		setRelease(1);
	}

	float get()
	{
		return m_currentGain;
	}

	AdsrState getState()
	{
		return m_currentState;
	}

	void setAttack(float attackDurationMsec)
	{
		float samples = m_sampleRate * attackDurationMsec / 1000.f;
		m_attackCoeff = expf(-logf((1.f + m_attackTco) / m_attackTco) / samples);
		m_attackOffset = (1.f + m_attackTco) * (1.f - m_attackCoeff);
	}

	void setDecay(float decayDurationMsec)
	{
		float samples = m_sampleRate * decayDurationMsec / 1000.f;
		m_decayCoeff = expf(-logf((1.f + m_releaseTco) / m_releaseTco) / samples);
		m_decayOffset = (m_sustainLevel - m_releaseTco)*(1.f - m_decayCoeff);
	}

	void setSustainLevel(float sustainLevel)
	{
		m_sustainLevel = sustainLevel;
	}

	void setRelease(float releaseDurationMsec)
	{
		float samples = m_sampleRate * releaseDurationMsec / 1000.f;
		m_releaseCoeff = expf(-logf((1.f + m_releaseTco) / m_releaseTco) / samples);
		m_releaseOffset = -m_releaseTco * (1.f - m_releaseCoeff);
	}

	void trigger(bool keyOn)
	{
		if (keyOn)
		{
			m_currentGain = 0;
			m_currentState = AdsrState::Attack;
		}
		else
		{
			m_currentState = AdsrState::Release;
		}
	}

	void tick()
	{
		switch (m_currentState)
		{
		case AdsrState::Attack:
			m_currentGain = m_attackOffset + m_currentGain * m_attackCoeff;
			if (m_currentGain >= 1.f)
			{
				m_currentState = AdsrState::Decay;
				m_currentGain = 1.f;
			}
			return;

		case AdsrState::Decay:
			m_currentGain = m_decayOffset + m_currentGain * m_decayCoeff;
			if (m_currentGain <= m_sustainLevel)
			{
				m_currentState = AdsrState::Sustain;
				m_currentGain = m_sustainLevel;
			}
			return;

		case AdsrState::Sustain:
			m_currentGain = m_sustainLevel;
			return;

		case AdsrState::Release:
			m_currentGain = m_releaseOffset + m_currentGain * m_releaseCoeff;
			if (m_currentGain <= 0)
			{
				m_currentState = AdsrState::Shutdown;
			}
			return;

		case AdsrState::Shutdown:
			m_currentGain = 0.f;
			return;
		}
	}

protected:
	AdsrState m_currentState;
	float m_sampleRate;
	float m_attackCoeff, m_attackOffset, m_attackTco;
	float m_decayCoeff, m_decayOffset;
	float m_releaseCoeff, m_releaseOffset, m_releaseTco;
	float m_sustainLevel, m_currentGain;
};