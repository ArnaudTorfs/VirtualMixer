/*
  ==============================================================================

	This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{

	my_audio_players = OwnedArray<AudioPlayer>();

	my_audio_players.add(new AudioPlayer());
	my_audio_players.add(new AudioPlayer());

	for (auto* my_audio_player : my_audio_players)
	{
		addAndMakeVisible(my_audio_player);
	}


	my_mixer = new Mixer(&my_audio_players);
	addAndMakeVisible(my_mixer);

	setSize(600, 400);

}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint(Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(Colours::transparentWhite);
}

void MainComponent::resized()
{
	// This is called when the MainComponent is resized.
	// If you add any child components, this is where you should
	// update their positions.

	auto r = getLocalBounds();
	int reduceAmount = 3;

	int number_of_elements = my_audio_players.size() + 1;
	int playerWidth = r.getWidth() / number_of_elements;
	for (int element_index = 0; element_index < number_of_elements; ++element_index)
	{
		if (element_index < number_of_elements / 2)
		{
			my_audio_players[element_index]->setBounds(r.removeFromLeft(playerWidth));
		}
		else if(element_index == number_of_elements / 2)
		{
			my_mixer->setBounds(r.removeFromLeft(playerWidth));
		}
		else
		{
			my_audio_players[element_index-1]->setBounds(r.removeFromLeft(playerWidth));
		}
	}
}
