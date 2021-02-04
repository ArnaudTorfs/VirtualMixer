/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "AudioPlayer.h"
#include "Mixer.h"
#include "TrackSelector.h"

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
    int get_settings_bar_height() const;
    void resized() override;



private:
	void setMidiInput(int index);
	void set_midi_device_choice();

	OwnedArray<AudioPlayer> my_audio_players;
	ScopedPointer<Mixer> my_mixer;
	ScopedPointer<TrackSelector> track_selector_;

	ComboBox midiInputList;                    

	Rectangle<int> settings_bar;


	std::unique_ptr<TextButton> settingButton;
	AudioFormatManager formatManager;

	int midi_input_device_index;

    //==============================================================================
    // Your private member variables go here...


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

class IncomingMessageCallback : public juce::CallbackMessage
{
public:
	IncomingMessageCallback(MainComponent* o, const juce::MidiMessage& m,MidiInput* _source, Mixer*  _mixer)
		: owner(o), message(m), mixer(_mixer), source(_source)
	{}

	void messageCallback() override;

	Component::SafePointer<MainComponent> owner;
	juce::MidiMessage message;
	Mixer* mixer;
	MidiInput* source;
};


