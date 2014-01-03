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

#ifndef __JUCER_HEADER_SEARCHCOMPONENT_ANGELJUICESEARCHCOMPONENT_73AEC029__
#define __JUCER_HEADER_SEARCHCOMPONENT_ANGELJUICESEARCHCOMPONENT_73AEC029__

//[Headers]     -- You can add your own extra header files here --
#include "../AngelJuice_config.h"
//[/Headers]


//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class SearchComponent  : public Component,
                         public ButtonListener
{
public:
    //==============================================================================
    SearchComponent ();
    ~SearchComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    GroupComponent* groupSearch;
    TextEditor* textSearch;
    TextButton* searchButton;
    TextEditor* textReplace;
    TextButton* replaceButton;
    ToggleButton* toggleSearchAll;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    SearchComponent (const SearchComponent&);
    const SearchComponent& operator= (const SearchComponent&);
};


#endif  // __JUCER_HEADER_SEARCHCOMPONENT_ANGELJUICESEARCHCOMPONENT_73AEC029__
