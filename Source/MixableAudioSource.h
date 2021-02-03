#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class MixableAudioSource : public AudioTransportSource
{
public:
	MixableAudioSource();
	void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
	void getNextAudioBlock(const AudioSourceChannelInfo&) override;
	void setFrequecyBandLevel(float value);
	dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> filter;
	void process(dsp::ProcessContextReplacing<float>);
	void updateParameters(float frequency);
private:

	dsp::ProcessSpec specs;
	double ButterworthFilter(double input);
	double xv[4 + 1], yv[4 + 1];
};
