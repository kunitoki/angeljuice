/*
  ==============================================================================

   This file is part of AngelJuice

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

  ==============================================================================
*/

#include "Bindings/AngelScriptCore.h"
#include "Bindings/AngelScriptString.h"
#include "Bindings/AngelScriptFile.h"
#include "Bindings/AngelScriptCrypt.h"
//#include "Bindings/AngelScriptSocket.h"
//#include "Bindings/AngelScriptOpenGL.h"
//#include "Bindings/AngelScriptImaging.h"
//#include "Bindings/AngelScriptComponent.h"

#include "ScriptableEngine.h"
#include "ScriptablePlugin.h"
#include "ScriptablePreprocessor.h"


//==============================================================================

//------------------------------------------------------------------------------

ScriptableExtension::ScriptableExtension(const String& extToLoad) :
	extensionName(extToLoad)
{
    // core
    creators.add(new Bindings::ScriptableCore);
    creators.add(new Bindings::ScriptableMath);
    creators.add(new Bindings::ScriptableByteOrder);
    creators.add(new Bindings::ScriptableBigInteger);
    creators.add(new Bindings::ScriptableRandom);
    creators.add(new Bindings::ScriptableSystemStats);
    creators.add(new Bindings::ScriptableTime);
    creators.add(new Bindings::ScriptableRelativeTime);
    creators.add(new Bindings::ScriptableMemoryBlock);
    //creators.add(new Bindings::ScriptableArrayTemplate);

    // string
    creators.add(new Bindings::ScriptableString);
    creators.add(new Bindings::ScriptableStringArray);

    // file
    creators.add(new Bindings::ScriptableFile);
    creators.add(new Bindings::ScriptableInputStream);
    
    // crypt
    // TODO - creators.add(new Bindings::ScriptableBlowFish);
    
    //creators.add(new asRegularExpression);
    //creators.add(new asURL);
    //creators.add(new asXmlElement);
    //creators.add(new asXmlDocument);

    //creators.add(new asColour);
    //creators.add(new asImage);
    //creators.add(new asImageConvolutionKernel);
    //creators.add(new asFont);
    //creators.add(new asAffineTransform);
    //creators.add(new asPath);
    //creators.add(new asPathStrokeType);
    //creators.add(new asPoint);
    //creators.add(new asLine);
    //creators.add(new asRectangle);
    //creators.add(new asGraphics);
    //creators.add(new asOpenGL);
    //creators.add(new asImagePreview);

    //creators.add(new asModifierKeys);
    //creators.add(new asKeyPress);
    //creators.add(new asMouseEvent);
    //creators.add(new asComponent);
    //creators.add(new asComponentBoundsConstrainer);
    //creators.add(new asComponentDragger);
    //creators.add(new asDesktop);
    //creators.add(new asTextButton);
}

bool ScriptableExtension::identifyPlugin(const char* pluginName)
{
	return (String(pluginName) == extensionName);
}

int ScriptableExtension::registerCallback(asIScriptEngine* engine)
{
    for (int i = 0; i < creators.size(); ++i)
    {
        creators.getUnchecked(i)->registerTypes(engine);
    }

    for (int i = 0; i < creators.size(); ++i)
    {
        creators.getUnchecked(i)->registerFunctions(engine);
    }
    
	return asSUCCESS;
}

int ScriptableExtension::compileCallback (asIScriptEngine* engine)
{
    for (int i = 0; i < creators.size(); ++i)
    {
        creators.getUnchecked(i)->compileCallback(engine);
    }

    /*
	// hack for the component bindings
	asComponentManager::getInstance()->releaseComponents();
	*/

	return asSUCCESS;
}

#define ALLOCATE(var, size, value) \
	var = (char*) malloc (size + 1); \
	strncpy (var, value, size); \
	var[size] = 0;

