#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "AudioPlayer.h"
//[/Headers]


//==============================================================================
/**
																	//[Comments]
	An auto-generated component, created by the Projucer.

	Describe your class and how it works here!
																	//[/Comments]
*/

class Mixer;

class channel_parameters : public Component
{
public:

	channel_parameters(LookAndFeel_V4* look_)
	{
		addAndMakeVisible(volume_slider);
		volume_slider.setSliderStyle(Slider::LinearVertical);

		volume_slider.setLookAndFeel(look_);
		volume_slider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);

		for (int i = 0; i < 3; ++i)
		{
			Slider* my_knob = new Slider();
			my_knob->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
			addAndMakeVisible(my_knob);
			eq_knobs.add(my_knob);
		}

		addAndMakeVisible(gain_knob);
		gain_knob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	};

	~channel_parameters()
	{
	}

	void paint(Graphics& g) override
	{
	}

	void addListener(Mixer* mixer)
	{
		Slider::Listener* listener = (Slider::Listener*)mixer;
		volume_slider.addListener(listener);
		for (auto* eq_knob : eq_knobs)
		{
			eq_knob->addListener(listener);
		}
		gain_knob.addListener(listener);
	}

	void resized() override
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
	};

	Slider volume_slider;
	Slider gain_knob;
	OwnedArray<Slider> eq_knobs;
};

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
	void onMidiPlayStopButtonPressed(int channel);


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
