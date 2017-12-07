/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.2.0

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PluginGui.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
/*
	: processor(processor)
	, AudioProcessorEditor(&processor)
*/
//[/MiscUserDefs]

//==============================================================================
PluginGui::PluginGui (StringMaschineAudioProcessor& processor)
	: processor(processor)
	, AudioProcessorEditor(&processor)
{
    //[Constructor_pre] You can add your own custom stuff here..

    //[/Constructor_pre]

    addAndMakeVisible (gcTremolo = new GroupComponent ("Tremolo",
                                                       TRANS("Tremolo")));
    gcTremolo->setTextLabelPosition (Justification::centred);

    addAndMakeVisible (gcStringDamping = new GroupComponent ("String damping",
                                                             TRANS("String damping")));
    gcStringDamping->setTextLabelPosition (Justification::centred);

    addAndMakeVisible (gcExcitationSource = new GroupComponent ("Excitation source",
                                                                TRANS("Excitation source")));
    gcExcitationSource->setTextLabelPosition (Justification::centred);

    addAndMakeVisible (sldExcitationSource = new Slider ("Excitation source"));
    sldExcitationSource->setTooltip (TRANS("State of the string when fully pulled - i.e. Sin will bend it to the shape of a wave"));
    sldExcitationSource->setExplicitFocusOrder (1);
    sldExcitationSource->setRange (0, 5, 1);
    sldExcitationSource->setSliderStyle (Slider::Rotary);
    sldExcitationSource->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sldExcitationSource->addListener (this);

    addAndMakeVisible (sldStringDamping = new Slider ("String damping"));
    sldStringDamping->setTooltip (TRANS("String damping factor"));
    sldStringDamping->setExplicitFocusOrder (1);
    sldStringDamping->setRange (0, 10, 0);
    sldStringDamping->setSliderStyle (Slider::Rotary);
    sldStringDamping->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sldStringDamping->addListener (this);
    sldStringDamping->setSkewFactor (0.5);

    addAndMakeVisible (gcEnvelope = new GroupComponent ("ADSR envelope",
                                                        TRANS("ADSR envelope")));
    gcEnvelope->setTextLabelPosition (Justification::centred);

    addAndMakeVisible (sldAttack = new Slider ("Attack"));
    sldAttack->setTooltip (TRANS("Attack"));
    sldAttack->setExplicitFocusOrder (1);
    sldAttack->setRange (0, 4000, 0);
    sldAttack->setSliderStyle (Slider::Rotary);
    sldAttack->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sldAttack->addListener (this);

    addAndMakeVisible (sldDecay = new Slider ("Decay"));
    sldDecay->setTooltip (TRANS("Decay"));
    sldDecay->setExplicitFocusOrder (1);
    sldDecay->setRange (0, 4000, 0);
    sldDecay->setSliderStyle (Slider::Rotary);
    sldDecay->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sldDecay->addListener (this);

    addAndMakeVisible (sldSustain = new Slider ("Sustain"));
    sldSustain->setTooltip (TRANS("Sustain"));
    sldSustain->setExplicitFocusOrder (1);
    sldSustain->setRange (0, 1, 0);
    sldSustain->setSliderStyle (Slider::Rotary);
    sldSustain->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sldSustain->addListener (this);

    addAndMakeVisible (sldRelease = new Slider ("Release"));
    sldRelease->setTooltip (TRANS("Release"));
    sldRelease->setExplicitFocusOrder (1);
    sldRelease->setRange (0, 8000, 0);
    sldRelease->setSliderStyle (Slider::Rotary);
    sldRelease->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sldRelease->addListener (this);
    sldRelease->setSkewFactor (0.9);

    addAndMakeVisible (sldFeedbackFilterBrightness = new Slider ("Feedback filter brightness"));
    sldFeedbackFilterBrightness->setTooltip (TRANS("Filter brightness"));
    sldFeedbackFilterBrightness->setExplicitFocusOrder (1);
    sldFeedbackFilterBrightness->setRange (-1, 1, 0);
    sldFeedbackFilterBrightness->setSliderStyle (Slider::Rotary);
    sldFeedbackFilterBrightness->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sldFeedbackFilterBrightness->addListener (this);
    sldFeedbackFilterBrightness->setSkewFactor (1.5);

    addAndMakeVisible (sldExcitationVolume = new Slider ("Excitation volume"));
    sldExcitationVolume->setTooltip (TRANS("Determines the strength of the string excitation"));
    sldExcitationVolume->setExplicitFocusOrder (1);
    sldExcitationVolume->setRange (0, 1, 0);
    sldExcitationVolume->setSliderStyle (Slider::Rotary);
    sldExcitationVolume->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sldExcitationVolume->addListener (this);

    addAndMakeVisible (tbExcitationMomentary = new ToggleButton ("Momentary excitation"));
    tbExcitationMomentary->setTooltip (TRANS("Typical for plucked instruments and claviers"));
    tbExcitationMomentary->setExplicitFocusOrder (1);
    tbExcitationMomentary->setButtonText (TRANS("Momentary"));
    tbExcitationMomentary->setRadioGroupId (2);
    tbExcitationMomentary->addListener (this);
    tbExcitationMomentary->setToggleState (true, dontSendNotification);

    addAndMakeVisible (tbExcitationContinuous = new ToggleButton ("Continuous excitation"));
    tbExcitationContinuous->setTooltip (TRANS("Typical for bowed instruments"));
    tbExcitationContinuous->setExplicitFocusOrder (1);
    tbExcitationContinuous->setButtonText (TRANS("Continuous"));
    tbExcitationContinuous->setRadioGroupId (2);
    tbExcitationContinuous->addListener (this);

    addAndMakeVisible (lblDamping = new Label ("Damping",
                                               TRANS("Level")));
    lblDamping->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblDamping->setJustificationType (Justification::centred);
    lblDamping->setEditable (false, false, false);
    lblDamping->setColour (TextEditor::textColourId, Colours::black);
    lblDamping->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lblDampingBrightness = new Label ("Damping brightness",
                                                         TRANS("Brightness")));
    lblDampingBrightness->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblDampingBrightness->setJustificationType (Justification::centred);
    lblDampingBrightness->setEditable (false, false, false);
    lblDampingBrightness->setColour (TextEditor::textColourId, Colours::black);
    lblDampingBrightness->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lblAttack = new Label ("Attack",
                                              TRANS("Attack")));
    lblAttack->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblAttack->setJustificationType (Justification::centred);
    lblAttack->setEditable (false, false, false);
    lblAttack->setColour (TextEditor::textColourId, Colours::black);
    lblAttack->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lblDecay = new Label ("Decay",
                                             TRANS("Decay")));
    lblDecay->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblDecay->setJustificationType (Justification::centred);
    lblDecay->setEditable (false, false, false);
    lblDecay->setColour (TextEditor::textColourId, Colours::black);
    lblDecay->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lblSustain = new Label ("Sustain",
                                               TRANS("Sustain")));
    lblSustain->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblSustain->setJustificationType (Justification::centred);
    lblSustain->setEditable (false, false, false);
    lblSustain->setColour (TextEditor::textColourId, Colours::black);
    lblSustain->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lblRelease = new Label ("Release",
                                               TRANS("Release\n")));
    lblRelease->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblRelease->setJustificationType (Justification::centred);
    lblRelease->setEditable (false, false, false);
    lblRelease->setColour (TextEditor::textColourId, Colours::black);
    lblRelease->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sldDynamicLevel = new Slider ("Dynamic level"));
    sldDynamicLevel->setTooltip (TRANS("Attenuation of string dynamics"));
    sldDynamicLevel->setExplicitFocusOrder (1);
    sldDynamicLevel->setRange (0, 2, 0);
    sldDynamicLevel->setSliderStyle (Slider::Rotary);
    sldDynamicLevel->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    sldDynamicLevel->addListener (this);

    addAndMakeVisible (sldExcitationCutoff = new Slider ("Excitation cutoff"));
    sldExcitationCutoff->setTooltip (TRANS("Determines the excitation filter cutoff"));
    sldExcitationCutoff->setExplicitFocusOrder (1);
    sldExcitationCutoff->setRange (0, 44100, 0);
    sldExcitationCutoff->setSliderStyle (Slider::Rotary);
    sldExcitationCutoff->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sldExcitationCutoff->addListener (this);
    sldExcitationCutoff->setSkewFactor (0.5);

    addAndMakeVisible (lblDampingThickness = new Label ("Damping thickness",
                                                        TRANS("Thickness")));
    lblDampingThickness->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblDampingThickness->setJustificationType (Justification::centred);
    lblDampingThickness->setEditable (false, false, false);
    lblDampingThickness->setColour (TextEditor::textColourId, Colours::black);
    lblDampingThickness->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lblExcitationSource = new Label ("Excitation source",
                                                        TRANS("Saw")));
    lblExcitationSource->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblExcitationSource->setJustificationType (Justification::centred);
    lblExcitationSource->setEditable (false, false, false);
    lblExcitationSource->setColour (TextEditor::textColourId, Colours::black);
    lblExcitationSource->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lblExcitationVolume = new Label ("Excitation volume",
                                                        TRANS("Strength")));
    lblExcitationVolume->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblExcitationVolume->setJustificationType (Justification::centred);
    lblExcitationVolume->setEditable (false, false, false);
    lblExcitationVolume->setColour (TextEditor::textColourId, Colours::black);
    lblExcitationVolume->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lblExcitationCutoff = new Label ("Excitation cutoff",
                                                        TRANS("Cutoff")));
    lblExcitationCutoff->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblExcitationCutoff->setJustificationType (Justification::centred);
    lblExcitationCutoff->setEditable (false, false, false);
    lblExcitationCutoff->setColour (TextEditor::textColourId, Colours::black);
    lblExcitationCutoff->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sldTremoloWaveform = new Slider ("Tremolo waveform"));
    sldTremoloWaveform->setTooltip (TRANS("State of the string when fully pulled - i.e. Sin will bend it to the shape of a wave"));
    sldTremoloWaveform->setExplicitFocusOrder (1);
    sldTremoloWaveform->setRange (0, 4, 1);
    sldTremoloWaveform->setSliderStyle (Slider::Rotary);
    sldTremoloWaveform->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sldTremoloWaveform->addListener (this);

    addAndMakeVisible (lblTremoloWaveform = new Label ("Tremolo depth",
                                                       TRANS("Saw")));
    lblTremoloWaveform->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblTremoloWaveform->setJustificationType (Justification::centred);
    lblTremoloWaveform->setEditable (false, false, false);
    lblTremoloWaveform->setColour (TextEditor::textColourId, Colours::black);
    lblTremoloWaveform->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sldTremoloFrequency = new Slider ("Tremolo frequency"));
    sldTremoloFrequency->setExplicitFocusOrder (1);
    sldTremoloFrequency->setRange (0, 15, 0);
    sldTremoloFrequency->setSliderStyle (Slider::Rotary);
    sldTremoloFrequency->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sldTremoloFrequency->addListener (this);
    sldTremoloFrequency->setSkewFactor (0.5);

    addAndMakeVisible (sldTremoloDepth = new Slider ("Excitation cutoff"));
    sldTremoloDepth->setExplicitFocusOrder (1);
    sldTremoloDepth->setRange (0, 1, 0);
    sldTremoloDepth->setSliderStyle (Slider::Rotary);
    sldTremoloDepth->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sldTremoloDepth->addListener (this);

    addAndMakeVisible (lblExcitationVolume2 = new Label ("Excitation volume",
                                                         TRANS("Frequency")));
    lblExcitationVolume2->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblExcitationVolume2->setJustificationType (Justification::centred);
    lblExcitationVolume2->setEditable (false, false, false);
    lblExcitationVolume2->setColour (TextEditor::textColourId, Colours::black);
    lblExcitationVolume2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lblTremoloDepth = new Label ("Tremolo depth",
                                                    TRANS("Depth\n")));
    lblTremoloDepth->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblTremoloDepth->setJustificationType (Justification::centred);
    lblTremoloDepth->setEditable (false, false, false);
    lblTremoloDepth->setColour (TextEditor::textColourId, Colours::black);
    lblTremoloDepth->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sldMasterVolume = new Slider ("Master volume"));
    sldMasterVolume->setTooltip (TRANS("Setup master volume"));
    sldMasterVolume->setExplicitFocusOrder (1);
    sldMasterVolume->setRange (0, 1, 0);
    sldMasterVolume->setSliderStyle (Slider::Rotary);
    sldMasterVolume->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sldMasterVolume->addListener (this);
    sldMasterVolume->setSkewFactor (0.5);

    addAndMakeVisible (lblMasterVolume = new Label ("MasterVolume",
                                                    TRANS("Master Volume")));
    lblMasterVolume->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lblMasterVolume->setJustificationType (Justification::centred);
    lblMasterVolume->setEditable (false, false, false);
    lblMasterVolume->setColour (TextEditor::textColourId, Colours::black);
    lblMasterVolume->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (textButton = new TextButton ("new button"));
    textButton->setButtonText (TRANS("V"));
    textButton->addListener (this);

    addAndMakeVisible (tbThicknesVel = new TextButton (String()));
    tbThicknesVel->setButtonText (TRANS("N"));
    tbThicknesVel->addListener (this);
    tbThicknesVel->setColour (TextButton::buttonColourId, Colours::grey);

    addAndMakeVisible (tbBrightnessVel = new TextButton (String()));
    tbBrightnessVel->setButtonText (TRANS("N"));
    tbBrightnessVel->addListener (this);
    tbBrightnessVel->setColour (TextButton::buttonColourId, Colours::grey);

    addAndMakeVisible (tbLevelVel = new TextButton (String()));
    tbLevelVel->setButtonText (TRANS("N"));
    tbLevelVel->addListener (this);
    tbLevelVel->setColour (TextButton::buttonColourId, Colours::grey);

    addAndMakeVisible (tbStrengthVel = new TextButton (String()));
    tbStrengthVel->setButtonText (TRANS("N"));
    tbStrengthVel->addListener (this);
    tbStrengthVel->setColour (TextButton::buttonColourId, Colours::grey);

    addAndMakeVisible (tbCutoffVel = new TextButton (String()));
    tbCutoffVel->setButtonText (TRANS("N"));
    tbCutoffVel->addListener (this);
    tbCutoffVel->setColour (TextButton::buttonColourId, Colours::grey);

    addAndMakeVisible (tbTremoloFreqVel = new TextButton (String()));
    tbTremoloFreqVel->setButtonText (TRANS("N"));
    tbTremoloFreqVel->addListener (this);
    tbTremoloFreqVel->setColour (TextButton::buttonColourId, Colours::grey);

    addAndMakeVisible (tbTremoloDepthVel = new TextButton (String()));
    tbTremoloDepthVel->setButtonText (TRANS("N"));
    tbTremoloDepthVel->addListener (this);
    tbTremoloDepthVel->setColour (TextButton::buttonColourId, Colours::grey);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (634, 490);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

