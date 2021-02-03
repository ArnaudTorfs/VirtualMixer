/*
  ==============================================================================

    ChannelParametersStrip.cpp
    Created: 3 Feb 2021 11:55:58am
    Author:  arnau

  ==============================================================================
*/

#include "ChannelParametersStrip.h"

channel_parameters::channel_parameters(LookAndFeel_V4* look_)
{
	addAndMakeVisible(volume_slider);
	volume_slider.setSliderStyle(Slider::LinearVertical);

	volume_slider.setLookAndFeel(look_);
	volume_slider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);

	for (int i = 0; i < 3; ++i)
	{
		Slider* my_knob = new Slider();
		my_knob->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
		my_knob->setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
		addAndMakeVisible(my_knob);
		eq_knobs.add(my_knob);
	}

	addAndMakeVisible(gain_knob);
	gain_knob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
}

channel_parameters::~channel_parameters()
{
}

void channel_parameters::add_listener(Mixer* mixer)
{
	Slider::Listener* listener = (Slider::Listener*)mixer;
	volume_slider.addListener(listener);
	for (auto* eq_knob : eq_knobs)
	{
		eq_knob->addListener(listener);
	}
	gain_knob.addListener(listener);
}

void channel_parameters::resized()
{
	Rectangle<int> r = getLocalBounds();
	const int localWidth = r.getWidth();
	const int localHeight = r.getHeight();


	volume_slider.setBounds(r.removeFromBottom(localHeight / 2).reduced(localWidth / 5, 0));

	const int knob_height = r.getHeight() / 4;
	for (auto* eq_knob : eq_knobs)
	{
		eq_knob->setBounds(r.removeFromBottom(knob_height));
	}

	gain_knob.setBounds(r);
}
