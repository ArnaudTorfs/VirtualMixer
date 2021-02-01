/*
  ==============================================================================

	This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{

	formatManager.registerBasicFormats();

	my_audio_players = OwnedArray<AudioPlayer>();

	my_audio_players.add(new AudioPlayer(&formatManager, &deviceManager));
	my_audio_players.add(new AudioPlayer(&formatManager, &deviceManager));

	for (auto* my_audio_player : my_audio_players)
	{
		addAndMakeVisible(my_audio_player);
	}


	my_mixer = new Mixer(&my_audio_players);
	addAndMakeVisible(my_mixer);


	settingButton = std::make_unique<TextButton>("settingButton");
	addAndMakeVisible(settingButton.get());
	settingButton->setButtonText("Audio Preference");
	settingButton->addListener(this);


	deviceManager.initialise(0, 2, nullptr, true);
	deviceManager.addChangeListener(this);


	setSize(600, 400);

}

MainComponent::~MainComponent()
{

	deviceManager.removeChangeListener(this);
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
}

void MainComponent::releaseResources()
{
}

void MainComponent::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
}

void MainComponent::changeListenerCallback(ChangeBroadcaster* source)

{
	if (source == &deviceManager)
	{
		AudioDeviceManager::AudioDeviceSetup setup;
		deviceManager.getAudioDeviceSetup(setup);

		//if (setup.outputChannels.isZero())
		//{
		//	setAudioFile(nullptr);
		//}
	}
}

void MainComponent::handleIncomingMidiMessage(MidiInput* source, const MidiMessage& message)
{
	int x = 5;
}

void MainComponent::setting_button_clicked() const
{
	std::cout << "settingButton" << std::endl;
	bool showMIDIInputOptions = true;
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
		Colours::wheat,
		true,
		true,
		true);
}

void MainComponent::buttonClicked(Button* button)
{

	if (button == settingButton.get())
	{
		setting_button_clicked();
	}
}


//==============================================================================
void MainComponent::paint(Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(Colours::transparentWhite);

	g.setColour(Colours::white);
	g.fillRect(settings_bar);
}

void MainComponent::resized()
{
	// This is called when the MainComponent is resized.
	// If you add any child components, this is where you should
	// update their positions.

	auto r = getLocalBounds();
	settings_bar = r.removeFromTop(70);
	int reduceAmount = 3;

	int number_of_elements = my_audio_players.size() + 1;
	int playerWidth = r.getWidth() / number_of_elements;
	for (int element_index = 0; element_index < number_of_elements; ++element_index)
	{
		if (element_index < number_of_elements / 2)
		{
			my_audio_players[element_index]->setBounds(r.removeFromLeft(playerWidth));
		}
		else if (element_index == number_of_elements / 2)
		{
			my_mixer->setBounds(r.removeFromLeft(playerWidth));
		}
		else
		{
			my_audio_players[element_index - 1]->setBounds(r.removeFromLeft(playerWidth));
		}
	}


	settingButton->setBounds(settings_bar.removeFromLeft(90).reduced(reduceAmount));


}