PluginGui::~PluginGui()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    gcTremolo = nullptr;
    gcStringDamping = nullptr;
    gcExcitationSource = nullptr;
    sldExcitationSource = nullptr;
    sldStringDamping = nullptr;
    gcEnvelope = nullptr;
    sldAttack = nullptr;
    sldDecay = nullptr;
    sldSustain = nullptr;
    sldRelease = nullptr;
    sldFeedbackFilterBrightness = nullptr;
    sldExcitationVolume = nullptr;
    tbExcitationMomentary = nullptr;
    tbExcitationContinuous = nullptr;
    lblDamping = nullptr;
    lblDampingBrightness = nullptr;
    lblAttack = nullptr;
    lblDecay = nullptr;
    lblSustain = nullptr;
    lblRelease = nullptr;
    sldDynamicLevel = nullptr;
    sldExcitationCutoff = nullptr;
    lblDampingThickness = nullptr;
    lblExcitationSource = nullptr;
    lblExcitationVolume = nullptr;
    lblExcitationCutoff = nullptr;
    sldTremoloWaveform = nullptr;
    lblTremoloWaveform = nullptr;
    sldTremoloFrequency = nullptr;
    sldTremoloDepth = nullptr;
    lblExcitationVolume2 = nullptr;
    lblTremoloDepth = nullptr;
    sldMasterVolume = nullptr;
    lblMasterVolume = nullptr;
    textButton = nullptr;
    tbThicknesVel = nullptr;
    tbBrightnessVel = nullptr;
    tbLevelVel = nullptr;
    tbStrengthVel = nullptr;
    tbCutoffVel = nullptr;
    tbTremoloFreqVel = nullptr;
    tbTremoloDepthVel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PluginGui::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PluginGui::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    gcTremolo->setBounds (8, 328, 360, 152);
    gcStringDamping->setBounds (8, 168, 360, 152);
    gcExcitationSource->setBounds (8, 8, 616, 152);
    sldExcitationSource->setBounds (24, 32, 104, 104);
    sldStringDamping->setBounds (24, 192, 104, 104);
    gcEnvelope->setBounds (376, 168, 248, 312);
    sldAttack->setBounds (392, 192, 104, 104);
    sldDecay->setBounds (504, 192, 104, 104);
    sldSustain->setBounds (392, 344, 104, 104);
    sldRelease->setBounds (504, 344, 104, 104);
    sldFeedbackFilterBrightness->setBounds (136, 192, 104, 104);
    sldExcitationVolume->setBounds (136, 32, 104, 104);
    tbExcitationMomentary->setBounds (492, 57, 104, 24);
    tbExcitationContinuous->setBounds (492, 97, 104, 24);
    lblDamping->setBounds (40, 288, 72, 24);
    lblDampingBrightness->setBounds (152, 288, 72, 24);
    lblAttack->setBounds (408, 288, 72, 24);
    lblDecay->setBounds (520, 288, 72, 24);
    lblSustain->setBounds (408, 440, 72, 24);
    lblRelease->setBounds (520, 440, 72, 24);
    sldDynamicLevel->setBounds (248, 192, 104, 104);
    sldExcitationCutoff->setBounds (248, 32, 104, 104);
    lblDampingThickness->setBounds (264, 288, 72, 24);
    lblExcitationSource->setBounds (32, 128, 88, 24);
    lblExcitationVolume->setBounds (144, 128, 88, 24);
    lblExcitationCutoff->setBounds (256, 128, 88, 24);
    sldTremoloWaveform->setBounds (24, 344, 104, 104);
    lblTremoloWaveform->setBounds (32, 440, 88, 24);
    sldTremoloFrequency->setBounds (136, 344, 104, 104);
    sldTremoloDepth->setBounds (248, 344, 104, 104);
    lblExcitationVolume2->setBounds (144, 440, 88, 24);
    lblTremoloDepth->setBounds (256, 440, 88, 24);
    sldMasterVolume->setBounds (360, 32, 104, 104);
    lblMasterVolume->setBounds (360, 128, 104, 24);
    textButton->setBounds (336, 192, 16, 16);
    tbThicknesVel->setBounds (336, 192, 16, 16);
    tbBrightnessVel->setBounds (224, 192, 16, 16);
    tbLevelVel->setBounds (112, 192, 16, 16);
    tbStrengthVel->setBounds (224, 32, 16, 16);
    tbCutoffVel->setBounds (336, 32, 16, 16);
    tbTremoloFreqVel->setBounds (224, 344, 16, 16);
    tbTremoloDepthVel->setBounds (336, 344, 16, 16);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void PluginGui::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == sldExcitationSource)
    {
        //[UserSliderCode_sldExcitationSource] -- add your slider handling code here..
		auto excitationSource = (LUTBank::Waveform)(int)sldExcitationSource->getValue();
		processor.m_karplusString.setExcitationSource(excitationSource);
		lblExcitationSource->setText(m_waveformToString.at(excitationSource), juce::NotificationType::dontSendNotification);
        //[/UserSliderCode_sldExcitationSource]
    }
    else if (sliderThatWasMoved == sldStringDamping)
    {
        //[UserSliderCode_sldStringDamping] -- add your slider handling code here..
		processor.m_karplusString.setDampingCoefficient(sldStringDamping->getValue());
        //[/UserSliderCode_sldStringDamping]
    }
    else if (sliderThatWasMoved == sldAttack)
    {
        //[UserSliderCode_sldAttack] -- add your slider handling code here..
		processor.m_karplusString.setAttack(sldAttack->getValue());
        //[/UserSliderCode_sldAttack]
    }
    else if (sliderThatWasMoved == sldDecay)
    {
        //[UserSliderCode_sldDecay] -- add your slider handling code here..
		processor.m_karplusString.setDecay(sldDecay->getValue());
        //[/UserSliderCode_sldDecay]
    }
    else if (sliderThatWasMoved == sldSustain)
    {
        //[UserSliderCode_sldSustain] -- add your slider handling code here..
		processor.m_karplusString.setSustain(sldSustain->getValue());
        //[/UserSliderCode_sldSustain]
    }
    else if (sliderThatWasMoved == sldRelease)
    {
        //[UserSliderCode_sldRelease] -- add your slider handling code here..
		processor.m_karplusString.setRelease(sldRelease->getValue());
        //[/UserSliderCode_sldRelease]
    }
    else if (sliderThatWasMoved == sldFeedbackFilterBrightness)
    {
        //[UserSliderCode_sldFeedbackFilterBrightness] -- add your slider handling code here..
		processor.m_karplusString.setDampingBrightness(sldFeedbackFilterBrightness->getValue());
        //[/UserSliderCode_sldFeedbackFilterBrightness]
    }
    else if (sliderThatWasMoved == sldExcitationVolume)
    {
        //[UserSliderCode_sldExcitationVolume] -- add your slider handling code here..
		processor.m_karplusString.setExcitationStrength(sldExcitationVolume->getValue());
        //[/UserSliderCode_sldExcitationVolume]
    }
    else if (sliderThatWasMoved == sldDynamicLevel)
    {
        //[UserSliderCode_sldDynamicLevel] -- add your slider handling code here..
		processor.m_karplusString.setDynamicLevel(sldDynamicLevel->getValue());
        //[/UserSliderCode_sldDynamicLevel]
    }
    else if (sliderThatWasMoved == sldExcitationCutoff)
    {
        //[UserSliderCode_sldExcitationCutoff] -- add your slider handling code here..
		processor.m_karplusString.setExcitationCutoff(sldExcitationCutoff->getValue());
        //[/UserSliderCode_sldExcitationCutoff]
    }
    else if (sliderThatWasMoved == sldTremoloWaveform)
    {
        //[UserSliderCode_sldTremoloWaveform] -- add your slider handling code here..
		auto waveform = (LUTBank::Waveform)(int)sldTremoloWaveform->getValue();
		processor.m_karplusString.setTremoloWaveform(waveform);
		lblTremoloWaveform->setText(m_waveformToString.at(waveform), juce::NotificationType::dontSendNotification);
        //[/UserSliderCode_sldTremoloWaveform]
    }
    else if (sliderThatWasMoved == sldTremoloFrequency)
    {
        //[UserSliderCode_sldTremoloFrequency] -- add your slider handling code here..
		processor.m_karplusString.setTremoloFrequency(sldTremoloFrequency->getValue());
        //[/UserSliderCode_sldTremoloFrequency]
    }
    else if (sliderThatWasMoved == sldTremoloDepth)
    {
        //[UserSliderCode_sldTremoloDepth] -- add your slider handling code here..
		processor.m_karplusString.setTremoloDepth(sldTremoloDepth->getValue());
        //[/UserSliderCode_sldTremoloDepth]
    }
    else if (sliderThatWasMoved == sldMasterVolume)
    {
        //[UserSliderCode_sldMasterVolume] -- add your slider handling code here..
		processor.m_karplusString.setMasterVolume(sldMasterVolume->getValue());
        //[/UserSliderCode_sldMasterVolume]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void PluginGui::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == tbExcitationMomentary)
    {
        //[UserButtonCode_tbExcitationMomentary] -- add your button handler code here..
		processor.m_karplusString.setExcitationType(Momentary);
        //[/UserButtonCode_tbExcitationMomentary]
    }
    else if (buttonThatWasClicked == tbExcitationContinuous)
    {
        //[UserButtonCode_tbExcitationContinuous] -- add your button handler code here..
		processor.m_karplusString.setExcitationType(Continuous);
        //[/UserButtonCode_tbExcitationContinuous]
    }
    else if (buttonThatWasClicked == textButton)
    {
        //[UserButtonCode_textButton] -- add your button handler code here..
        //[/UserButtonCode_textButton]
    }
    else if (buttonThatWasClicked == tbThicknesVel)
    {
        //[UserButtonCode_tbThicknesVel] -- add your button handler code here..
		processor.m_karplusString.followDynamicLevel = (StringSynthesizer::FollowType)((processor.m_karplusString.followDynamicLevel + 1) % StringSynthesizer::FollowType::Count);
		toggleFollowButtonState(tbThicknesVel, processor.m_karplusString.followDynamicLevel);
        //[/UserButtonCode_tbThicknesVel]
    }
    else if (buttonThatWasClicked == tbBrightnessVel)
    {
        //[UserButtonCode_tbBrightnessVel] -- add your button handler code here..
		processor.m_karplusString.followDampingBrightness = (StringSynthesizer::FollowType)((processor.m_karplusString.followDampingBrightness + 1) % StringSynthesizer::FollowType::Count);
		toggleFollowButtonState(tbBrightnessVel, processor.m_karplusString.followDampingBrightness);
        //[/UserButtonCode_tbBrightnessVel]
    }
    else if (buttonThatWasClicked == tbLevelVel)
    {
        //[UserButtonCode_tbLevelVel] -- add your button handler code here..
		processor.m_karplusString.followDampingCoefficient = (StringSynthesizer::FollowType)((processor.m_karplusString.followDampingCoefficient + 1) % StringSynthesizer::FollowType::Count);
		toggleFollowButtonState(tbLevelVel, processor.m_karplusString.followDampingCoefficient);
        //[/UserButtonCode_tbLevelVel]
    }
    else if (buttonThatWasClicked == tbStrengthVel)
    {
        //[UserButtonCode_tbStrengthVel] -- add your button handler code here..
		processor.m_karplusString.followExcitationStrength = (StringSynthesizer::FollowType)((processor.m_karplusString.followExcitationStrength + 1) % StringSynthesizer::FollowType::Count);
		toggleFollowButtonState(tbStrengthVel, processor.m_karplusString.followExcitationStrength);
        //[/UserButtonCode_tbStrengthVel]
    }
    else if (buttonThatWasClicked == tbCutoffVel)
    {
        //[UserButtonCode_tbCutoffVel] -- add your button handler code here..
		processor.m_karplusString.followExcitationCutoff = (StringSynthesizer::FollowType)((processor.m_karplusString.followExcitationCutoff + 1) % StringSynthesizer::FollowType::Count);
		toggleFollowButtonState(tbCutoffVel, processor.m_karplusString.followExcitationCutoff);
        //[/UserButtonCode_tbCutoffVel]
    }
    else if (buttonThatWasClicked == tbTremoloFreqVel)
    {
        //[UserButtonCode_tbTremoloFreqVel] -- add your button handler code here..
		processor.m_karplusString.followTremoloFrequency = (StringSynthesizer::FollowType)((processor.m_karplusString.followTremoloFrequency + 1) % StringSynthesizer::FollowType::Count);
		toggleFollowButtonState(tbTremoloFreqVel, processor.m_karplusString.followTremoloFrequency);
        //[/UserButtonCode_tbTremoloFreqVel]
    }
    else if (buttonThatWasClicked == tbTremoloDepthVel)
    {
        //[UserButtonCode_tbTremoloDepthVel] -- add your button handler code here..
		processor.m_karplusString.followTremoloDepth = (StringSynthesizer::FollowType)((processor.m_karplusString.followTremoloDepth + 1) % StringSynthesizer::FollowType::Count);
		toggleFollowButtonState(tbTremoloDepthVel, processor.m_karplusString.followTremoloDepth);
        //[/UserButtonCode_tbTremoloDepthVel]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}





//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PluginGui" componentName=""
                 parentClasses="public AudioProcessorEditor" constructorParams="StringMaschineAudioProcessor&amp; processor"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="0" initialWidth="634" initialHeight="490">
  <BACKGROUND backgroundColour="ff323e44"/>
  <GROUPCOMPONENT name="Tremolo" id="343f31c6597cf59c" memberName="gcTremolo" virtualName=""
                  explicitFocusOrder="0" pos="8 328 360 152" title="Tremolo" textpos="36"/>
  <GROUPCOMPONENT name="String damping" id="7e50eccc504224bc" memberName="gcStringDamping"
                  virtualName="" explicitFocusOrder="0" pos="8 168 360 152" title="String damping"
                  textpos="36"/>
  <GROUPCOMPONENT name="Excitation source" id="b76c91a1c5f941ad" memberName="gcExcitationSource"
                  virtualName="" explicitFocusOrder="0" pos="8 8 616 152" title="Excitation source"
                  textpos="36"/>
  <SLIDER name="Excitation source" id="af916b998d7f0d9a" memberName="sldExcitationSource"
          virtualName="" explicitFocusOrder="1" pos="24 32 104 104" tooltip="State of the string when fully pulled - i.e. Sin will bend it to the shape of a wave"
          min="0" max="5" int="1" style="Rotary" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="String damping" id="b6e79453c1007ddb" memberName="sldStringDamping"
          virtualName="" explicitFocusOrder="1" pos="24 192 104 104" tooltip="String damping factor"
          min="0" max="10" int="0" style="Rotary" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="0.5"
          needsCallback="1"/>
  <GROUPCOMPONENT name="ADSR envelope" id="3e9bc29cef49135b" memberName="gcEnvelope"
                  virtualName="" explicitFocusOrder="0" pos="376 168 248 312" title="ADSR envelope"
                  textpos="36"/>
  <SLIDER name="Attack" id="1f1949ed86fd1d1a" memberName="sldAttack" virtualName=""
          explicitFocusOrder="1" pos="392 192 104 104" tooltip="Attack"
          min="0" max="4000" int="0" style="Rotary" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="Decay" id="cd7809220fc2511e" memberName="sldDecay" virtualName=""
          explicitFocusOrder="1" pos="504 192 104 104" tooltip="Decay"
          min="0" max="4000" int="0" style="Rotary" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="Sustain" id="52755248df039389" memberName="sldSustain"
          virtualName="" explicitFocusOrder="1" pos="392 344 104 104" tooltip="Sustain"
          min="0" max="1" int="0" style="Rotary" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="Release" id="5809c1c05520e681" memberName="sldRelease"
          virtualName="" explicitFocusOrder="1" pos="504 344 104 104" tooltip="Release"
          min="0" max="8000" int="0" style="Rotary" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="0.9000000000000000222"
          needsCallback="1"/>
  <SLIDER name="Feedback filter brightness" id="1fd610d5bca2448f" memberName="sldFeedbackFilterBrightness"
          virtualName="" explicitFocusOrder="1" pos="136 192 104 104" tooltip="Filter brightness"
          min="-1" max="1" int="0" style="Rotary" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.5"
          needsCallback="1"/>
  <SLIDER name="Excitation volume" id="bcf0f6716693dffe" memberName="sldExcitationVolume"
          virtualName="" explicitFocusOrder="1" pos="136 32 104 104" tooltip="Determines the strength of the string excitation"
          min="0" max="1" int="0" style="Rotary" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <TOGGLEBUTTON name="Momentary excitation" id="741314ea31aca291" memberName="tbExcitationMomentary"
                virtualName="" explicitFocusOrder="1" pos="492 57 104 24" tooltip="Typical for plucked instruments and claviers"
                buttonText="Momentary" connectedEdges="0" needsCallback="1" radioGroupId="2"
                state="1"/>
  <TOGGLEBUTTON name="Continuous excitation" id="729a5786fd74eb91" memberName="tbExcitationContinuous"
                virtualName="" explicitFocusOrder="1" pos="492 97 104 24" tooltip="Typical for bowed instruments"
                buttonText="Continuous" connectedEdges="0" needsCallback="1"
                radioGroupId="2" state="0"/>
  <LABEL name="Damping" id="d74c1e3577dba17e" memberName="lblDamping"
         virtualName="" explicitFocusOrder="0" pos="40 288 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Level" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         kerning="0" bold="0" italic="0" justification="36"/>
  <LABEL name="Damping brightness" id="7225e346188640cf" memberName="lblDampingBrightness"
         virtualName="" explicitFocusOrder="0" pos="152 288 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Brightness" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         kerning="0" bold="0" italic="0" justification="36"/>
  <LABEL name="Attack" id="59fa6a3ecd0a9b58" memberName="lblAttack" virtualName=""
         explicitFocusOrder="0" pos="408 288 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Attack" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         kerning="0" bold="0" italic="0" justification="36"/>
  <LABEL name="Decay" id="58b84c8632a61d73" memberName="lblDecay" virtualName=""
         explicitFocusOrder="0" pos="520 288 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Decay" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         kerning="0" bold="0" italic="0" justification="36"/>
  <LABEL name="Sustain" id="8ae3f11b96181dac" memberName="lblSustain"
         virtualName="" explicitFocusOrder="0" pos="408 440 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Sustain" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         kerning="0" bold="0" italic="0" justification="36"/>
  <LABEL name="Release" id="44acd08419beb97f" memberName="lblRelease"
         virtualName="" explicitFocusOrder="0" pos="520 440 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Release&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" kerning="0" bold="0" italic="0" justification="36"/>
  <SLIDER name="Dynamic level" id="4fe1b8055576c44c" memberName="sldDynamicLevel"
          virtualName="" explicitFocusOrder="1" pos="248 192 104 104" tooltip="Attenuation of string dynamics"
          min="0" max="2" int="0" style="Rotary" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="Excitation cutoff" id="a4bbe216a45ac849" memberName="sldExcitationCutoff"
          virtualName="" explicitFocusOrder="1" pos="248 32 104 104" tooltip="Determines the excitation filter cutoff"
          min="0" max="44100" int="0" style="Rotary" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="0.5"
          needsCallback="1"/>
  <LABEL name="Damping thickness" id="476be157ddfd1c5a" memberName="lblDampingThickness"
         virtualName="" explicitFocusOrder="0" pos="264 288 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Thickness" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         kerning="0" bold="0" italic="0" justification="36"/>
  <LABEL name="Excitation source" id="80083e5000b612b3" memberName="lblExcitationSource"
         virtualName="" explicitFocusOrder="0" pos="32 128 88 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Saw" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         kerning="0" bold="0" italic="0" justification="36"/>
  <LABEL name="Excitation volume" id="32031afdb5b7929" memberName="lblExcitationVolume"
         virtualName="" explicitFocusOrder="0" pos="144 128 88 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Strength" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         kerning="0" bold="0" italic="0" justification="36"/>
  <LABEL name="Excitation cutoff" id="d3f73a9658e8384" memberName="lblExcitationCutoff"
         virtualName="" explicitFocusOrder="0" pos="256 128 88 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Cutoff" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         kerning="0" bold="0" italic="0" justification="36"/>
  <SLIDER name="Tremolo waveform" id="ac06ae33a1ebbd4f" memberName="sldTremoloWaveform"
          virtualName="" explicitFocusOrder="1" pos="24 344 104 104" tooltip="State of the string when fully pulled - i.e. Sin will bend it to the shape of a wave"
          min="0" max="4" int="1" style="Rotary" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <LABEL name="Tremolo depth" id="3fdd662084d0b8e7" memberName="lblTremoloWaveform"
         virtualName="" explicitFocusOrder="0" pos="32 440 88 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Saw" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         kerning="0" bold="0" italic="0" justification="36"/>
  <SLIDER name="Tremolo frequency" id="657ebdfa44885902" memberName="sldTremoloFrequency"
          virtualName="" explicitFocusOrder="1" pos="136 344 104 104" min="0"
          max="15" int="0" style="Rotary" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="0.5" needsCallback="1"/>
  <SLIDER name="Excitation cutoff" id="af5ccd70f4a99dc8" memberName="sldTremoloDepth"
          virtualName="" explicitFocusOrder="1" pos="248 344 104 104" min="0"
          max="1" int="0" style="Rotary" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <LABEL name="Excitation volume" id="eb5f1913491e462e" memberName="lblExcitationVolume2"
         virtualName="" explicitFocusOrder="0" pos="144 440 88 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Frequency" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         kerning="0" bold="0" italic="0" justification="36"/>
  <LABEL name="Tremolo depth" id="25f5cf9527b0cf71" memberName="lblTremoloDepth"
         virtualName="" explicitFocusOrder="0" pos="256 440 88 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Depth&#10;" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         kerning="0" bold="0" italic="0" justification="36"/>
  <SLIDER name="Master volume" id="b1534645c1e0cda5" memberName="sldMasterVolume"
          virtualName="" explicitFocusOrder="1" pos="360 32 104 104" tooltip="Setup master volume"
          min="0" max="1" int="0" style="Rotary" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="0.5"
          needsCallback="1"/>
  <LABEL name="MasterVolume" id="382ee28e22784756" memberName="lblMasterVolume"
         virtualName="" explicitFocusOrder="0" pos="360 128 104 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Master Volume" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" kerning="0" bold="0" italic="0" justification="36"/>
  <TEXTBUTTON name="new button" id="c66178510a2d6fbe" memberName="textButton"
              virtualName="" explicitFocusOrder="0" pos="336 192 16 16" buttonText="V"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="469687030c533769" memberName="tbThicknesVel" virtualName=""
              explicitFocusOrder="0" pos="336 192 16 16" bgColOff="ff808080"
              buttonText="N" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="13cee11fde3779e1" memberName="tbBrightnessVel" virtualName=""
              explicitFocusOrder="0" pos="224 192 16 16" bgColOff="ff808080"
              buttonText="N" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="4d0a8af2de40f94f" memberName="tbLevelVel" virtualName=""
              explicitFocusOrder="0" pos="112 192 16 16" bgColOff="ff808080"
              buttonText="N" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="d5d81509c68cbce7" memberName="tbStrengthVel" virtualName=""
              explicitFocusOrder="0" pos="224 32 16 16" bgColOff="ff808080"
              buttonText="N" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="4c3fbe2c289c1d06" memberName="tbCutoffVel" virtualName=""
              explicitFocusOrder="0" pos="336 32 16 16" bgColOff="ff808080"
              buttonText="N" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="a8ba413bb2e4fc8b" memberName="tbTremoloFreqVel" virtualName=""
              explicitFocusOrder="0" pos="224 344 16 16" bgColOff="ff808080"
              buttonText="N" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="8f4f04c95eeaaf83" memberName="tbTremoloDepthVel"
              virtualName="" explicitFocusOrder="0" pos="336 344 16 16" bgColOff="ff808080"
              buttonText="N" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
