#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "AudioPlayer.h"
#include "ChannelParametersStrip.h"
//[/Headers]


//==============================================================================
/**
																	//[Comments]
	An auto-generated component, created by the Projucer.

	Describe your class and how it works here!
																	//[/Comments]
*/


class myLookAndFill : public LookAndFeel_V4
{
public:
	void drawLinearSlider(Graphics&, int x, int y, int width, int height, float sliderPos, float minSliderPos,
	                      float maxSliderPos, const Slider::SliderStyle, Slider&) override;
};

class Mixer : public Component, public Slider::Listener
{
public:
	//==============================================================================
	Mixer(OwnedArray<AudioPlayer>* channels);
	~Mixer();

	//==============================================================================
	//[UserMethods]     -- You can add your own custom methods in this section.
	//[/UserMethods]

	void paint(Graphics& g) override;
	void resized() override;

	void sliderValueChanged(Slider* slider) override;

	void set_slider_value(int channel, float value) const;
	void set_crossfader_value(const float value_in_range) const;
	void onMidiPlayStopButtonPressed(int channel) const;
	void set_knob_value(int channel, Knob_Type knob_type, const float value) const;


private:
	OwnedArray<channel_parameters> channels_parameters_;

	myLookAndFill look_;

	ScopedPointer<Slider> cross_fader;
	int number_of_channels_;


	Rectangle<int>* channels_rectangles_{};
	OwnedArray<AudioPlayer>* channels_;
	//[UserVariables]   -- You can add your own custom variables in this section.
	//[/UserVariables]

	//==============================================================================


	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Mixer)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
