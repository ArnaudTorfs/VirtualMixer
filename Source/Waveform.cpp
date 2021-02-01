/*
  ==============================================================================

	Waveform.cpp
	Created: 31 Jan 2021 8:43:46pm
	Author:  arnau

  ==============================================================================
*/

#include "Waveform.h"

Waveform::Waveform(AudioTransportSource& transportSource_, int sourceSamplesPerThumbnailSample_)
	:
	transportSource(transportSource_),
	thumbnailCache(2),
	sourceSamplesPerThumbnailSample(sourceSamplesPerThumbnailSample_)
{
	formatManager.registerBasicFormats();
	transportPosition.setStart(0.0);
	thumbnail_total = std::make_unique<AudioThumbnail>(sourceSamplesPerThumbnailSample, formatManager, thumbnailCache);
	thumbnail_zoomed = std::make_unique<AudioThumbnail>(sourceSamplesPerThumbnailSample, formatManager, thumbnailCache);

	thumbnail_total->addChangeListener(this);
	thumbnail_zoomed->addChangeListener(this);

	startTimerHz(60);
}

Waveform::~Waveform()
{
}
//==============================================================================
void Waveform::readFromFile(File& file)
{
	thumbnail_total->setSource(new FileInputSource(file));
	thumbnail_zoomed->setSource(new FileInputSource(file));
	formatReader.reset(formatManager.createReaderFor(file));
	transportPosition = Range<double>(0.0, thumbnail_total->getTotalLength());
}

void Waveform::paint(Graphics& g)
{
	if (thumbnail_total->getTotalLength() > 0.0)
	{
		Rectangle<int> bottomThumbArea = getLocalBounds();
		Rectangle<int> topThumbArea = bottomThumbArea.removeFromTop(getLocalBounds().getHeight() / 2);


		g.setGradientFill(ColourGradient(Colour::fromRGBA(255, 255, 255, 255), topThumbArea.getX(), topThumbArea.getHeight() / 2, Colour::fromRGBA(255, 255, 255, 101), topThumbArea.getWidth(), topThumbArea.getHeight() / 2, false));

		if (transportPosition.getStart() < transportSource.getLengthInSeconds())
		{
			thumbnail_total->drawChannel(g, topThumbArea.reduced(2),
				0.0, thumbnail_total->getTotalLength(), 0, 1.0f);

			//thumbnail_zoomed->drawChannel(g, bottomThumbArea.reduced(2),
			//	transportPosition.getStart(), transportPosition.getEnd(), 0, 1.0f);


		}
		else
		{

			thumbnail_total->drawChannel(g, topThumbArea.reduced(2),
				0.0, thumbnail_total->getTotalLength(), 0, 1.0f);

			thumbnail_zoomed->drawChannel(g, bottomThumbArea.reduced(2),
				transportPosition.getStart(), transportPosition.getEnd(), 0, 1.0f);
		}
	}
	else
	{
		g.setColour(Colours::black);
		g.setFont(28.0f);
		g.drawFittedText("No audio file selected...", getLocalBounds(), Justification::centred, 2);
	}
}

void Waveform::resized()
{

	auto r = getLocalBounds();
	auto transportBounds = r.removeFromBottom(30);
	int transportButtonWidth = transportBounds.getWidth() / 5;
	int reduceAmount = 3;
}

void Waveform::setTransportFollowing(bool transportFollowing)
{
	enableTransportFollow = transportFollowing;
}

//==============================================================================
void Waveform::changeListenerCallback(ChangeBroadcaster* source)
{
	if (source == thumbnail_total.get())
	{
		if (thumbnail_total->getTotalLength() > 0.0)
			repaint();
	}
}

void Waveform::timerCallback()
{
	double currentTime = transportSource.getCurrentPosition();
	transportPosition.setStart(currentTime);
	transportPosition.setEnd(currentTime + 4.0);
	repaint();
}
