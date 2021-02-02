#include "../JuceLibraryCode/JuceHeader.h"
#include "PlayingTrackInformationPanel.h"

class Waveform :
	public Component,
	public ChangeListener,
	public Timer
{
public:
	Waveform(AudioTransportSource& transportSource_, int sourceSamplesPerThumbnailSample_);
	~Waveform();
	//==============================================================================
	void readFromFile(File& file);
	void paint(Graphics& g) override;
	void resized() override;
	void setTransportFollowing(bool transportFollowing);

private:
	void changeListenerCallback(ChangeBroadcaster* source) override;
	void timerCallback() override;
	//==============================================================================
	AudioFormatManager formatManager;
	AudioTransportSource& transportSource;
	AudioThumbnailCache thumbnailCache;
	Range<double> transportPosition;
	std::unique_ptr<AudioThumbnail> thumbnail_total;
	std::unique_ptr<AudioThumbnail> thumbnail_zoomed;
	std::unique_ptr<AudioFormatReader> formatReader;
	int sourceSamplesPerThumbnailSample;
	bool enableTransportFollow = false;


	ScopedPointer<PlayingTrackInformationPanel> track_information_panel_;


	//==============================================================================
	Rectangle<int> bottomThumbArea;
	Rectangle<int> topThumbArea;

};

