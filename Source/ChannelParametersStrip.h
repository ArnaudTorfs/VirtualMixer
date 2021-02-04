#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
// #include "Mixer.h"


class Mixer;

class channel_parameters : public Component
{
public:

	channel_parameters(LookAndFeel_V4* look_);;
	virtual ~channel_parameters() override;
	void paint(Graphics& g) override;
	void resized() override;
	//==============================================================================

	Slider volume_slider;
	Slider gain_knob;
	OwnedArray<Slider> eq_knobs;

private:
};

