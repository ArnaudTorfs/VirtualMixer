#pragma once

//[Headers]     -- You can add your own extra header files here --
#include  "Waveform.h"
#include "MixableAudioSource.h"
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
	public Component,
	public Button::Listener,
	public FileDragAndDropTarget

{
public:
	AudioPlayer(AudioFormatManager* formatManager, AudioDeviceManager* deviceManager);
	~AudioPlayer();
	//==============================================================================
	float getAudioLevel() const { return audio_level_; }
	void setFrequecyBandLevel(float value);;
	void setAudioLevel(float value);
	//==============================================================================
	void paint(Graphics& g) override;
	void resized() override;
	void buttonClicked(Button *button) override;
	//==============================================================================
	void filesDropped(const StringArray&, int, int) override;
	bool isInterestedInFileDrag(const StringArray& files) override;
	//==============================================================================
	void changeTransportState(TransportState newState);
	TransportState getTransportState() { return state; };
	void playButtonClicked();
	void stopButtonClicked();
private:
	void openButtonClicked();
	void setAudioFile(File* file);


	//==============================================================================
	// Your private member variables go here...
	std::unique_ptr<TextButton> openButton;
	std::unique_ptr<TextButton> playButton;
	std::unique_ptr<TextButton> stopButton;
	std::unique_ptr<AudioFormatReaderSource> readerSource;
	std::unique_ptr<AudioFormatReader> formatReader;
	AudioSourcePlayer sourcePlayer;
	MixableAudioSource transportSource;
	std::unique_ptr<Waveform> waveform;
	TransportState state;


	float audio_level_;
	//==============================================================================
	AudioFormatManager* format_manager_;
	AudioDeviceManager* device_manager_;

	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPlayer);
};

//[EndFile] You can add extra defines here...
//[/EndFile]

