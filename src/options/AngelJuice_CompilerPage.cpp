/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  16 Jun 2006 1:18:16 am

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "AngelJuice_CompilerPage.h"

/*


//==============================================================================
CompilerPage::CompilerPage ()
    : groupScripts (0),
      groupApplication (0),
      groupCompiler (0),
      textPreferredExt (0),
      toggleSaveOptions (0),
      toggleUpdates (0),
      labelPreferredExt (0),
      saveButton (0),
      toggleBreakpoint (0)
{
    addAndMakeVisible (groupScripts = new GroupComponent (String::empty,
                                                          T("Scripts")));
    addAndMakeVisible (groupApplication = new GroupComponent (String::empty,
                                                              T("Application")));
    addAndMakeVisible (groupCompiler = new GroupComponent (String::empty,
                                                           T("Compiler")));
    addAndMakeVisible (textPreferredExt = new TextEditor (String::empty));
    textPreferredExt->setMultiLine (false);
    textPreferredExt->setReturnKeyStartsNewLine (false);
    textPreferredExt->setReadOnly (false);
    textPreferredExt->setScrollbarsShown (false);
    textPreferredExt->setCaretVisible (true);
    textPreferredExt->setPopupMenuEnabled (true);
    textPreferredExt->setColours (Colours::black, Colours::white, Colour (0x401111ee), Colours::transparentBlack, Colour (0x38000000));
    textPreferredExt->setCaretColour (Colours::black);
    textPreferredExt->setText (T("ajs"));

    addAndMakeVisible (toggleSaveOptions = new ToggleButton (T("Save options at exit")));
    toggleSaveOptions->setTooltip (T("Check if you want to save your current changes to the options when exiting application"));
    toggleSaveOptions->addButtonListener (this);

    addAndMakeVisible (toggleUpdates = new ToggleButton (T("Automatic updates check")));
    toggleUpdates->setTooltip (T("Check if you want AngelJuice to check to new updates on the net"));
    toggleUpdates->addButtonListener (this);

    addAndMakeVisible (labelPreferredExt = new Label (String::empty,
                                                      T("preferred script extension")));
    labelPreferredExt->setFont (Font (15.0000f, Font::plain));
    labelPreferredExt->setJustificationType (Justification::centredLeft);
    labelPreferredExt->setEditable (false, false, false);
    labelPreferredExt->setColours (Colours::black, Colours::transparentBlack, Colours::black,
                                   Colours::transparentBlack, Colour (0x401111ee), Colours::transparentBlack);

    addAndMakeVisible (saveButton = new TextButton (T("save now!")));
    saveButton->addButtonListener (this);
    addAndMakeVisible (toggleBreakpoint = new ToggleButton (T("Save breakpoints with project")));
    toggleBreakpoint->setTooltip (T("Check if you want AngelJuice to check to new updates on the net"));
    toggleBreakpoint->addButtonListener (this);

    setSize (600, 400);

    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

CompilerPage::~CompilerPage()
{
    deleteAndZero (groupScripts);
    deleteAndZero (groupApplication);
    deleteAndZero (groupCompiler);
    deleteAndZero (textPreferredExt);
    deleteAndZero (toggleSaveOptions);
    deleteAndZero (toggleUpdates);
    deleteAndZero (labelPreferredExt);
    deleteAndZero (saveButton);
    deleteAndZero (toggleBreakpoint);

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CompilerPage::paint (Graphics& g)
{
    g.fillAll (Colours::transparentWhite);

    //[UserPaint] Add your own custom paint stuff here..
    //[/UserPaint]
}

void CompilerPage::resized()
{
    groupScripts->setBounds (proportionOfWidth (0.5033f), proportionOfHeight (0.5000f), proportionOfWidth (0.4900f), proportionOfHeight (0.4900f));
    groupApplication->setBounds (proportionOfWidth (0.0067f), proportionOfHeight (0.5000f), proportionOfWidth (0.4867f), proportionOfHeight (0.4900f));
    groupCompiler->setBounds (proportionOfWidth (0.0067f), proportionOfHeight (0.0100f), proportionOfWidth (0.9867f), proportionOfHeight (0.4900f));
    textPreferredExt->setBounds (proportionOfWidth (0.9667f) - proportionOfWidth (0.0967f), proportionOfHeight (0.5600f), proportionOfWidth (0.0967f), proportionOfHeight (0.0600f));
    toggleSaveOptions->setBounds (proportionOfWidth (0.0333f), proportionOfHeight (0.6200f), proportionOfWidth (0.2500f), proportionOfHeight (0.0600f));
    toggleUpdates->setBounds (proportionOfWidth (0.0333f), proportionOfHeight (0.5600f), proportionOfWidth (0.4333f), proportionOfHeight (0.0600f));
    labelPreferredExt->setBounds (proportionOfWidth (0.5300f), proportionOfHeight (0.5600f), proportionOfWidth (0.3233f), proportionOfHeight (0.0600f));
    saveButton->setBounds (proportionOfWidth (0.3000f), proportionOfHeight (0.6300f), proportionOfWidth (0.1733f), proportionOfHeight (0.0450f));
    toggleBreakpoint->setBounds (proportionOfWidth (0.5300f), proportionOfHeight (0.6200f), proportionOfWidth (0.4333f), proportionOfHeight (0.0600f));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void CompilerPage::buttonClicked (Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == toggleSaveOptions)
    {
        //[UserButtonCode_toggleSaveOptions] -- add your button handler code here..
		updateGlobalConfig();
        //[/UserButtonCode_toggleSaveOptions]
    }
    else if (buttonThatWasClicked == toggleUpdates)
    {
        //[UserButtonCode_toggleUpdates] -- add your button handler code here..
		updateGlobalConfig();
        //[/UserButtonCode_toggleUpdates]
    }
    else if (buttonThatWasClicked == saveButton)
    {
        //[UserButtonCode_saveButton] -- add your button handler code here..
		GlobalConfig::getInstance()->flush();
        //[/UserButtonCode_saveButton]
    }
    else if (buttonThatWasClicked == toggleBreakpoint)
    {
        //[UserButtonCode_toggleBreakpoint] -- add your button handler code here..
		updateGlobalConfig();
        //[/UserButtonCode_toggleBreakpoint]
    }
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void CompilerPage::updateGlobalConfig()
{
	GlobalConfig* config = GlobalConfig::getInstance();

	config->automaticUpdates = toggleUpdates->getToggleState();
	config->saveAtExit = toggleSaveOptions->getToggleState();

}
//[/MiscUserCode]


*/

