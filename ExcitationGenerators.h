#pragma once

enum Waveform { Sawtooth, Uniform, Sine, External };

float uniformExcitation(float stringLength, float currentPosition);
float sawtoothExcitation(float stringLength, float currentPosition);
float sineExcitation(float stringLength, float currentPosition);
float noExcitation(float stringLength, float currentPosition);