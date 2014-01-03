/*
  ==============================================================================

   This file is part of AngelJuice

   which is based on kRAkEn/gORe eJUCE library
   which uses
               Raw Material Software ltd. JUCE library
               AngelCode AngelScript scripting library

   AngelJuice can be redistributed and/or modified under the terms of the
   GNU General Public License, as published by the Free Software Foundation;
   either version 2 of the License, or (at your option) any later version.

   AngelJuice is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with eJUCE; if not, visit www.gnu.org/licenses or write to the
   Free Software Foundation, Inc., 59 Temple Place, Suite 330,
   Boston, MA 02111-1307 USA

   @coder	Asnaghi Lucio a.k.a. kRAkEn/gORe

  ==============================================================================
*/

#include "../../libraries/angelscript/angelscript.h"
#include "AngelJuice_AngelScriptCommon.h"
#include "AngelJuice_AngelScriptCore.h"
#include "AngelJuice_AngelScriptString.h"
#include "AngelJuice_AngelScriptImaging.h"
#include "AngelJuice_AngelScriptComponent.h"
#include "../AngelJuice_ScriptableEngine.h"


//==============================================================================
asComponentPeer::asComponentPeer()
{
    windowAppearsOnTaskbar   = ComponentPeer::windowAppearsOnTaskbar;
    windowIsTemporary        = ComponentPeer::windowIsTemporary;
    windowIgnoresMouseClicks = ComponentPeer::windowIgnoresMouseClicks;
    windowHasTitleBar        = ComponentPeer::windowHasTitleBar;
    windowIsResizable        = ComponentPeer::windowIsResizable;
    windowHasMinimiseButton  = ComponentPeer::windowHasMinimiseButton;
    windowHasMaximiseButton  = ComponentPeer::windowHasMaximiseButton;
    windowHasCloseButton     = ComponentPeer::windowHasCloseButton;
    windowHasDropShadow      = ComponentPeer::windowHasDropShadow;
}

asComponentPeer::~asComponentPeer()
{
}

static asComponentPeer globalPeer = asComponentPeer();

//==============================================================================
asComponent::asComponent() :
	Thread("asComponent"),
	methodOwner(0)
{
	setOpaque (true);
	eventContext = ScriptableEngine::getInstance()->createContext();
}

asComponent::~asComponent()
{
	deleteAllChildren();

	eventContext->Release();
	eventContext = 0;
}

void asComponent::addRef() {}
void asComponent::release() {}

enum asComponentMethods
{
	PAINT = 0,
	PAINTOVERCHILDREN,
	MOUSEMOVE,
	MOUSEENTER,
	MOUSEEXIT,
	MOUSEDRAG,
	MOUSEDOWN,
	MOUSEUP,
	MOUSEDOUBLECLICK,
	MOUSEWHEELMOVE,
	KEYPRESSED,
	KEYSTATECHANGED,
	MODIFIERKEYSCHANGED,
	RESIZED,
	MOVED,
	CHILDBOUNDSCHANGED,
	PARENTSIZECHANGED,
	INPUTATTEMPTWHENMODAL,
	BROUGHTTOFRONT,
	FILESDROPPED,
	VISIBILITYCHANGED,
	USERTRIEDTOCLOSEWINDOW,
	MINIMISATIONSTATECHANGED,
	PARENTHIERARCHYCHANGED,
	CHILDRENCHANGED,
	HITTEST,
	ENABLEMENTCHANGED,
	RUN,
	TIMER,
	BUTTONCLICKED,
	NUM_CALLBACKS
};

void asComponent::setClassAndObject(const String& className_,const String& objectName_)
{
	className = className_;
	objectName = objectName_;

	asIScriptEngine* scriptEngine = ScriptableEngine::getInstance()->getEngine();

	int classID = scriptEngine->GetTypeIdByDecl (0, (const char*)className_);
	int methodOwnerID = scriptEngine->GetGlobalVarIDByName (0, (const char*)objectName_);
	methodOwner = scriptEngine->GetGlobalVarPointer (methodOwnerID);

	methodId.ensureStorageAllocated (NUM_CALLBACKS);

	methodId.insert(PAINT,						scriptEngine->GetMethodIDByDecl(classID,"void paint(Graphics&)"));
	methodId.insert(PAINTOVERCHILDREN,			scriptEngine->GetMethodIDByDecl(classID,"void paintOverChildren(Graphics&)"));
	methodId.insert(MOUSEMOVE,					scriptEngine->GetMethodIDByDecl(classID,"void mouseMove(const MouseEvent& in)"));
	methodId.insert(MOUSEENTER,					scriptEngine->GetMethodIDByDecl(classID,"void mouseEnter(const MouseEvent& in)"));
	methodId.insert(MOUSEEXIT,					scriptEngine->GetMethodIDByDecl(classID,"void mouseExit(const MouseEvent& in)"));
	methodId.insert(MOUSEDRAG,					scriptEngine->GetMethodIDByDecl(classID,"void mouseDrag(const MouseEvent& in)"));
	methodId.insert(MOUSEDOWN,					scriptEngine->GetMethodIDByDecl(classID,"void mouseDown(const MouseEvent& in)"));
	methodId.insert(MOUSEUP,					scriptEngine->GetMethodIDByDecl(classID,"void mouseUp(const MouseEvent& in)"));
	methodId.insert(MOUSEDOUBLECLICK,			scriptEngine->GetMethodIDByDecl(classID,"void mouseDoubleClick(const MouseEvent& in)"));
	methodId.insert(MOUSEWHEELMOVE,				scriptEngine->GetMethodIDByDecl(classID,"void mouseWheelMove(const MouseEvent& in, float, float)"));
	methodId.insert(KEYPRESSED,					scriptEngine->GetMethodIDByDecl(classID,"bool keyPressed(const KeyPress& in)"));
	methodId.insert(KEYSTATECHANGED,			scriptEngine->GetMethodIDByDecl(classID,"void keyStateChanged()"));
	methodId.insert(MODIFIERKEYSCHANGED,		scriptEngine->GetMethodIDByDecl(classID,"void modifiersKeyChanged(const ModifierKeys& in)"));
	methodId.insert(RESIZED,					scriptEngine->GetMethodIDByDecl(classID,"void resized()"));
	methodId.insert(MOVED,						scriptEngine->GetMethodIDByDecl(classID,"void moved()"));
	methodId.insert(CHILDBOUNDSCHANGED,			scriptEngine->GetMethodIDByDecl(classID,"void childBoundsChanged(Component@+)"));
	methodId.insert(PARENTSIZECHANGED,			scriptEngine->GetMethodIDByDecl(classID,"void parentSizeChanged()"));
	methodId.insert(INPUTATTEMPTWHENMODAL,		scriptEngine->GetMethodIDByDecl(classID,"void inputAttemptWhenModal()"));
	methodId.insert(BROUGHTTOFRONT,				scriptEngine->GetMethodIDByDecl(classID,"void broughtToFront()"));
//	methodId.insert(FILESDROPPED,				scriptEngine->GetMethodIDByDecl(classID,"void filesDropped(const StringArray& in,int,int)"));
    methodId.insert(FILESDROPPED,               scriptEngine->GetMethodIDByDecl(classID,"void filesDropped(const String& in,int,int)"));
	methodId.insert(VISIBILITYCHANGED,			scriptEngine->GetMethodIDByDecl(classID,"void visibilityChanged()"));
	methodId.insert(USERTRIEDTOCLOSEWINDOW,		scriptEngine->GetMethodIDByDecl(classID,"void userTriedToCloseWindow()"));
	methodId.insert(MINIMISATIONSTATECHANGED,	scriptEngine->GetMethodIDByDecl(classID,"void minimisationStateChanged(bool)"));
	methodId.insert(PARENTHIERARCHYCHANGED,		scriptEngine->GetMethodIDByDecl(classID,"void parentHierarchyChanged()"));
	methodId.insert(CHILDRENCHANGED,			scriptEngine->GetMethodIDByDecl(classID,"void childrenChanged()"));
	methodId.insert(HITTEST,					scriptEngine->GetMethodIDByDecl(classID,"void hitTest(int,int)"));
	methodId.insert(ENABLEMENTCHANGED,			scriptEngine->GetMethodIDByDecl(classID,"void enablementChanged()"));
	methodId.insert(RUN,						scriptEngine->GetMethodIDByDecl(classID,"void run()"));
	methodId.insert(TIMER,						scriptEngine->GetMethodIDByDecl(classID,"void timerCallback()"));
	methodId.insert(BUTTONCLICKED,				scriptEngine->GetMethodIDByDecl(classID,"void buttonClicked(const String&)"));
}

