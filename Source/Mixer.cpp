#include "Mixer.h"


void myLookAndFill::drawLinearSlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
                                     float minSliderPos, float maxSliderPos, const Slider::SliderStyle, Slider&)
{
	const int fader_slider_width = width * 0.06;
	const auto fader_slider_rectangle = Rectangle<int>(width / 2 - fader_slider_width / 2, 0, fader_slider_width,
	                                                   height + y);
	g.setColour(Colours::black);
	g.fillRect(fader_slider_rectangle);


	const int slider_height = 20;
	const int slider_width = width * 0.8;

	g.setColour(Colours::darkgrey);
	const Rectangle<int> my_rectangle = Rectangle<int>(x + width * 0.1, sliderPos - (slider_height / 2.), slider_width,
	                                                   (slider_height / 2.));
	g.fillRect(my_rectangle);
}

//==============================================================================
Mixer::Mixer(OwnedArray<AudioPlayer>* channels) : channels_(channels)
{
	setName("MIXIER");
	number_of_channels_ = channels->size();

	for (int channel = 0; channel < number_of_channels_; ++channel)
	{
		channel_parameters* temp_channel_parameter = new channel_parameters(&look_);

		addAndMakeVisible(temp_channel_parameter);
		temp_channel_parameter->volume_slider.addListener(this);
		temp_channel_parameter->gain_knob.addListener(this);
		for (auto eq_knob : temp_channel_parameter->eq_knobs)
		{
			eq_knob->addListener(this);
		}

		channels_parameters_.add(temp_channel_parameter);
	}

	cross_fader = new Slider();
	cross_fader->setSliderStyle(Slider::LinearHorizontal);
	addAndMakeVisible(cross_fader);
	cross_fader->addListener(this);
	cross_fader->setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	cross_fader->setName("Cross");
}

Mixer::~Mixer()
{
	//[Destructor_pre]. You can add your own custom destruction code here..
	//[/Destructor_pre]


	//[Destructor]. You can add your own custom destruction code here..
	//[/Destructor]

	delete[] channels_rectangles_;
}

//==============================================================================
void Mixer::paint(Graphics& g)
{
	//[UserPrePaint] Add your own custom painting code here..
	//[/UserPrePaint]

	g.fillAll(Colours::grey);


	//[UserPaint] Add your own custom painting code here..
	//[/UserPaint]
}

void Mixer::resized()
{
	//[UserPreResize] Add your own custom resize code here..
	//[/UserPreResize]

	//[UserResized] Add your own custom resize handling here..
	//[/UserResized]
	auto r = getLocalBounds();

	const auto cross_fader_rectangle = r.removeFromBottom(r.getHeight() / 6);
	const int channel_width = r.getWidth() / number_of_channels_;
	const int channel_height = r.getHeight();

	channels_rectangles_ = new Rectangle<int>[number_of_channels_];

	for (int channel = 0; channel < number_of_channels_; ++channel)
	{
		channels_rectangles_[channel] = r.removeFromLeft(channel_width);
		channels_parameters_[channel]->setBounds(channels_rectangles_[channel].reduced(channel_width / 5, 0));
	}

	cross_fader->setBounds(cross_fader_rectangle.reduced(channel_width / 3, channel_height / 60));
}

void Mixer::sliderValueChanged(Slider* slider)
{
	for (int channel = 0; channel < number_of_channels_; ++channel)
	{
		if (slider == &channels_parameters_[channel]->volume_slider)
		{
			channels_->getRawDataPointer()[channel]->setAudioLevel(slider->getValue());
		}
		// if (slider == &channels_parameters_[channel]->gain_knob)
		// {
		// 	channels_->getRawDataPointer()[channel]->setAudioLevel(slider->getValue());
		// }
		auto* eq_knobs_array = channels_parameters_[channel]->eq_knobs.getRawDataPointer();

		if (slider == eq_knobs_array[0])
		{
			channels_->getRawDataPointer()[channel]->setFrequecyBandLevel(Knob_Type::LowEq, slider->getValue());
		}
		if (slider == eq_knobs_array[1])
		{
			channels_->getRawDataPointer()[channel]->setFrequecyBandLevel(Knob_Type::MidEq, slider->getValue());
		}
		if (slider == eq_knobs_array[2])
		{
			channels_->getRawDataPointer()[channel]->setFrequecyBandLevel(Knob_Type::HiEq, slider->getValue());
		}
	}
}

void Mixer::set_slider_value(int channel, float value) const
{
	if (channel < number_of_channels_)
	{
		channels_parameters_[channel]->volume_slider.setValue(value);
	}
}

void Mixer::set_crossfader_value(const float value_in_range) const
{
	cross_fader->setValue(value_in_range);
}

void Mixer::set_knob_value(int channel, Knob_Type knob_type, const float value) const
{
	switch (knob_type)
	{
	case Knob_Type::Gain:
		channels_parameters_[channel]->gain_knob.setValue(value);
		break;
	case Knob_Type::HiEq:
		channels_parameters_[channel]->eq_knobs[2]->setValue(value);
		break;
	case Knob_Type::MidEq:
		channels_parameters_[channel]->eq_knobs[1]->setValue(value);
		break;
	case Knob_Type::LowEq:
		channels_parameters_[channel]->eq_knobs[0]->setValue(value);
		break;
	default: break ;
	}
}

void Mixer::onMidiPlayStopButtonPressed(int channel) const
{
	if (channel < channels_->size())
	{
		AudioPlayer* channel_player = channels_->getRawDataPointer()[channel];
		TransportState current_state = channel_player->getTransportState();
		switch (current_state)
		{
		case TransportState::Play:
			channel_player->stopButtonClicked();
			break;
		case TransportState::Stop:
			channel_player->playButtonClicked();
			break;
		case TransportState::NoFile: break;
		case TransportState::Pause:
			channel_player->playButtonClicked();
			break;

		default:
			break;
		}
	}
}


//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

	This is where the Projucer stores the metadata that describe this GUI layout, so
	make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Mixer" componentName="" parentClasses="public Component"
				 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
				 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
				 initialHeight="400">
  <BACKGROUND backgroundColour="ff323e44"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
