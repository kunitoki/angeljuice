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

#ifndef __ANGELJUICE_ANGELSCRIPTCOMPONENT_HEADER__
#define __ANGELJUICE_ANGELSCRIPTCOMPONENT_HEADER__

#include "juce.h"

class ScriptableEngine;
class asString;
class asRectangle;
class asImage;
class asGraphics;


//==============================================================================
/** Manages modifier keypresses in angel scripts

    @see AngelScriptEngine, ModifierKeys
*/
class asModifierKeys
{
public:
	static void registerObjectType(asIScriptEngine *engine);
};


//==============================================================================
/** Manages key press events in angel scripts

    @see AngelScriptEngine, KeyPress
*/
class asKeyPress
{
public:

//	asModifierKeys* getModifiers();
//	static const KeyPress createFromDescription (const String& textVersion);
//	asString* getTextDescription ();

	static void registerObjectType(asIScriptEngine *engine);
};


//==============================================================================
/** Manages mouse event messages in angel scripts

    @see AngelScriptEngine, MouseEvent
*/
class asMouseEvent
{
public:
	static void registerObjectType(asIScriptEngine *engine);
};


//==============================================================================
/** Manages native component peer in angel scripts

    @see AngelScriptEngine, ComponentPeer
*/
class asComponentPeer
{
public:

	asComponentPeer();
	~asComponentPeer();

	int windowAppearsOnTaskbar;
	int windowIsTemporary;
	int windowIgnoresMouseClicks;
	int windowHasTitleBar;
	int windowIsResizable;
	int windowHasMinimiseButton;
	int windowHasMaximiseButton;
	int windowHasCloseButton;
	int windowHasDropShadow;
};


//==============================================================================
/** Manages components in angel scripts

    @see AngelScriptEngine, Component
*/
class asComponent : public Component,
					public ButtonListener,
					public Thread,
					public Timer
{
public:

	//==============================================================================
	asComponent();
	~asComponent();

	void addRef();
	void release();

	//==============================================================================
	asString* getName();
    void addToDesktop (int windowStyleFlags);
	asRectangle* getBounds();
	asRectangle* getParentMonitorArea();
	asImage* createComponentSnapshot (const asRectangle& areaToGrab);

	//==============================================================================
	void paint (Graphics& g);
	void paintOverChildren (Graphics& g);
	void mouseMove (const MouseEvent& e);
	void mouseEnter (const MouseEvent& e);
	void mouseExit (const MouseEvent& e);
	void mouseDrag (const MouseEvent& e);
	void mouseDown (const MouseEvent& e);
	void mouseUp (const MouseEvent& e);
	void mouseDoubleClick (const MouseEvent& e);
	void mouseWheelMove (const MouseEvent& e, float ix, float iy);
	bool keyPressed (const KeyPress& key);
//	void keyStateChanged();
//	void modifierKeysChanged (const ModifierKeys& modifiers);
	void resized();
	void moved();
//	void childBoundsChanged (Component* child);
//	void parentSizeChanged();
//	void inputAttemptWhenModal();
//	void broughtToFront();
//	bool filesDropped (const StringArray& filenames,int mouseX,int mouseY);
//	void visibilityChanged();
//	void userTriedToCloseWindow();
//	void minimisationStateChanged (bool isNowMinimised);
//	void parentHierarchyChanged();
//	void childrenChanged();
//	bool hitTest (int x, int y);
//	void enablementChanged();

	void run ();
	void timerCallback ();
	void buttonClicked (Button* button);

	//==============================================================================
	void setClassAndObject (const String& className,const String& objectName);
	void doExecuteContext ();

	//==============================================================================
	static void registerObjectType(asIScriptEngine *engine);

	//==============================================================================
	juce_UseDebuggingNewOperator

protected:
//	~asComponent();
//	int refCount;
	String className;
	String objectName;
	void* methodOwner;
	Array<int> methodId;
	asIScriptContext* eventContext;
};


//==============================================================================
/** Manages created components in angel scripts

    @see AngelScriptEngine, asComponent, Component
*/
class asComponentBoundsConstrainer
{
public:

	asComponentBoundsConstrainer();

	void addRef();
	void release();

	void checkBounds (int* x, int* y, int* w, int* h,
                      const Rectangle& previousBounds,
                      const Rectangle& limits,
                      const bool isStretchingTop,
                      const bool isStretchingLeft,
                      const bool isStretchingBottom,
                      const bool isStretchingRight);

    void setBoundsForComponent (asComponent* component,
                                int x, int y, int w, int h,
                                const bool isStretchingTop,
                                const bool isStretchingLeft,
                                const bool isStretchingBottom,
                                const bool isStretchingRight);

	static void registerObjectType(asIScriptEngine *engine);

	ComponentBoundsConstrainer bounds;

protected:
	~asComponentBoundsConstrainer();
	int refCount;
};

//==============================================================================
/** Manages created components in angel scripts

    @see AngelScriptEngine, asComponent, Component
*/
class asComponentDragger
{
public:

	asComponentDragger();

	void addRef();
	void release();

