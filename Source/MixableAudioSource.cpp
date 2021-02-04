#include "MixableAudioSource.h"

MixableAudioSource::MixableAudioSource():
	lowPassFilter(dsp::ProcessorDuplicator<
		dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>>(
		dsp::IIR::Coefficients<float>::makeLowPass(44100, 250.f, 1.f))),
	bandPassLowCutFilter(
		dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>>(
			dsp::IIR::Coefficients<float>::makeHighPass(44100, 250.f, 1.f))),
	bandPassHighCutFilter(
		dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>>(
			dsp::IIR::Coefficients<float>::makeLowPass(44100, 2500.f, 1.f))),
	highPassFilter(
		dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>>(
			dsp::IIR::Coefficients<float>::makeHighPass(44100, 2500.f, 1.f)))
{
}

void MixableAudioSource::prepareToPlay(int samplesPerBlockExpected, double _sampleRate)
{
	AudioTransportSource::prepareToPlay(samplesPerBlockExpected, _sampleRate);

	specs.maximumBlockSize = samplesPerBlockExpected;
	specs.sampleRate = samplesPerBlockExpected;
	specs.numChannels = 2;

	// filter.prepare(specs);
	lowPassFilter.prepare(specs);
	bandPassLowCutFilter.prepare(specs);
	bandPassHighCutFilter.prepare(specs);
	highPassFilter.prepare(specs);
}


void MixableAudioSource::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
	AudioTransportSource::getNextAudioBlock(bufferToFill);


	if (isPlaying())
	{
		low_buffer.makeCopyOf(*bufferToFill.buffer);
		mid_buffer.makeCopyOf(*bufferToFill.buffer);
		high_buffer.makeCopyOf(*bufferToFill.buffer);

		dsp::AudioBlock<float> low_block(low_buffer);
		dsp::AudioBlock<float> mid_block(mid_buffer);
		dsp::AudioBlock<float> high_block(high_buffer);

		lowPassFilter.process(dsp::ProcessContextReplacing<float>(low_block));
		bandPassHighCutFilter.process(dsp::ProcessContextReplacing<float>(mid_block));
		bandPassLowCutFilter.process(dsp::ProcessContextReplacing<float>(mid_block));
		highPassFilter.process(dsp::ProcessContextReplacing<float>(high_block));

		for (auto channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel)
		{
			auto* final_buffer = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);

			auto* low_buffer_pointer = low_buffer.getWritePointer(channel, bufferToFill.startSample);
			auto* mid_buffer_pointer = mid_buffer.getWritePointer(channel, bufferToFill.startSample);
			auto* high_buffer_pointer = high_buffer.getWritePointer(channel, bufferToFill.startSample);

			for (auto sample = 0; sample < bufferToFill.numSamples; ++sample)
			{
				final_buffer[sample] = low_buffer_pointer[sample] * low_gain + mid_buffer_pointer[sample] * mid_gain +
					high_buffer_pointer[sample] * high_gain;
				// final_buffer[sample] = low_buffer_pointer[sample];
				// final_buffer[sample] = mid_buffer_pointer[sample];
				// final_buffer[sample] = high_buffer_pointer[sample] + low_buffer_pointer[sample];
			}
		}
	}
}

void MixableAudioSource::setFrequencyBandLevel(Knob_Type knob_type, float value)
{
	float gain = jmap(value, 0.f, 10.f, 0.f, 2.f);
	switch (knob_type)
	{
	case Knob_Type::Gain: break;
	case Knob_Type::HiEq:
		high_gain = gain;
		break;
	case Knob_Type::MidEq:
		mid_gain = gain;
		break;
	case Knob_Type::LowEq:
		low_gain = gain;
		break;
	default: ;
	}
}

void MixableAudioSource::process(dsp::ProcessContextReplacing<float>)
{
	//do processing an output
}

void MixableAudioSource::updateParameters(float frequency)
{
	//Update your parameters
	// *filter.state = *dsp::IIR::Coefficients<float>::makeLowPass(44100, frequency, 0.1f);
}

void MixableAudioSource::set_mid_gain(float value)
{
	mid_gain = value;
}

void MixableAudioSource::set_high_gain(float value)
{
	high_gain = value;
}

void MixableAudioSource::set_low_gain(float value)
{
	low_gain = value;
}
