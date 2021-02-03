#include "../JuceLibraryCode/JuceHeader.h"


class Mixer;

enum class Knob_Type: int
{
	Gain,
	HiEq,
	MidEq,
	LowEq,
};

class channel_parameters : public Component
{
public:

	channel_parameters(LookAndFeel_V4* look_);;

	virtual ~channel_parameters() override;

	void paint(Graphics& g) override
	{
	}

	void add_listener(Mixer* mixer);

	void resized() override;

	Slider volume_slider;
	Slider gain_knob;
	OwnedArray<Slider> eq_knobs;
};

#pragma once