void asComponent::paint(Graphics& g) {
	if (eventContext && methodId[PAINT] >= 0 && methodOwner != 0) {
		eventContext->Prepare(methodId[PAINT]);
		eventContext->SetObject(methodOwner);
		eventContext->SetArgObject(0, (void*)&g);
		doExecuteContext();
	}
}

void asComponent::paintOverChildren(Graphics& g) {
	if (eventContext && methodId[PAINTOVERCHILDREN] >= 0 && methodOwner != 0) {
		eventContext->Prepare(methodId[PAINTOVERCHILDREN]);
		eventContext->SetObject(methodOwner);
		eventContext->SetArgObject(0, (void*)&g);
		doExecuteContext();
	}
}

void asComponent::mouseMove (const MouseEvent& e) {
	if (eventContext && eventContext && methodId[MOUSEMOVE] >= 0 && methodOwner != 0) {
		eventContext->Prepare(methodId[MOUSEMOVE]);
		eventContext->SetObject(methodOwner);
		eventContext->SetArgObject(0, (void*)&e);
		doExecuteContext();
	}
}

void asComponent::mouseEnter (const MouseEvent& e) {
	if (eventContext && methodId[MOUSEENTER] >= 0 && methodOwner != 0) {
		eventContext->Prepare(methodId[MOUSEENTER]);
		eventContext->SetObject(methodOwner);
		eventContext->SetArgObject(0, (void*)&e);
		doExecuteContext();
	}
}

void asComponent::mouseExit (const MouseEvent& e) {
	if (eventContext && methodId[MOUSEEXIT] >= 0 && methodOwner != 0) {
		eventContext->Prepare(methodId[MOUSEEXIT]);
		eventContext->SetObject(methodOwner);
		eventContext->SetArgObject(0, (void*)&e);
		doExecuteContext();
	}
}

void asComponent::mouseDrag (const MouseEvent& e) {
	if (eventContext && methodId[MOUSEDRAG] >= 0 && methodOwner != 0) {
		eventContext->Prepare(methodId[MOUSEDRAG]);
		eventContext->SetObject(methodOwner);
		eventContext->SetArgObject(0, (void*)&e);
		doExecuteContext();
	}
}

void asComponent::mouseDown (const MouseEvent& e) {
	if (eventContext && methodId[MOUSEDOWN] >= 0 && methodOwner != 0) {
		eventContext->Prepare(methodId[MOUSEDOWN]);
		eventContext->SetObject(methodOwner);
		eventContext->SetArgObject(0, (void*)&e);
		doExecuteContext();
	}
}

void asComponent::mouseUp (const MouseEvent& e) {
	if (eventContext && methodId[MOUSEUP] >= 0 && methodOwner != 0) {
		eventContext->Prepare(methodId[MOUSEUP]);
		eventContext->SetObject(methodOwner);
		eventContext->SetArgObject(0, (void*)&e);
		doExecuteContext();
	}
}

void asComponent::mouseDoubleClick (const MouseEvent& e) {
	if (eventContext && methodId[MOUSEDOUBLECLICK] >= 0 && methodOwner != 0) {
		eventContext->Prepare(methodId[MOUSEDOUBLECLICK]);
		eventContext->SetObject(methodOwner);
		eventContext->SetArgObject(0, (void*)&e);
		doExecuteContext();
	}
}

void asComponent::mouseWheelMove (const MouseEvent& e, float ix, float iy) {
	if (eventContext && methodId[MOUSEWHEELMOVE] >= 0 && methodOwner != 0) {
		eventContext->Prepare(methodId[MOUSEWHEELMOVE]);
		eventContext->SetObject(methodOwner);
		eventContext->SetArgObject(0, (void*)&e);
		eventContext->SetArgFloat(1, ix);
		eventContext->SetArgFloat(2, iy);
		doExecuteContext();
	}
}

bool asComponent::keyPressed (const KeyPress& e) {
	if (eventContext && methodId[KEYPRESSED] >= 0 && methodOwner != 0) {
		eventContext->Prepare(methodId[KEYPRESSED]);
		eventContext->SetObject(methodOwner);
		eventContext->SetArgObject(0, (void*)&e);
		doExecuteContext();
        return true; // TODO - get arg from script
	}
	return false;
}

void asComponent::resized() {
	if (eventContext && methodId[RESIZED] >= 0 && methodOwner != 0) {
		eventContext->Prepare(methodId[RESIZED]);
		eventContext->SetObject(methodOwner);
		doExecuteContext();
	}
}

void asComponent::moved() {
	if (eventContext && methodId[MOVED] >= 0 && methodOwner != 0) {
		eventContext->Prepare(methodId[MOVED]);
		eventContext->SetObject(methodOwner);
		doExecuteContext();
	}
}

void asComponent::run() {
	if (eventContext && methodId[RUN] >= 0 && methodOwner != 0) {
		eventContext->Prepare(methodId[RUN]);
		eventContext->SetObject(methodOwner);
		doExecuteContext();
	}
}

void asComponent::timerCallback() {
	if (eventContext && methodId[TIMER] >= 0 && methodOwner != 0) {
		eventContext->Prepare(methodId[TIMER]);
		eventContext->SetObject(methodOwner);
		doExecuteContext();
	}
}

