/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.4

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "AudioPlayer.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
AudioPlayer::AudioPlayer(AudioFormatManager* formatManager, AudioDeviceManager* deviceManager)
	:
	state(TransportState::NoFile), format_manager_(formatManager), device_manager_(deviceManager)
{

	//C++14 style : Making smart pointer and addAndMakeVisible().
	openButton = std::make_unique<TextButton>("openButton");
	addAndMakeVisible(openButton.get());
	openButton->setButtonText("Open");
	openButton->addListener(this);

	playButton = std::make_unique<TextButton>("playButton");
	addAndMakeVisible(playButton.get());
	playButton->setButtonText("Play");
	playButton->addListener(this);
	playButton->setEnabled(false);
	playButton->setColour(TextButton::buttonColourId, Colours::green);

	stopButton = std::make_unique<TextButton>("stopButton");
	addAndMakeVisible(stopButton.get());
	stopButton->setButtonText("Stop");
	stopButton->addListener(this);
	stopButton->setEnabled(false);
	stopButton->setColour(TextButton::buttonColourId, Colours::red);


	sourcePlayer.setSource(&transportSource);
	device_manager_->addAudioCallback(&sourcePlayer);
	waveform = std::make_unique<Waveform>(transportSource, 512);
	addAndMakeVisible(waveform.get());



	setOpaque(false);
}

AudioPlayer::~AudioPlayer()
{
}

//==============================================================================


//==============================================================================
void AudioPlayer::paint(Graphics& g)
{
	g.fillAll(Colours::transparentWhite);
}

void AudioPlayer::resized()
{
	auto r = getLocalBounds();

	auto transport_bounds = r.removeFromBottom(30);
	const int transport_button_width = transport_bounds.getWidth() / 4;
	const int reduce_amount = 3;

	openButton->setBounds(transport_bounds.removeFromLeft(transport_button_width).reduced(reduce_amount));
	playButton->setBounds(transport_bounds.removeFromLeft(transport_button_width).reduced(reduce_amount));
	stopButton->setBounds(transport_bounds.removeFromLeft(transport_button_width).reduced(reduce_amount));
	waveform->setBounds(r);
}

void AudioPlayer::buttonClicked(Button *button)
{
	if (button == openButton.get())
	{
		openButtonClicked();
	}
	else if (button == playButton.get())
	{
		playButtonClicked();
	}
	else if (button == stopButton.get())
	{
		stopButtonClicked();
	}
}

void AudioPlayer::filesDropped(const StringArray& file_string, int, int)
{
	File file(file_string[0]);
	waveform->readFromFile(file);
	setAudioFile(&file);
	changeTransportState(TransportState::Stop);
	DBG(file.getFullPathName());
}

bool AudioPlayer::isInterestedInFileDrag(const StringArray& files)
{
	const String file_name = files[0];
	if (file_name.contains(".wav") || file_name.contains(".mp3"))
	{
		return true;

	}
	return false;
}


void AudioPlayer::setFrequecyBandLevel(float value)
{
	transportSource.setFrequecyBandLevel(value);
}

void AudioPlayer::setAudioLevel(float value)
{
	//Receive a value between 0 and 10.0
	audio_level_ = value / 10;
	//Set a Value between 0 and 1;
	transportSource.setGain(audio_level_);
}
//==============================================================================
//private
void AudioPlayer::openButtonClicked()
{
	FileChooser chooser("Select a audio file to play...",
		{},
		format_manager_->getWildcardForAllFormats());
	if (chooser.browseForFileToOpen())
	{
		File file(chooser.getResult());
		waveform->readFromFile(file);
		setAudioFile(&file);
		changeTransportState(TransportState::Stop);
	}
}


void AudioPlayer::playButtonClicked()
{
	std::cout << "playButton clicked" << std::endl;
	transportSource.start();
	changeTransportState(TransportState::Play);
}

void AudioPlayer::stopButtonClicked()
{
	std::cout << "stopButton clicked" << std::endl;
	if (state == TransportState::Pause)
	{
		transportSource.setPosition(0.0);
		changeTransportState(TransportState::Stop);
	}
	else
	{
		transportSource.stop();
		changeTransportState(TransportState::Pause);
	}
}


void AudioPlayer::changeTransportState(TransportState newState)
{
	if (state != newState)
	{
		state = newState;
		switch (state) {
		case TransportState::NoFile:
			std::cout << "NoFile" << std::endl;
			playButton->setEnabled(false);
			stopButton->setEnabled(false);
			break;
		case TransportState::Play:
			std::cout << "Play" << std::endl;
			playButton->setEnabled(false);
			stopButton->setButtonText("Pause");
			stopButton->setEnabled(true);
			break;
		case TransportState::Stop:
			std::cout << "Stop" << std::endl;
			playButton->setButtonText("Play");
			playButton->setEnabled(true);
			stopButton->setButtonText("Stop");
			stopButton->setEnabled(false);
			break;
		case TransportState::Pause:
			std::cout << "Pause" << std::endl;
			playButton->setButtonText("Restart");
			playButton->setEnabled(true);
			stopButton->setButtonText("Back to head");
			stopButton->setEnabled(true);
			break;
		}
	}
}

void AudioPlayer::setAudioFile(File* file)
{
	if (file == nullptr)
	{
		if (transportSource.isPlaying())
		{
			transportSource.stop();
		}

		transportSource.setSource(nullptr);
		sourcePlayer.setSource(nullptr);
	}
	else
	{
		transportSource.setSource(nullptr);
		readerSource.reset(new AudioFormatReaderSource(format_manager_->createReaderFor(*file), true));
		formatReader.reset(format_manager_->createReaderFor(*file));
		transportSource.setSource(readerSource.get(),
			0,
			nullptr,
			formatReader->sampleRate,
			formatReader->numChannels);
		sourcePlayer.setSource(&transportSource);
	}
}




//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

	This is where the Projucer stores the metadata that describe this GUI layout, so
	make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="AudioPlayer" componentName=""
				 parentClasses="public Component" constructorParams="" variableInitialisers=""
				 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
				 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff323e44"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

