#include "MixableAudioSource.h"

MixableAudioSource::MixableAudioSource():
	filter(dsp::ProcessorDuplicator<
		dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>>(
		dsp::IIR::Coefficients<float>::makeBandPass(44100, 1000.f, 0.1f)))
{
}

void MixableAudioSource::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
	AudioTransportSource::prepareToPlay(samplesPerBlockExpected, sampleRate);

	specs.maximumBlockSize = samplesPerBlockExpected;
	specs.sampleRate = samplesPerBlockExpected;
	specs.numChannels = 2;

	filter.prepare(specs);
}


void MixableAudioSource::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
	AudioTransportSource::getNextAudioBlock(bufferToFill);

	dsp::AudioBlock<float> block(*bufferToFill.buffer);
	// process(dsp::ProcessContextReplacing<float>(block));

	filter.process(dsp::ProcessContextReplacing<float>(block));
	if (isPlaying())
	{
		for (auto channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel)
		{
			auto* buffer = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);

			for (auto sample = 0; sample < bufferToFill.numSamples; ++sample)
			{
			}
		}
	}
}

void MixableAudioSource::setFrequecyBandLevel(float value)
{
	float frequency = jmap(value, 0.f, 10.f, 100.f, 20000.f);
	updateParameters(frequency);
}

void MixableAudioSource::process(dsp::ProcessContextReplacing<float>)
{
	//do processing an output
}

void MixableAudioSource::updateParameters(float frequency)
{
	//Update your parameters
	*filter.state = *dsp::IIR::Coefficients<float>::makeLowPass(44100, frequency, 0.1f);
}


double MixableAudioSource::ButterworthFilter(double input)
{
	/* http://www-users.cs.york.ac.uk/~fisher/cgi-bin/mkfscript */
	/* Butterworth Bandpass filter */
	/* 2nd order */
	/* sample rate - choice of 300 or 3000 Hz */
	/* corner1 freq. = 0.5 or 1 Hz */
	/* corner2 freq. = 20 Hz */
	/* removes high and low frequency noise */
	double dCoefficient1 = 0.0;
	double dCoefficient2 = 0.0;
	double dCoefficient3 = 0.0;
	double dCoefficient4 = 0.0;
	double dCoefficient5 = 0.0;
	double dGain = 0.0;

	/* coefficients will vary depending on sampling rate */
	/* and cornering frequencies                         */
	switch (44100)
	{
	case 300:
		/* 1 to 20 Hz */
		dCoefficient1 = 2.0;
		dCoefficient2 = -0.5698403540;
		dCoefficient3 = 2.5753677309;
		dCoefficient4 = -4.4374523505;
		dCoefficient5 = 3.4318654424;
		dGain = 3.198027802e+01;
		break;

	case 3000:
	default:
		/* 0.5 to 20 Hz */
		dCoefficient1 = 2.0;
		dCoefficient2 = -0.9438788347;
		dCoefficient3 = 3.8299315572;
		dCoefficient4 = -5.8282241502;
		dCoefficient5 = 3.9421714258;
		dGain = 2.406930558e+03;
		break;
	}

	xv[0] = xv[1];
	xv[1] = xv[2];
	xv[2] = xv[3];
	xv[3] = xv[4];
	xv[4] = (double)(input / dGain);
	yv[0] = yv[1];
	yv[1] = yv[2];
	yv[2] = yv[3];
	yv[3] = yv[4];
	yv[4] = (double)((xv[0] + xv[4]) - (dCoefficient1 * xv[2]) + (dCoefficient2 * yv[0]) +
		(dCoefficient3 * yv[1]) + (dCoefficient4 * yv[2]) +
		(dCoefficient5 * yv[3]));

	return (double)(yv[4]);
}
