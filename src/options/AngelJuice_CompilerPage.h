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

#ifndef __JUCER_HEADER_COMPILERPAGE_ANGELJUICECOMPILERPAGE_85D1107D__
#define __JUCER_HEADER_COMPILERPAGE_ANGELJUICECOMPILERPAGE_85D1107D__

//[Headers]     -- You can add your own extra header files here --
#include "../AngelJuice.h"
#include "../AngelJuice_config.h"
//[/Headers]


//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class CompilerPage  : public Component,
                      public ButtonListener
{
public:
    //==============================================================================
    CompilerPage ();
    ~CompilerPage();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void updateGlobalConfig();
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
    GroupComponent* groupScripts;
    GroupComponent* groupApplication;
    GroupComponent* groupCompiler;
    TextEditor* textPreferredExt;
    ToggleButton* toggleSaveOptions;
    ToggleButton* toggleUpdates;
    Label* labelPreferredExt;
    TextButton* saveButton;
    ToggleButton* toggleBreakpoint;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    CompilerPage (const CompilerPage&);
    const CompilerPage& operator= (const CompilerPage&);
};


#endif  // __JUCER_HEADER_COMPILERPAGE_ANGELJUICECOMPILERPAGE_85D1107D__
