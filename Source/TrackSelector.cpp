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

#include "TrackSelector.h"
#include "string"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

void TrackSelector::load_data()
{
	const String filePath = R"(D:\SOUNDS\FL Studio\Projects\ABLETON\Exports)";
	File myfile = File(filePath);
	audio_files = myfile.findChildFiles(File::findFiles, true, "*.wav;*.mp3");
	for (auto file : audio_files)
	{
		DBG(file.getFileName());
	}
	number_of_rows = audio_files.size();
}

//==============================================================================
TrackSelector::TrackSelector()
{
	//[Constructor_pre] You can add your own custom stuff here..
	//[/Constructor_pre]


	//[UserPreSize]
	//[/UserPreSize]
	load_data();

	addAndMakeVisible(table); // [1]

	table.setColour(juce::ListBox::outlineColourId, juce::Colours::grey); // [2]
	table.setOutlineThickness(1);


	table.getHeader().addColumn("FILE NAME", 1, 160, 140, 380, juce::TableHeaderComponent::defaultFlags);
	table.getHeader().addColumn("ARTIST", 2, 160, 140, 380, juce::TableHeaderComponent::defaultFlags);
	table.getHeader().addColumn("TITLE", 3, 160, 140, 380, juce::TableHeaderComponent::defaultFlags);


	//[Constructor] You can add your own custom stuff here..
	//[/Constructor]
}

TrackSelector::~TrackSelector()
{
	//[Destructor_pre]. You can add your own custom destruction code here..
	//[/Destructor_pre]


	//[Destructor]. You can add your own custom destruction code here..
	//[/Destructor]
}

void TrackSelector::paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
	g.setColour(rowIsSelected ? juce::Colours::darkblue : getLookAndFeel().findColour(juce::ListBox::textColourId));
	const File file = audio_files[rowNumber];
	String text = "";
	switch (columnId)
	{
	case 1:
		text = file.getFileName();
		break;
	case 2:
		// text = file.getFile();
		break;
	default: break;
	}

	g.drawText(text, 2, 0, width - 4, height, juce::Justification::centredLeft, true);
	g.setColour(getLookAndFeel().findColour(juce::ListBox::backgroundColourId));
	g.fillRect(width - 1, 0, 1, height); // [7]
}

void TrackSelector::paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
	auto alternateColour = getLookAndFeel().findColour(juce::ListBox::backgroundColourId)
	                                       .interpolatedWith(getLookAndFeel().findColour(juce::ListBox::textColourId),
	                                                         0.03f);
	if (rowIsSelected)
		g.fillAll(juce::Colours::lightblue);
	else if (rowNumber % 2)
		g.fillAll(alternateColour);
}

int TrackSelector::getNumRows()
{
	return number_of_rows;
}

//==============================================================================
void TrackSelector::paint(Graphics& g)
{
	g.fillAll(Colour(0xff323e44));
}

void TrackSelector::resized()
{
	table.setBoundsInset(juce::BorderSize<int>(8));
}


//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

	This is where the Projucer stores the metadata that describe this GUI layout, so
	make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TrackSelector" componentName=""
				 parentClasses="public Component" constructorParams="" variableInitialisers=""
				 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
				 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff323e44"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