    void startDraggingComponent (asComponent* componentToDrag);
    void startDraggingComponent (asComponent* componentToDrag, asComponentBoundsConstrainer* constrainer);
    void dragComponent (asComponent* componentToDrag, const MouseEvent& e);

	static void registerObjectType(asIScriptEngine *engine);

	ComponentDragger dragger;

protected:
	~asComponentDragger();
	int refCount;
};


//==============================================================================
/** Manages created components in angel scripts

    @see AngelScriptEngine, asComponent, Component
*/
class asComponentManager : public DeletedAtShutdown
{
public:

	asComponentManager();
	~asComponentManager();

	void registerComponent (Component* component);
	void releaseComponents ();

	juce_DeclareSingleton (asComponentManager, true)

protected:

	OwnedArray<Component> components;
};


//==============================================================================
/** Manages desktop information functions in angel scripts

    @see AngelScriptEngine, Desktop
*/
class asDesktop : public DeletedAtShutdown
{
public:

	//asRectangleList* getAllMonitorDisplayAreas() {}
	asRectangle* getMainMonitorArea();
	asRectangle* getMonitorAreaContaining(int x, int y);
	void getMousePosition(int* x, int* y);
	void setMousePosition(int x, int y);
	void getLastMouseDownPosition(int* x, int* y);
	int getMouseButtonClickCounter();
	// void addGlobalMouseListener (MouseListener* listener);
	// void removeGlobalMouseListener (MouseListener* listener);
	int getNumComponents();
	asComponent* getComponent(int index);
	asComponent* findComponentAt(int screenX, int screenY);
	void refreshMonitorSizes();
	bool canUseSemiTransparentWindows();


	static void registerObjectType(asIScriptEngine *engine);

};


//==============================================================================
/** Manages text buttons in angel scripts

    @see AngelScriptEngine, Component
*/
class asTextButton : public TextButton
{
public:

	//==============================================================================
	asTextButton(const String& name, const String& tooltip);
	~asTextButton();

	void addRef();
	void release();


	static void registerObjectType(asIScriptEngine *engine);

};


//==============================================================================
/** Manages image previews in angel scripts

    @see AngelScriptEngine, Component
*/

class asImagePreview :	public Component,
						public Timer
{
public:

	//==============================================================================
	asImagePreview() :
		graphics (0),
		bufferedImage (0)
	{
		setOpaque (true);
		setAlwaysOnTop(false);

		addToDesktop (ComponentPeer::windowHasDropShadow |
				ComponentPeer::windowAppearsOnTaskbar);

		centreWithSize(400,300);

		startTimer (200);
	}

	~asImagePreview()
	{
		deleteAndZero (bufferedImage);
		deleteAllChildren();
	}

	void addRef();
	void release();

	//==============================================================================
	void resized ()
	{
		Image* imgToSet = new Image (Image::ARGB,getWidth(),getHeight(),true);

		if (bufferedImage)
		{
			Graphics g (*imgToSet);
			g.drawImage (bufferedImage,
					0, 0, getWidth(), getHeight(),
					0, 0, bufferedImage->getWidth(), bufferedImage->getHeight());

			delete bufferedImage;
		}

		bufferedImage = imgToSet;
	}

	void paint(Graphics& g)
	{
		g.fillAll(Colours::black);

		if (bufferedImage)
		{
			g.drawImage (bufferedImage,
					0, 0, getWidth(), getHeight(),
					0, 0, bufferedImage->getWidth(), bufferedImage->getHeight());
		}
	}

	void mouseDoubleClick (const MouseEvent& e)
	{
		setVisible (false);
	}

	void mouseDown (const MouseEvent& e)
	{
		dx = e.x;
		dy = e.y;
		Component::mouseDown(e);
	}

	void mouseDrag (const MouseEvent& e)
	{
		int x, y;

		Desktop::getInstance().getMousePosition (x,y);

		x -= dx;
		y -= dy;

		// keep the whole thing on-screen
		const Rectangle wholeScreen (Desktop::getInstance()
                                    .getAllMonitorDisplayAreas().getBounds());

		x = jlimit (wholeScreen.getX(), wholeScreen.getRight() - getWidth(), x);
		y = jlimit (wholeScreen.getY(), wholeScreen.getBottom() - getHeight(), y);

		setTopLeftPosition (x, y);

		Component::mouseDrag(e);
	}

	void timerCallback ()
	{
		if (bufferedImage)
			repaint ();
	}

	//==============================================================================
	void setImage (asImage& imgToShow)
	{
		stopTimer ();

		Image* newImage = imgToShow.image->createCopy();

		deleteAndZero (bufferedImage);

		if (newImage->getWidth() != getWidth() && newImage->getHeight() != getHeight())
			setSize(newImage->getWidth(),newImage->getHeight());

		bufferedImage = newImage;

		if (!isVisible())
			setVisible(true);

		startTimer (200);
	}

	asGraphics* getGraphics ();


	//==============================================================================
	static void registerObjectType(asIScriptEngine *engine);

protected:

	int dx, dy;
	Graphics* graphics;
	Image* bufferedImage;
};


#endif	// __ANGELJUICE_ANGELSCRIPTCOMPONENT_HEADER__
