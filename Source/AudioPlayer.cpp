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
AudioPlayer::AudioPlayer()
	:
	state(TransportState::NoFile)
{
	formatManager.registerBasicFormats();

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

	settingButton = std::make_unique<TextButton>("settingButton");
	addAndMakeVisible(settingButton.get());
	settingButton->setButtonText("Audio Preference");
	settingButton->addListener(this);

	deviceManager.initialise(0, 2, nullptr, true);
	deviceManager.addChangeListener(this);
	sourcePlayer.setSource(&transportSource);
	deviceManager.addAudioCallback(&sourcePlayer);
	waveform = std::make_unique<Waveform>(transportSource, 512);
	addAndMakeVisible(waveform.get());
	transportSource.addChangeListener(this);

	setOpaque(false);
}

AudioPlayer::~AudioPlayer()
{
	deviceManager.removeChangeListener(this);
}

//==============================================================================
void AudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{

}

void AudioPlayer::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{

}

void AudioPlayer::releaseResources()
{

}

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
	settingButton->setBounds(transport_bounds.removeFromLeft(transport_button_width).reduced(reduce_amount));
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
	else if (button == settingButton.get())
	{
		settingButtonClicked();
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

//==============================================================================
//private
void AudioPlayer::openButtonClicked()
{
	FileChooser chooser("Select a audio file to play...",
		{},
		formatManager.getWildcardForAllFormats());
	if (chooser.browseForFileToOpen())
	{
		File file(chooser.getResult());
		waveform->readFromFile(file);
		setAudioFile(&file);
		changeTransportState(TransportState::Stop);
	}
}

void AudioPlayer::settingButtonClicked()
{
	std::cout << "settingButton" << std::endl;
	bool showMIDIInputOptions = false;
	bool showMIDIOutputOption = false;
	bool showChannelAsSterepPairs = true;
	bool hideAdvancedOptions = false;

	AudioDeviceSelectorComponent settings(deviceManager,
		0, 0,//AudioInputChannels: min/Max
		1, 2,//AudioOutputChannels: min/Max
		showMIDIInputOptions,
		showMIDIOutputOption,
		showChannelAsSterepPairs,
		hideAdvancedOptions);
	settings.setSize(500, 400);
	DialogWindow::showModalDialog(String("Audio Settings"),
		&settings,
		TopLevelWindow::getTopLevelWindow(0),
		Colours::white,
		true,
		true,
		true);}

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

void AudioPlayer::changeListenerCallback(ChangeBroadcaster* source)
{
	if (source == &deviceManager)
	{
		AudioDeviceManager::AudioDeviceSetup setup;
		deviceManager.getAudioDeviceSetup(setup);

		if (setup.outputChannels.isZero())
		{
			setAudioFile(nullptr);
		}
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
		readerSource.reset(new AudioFormatReaderSource(formatManager.createReaderFor(*file), true));
		formatReader.reset(formatManager.createReaderFor(*file));
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

