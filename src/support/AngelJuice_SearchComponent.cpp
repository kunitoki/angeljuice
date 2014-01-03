/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  22 Jun 2006 10:04:09 pm

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

#include "AngelJuice_SearchComponent.h"

/*

//==============================================================================
SearchComponent::SearchComponent ()
    : groupSearch (0),
      textSearch (0),
      searchButton (0),
      textReplace (0),
      replaceButton (0),
      toggleSearchAll (0)
{
    addAndMakeVisible (groupSearch = new GroupComponent (T("search"),
                                                         T("Find")));
    addAndMakeVisible (textSearch = new TextEditor (T("searchText")));
    textSearch->setMultiLine (false);
    textSearch->setReturnKeyStartsNewLine (false);
    textSearch->setReadOnly (false);
    textSearch->setScrollbarsShown (false);
    textSearch->setCaretVisible (true);
    textSearch->setPopupMenuEnabled (true);
    textSearch->setColours (Colours::black, Colours::white, Colour (0x401111ee), Colours::transparentBlack, Colour (0x38000000));
    textSearch->setCaretColour (Colours::black);
    textSearch->setText (String::empty);

    addAndMakeVisible (searchButton = new TextButton (T("searchButton")));
    searchButton->addButtonListener (this);
    addAndMakeVisible (textReplace = new TextEditor (T("replaceText")));
    textReplace->setMultiLine (false);
    textReplace->setReturnKeyStartsNewLine (false);
    textReplace->setReadOnly (false);
    textReplace->setScrollbarsShown (false);
    textReplace->setCaretVisible (true);
    textReplace->setPopupMenuEnabled (true);
    textReplace->setColours (Colours::black, Colours::white, Colour (0x401111ee), Colours::transparentBlack, Colour (0x38000000));
    textReplace->setCaretColour (Colours::black);
    textReplace->setText (String::empty);

    addAndMakeVisible (replaceButton = new TextButton (T("replaceButton")));
    replaceButton->addButtonListener (this);
    addAndMakeVisible (toggleSearchAll = new ToggleButton (T("searchAll")));
    toggleSearchAll->addButtonListener (this);

    setSize (500, 300);

    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

SearchComponent::~SearchComponent()
{
    deleteAndZero (groupSearch);
    deleteAndZero (textSearch);
    deleteAndZero (searchButton);
    deleteAndZero (textReplace);
    deleteAndZero (replaceButton);
    deleteAndZero (toggleSearchAll);

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void SearchComponent::paint (Graphics& g)
{
    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom paint stuff here..
    //[/UserPaint]
}

void SearchComponent::resized()
{
    groupSearch->setBounds (proportionOfWidth (0.0060f), proportionOfHeight (0.0000f), proportionOfWidth (0.9860f), proportionOfHeight (0.9900f));
    textSearch->setBounds (proportionOfWidth (0.0340f), proportionOfHeight (0.0800f), proportionOfWidth (0.7600f), proportionOfHeight (0.0500f));
    searchButton->setBounds (proportionOfWidth (0.8060f), proportionOfHeight (0.0767f), proportionOfWidth (0.1600f), proportionOfHeight (0.0533f));
    textReplace->setBounds (proportionOfWidth (0.0340f), proportionOfHeight (0.1600f), proportionOfWidth (0.7600f), proportionOfHeight (0.0500f));
    replaceButton->setBounds (proportionOfWidth (0.8060f), proportionOfHeight (0.1600f), proportionOfWidth (0.1600f), proportionOfHeight (0.0533f));
    toggleSearchAll->setBounds (proportionOfWidth (0.0280f), proportionOfHeight (0.2600f), proportionOfWidth (0.5000f), proportionOfHeight (0.0600f));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void SearchComponent::buttonClicked (Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == searchButton)
    {
        //[UserButtonCode_searchButton] -- add your button handler code here..
        //[/UserButtonCode_searchButton]
    }
    else if (buttonThatWasClicked == replaceButton)
    {
        //[UserButtonCode_replaceButton] -- add your button handler code here..
        //[/UserButtonCode_replaceButton]
    }
    else if (buttonThatWasClicked == toggleSearchAll)
    {
        //[UserButtonCode_toggleSearchAll] -- add your button handler code here..
        //[/UserButtonCode_toggleSearchAll]
    }
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]

*/

//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SearchComponent" componentName=""
                 parentClasses="public Component" constructorParams="" snapPixels="4"
                 snapActive="0" snapShown="0" fixedSize="1" initialWidth="500"
                 initialHeight="300">
  <BACKGROUND backgroundColour="ffffffff"/>
  <GROUPCOMPONENT name="search" memberName="groupSearch" pos="0.6% 0% 98.6% 99%"
                  title="Find"/>
  <TEXTEDITOR name="searchText" memberName="textSearch" pos="3.4% 8% 76% 5%"
              initialText="" multiline="0" retKeyStartsLine="0" readonly="0"
              scrollbars="0" caret="1" popupmenu="1" textcol="ff000000" bkgcol="ffffffff"
              hilitecol="401111ee" outlinecol="0" shadowcol="38000000" caretcol="ff000000"/>
  <TEXTBUTTON name="searchButton" memberName="searchButton" pos="80.6% 7.667% 16% 5.333%"
              buttonText="Search" connectedEdges="0" needsCallback="1" textCol="ff000000"
              bgColOff="ffbbbbff" bgColOn="ff4444ff"/>
  <TEXTEDITOR name="replaceText" memberName="textReplace" pos="3.4% 16% 76% 5%"
              initialText="" multiline="0" retKeyStartsLine="0" readonly="0"
              scrollbars="0" caret="1" popupmenu="1" textcol="ff000000" bkgcol="ffffffff"
              hilitecol="401111ee" outlinecol="0" shadowcol="38000000" caretcol="ff000000"/>
  <TEXTBUTTON name="replaceButton" memberName="replaceButton" pos="80.6% 16% 16% 5.333%"
              buttonText="Replace" connectedEdges="0" needsCallback="1" textCol="ff000000"
              bgColOff="ffbbbbff" bgColOn="ff4444ff"/>
  <TOGGLEBUTTON name="searchAll" memberName="toggleSearchAll" pos="2.8% 26% 50% 6%"
                buttonText="Search in all scripts" connectedEdges="0" needsCallback="1"
                state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


