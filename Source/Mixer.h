/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.4

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

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
class myLookAndFill : public LookAndFeel_V4
{
public:
	void drawLinearSlider(Graphics&, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle, Slider&) override;
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

	void sliderValueChanged(Slider *slider)override;




private:
	OwnedArray<Slider> sliders_;

	myLookAndFill look_;

	ScopedPointer<Slider> cross_fader;
	int number_of_channels_;



	Rectangle<int>* channels_rectangles_;
	OwnedArray<AudioPlayer>* channels_;
	//[UserVariables]   -- You can add your own custom variables in this section.
	//[/UserVariables]

	//==============================================================================


	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Mixer)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

