/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.1.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <map>
#include "PluginProcessor.h"
#include "../JuceLibraryCode/JuceHeader.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
	An auto-generated component, created by the Projucer.

	Describe your class and how it works here!
                                                                    //[/Comments]
*/
class PluginGui  : public AudioProcessorEditor,
                   public SliderListener,
                   public ButtonListener
{
public:
    //==============================================================================
    PluginGui (StringMaschineAudioProcessor& processor);
    ~PluginGui();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	StringMaschineAudioProcessor& processor;
	std::map<LUTBank::Waveform, std::string> m_waveformToString =
	{
		{ LUTBank::Waveform::Sine, "Sine" },
		{ LUTBank::Waveform::Noise, "Noise" } ,
		{ LUTBank::Waveform::Sawtooth, "Saw" } ,
		{ LUTBank::Waveform::Square, "Square" },
		{ LUTBank::Waveform::Triangle, "Triangle" },
		{ LUTBank::Waveform::None, "External" }
	};
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> gcTremolo;
    ScopedPointer<GroupComponent> gcStringDamping;
    ScopedPointer<GroupComponent> gcExcitationSource;
    ScopedPointer<Slider> sldExcitationSource;
    ScopedPointer<Slider> sldStringDamping;
    ScopedPointer<GroupComponent> gcEnvelope;
    ScopedPointer<Slider> sldAttack;
    ScopedPointer<Slider> sldDecay;
    ScopedPointer<Slider> sldSustain;
    ScopedPointer<Slider> sldRelease;
    ScopedPointer<Slider> sldFeedbackFilterBrightness;
    ScopedPointer<Slider> sldExcitationVolume;
    ScopedPointer<ToggleButton> tbExcitationMomentary;
    ScopedPointer<ToggleButton> tbExcitationContinuous;
    ScopedPointer<Label> lblDamping;
    ScopedPointer<Label> lblDampingBrightness;
    ScopedPointer<Label> lblAttack;
    ScopedPointer<Label> lblDecay;
    ScopedPointer<Label> lblSustain;
    ScopedPointer<Label> lblRelease;
    ScopedPointer<Slider> sldDynamicLevel;
    ScopedPointer<Slider> sldExcitationCutoff;
    ScopedPointer<Label> lblDampingThickness;
    ScopedPointer<Label> lblExcitationSource;
    ScopedPointer<Label> lblExcitationVolume;
    ScopedPointer<Label> lblExcitationCutoff;
    ScopedPointer<Slider> sldTremoloWaveform;
    ScopedPointer<Label> lblTremoloWaveform;
    ScopedPointer<Slider> sldTremoloFrequency;
    ScopedPointer<Slider> sldTremoloDepth;
    ScopedPointer<Label> lblExcitationVolume2;
    ScopedPointer<Label> lblTremoloDepth;
    ScopedPointer<Slider> sldMasterVolume;
    ScopedPointer<Label> lblMasterVolume;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginGui)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
