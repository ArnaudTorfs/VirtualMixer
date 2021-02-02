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
#include "math.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class PlayingTrackInformationPanel  : public Component
{
public:
    //==============================================================================
    PlayingTrackInformationPanel ();
    ~PlayingTrackInformationPanel();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    //==============================================================================
	void set_time_label_text(double currentTime, double totalTime);
	void set_track_title(String title);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
	Rectangle<int> track_name_panel;
	Rectangle<int> artist_name_panel;
	Rectangle<int> time_panel;
    //==============================================================================
	Label timeLabel;
	Label titleLabel;
	Label artistLabel;
    //==============================================================================



    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlayingTrackInformationPanel)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

