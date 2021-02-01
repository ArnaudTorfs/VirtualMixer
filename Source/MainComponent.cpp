/*
  ==============================================================================

	This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{

	my_audio_player_ = new AudioPlayer();
	addAndMakeVisible(my_audio_player_);

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

	g.setFont(Font(16.0f));
	g.setColour(Colours::white);
	g.drawText("Hello World!", getLocalBounds(), Justification::centred, true);
}

void MainComponent::resized()
{
	// This is called when the MainComponent is resized.
	// If you add any child components, this is where you should
	// update their positions.

	auto r = getLocalBounds();
	auto transportBounds = r;
	int transportButtonWidth = transportBounds.getWidth() / 2;
	int reduceAmount = 3;
	my_audio_player_->setBounds(transportBounds.removeFromLeft(transportButtonWidth).reduced(reduceAmount));
}
