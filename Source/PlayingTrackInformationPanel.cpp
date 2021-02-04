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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PlayingTrackInformationPanel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
PlayingTrackInformationPanel::PlayingTrackInformationPanel()
{
	//[Constructor_pre] You can add your own custom stuff here..
	//[/Constructor_pre]


	//[UserPreSize]
	//[/UserPreSize]
	addAndMakeVisible(timeLabel);
	timeLabel.setText("0:00/0:00", NotificationType::dontSendNotification);
	timeLabel.setColour(0x1000281, Colours::black);

	addAndMakeVisible(titleLabel);
	titleLabel.setColour(0x1000281, Colours::black);


	addAndMakeVisible(artistLabel);
	artistLabel.setColour(0x1000281, Colours::black);


	//[Constructor] You can add your own custom stuff here..
	//[/Constructor]
}

PlayingTrackInformationPanel::~PlayingTrackInformationPanel()
{
	//[Destructor_pre]. You can add your own custom destruction code here..
	//[/Destructor_pre]


	//[Destructor]. You can add your own custom destruction code here..
	//[/Destructor]
}

//==============================================================================
void PlayingTrackInformationPanel::paint(Graphics& g)
{
	//[UserPrePaint] Add your own custom painting code here..
	//[/UserPrePaint]

	//g.fillAll (Colour (0xff323e44));
	g.fillAll(Colours::lightgrey);

	//[UserPaint] Add your own custom painting code here..
	//[/UserPaint]
}

void PlayingTrackInformationPanel::resized()
{
	Rectangle<int> r = getLocalBounds();
	const int local_width = r.getWidth();
	artistLabel.setBounds(r.removeFromLeft(local_width / 5));
	titleLabel.setBounds(r.removeFromLeft(local_width / 4));
	timeLabel.setBounds(r.removeFromRight(local_width / 3));
}

String timeToString(double current_time)
{
	const int seconds = (int)floor(current_time) % 60;
	const int minutes = floor(current_time) / 60;

	String secondsString;
	if (seconds > 9)
	{
		secondsString = String(seconds);
	}
	else
	{
		secondsString = "0" + String(seconds);
	}
	String finalString = String(minutes) + ":" + secondsString;
	return finalString;
}

void PlayingTrackInformationPanel::set_time_label_text(double currentTime, double totalTime)
{
	const String currentTimeString = timeToString(currentTime);
	const String totalTimeString = timeToString(totalTime);
	timeLabel.setText(currentTimeString + "/" + totalTimeString, NotificationType::dontSendNotification);
}

void PlayingTrackInformationPanel::set_track_title(String title)
{
	titleLabel.setText(title, NotificationType::dontSendNotification);
}


//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

	This is where the Projucer stores the metadata that describe this GUI layout, so
	make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PlayingTrackInformationPanel"
				 componentName="" parentClasses="public Component" constructorParams=""
				 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
				 overlayOpacity="0.330" fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff323e44"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