void asComponent::buttonClicked (Button* button) {
	if (eventContext && methodId[BUTTONCLICKED] >= 0 && methodOwner != 0)
	{
		asString* buttonName = new asString (button->getButtonText());

		eventContext->Prepare(methodId[BUTTONCLICKED]);
		eventContext->SetObject(methodOwner);
		eventContext->SetArgObject(0, (void*)buttonName);
		doExecuteContext();

		buttonName->release ();
	}
}



void asComponent::doExecuteContext ()
{
	// @TODO : call execute on the script engine instead !

    ScriptableEngine* engine = ScriptableEngine::getInstance();

    bool returnValue = false;
    bool exitLoop = false;

    engine->runningScript = true;
    engine->abortScript = false;
    engine->continueSilently = false;

    while (!engine->abortScript && !exitLoop)
    {
        engine->timeOut = Time::getMillisecondCounter() + 100; // 100
        int r = eventContext->Execute();

        switch(r)
        {
        case asEXECUTION_FINISHED:
            {
            returnValue = true;
            exitLoop = true;
            break;
            }
        case asEXECUTION_SUSPENDED:
            {
            MessageManager::getInstance()->dispatchPendingMessages ();
            break;
            }
        case asEXECUTION_ABORTED:
            {
            engine->engineModel->reportErrors (T("Exception"),
                                               T("The script has timed out."),
                                               engine->resolveOriginalFile (eventContext->GetExceptionLineNumber()),
                                               engine->resolveOriginalLine (eventContext->GetExceptionLineNumber()) );
            exitLoop = true;
            break;
            }
        case asEXECUTION_EXCEPTION:
            {
            int funcID = eventContext->GetExceptionFunction();

            engine->engineModel->reportErrors (T("Exception"),
                                               engine->resolveFunctionDeclaration (funcID) + " : " +eventContext->GetExceptionString(),
                                               engine->resolveOriginalFile (eventContext->GetExceptionLineNumber()),
                                               engine->resolveOriginalLine (eventContext->GetExceptionLineNumber()) );
            exitLoop = true;
            break;
            }
        default:
            exitLoop = true;
            break;
        }

        if (exitLoop)
            break;
    }

    // @TODO : keep out this from here ?
    engine->runningScript = false;
}


//==============================================================================
asString* asComponent::getName () {
	return new asString(Component::getName());
}

void asComponent::addToDesktop (int windowStyleFlags){
	Component::addToDesktop (windowStyleFlags);
}
asRectangle* asComponent::getBounds(){
	return new asRectangle(Component::getBounds ());
}
asRectangle* asComponent::getParentMonitorArea(){
	return new asRectangle(Component::getParentMonitorArea ());
}
asImage* asComponent::createComponentSnapshot (const asRectangle& areaToGrab){
	return new asImage(Component::createComponentSnapshot (areaToGrab.rect));
}


void Component_addAndMakeVisible (Component* const child, asComponent *thisPointer)
{
	thisPointer->addAndMakeVisible (child);
}
void Component_addAndMakeVisible (Component* const child, int zOrder, asComponent *thisPointer)
{
	thisPointer->addAndMakeVisible (child, zOrder);
}


//==============================================================================
void Component_startTimer (int millis, asComponent *thisPointer){
	thisPointer->startTimer (millis);
}
void Component_stopTimer (asComponent *thisPointer){
	thisPointer->stopTimer ();
}
bool Component_isTimerRunning (asComponent *thisPointer){
	return thisPointer->isTimerRunning ();
}
int Component_getTimerInterval (asComponent *thisPointer){
	return thisPointer->getTimerInterval ();
}



//==============================================================================
void ConstructComponent(asComponent *thisPointer) {
    new(thisPointer) asComponent();
	asComponentManager::getInstance()->registerComponent (thisPointer);
}
void DestructComponent(asComponent *thisPointer) {
//	thisPointer->~asComponent();
}
static void *AllocComponent(int) {
	return new char[sizeof(asComponent)];
}
static void FreeComponent(void *p) {
//	jassert( p );
//	delete p;
}

