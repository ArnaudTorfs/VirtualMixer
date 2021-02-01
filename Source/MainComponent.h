/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "AudioPlayer.h"
#include "Mixer.h"

class AudioPlayer;
//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AudioAppComponent, private MidiInputCallback, public Button::Listener, public ChangeListener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();
    //==============================================================================
	void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
	void releaseResources() override;
	void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;

	void changeListenerCallback(ChangeBroadcaster* source) override;
    //==============================================================================
	void handleIncomingMidiMessage(MidiInput* source, const MidiMessage& message) override;
    void setting_button_clicked() const;
    //==============================================================================
	void buttonClicked(Button*) override;

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
	OwnedArray<AudioPlayer> my_audio_players;
	ScopedPointer<Mixer> my_mixer;

	Rectangle<int> settings_bar;


	std::unique_ptr<TextButton> settingButton;
	AudioFormatManager formatManager;

    //==============================================================================
    // Your private member variables go here...


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
