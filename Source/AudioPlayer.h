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

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include  "Waveform.h"
#include "../JuceLibraryCode/JuceHeader.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
	An auto-generated component, created by the Projucer.

	Describe your class and how it works here!
                                                                    //[/Comments]
*/
enum class TransportState : int {
	NoFile,
	Play,
	Stop,
	Pause
};

class AudioPlayer :
	public AudioAppComponent,
	public Button::Listener,
	public ChangeListener
{
public:
	AudioPlayer();
	~AudioPlayer();
	//==============================================================================
	void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
	void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
	void releaseResources() override;
	//==============================================================================
	void paint(Graphics& g) override;
	void resized() override;
	void buttonClicked(Button *button) override;
	//==============================================================================
private:
	void openButtonClicked();
	void settingButtonClicked();
	void playButtonClicked();
	void stopButtonClicked();
	void changeListenerCallback(ChangeBroadcaster* source) override;
	void changeTransportState(TransportState newState);
	void setAudioFile(File* file);
	//==============================================================================
	// Your private member variables go here...
	std::unique_ptr<TextButton> openButton;
	std::unique_ptr<TextButton> playButton;
	std::unique_ptr<TextButton> stopButton;
	std::unique_ptr<TextButton> settingButton;
	std::unique_ptr<ToggleButton> transportFollowButton;
	std::unique_ptr<AudioFormatReaderSource> readerSource;
	std::unique_ptr<AudioFormatReader> formatReader;
	AudioFormatManager formatManager;
	AudioSourcePlayer sourcePlayer;
	AudioTransportSource transportSource;
	AudioDeviceManager deviceManager;
	std::unique_ptr<Waveform> waveform;
	TransportState state;
	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPlayer);
};

//[EndFile] You can add extra defines here...
//[/EndFile]