void asComponent::registerObjectType(asIScriptEngine *engine)
{
	int r;

	//==============================================================================
	r = engine->RegisterObjectType("ComponentPeer_", 0, asOBJ_PRIMITIVE); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("ComponentPeer_", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(dummy_Constructor), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectBehaviour("ComponentPeer_", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(dummy_Destructor), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectProperty("ComponentPeer_", "const int windowAppearsOnTaskbar",	offsetof(asComponentPeer,windowAppearsOnTaskbar));
	r = engine->RegisterObjectProperty("ComponentPeer_", "const int windowIsTemporary",		    offsetof(asComponentPeer,windowIsTemporary));
	r = engine->RegisterObjectProperty("ComponentPeer_", "const int windowIgnoresMouseClicks",	offsetof(asComponentPeer,windowIgnoresMouseClicks));
	r = engine->RegisterObjectProperty("ComponentPeer_", "const int windowHasTitleBar",		    offsetof(asComponentPeer,windowHasTitleBar));
	r = engine->RegisterObjectProperty("ComponentPeer_", "const int windowIsResizable",		    offsetof(asComponentPeer,windowIsResizable));
	r = engine->RegisterObjectProperty("ComponentPeer_", "const int windowHasMinimiseButton",	offsetof(asComponentPeer,windowHasMinimiseButton));
	r = engine->RegisterObjectProperty("ComponentPeer_", "const int windowHasMaximiseButton",	offsetof(asComponentPeer,windowHasMaximiseButton));
	r = engine->RegisterObjectProperty("ComponentPeer_", "const int windowHasCloseButton",		offsetof(asComponentPeer,windowHasCloseButton));
	r = engine->RegisterObjectProperty("ComponentPeer_", "const int windowHasDropShadow",		offsetof(asComponentPeer,windowHasDropShadow));

	engine->RegisterGlobalProperty("ComponentPeer_ ComponentPeer",(void*)&globalPeer);

	//==============================================================================
	r = engine->RegisterObjectType("Component", sizeof(asComponent), asOBJ_CLASS_CD); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Component", asBEHAVE_CONSTRUCT,  "void f()",                           asFUNCTION(ConstructComponent), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Component", asBEHAVE_DESTRUCT,   "void f()",                           asFUNCTION(DestructComponent), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Component", asBEHAVE_ADDREF,     "void f()",                           asMETHOD(asComponent,addRef), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Component", asBEHAVE_RELEASE,    "void f()",                           asMETHOD(asComponent,release), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Component", asBEHAVE_ALLOC,      "Component &f(uint)",                 asFUNCTION(AllocComponent), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Component", asBEHAVE_FREE,       "void f(Component &in)",              asFUNCTION(FreeComponent), asCALL_CDECL); jassert( r >= 0 );

	r = engine->RegisterObjectMethod("Component", "void setClassAndObject(const String& in,const String& in)",  asMETHOD(asComponent,setClassAndObject), asCALL_THISCALL); jassert( r >= 0 );

	r = engine->RegisterObjectMethod("Component", "String@ getName()",                                          asMETHOD(asComponent,getName), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "void setName(const String& in)",                             asMETHOD(Component,setName), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "bool isValidComponent()",                                    asMETHOD(Component,isValidComponent), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "void setVisible(bool)",                                      asMETHOD(Component,setVisible), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "bool isVisible()",                                           asMETHOD(Component,isVisible), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "bool isShowing()",                                           asMETHOD(Component,isShowing), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "void fadeOutComponent(int,int,int,float)",                   asMETHOD(Component,fadeOutComponent), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "void addToDesktop(int)",                                     asMETHOD(asComponent,addToDesktop), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "void removeFromDesktop()",                                   asMETHOD(Component,removeFromDesktop), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "bool isOnDesktop()",                                         asMETHOD(Component,isOnDesktop), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "void toFront(bool)",                                         asMETHOD(Component,toFront), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "void toBack()",                                              asMETHOD(Component,toBack), asCALL_THISCALL); jassert( r >= 0 );
//    void toBehind (Component* const other);
	r = engine->RegisterObjectMethod("Component", "void setAlwaysOnTop(bool)",                                  asMETHOD(Component,setAlwaysOnTop), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "bool isAlwaysOnTop()",                                       asMETHOD(Component,isAlwaysOnTop), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "int getX()",                                                 asMETHOD(Component,getX), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "int getY()",                                                 asMETHOD(Component,getY), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "int getWidth()",                                             asMETHOD(Component,getWidth), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "int getHeight()",                                            asMETHOD(Component,getHeight), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "int getRight()",                                             asMETHOD(Component,getRight), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "int getBottom()",                                            asMETHOD(Component,getBottom), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "Rectangle@ getBounds()",                                     asMETHOD(asComponent,getBounds), asCALL_THISCALL); jassert( r >= 0 );
//    int getXRelativeTo (Component* otherComponent) const;
//    int getYRelativeTo (Component* otherComponent) const;
//    void getVisibleArea (RectangleList& result, const bool includeSiblings) const;
	r = engine->RegisterObjectMethod("Component", "int getScreenX()",                                           asMETHOD(Component,getScreenX), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "int getScreenY()",                                           asMETHOD(Component,getScreenY), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "void setTopLeftPosition(int,int)",                           asMETHOD(Component,setTopLeftPosition), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "void setTopRightPosition(int,int)",                          asMETHOD(Component,setTopRightPosition), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "void setSize(int,int)",                                      asMETHOD(Component,setSize), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "void setBounds(int,int,int,int)",                            asMETHODPR(Component,setBounds,(const int,const int,const int,const int),void), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "void setBounds(const Rectangle& in)",                        asMETHODPR(Component,setBounds,(const Rectangle&),void), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "void setBoundsRelative(float,float,float,float)",            asMETHOD(Component,setBoundsRelative), asCALL_THISCALL); jassert( r >= 0 );
//    void setBoundsInset (const BorderSize& borders);
//    void setBoundsToFit (int x, int y, int width, int height,const Justification& justification,const bool onlyReduceInSize);
	r = engine->RegisterObjectMethod("Component", "void setCentrePosition(int,int)",                            asMETHOD(Component,setCentrePosition), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "void setCentreRelative(int,int)",                            asMETHOD(Component,setCentreRelative), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "void centreWithSize(int,int)",                               asMETHOD(Component,centreWithSize), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "int proportionOfWidth(float)",                               asMETHOD(Component,proportionOfWidth), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "int proportionOfHeight(float)",                              asMETHOD(Component,proportionOfHeight), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "int getParentWidth()",                                       asMETHOD(Component,getParentWidth), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "int getParentHeight()",                                      asMETHOD(Component,getParentHeight), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "Rectangle@ getParentMonitorArea()",                          asMETHOD(asComponent,getParentMonitorArea), asCALL_THISCALL); jassert( r >= 0 );

	r = engine->RegisterObjectMethod("Component", "int getNumChildComponents()",                                asMETHOD(Component,getNumChildComponents), asCALL_THISCALL); jassert( r >= 0 );
//    Component* getChildComponent (const int index) const throw();
//    void addChildComponent (Component* const child, int zOrder = -1);
//    void addAndMakeVisible (Component* const child, int zOrder = -1);
//    void removeChildComponent (Component* const childToRemove);
//    Component* removeChildComponent (const int childIndexToRemove);
	r = engine->RegisterObjectMethod("Component", "void removeAllChildren()",                                   asMETHOD(Component,removeAllChildren), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "void deleteAllChildren()",                                   asMETHOD(Component,deleteAllChildren), asCALL_THISCALL); jassert( r >= 0 );

	//    Component* getParentComponent() const    { return parentComponent_; }
//    Component* getTopLevelComponent() const;
//    bool isParentOf (const Component* possibleChild) const;
	r = engine->RegisterObjectMethod("Component", "void setInterceptsMouseClicks(bool,bool)",                   asMETHOD(Component,setInterceptsMouseClicks), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "bool contains(int,int)",                                     asMETHOD(Component,contains), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "bool reallyContains(int,int,bool)",                          asMETHOD(Component,reallyContains), asCALL_THISCALL); jassert( r >= 0 );
//    Component* getComponentAt (const int x, const int y);
	r = engine->RegisterObjectMethod("Component", "void repaint()",                                             asMETHODPR(Component,repaint,(),void), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "void repaint(int,int,int,int)",                              asMETHODPR(Component,repaint,(const int,const int,const int,const int),void), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "void setBufferedToImage(bool)",                              asMETHOD(Component,setBufferedToImage), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "Image@ createComponentSnapshot(const Rectangle& in)",        asMETHOD(asComponent,createComponentSnapshot), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "void paintEntireComponent(Graphics& in)",                    asMETHOD(Component,paintEntireComponent), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "void setOpaque(bool)",                                       asMETHOD(Component,setOpaque), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "bool isOpaque()",                                            asMETHOD(Component,isOpaque), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "void setBroughtToFrontOnMouseClick(bool)",                   asMETHOD(Component,setBroughtToFrontOnMouseClick), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "bool isBroughtToFrontOnMouseClick()",                        asMETHOD(Component,isBroughtToFrontOnMouseClick), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "void setWantsKeyboardFocus(bool)",                           asMETHOD(Component,setWantsKeyboardFocus), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "void setMouseClickGrabsKeyboardFocus(bool)",                 asMETHOD(Component,setMouseClickGrabsKeyboardFocus), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "bool getWantsKeyboardFocus()",                               asMETHOD(Component,getWantsKeyboardFocus), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "void grabKeyboardFocus()",                                   asMETHOD(Component,grabKeyboardFocus), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "bool hasKeyboardFocus(bool)",                                asMETHOD(Component,hasKeyboardFocus), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "void moveKeyboardFocusToSibling(bool)",                      asMETHOD(Component,moveKeyboardFocusToSibling), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "bool isEnabled()",                                           asMETHOD(Component,isEnabled), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "void setEnabled(bool)",                                      asMETHOD(Component,setEnabled), asCALL_THISCALL); jassert( r >= 0 );
//    void setMouseCursor (const MouseCursor& cursorType);
//    virtual const MouseCursor getMouseCursor();
//    void updateMouseCursor() const;
    r = engine->RegisterObjectMethod("Component", "void beginDragAutoRepeat (int)",                             asFUNCTION(Component::beginDragAutoRepeat), asCALL_THISCALL); jassert (r >= 0);
	r = engine->RegisterObjectMethod("Component", "void setRepaintsOnMouseActivity(bool)",                      asMETHOD(Component,setRepaintsOnMouseActivity), asCALL_THISCALL); jassert( r >= 0 );
//    void addMouseListener (MouseListener* const newListener, const bool wantsEventsForAllNestedChildComponents);
//    void removeMouseListener (MouseListener* const listenerToRemove);
//    void addKeyListener (KeyListener* const newListener);
//    void removeKeyListener (KeyListener* const listenerToRemove);
// ...
	r = engine->RegisterObjectMethod("Component", "bool isMouseOver()",                                         asMETHOD(Component,isMouseOver), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "bool isMouseButtonDown()",                                   asMETHOD(Component,isMouseButtonDown), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "bool isMouseOverOrDragging()",                               asMETHOD(Component,isMouseOverOrDragging), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "bool isMouseButtonDownAnywhere()",                           asFUNCTION(Component::isMouseButtonDownAnywhere), asCALL_THISCALL); jassert( r >= 0 );
//	r = engine->RegisterObjectMethod("Component", "int getMouseXRelative()",                                    asMETHOD(Component,getMouseXRelative), asCALL_THISCALL); jassert( r >= 0 );
//	r = engine->RegisterObjectMethod("Component", "int getMouseYRelative()",                                    asMETHOD(Component,getMouseYRelative), asCALL_THISCALL); jassert( r >= 0 );
//    static Component* getComponentUnderMouse() throw();
	r = engine->RegisterObjectMethod("Component", "void enableUnboundedMouseMovement(bool,bool)",               asMETHOD(Component,enableUnboundedMouseMovement), asCALL_THISCALL); jassert( r >= 0 );
// ...
	r = engine->RegisterObjectMethod("Component", "int runModalLoop()",                                         asMETHOD(Component,runModalLoop), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "void enterModalState()",                                     asMETHOD(Component,enterModalState), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "void exitModalState(int)",                                   asMETHOD(Component,exitModalState), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "bool isCurrentlyModal()",                                    asMETHOD(Component,isCurrentlyModal), asCALL_THISCALL); jassert( r >= 0 );
//    static Component* getCurrentlyModalComponent();
	r = engine->RegisterObjectMethod("Component", "bool isCurrentlyBlockedByAnotherModalComponent()",           asMETHOD(Component,isCurrentlyBlockedByAnotherModalComponent), asCALL_THISCALL); jassert( r >= 0 );

	r = engine->RegisterObjectMethod("Component", "String@ getComponentProperty(const String& in,bool,const String& in)", asMETHOD(asComponent,getComponentProperty), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "int getComponentPropertyInt(const String& in,bool,int)",               asMETHOD(Component,getComponentPropertyInt), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "double getComponentPropertyDouble(const String& in,bool,double)",      asMETHOD(Component,getComponentPropertyDouble), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "bool getComponentPropertyDouble(const String& in,bool,bool)",          asMETHOD(Component,getComponentPropertyDouble), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "void setComponentProperty(const String& in,const String& in)",         asMETHODPR(Component,setComponentProperty,(const String&,const String&),void), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "void setComponentProperty(const String& in,int)",                      asMETHODPR(Component,setComponentProperty,(const String&,int),void), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "void setComponentProperty(const String& in,double)",                   asMETHODPR(Component,setComponentProperty,(const String&,double),void), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "void setComponentProperty(const String& in,bool)",                     asMETHODPR(Component,setComponentProperty,(const String&,bool),void), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "bool removeComponentProperty(const String& in)",                       asMETHOD(Component,removeComponentProperty), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "uint getComponentUID()",                                               asMETHOD(Component,getComponentUID), asCALL_THISCALL); jassert( r >= 0 );

// experimental ----------
	r = engine->RegisterObjectMethod("Component", "void startThread()",                                         asMETHODPR(asComponent,startThread,(),void), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "void startThread(int)",                                      asMETHODPR(asComponent,startThread,(const int),void), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "void stopThread(int)",                                       asMETHOD(Thread,stopThread), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "bool isThreadRunning()",                                     asMETHOD(Thread,isThreadRunning), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "void signalThreadShouldExit()",                              asMETHOD(Thread,signalThreadShouldExit), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "bool threadShouldExit()",                                    asMETHOD(Thread,threadShouldExit), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "bool waitForThreadToExit(int)",                              asMETHOD(Thread,waitForThreadToExit), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "void setPriority(int)",                                      asMETHOD(Thread,setPriority), asCALL_THISCALL); jassert( r >= 0 );
//    static void setCurrentThreadPriority (const int priority);
	r = engine->RegisterObjectMethod("Component", "void setAffinityMask(uint)",                                 asMETHOD(Thread,setAffinityMask), asCALL_THISCALL); jassert( r >= 0 );
//    static void setCurrentThreadAffinityMask (const uint32 affinityMask);
//    static void sleep (int milliseconds);
//    static void yield();
	r = engine->RegisterObjectMethod("Component", "bool wait(int)",                                             asMETHOD(Thread,wait), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "void notify()",                                              asMETHOD(Thread,notify), asCALL_THISCALL); jassert( r >= 0 );
//    static int getCurrentThreadId();
	r = engine->RegisterObjectMethod("Component", "int getThreadId()",                                          asMETHOD(Thread,getThreadId), asCALL_THISCALL); jassert( r >= 0 );
// experimental ----------

	r = engine->RegisterObjectMethod("Component", "void startTimer(int)",                                       asFUNCTION(Component_startTimer), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "void stopTimer()",                                           asFUNCTION(Component_stopTimer), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "bool isTimerRunning()",                                      asFUNCTION(Component_isTimerRunning), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "int getTimerInterval()",                                     asFUNCTION(Component_getTimerInterval), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
}

//==============================================================================
void asModifierKeys::registerObjectType(asIScriptEngine *engine)
{
	int r;
	r = engine->RegisterObjectType("ModifierKeys", sizeof(ModifierKeys), asOBJ_CLASS); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("ModifierKeys", "bool isCommandDown()",           asMETHOD(ModifierKeys,isCommandDown), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("ModifierKeys", "bool isPopupMenu()",             asMETHOD(ModifierKeys,isPopupMenu), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("ModifierKeys", "bool isLeftButtonDown()",        asMETHOD(ModifierKeys,isLeftButtonDown), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("ModifierKeys", "bool isRightButtonDown()",       asMETHOD(ModifierKeys,isRightButtonDown), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("ModifierKeys", "bool isMiddleButtonDown()",      asMETHOD(ModifierKeys,isMiddleButtonDown), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("ModifierKeys", "bool isAnyMouseButtonDown()",    asMETHOD(ModifierKeys,isAnyMouseButtonDown), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("ModifierKeys", "bool isAnyModifierKeyDown()",    asMETHOD(ModifierKeys,isAnyModifierKeyDown), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("ModifierKeys", "bool isShiftDown()",             asMETHOD(ModifierKeys,isShiftDown), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("ModifierKeys", "bool isCtrlDown()",              asMETHOD(ModifierKeys,isCtrlDown), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("ModifierKeys", "bool isAltDown()",               asMETHOD(ModifierKeys,isAltDown), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("ModifierKeys", "int getRawFlags()",              asMETHOD(ModifierKeys,getRawFlags), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("ModifierKeys", "bool testFlags(int)",            asMETHOD(ModifierKeys,testFlags), asCALL_THISCALL); jassert( r >= 0 );
//    static const ModifierKeys getCurrentModifiers() throw();
//    static const ModifierKeys getCurrentModifiersRealtime();
}

//==============================================================================
// asModifierKeys* asKeyPress::getModifiers() {}
// asString* asKeyPress::getTextDescription() {}

void asKeyPress::registerObjectType(asIScriptEngine *engine)
{
	int r;
	r = engine->RegisterObjectType("KeyPress", sizeof(KeyPress), asOBJ_CLASS); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("KeyPress", "bool isValid()",                asMETHOD(KeyPress,isValid), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("KeyPress", "int getKeyCode()",              asMETHOD(KeyPress,getKeyCode), asCALL_THISCALL); jassert( r >= 0 );
//	r = engine->RegisterObjectMethod("KeyPress", "ModifierKeys@ getModifiers()",  asMETHOD(asKeyPress,getModifiers), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("KeyPress", "bool isKeyCode(int)",           asMETHOD(KeyPress,isKeyCode), asCALL_THISCALL); jassert( r >= 0 );
//	r = engine->RegisterObjectMethod("KeyPress", "String@ getTextDescription()",  asMETHOD(asKeyPress,getTextDescription), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("KeyPress", "bool isCurrentlyDown()",        asMETHOD(KeyPress,isCurrentlyDown), asCALL_THISCALL); jassert( r >= 0 );
//    static const KeyPress createFromDescription (const String& textVersion);
}

//==============================================================================
void asMouseEvent::registerObjectType(asIScriptEngine *engine)
{
	int r;
	r = engine->RegisterObjectType("MouseEvent", sizeof(MouseEvent), asOBJ_CLASS); jassert( r >= 0 );
	r = engine->RegisterObjectProperty("MouseEvent", "int x", offsetof(MouseEvent,x)); jassert( r >= 0 );
	r = engine->RegisterObjectProperty("MouseEvent", "int y", offsetof(MouseEvent,y)); jassert( r >= 0 );
	r = engine->RegisterObjectProperty("MouseEvent", "ModifierKeys mods", offsetof(MouseEvent,mods)); jassert( r >= 0 );
//	r = engine->RegisterObjectProperty("MouseEvent", "Component* component", offsetof(MouseEvent,component)); jassert( r >= 0 );
//	r = engine->RegisterObjectProperty("MouseEvent", "Time eventTime", offsetof(MouseEvent,eventTime)); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("MouseEvent", "int getMouseDownX()",              asMETHOD(MouseEvent,getMouseDownX), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("MouseEvent", "int getMouseDownY()",              asMETHOD(MouseEvent,getMouseDownY), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("MouseEvent", "int getDistanceFromDragStart()",   asMETHOD(MouseEvent,getDistanceFromDragStart), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("MouseEvent", "int getDistanceFromDragStartX()",  asMETHOD(MouseEvent,getDistanceFromDragStartX), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("MouseEvent", "int getDistanceFromDragStartY()",  asMETHOD(MouseEvent,getDistanceFromDragStartY), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("MouseEvent", "bool mouseWasClicked()",           asMETHOD(MouseEvent,mouseWasClicked), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("MouseEvent", "int getNumberOfClicks()",          asMETHOD(MouseEvent,getNumberOfClicks), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("MouseEvent", "int getLengthOfMousePress()",      asMETHOD(MouseEvent,getLengthOfMousePress), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("MouseEvent", "int getScreenX()",                 asMETHOD(MouseEvent,getScreenX), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("MouseEvent", "int getScreenY()",                 asMETHOD(MouseEvent,getScreenY), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("MouseEvent", "int getMouseDownScreenX()",        asMETHOD(MouseEvent,getMouseDownScreenX), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("MouseEvent", "int getMouseDownScreenY()",        asMETHOD(MouseEvent,getMouseDownScreenY), asCALL_THISCALL); jassert( r >= 0 );
//    const MouseEvent getEventRelativeTo (Component* const otherComponent) const throw();
//    static void setDoubleClickTimeout (const int timeOutMilliseconds) throw();
//    static int getDoubleClickTimeout() throw();
}

//==============================================================================
asComponentBoundsConstrainer::asComponentBoundsConstrainer() :
	refCount(1) {
}
asComponentBoundsConstrainer::~asComponentBoundsConstrainer() {
	jassert (refCount==0);
}

void asComponentBoundsConstrainer::addRef() {
	refCount++;
}
void asComponentBoundsConstrainer::release() {
	if( --refCount == 0 )
		delete this;
}

void asComponentBoundsConstrainer::checkBounds (int* x, int* y, int* w, int* h,
                                                const Rectangle& previousBounds,
                                                const Rectangle& limits,
                                                const bool isStretchingTop,
                                                const bool isStretchingLeft,
                                                const bool isStretchingBottom,
                                                const bool isStretchingRight) {
	bounds.checkBounds (*x,*y,*w,*h,previousBounds,limits,isStretchingTop,isStretchingLeft,isStretchingBottom,isStretchingRight);
}

void asComponentBoundsConstrainer::setBoundsForComponent (asComponent* component,
                                                          int x, int y, int w, int h,
                                                          const bool isStretchingTop,
                                                          const bool isStretchingLeft,
                                                          const bool isStretchingBottom,
                                                          const bool isStretchingRight) {
	bounds.setBoundsForComponent (component,x,y,w,h,isStretchingTop,isStretchingLeft,isStretchingBottom,isStretchingRight);
}

void ConstructComponentBoundsConstrainer(asComponentBoundsConstrainer *thisPointer) {
    new(thisPointer) asComponentBoundsConstrainer();
}

void asComponentBoundsConstrainer::registerObjectType(asIScriptEngine *engine)
{
	int r;
	r = engine->RegisterObjectType("ComponentBoundsConstrainer", sizeof(asComponentBoundsConstrainer), asOBJ_CLASS_CD); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("ComponentBoundsConstrainer", asBEHAVE_CONSTRUCT,  "void f()", asFUNCTION(ConstructComponentBoundsConstrainer), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("ComponentBoundsConstrainer", asBEHAVE_ADDREF,     "void f()", asMETHOD(asComponentBoundsConstrainer,addRef), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("ComponentBoundsConstrainer", asBEHAVE_RELEASE,    "void f()", asMETHOD(asComponentBoundsConstrainer,release), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("ComponentBoundsConstrainer", "void setMinimumWidth(int)",        asMETHOD(ComponentBoundsConstrainer,setMinimumWidth), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("ComponentBoundsConstrainer", "int getMinimumWidth()",            asMETHOD(ComponentBoundsConstrainer,getMinimumWidth), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("ComponentBoundsConstrainer", "void setMaximumWidth(int)",        asMETHOD(ComponentBoundsConstrainer,setMaximumWidth), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("ComponentBoundsConstrainer", "int getMaximumWidth()",            asMETHOD(ComponentBoundsConstrainer,getMaximumWidth), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("ComponentBoundsConstrainer", "void setMinimumHeight(int)",       asMETHOD(ComponentBoundsConstrainer,setMinimumHeight), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("ComponentBoundsConstrainer", "int getMinimumHeight()",           asMETHOD(ComponentBoundsConstrainer,getMinimumHeight), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("ComponentBoundsConstrainer", "void setMaximumHeight(int)",       asMETHOD(ComponentBoundsConstrainer,setMaximumHeight), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("ComponentBoundsConstrainer", "int getMaximumHeight()",           asMETHOD(ComponentBoundsConstrainer,getMaximumHeight), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("ComponentBoundsConstrainer", "void setMinimumSize(int,int)",     asMETHOD(ComponentBoundsConstrainer,setMinimumSize), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("ComponentBoundsConstrainer", "void setMaximumSize(int,int)",     asMETHOD(ComponentBoundsConstrainer,setMaximumSize), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("ComponentBoundsConstrainer", "void setSizeLimits(int,int,int,int)",             asMETHOD(ComponentBoundsConstrainer,setSizeLimits), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("ComponentBoundsConstrainer", "void setMinimumOnscreenAmounts(int,int,int,int)", asMETHOD(ComponentBoundsConstrainer,setMinimumOnscreenAmounts), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("ComponentBoundsConstrainer", "void setFixedAspectRatio(double)",                asMETHOD(ComponentBoundsConstrainer,setFixedAspectRatio), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("ComponentBoundsConstrainer", "double getFixedAspectRatio()",                    asMETHOD(ComponentBoundsConstrainer,getFixedAspectRatio), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("ComponentBoundsConstrainer", "void checkBounds(int& out,int& out,int& out,int&out,const Rectangle& in,const Rectangle& in,bool,bool,bool,bool)", asMETHOD(asComponentBoundsConstrainer,checkBounds), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("ComponentBoundsConstrainer", "void setBoundsForComponent(Component@+,int,int,int,int,bool,bool,bool,bool)",                                      asMETHOD(asComponentBoundsConstrainer,setBoundsForComponent), asCALL_THISCALL); jassert( r >= 0 );
}


//==============================================================================
asComponentDragger::asComponentDragger() :
	refCount(1) {
}
asComponentDragger::~asComponentDragger() {
	jassert (refCount==0);
}

void asComponentDragger::addRef() {
	refCount++;
}
void asComponentDragger::release() {
	if( --refCount == 0 )
		delete this;
}

void asComponentDragger::startDraggingComponent (asComponent* componentToDrag) {
	dragger.startDraggingComponent (componentToDrag,0);
}
void asComponentDragger::startDraggingComponent (asComponent* componentToDrag, asComponentBoundsConstrainer* constrainer) {
	dragger.startDraggingComponent (componentToDrag,&(constrainer->bounds));
}
void asComponentDragger::dragComponent (asComponent* componentToDrag, const MouseEvent& e) {
	dragger.dragComponent (componentToDrag,e);
}

void ConstructComponentDragger(asComponentDragger *thisPointer) {
    new(thisPointer) asComponentDragger();
}

void asComponentDragger::registerObjectType(asIScriptEngine *engine)
{
	int r;
	r = engine->RegisterObjectType("ComponentDragger", sizeof(asComponentDragger), asOBJ_CLASS_CD); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("ComponentDragger", asBEHAVE_CONSTRUCT,  "void f()",                        asFUNCTION(ConstructComponentDragger), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("ComponentDragger", asBEHAVE_ADDREF,     "void f()",                        asMETHOD(asComponentDragger,addRef), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("ComponentDragger", asBEHAVE_RELEASE,    "void f()",                        asMETHOD(asComponentDragger,release), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("ComponentDragger", "void startDraggingComponent(Component@+)",                              asMETHODPR(asComponentDragger,startDraggingComponent,(asComponent*),void), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("ComponentDragger", "void startDraggingComponent(Component@+,ComponentBoundsConstrainer@+)", asMETHODPR(asComponentDragger,startDraggingComponent,(asComponent*,asComponentBoundsConstrainer*),void), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("ComponentDragger", "void dragComponent(Component@+,const MouseEvent& in)",                  asMETHOD(asComponentDragger,dragComponent), asCALL_THISCALL); jassert( r >= 0 );
}


//==============================================================================
//asRectangleList* asDesktop::getAllMonitorDisplayAreas() {}
asRectangle* asDesktop::getMainMonitorArea() {
	return new asRectangle( Desktop::getInstance().getMainMonitorArea() );
}
asRectangle* asDesktop::getMonitorAreaContaining(int x, int y) {
	return new asRectangle( Desktop::getInstance().getMonitorAreaContaining(x,y) );
}
void asDesktop::getMousePosition(int* x, int* y) {
	Desktop::getMousePosition (*x,*y);
}
void asDesktop::setMousePosition(int x, int y) {
	Desktop::setMousePosition (x,y);
}
void asDesktop::getLastMouseDownPosition(int* x, int* y) {
	Desktop::getLastMouseDownPosition (*x,*y);
}
int asDesktop::getMouseButtonClickCounter() {
	return Desktop::getMouseButtonClickCounter ();
}
// void asDesktop::addGlobalMouseListener (MouseListener* listener);
// void asDesktop::removeGlobalMouseListener (MouseListener* listener);
int asDesktop::getNumComponents() {
	return  Desktop::getInstance().getNumComponents ();
}
asComponent* asDesktop::getComponent(int index) {
	return (asComponent*) Desktop::getInstance().getComponent (index);
}
asComponent* asDesktop::findComponentAt(int screenX, int screenY) {
	return (asComponent*) Desktop::getInstance().findComponentAt (screenX,screenY);
}
void asDesktop::refreshMonitorSizes() {
	Desktop::getInstance().refreshMonitorSizes ();
}
bool asDesktop::canUseSemiTransparentWindows() {
	return Desktop::canUseSemiTransparentWindows ();
}

void asDesktop::registerObjectType(asIScriptEngine *engine)
{
    int r;
	r = engine->RegisterObjectType("Desktop_", 0, asOBJ_PRIMITIVE); jassert(r>=0);
	r = engine->RegisterObjectBehaviour("Desktop_", asBEHAVE_CONSTRUCT, "void f()",asFUNCTION(dummy_Constructor), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectBehaviour("Desktop_", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(dummy_Destructor), asCALL_CDECL_OBJLAST); jassert(r>=0);
	r = engine->RegisterObjectMethod("Desktop_", "Rectangle@ getMainMonitorArea()",                  asMETHOD(asDesktop,getMainMonitorArea), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("Desktop_", "Rectangle@ getMonitorAreaContaining(int,int)",     asMETHOD(asDesktop,getMonitorAreaContaining), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("Desktop_", "void getMousePosition(int& out,int& out)",         asMETHOD(asDesktop,getMousePosition), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("Desktop_", "void setMousePosition(int,int)",                   asMETHOD(asDesktop,setMousePosition), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("Desktop_", "void getLastMouseDownPosition(int& out,int& out)", asMETHOD(asDesktop,getLastMouseDownPosition), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("Desktop_", "int getMouseButtonClickCounter()",                 asMETHOD(asDesktop,getMouseButtonClickCounter), asCALL_THISCALL); jassert(r>=0);
// void asDesktop::addGlobalMouseListener (MouseListener* listener);
// void asDesktop::removeGlobalMouseListener (MouseListener* listener);
	r = engine->RegisterObjectMethod("Desktop_", "int getNumComponents()",                           asMETHOD(asDesktop,getNumComponents), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("Desktop_", "Component@ getComponent(int)",                     asMETHOD(asDesktop,getComponent), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("Desktop_", "Component@ findComponentAt(int,int)",              asMETHOD(asDesktop,findComponentAt), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("Desktop_", "void refreshMonitorSizes()",                       asMETHOD(asDesktop,refreshMonitorSizes), asCALL_THISCALL); jassert(r>=0);
	r = engine->RegisterObjectMethod("Desktop_", "bool canUseSemiTransparentWindows()",              asMETHOD(asDesktop,canUseSemiTransparentWindows), asCALL_THISCALL); jassert(r>=0);

	engine->RegisterGlobalProperty ("Desktop_ Desktop", (void*)&dummy32bit);
}




//==============================================================================
asTextButton::asTextButton(const String& name, const String& tooltip) :
	TextButton (name, tooltip)
{
}

asTextButton::~asTextButton()
{
}

void asTextButton::addRef() {}
void asTextButton::release() {}

void DestructTextButton(asComponent *thisPointer) {}
void ConstructTextButton(asTextButton *thisPointer) {
	new(thisPointer) asTextButton (T("button"),String::empty);
}
void ConstructTextButtonByStrings(const String& name, const String& tooltip, asTextButton *thisPointer) {
    new(thisPointer) asTextButton (name,tooltip);
}
static void FreeTextButton(void *p) {}
static void *AllocTextButton(int) {
	return new char[sizeof(asTextButton)];
}

void TextButton_addButtonListener (asComponent* listener, asTextButton* thisPointer)
{
	thisPointer->addButtonListener (listener);
}

void asTextButton::registerObjectType (asIScriptEngine *engine)
{
	int r;
	r = engine->RegisterObjectType("TextButton", sizeof(asTextButton), asOBJ_CLASS_CD); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("TextButton", asBEHAVE_CONSTRUCT,  "void f()",								asFUNCTION(ConstructTextButton), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("TextButton", asBEHAVE_CONSTRUCT,  "void f(const String&, const String&)",  asFUNCTION(ConstructTextButtonByStrings), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("TextButton", asBEHAVE_DESTRUCT,   "void f()",                              asFUNCTION(DestructTextButton), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("TextButton", asBEHAVE_ALLOC,      "TextButton &f(uint)",                   asFUNCTION(AllocTextButton), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("TextButton", asBEHAVE_FREE,       "void f(TextButton &in)",                asFUNCTION(FreeTextButton), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("TextButton", asBEHAVE_ADDREF,     "void f()",                              asMETHOD(asTextButton,addRef), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("TextButton", asBEHAVE_RELEASE,    "void f()",                              asMETHOD(asTextButton,release), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("TextButton", "void setBounds (int,int,int,int)",                              asMETHODPR(Component,setBounds,(const int,const int,const int,const int),void), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("TextButton", "void setButtonText (const String&)",                            asMETHOD(TextButton,setButtonText), asCALL_THISCALL); jassert( r >= 0 );

	r = engine->RegisterObjectMethod("TextButton", "void addButtonListener (Component&)",                           asFUNCTIONPR(TextButton_addButtonListener,(asComponent*,asTextButton*),void), asCALL_CDECL_OBJLAST); jassert( r >= 0 );

	r = engine->RegisterObjectMethod("Component", "void addAndMakeVisible (TextButton&)",       asFUNCTIONPR (Component_addAndMakeVisible, (Component* const, asComponent*), void), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Component", "void addAndMakeVisible (TextButton&,int)",   asFUNCTIONPR (Component_addAndMakeVisible, (Component* const, int, asComponent*), void), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
}


//==============================================================================
void asImagePreview::addRef() {}
void asImagePreview::release() {}

asGraphics* asImagePreview::getGraphics ()
{
	if (bufferedImage)
		return new asGraphics (bufferedImage);
	else
		return 0;
}

void ConstructImagePreview(asImagePreview *thisPointer) {
    new(thisPointer) asImagePreview();
	asComponentManager::getInstance()->registerComponent (thisPointer);
}
void DestructImagePreview(asImagePreview *thisPointer) {
//	thisPointer->~asComponent();
}
static void *AllocImagePreview(int) {
	return new char[sizeof(asImagePreview)];
}
static void FreeImagePreview(void *p) {}

void asImagePreview::registerObjectType(asIScriptEngine *engine)
{
	int r;
	r = engine->RegisterObjectType("ImagePreview", sizeof(asImagePreview), asOBJ_CLASS_CD);
	r = engine->RegisterObjectBehaviour("ImagePreview", asBEHAVE_CONSTRUCT,  "void f()",                  asFUNCTION(ConstructImagePreview), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("ImagePreview", asBEHAVE_DESTRUCT,   "void f()",                  asFUNCTION(DestructImagePreview), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("ImagePreview", asBEHAVE_ADDREF,     "void f()",                  asMETHOD(asImagePreview,addRef), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("ImagePreview", asBEHAVE_RELEASE,    "void f()",                  asMETHOD(asImagePreview,release), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("ImagePreview", asBEHAVE_ALLOC,      "ImagePreview &f(uint)",     asFUNCTION(AllocImagePreview), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("ImagePreview", asBEHAVE_FREE,       "void f(ImagePreview &in)",  asFUNCTION(FreeImagePreview), asCALL_CDECL); jassert( r >= 0 );

	r = engine->RegisterObjectMethod("ImagePreview", "void setImage(Image&)",         asMETHOD(asImagePreview, setImage), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("ImagePreview", "Graphics@ getGraphics()",     asMETHOD(asImagePreview, getGraphics), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("ImagePreview", "void repaint()",                asMETHOD(Component, repaint), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("ImagePreview", "void setVisible(bool)",         asMETHOD(Component, setVisible), asCALL_THISCALL); jassert( r >= 0 );
}



//==============================================================================
asComponentManager::asComponentManager() {}
asComponentManager::~asComponentManager() {}

void asComponentManager::registerComponent (Component* component) {
	components.addIfNotAlreadyThere (component);
}

void asComponentManager::releaseComponents () {
	components.clear();
}

juce_ImplementSingleton (asComponentManager)

