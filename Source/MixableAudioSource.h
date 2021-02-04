#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Knob_Type.h"

class MixableAudioSource : public AudioTransportSource
{
public:
	MixableAudioSource();
	void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
	void getNextAudioBlock(const AudioSourceChannelInfo&) override;
	void setFrequencyBandLevel(Knob_Type knob_type, float value);
	void process(dsp::ProcessContextReplacing<float>);
	void updateParameters(float frequency);
	//=======================================================================
	void set_low_gain(float value);
	void set_mid_gain(float value);
	void set_high_gain(float value);

private:

	// dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> filter;
	dsp::ProcessSpec specs;
	dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> lowPassFilter;
	dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> bandPassLowCutFilter;
	dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> bandPassHighCutFilter;
	dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> highPassFilter;

	AudioBuffer<float> low_buffer;
	AudioBuffer<float> mid_buffer;
	AudioBuffer<float> high_buffer;


	float low_gain = 1.0;
	float mid_gain = 1.0;
	float high_gain = 1.0;
};

