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
	int playerWidth = r.getWidth() / my_audio_players.size();
	for (AudioPlayer* my_audio_player : my_audio_players)
	{
		my_audio_player->setBounds(r.removeFromLeft(playerWidth).reduced(reduceAmount));
	}
}