//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CompilerPage" componentName=""
                 parentClasses="public Component" constructorParams="" snapPixels="2"
                 snapActive="1" snapShown="0" fixedSize="1" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="00ffffff"/>
  <GROUPCOMPONENT name="" memberName="groupScripts" pos="50.333% 50% 49% 49%" title="Scripts"/>
  <GROUPCOMPONENT name="" memberName="groupApplication" pos="0.667% 50% 48.667% 49%"
                  title="Application"/>
  <GROUPCOMPONENT name="" memberName="groupCompiler" pos="0.667% 1% 98.667% 49%"
                  title="Compiler"/>
  <TEXTEDITOR name="" memberName="textPreferredExt" pos="96.667%r 56% 9.667% 6%"
              initialText="ajs" multiline="0" retKeyStartsLine="0" readonly="0"
              scrollbars="0" caret="1" popupmenu="1" textcol="ff000000" bkgcol="ffffffff"
              hilitecol="401111ee" outlinecol="0" shadowcol="38000000" caretcol="ff000000"/>
  <TOGGLEBUTTON name="Save options at exit" memberName="toggleSaveOptions" pos="3.333% 62% 25% 6%"
                tooltip="Check if you want to save your current changes to the options when exiting application"
                buttonText="Save options at exit" connectedEdges="0" needsCallback="1"
                state="0"/>
  <TOGGLEBUTTON name="Automatic updates check" memberName="toggleUpdates" pos="3.333% 56% 43.333% 6%"
                tooltip="Check if you want AngelJuice to check to new updates on the net"
                buttonText="Automatic updates check" connectedEdges="0" needsCallback="1"
                state="0"/>
  <LABEL name="" memberName="labelPreferredExt" pos="53% 56% 32.333% 6%"
         labelText="preferred script extension" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" textCol="ff000000"
         bkgCol="0" edTextCol="ff000000" edBkgCol="0" hiliteCol="401111ee"
         outlineCol="0" fontname="Default font" fontsize="15" bold="0"
         italic="0" justification="33"/>
  <TEXTBUTTON name="save now!" memberName="saveButton" pos="30% 63% 17.333% 4.5%"
              buttonText="save now!" connectedEdges="0" needsCallback="1" textCol="ff000000"
              bgColOff="ffbbbbff" bgColOn="ff4444ff"/>
  <TOGGLEBUTTON name="Save breakpoints with project" memberName="toggleBreakpoint"
                pos="53% 62% 43.333% 6%" tooltip="Check if you want AngelJuice to check to new updates on the net"
                buttonText="Save breakpoints with project" connectedEdges="0"
                needsCallback="1" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