char* ScriptableExtension::variableCallback (asIScriptEngine* engine,
											 const int typeID,
											 void* varPointer)
{
	String typeDecl = engine->GetTypeDeclaration (typeID);
	String varValue;
	char* stringToFill = 0;

	// @TODO - string allocations can be improved

	if (typeDecl == "String")
	{
		String* object = *(String**) varPointer;
		if (object)
		{
			ALLOCATE (stringToFill, object->length(), (const char*) object->toUTF8());
		}
	}
	if (typeDecl == "File")
	{
		File* object = *(File**) varPointer;
		if (object)
		{
			ALLOCATE (stringToFill, object->getFullPathName().length(), (const char*) object->getFullPathName().toUTF8());
		}
	}
	else if (typeDecl == "URL")
	{
		URL* object = *((URL**) varPointer);
		if (object)
		{
			ALLOCATE (stringToFill, object->toString(true).length(), (const char*) object->toString(true).toUTF8());
		}
	}
	else if (typeDecl == "Colour")
	{
		Colour* object = *((Colour**) varPointer);
		if (object)
		{
			varValue << "[" <<
				object->getRed() << "," <<
				object->getGreen() << "," <<
				object->getBlue() << "," <<
				object->getAlpha() << "]";

			ALLOCATE (stringToFill, varValue.length(), (const char*) varValue.toUTF8());
		}
	}
	/*
	else if (typeDecl == "Point")
	{
		Point* object = *((Point**) varPointer);
		if (object)
		{
			varValue << "[" <<
				object->getX() << "," <<
				object->getY() << "]";

			ALLOCATE (stringToFill, varValue.length(), (const char*) varValue.toUTF8());
		}
	}
	else if (typeDecl == "Line")
	{
		Line* object = *((Line**) varPointer);
		if (object)
		{
			varValue << "[" <<
				object->getStartX() << "," <<
				object->getStartY() << " - " <<
				object->getEndX() << "," <<
				object->getEndY() << "]";

			ALLOCATE (stringToFill, varValue.length(), (const char*) varValue.toUTF8());
		}
	}
	else if (typeDecl == "Rectangle")
	{
		Rectangle* object = *((Rectangle**) varPointer);
		if (object)
		{
			varValue << "[" <<
				object->getX() << "," <<
				object->getY() << "," <<
				object->getWidth() << "," <<
				object->getHeight() << "]";

			ALLOCATE (stringToFill, varValue.length(), (const char*) varValue.toUTF8());
		}
	}
	*/
	else if (typeDecl == "Font")
	{
		Font* object = *((Font**) varPointer);
		if (object)
		{
			ALLOCATE (stringToFill, object->getTypefaceName().length(), (const char*) object->getTypefaceName().toUTF8());
		}
	}

	return stringToFill;
}


//==============================================================================

//------------------------------------------------------------------------------

ScriptablePlugin::ScriptablePlugin (const File& fileToLoad) :
	pluginFile (fileToLoad),
	pluginLibrary (fileToLoad.getFullPathName())
{
}

bool ScriptablePlugin::identifyPlugin (const char* pluginName)
{
	return (String(pluginName) == pluginFile.getFullPathName());
}

int ScriptablePlugin::registerCallback (asIScriptEngine* engine)
{
	PluginRegister function =
		(PluginRegister) pluginLibrary.getFunction ("aj_PluginRegister");

	if (function)
		return function (engine);
	else
		return asNOT_SUPPORTED;
}

int ScriptablePlugin::compileCallback (asIScriptEngine* engine)
{
	PluginCompile function =
		(PluginCompile) pluginLibrary.getFunction ("aj_PluginCompile");

	if (function)
		return function (engine);
	else
		return asNOT_SUPPORTED;
}

char* ScriptablePlugin::variableCallback (asIScriptEngine* engine,
                                          const int typeID,
					                      void* varPointer)
{
	PluginVariableInfo function =
		(PluginVariableInfo) pluginLibrary.getFunction ("aj_PluginVariableInfo");

	if (function)
		return function (engine, typeID, varPointer);
	else
		return nullptr;
}

