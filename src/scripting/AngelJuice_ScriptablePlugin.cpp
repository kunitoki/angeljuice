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

#include "../libraries/angelscript/angelscript.h"

#include "bindings/AngelJuice_AngelScriptCore.h"
#include "bindings/AngelJuice_AngelScriptString.h"
#include "bindings/AngelJuice_AngelScriptFile.h"
#include "bindings/AngelJuice_AngelScriptSocket.h"
#include "bindings/AngelJuice_AngelScriptOpenGL.h"
#include "bindings/AngelJuice_AngelScriptImaging.h"
#include "bindings/AngelJuice_AngelScriptComponent.h"

#include "AngelJuice_ScriptableEngine.h"
#include "AngelJuice_ScriptablePlugin.h"
#include "AngelJuice_ScriptablePreprocessor.h"


//==============================================================================
ScriptablePlugin::ScriptablePlugin (const File& fileToLoad) :
	DynamicLibraryLoader (fileToLoad.getFullPathName()),
	pluginFile (fileToLoad)
{}

bool ScriptablePlugin::identifyPlugin (const char* pluginName)
{
	return (String(pluginName) == pluginFile.getFullPathName());
}

//==============================================================================
int ScriptablePlugin::registerCallback (asIScriptEngine* engine, asDebuggerOutput func)
{
	PluginRegister function =
		(PluginRegister) findProcAddress ("aj_PluginRegister");

	if (function)
		return function (engine, func);
	else
		return asNOT_SUPPORTED;
}

int ScriptablePlugin::compileCallback (asIScriptEngine* engine)
{
	PluginCompile function =
		(PluginCompile) findProcAddress ("aj_PluginCompile");

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
		(PluginVariableInfo) findProcAddress ("aj_PluginVariableInfo");

	if (function)
		return function (engine, typeID, varPointer);
	else
		return 0;
}


//==============================================================================
static asDebuggerOutput outputFunction = 0;
static void clearFunctionWrapper (const String& message)
{
	if (outputFunction)
		outputFunction ((const char*) message, 0);
}
static void printFunctionWrapper (const String& message)
{
	if (outputFunction)
		outputFunction ((const char*) message, 1);
}
static void printlnFunctionWrapper (const String& message)
{
	String messageToSend = message + T("\n");
	if (outputFunction)
		outputFunction ((const char*) messageToSend, 1);
}

//==============================================================================
ScriptableExtension::ScriptableExtension (const String& extToLoad) :
	extensionName (extToLoad)
{}

bool ScriptableExtension::identifyPlugin (const char* pluginName)
{
	return (String(pluginName) == extensionName);
}

//==============================================================================
int ScriptableExtension::registerCallback (asIScriptEngine* engine, asDebuggerOutput func)
{
	int r;

	// register core string (has to be done first)
	asString::registerObjectType (engine);

	// generic core input stream
	asInputStream::registerObjectType (engine);

	// register classes that works on strings
	asFile::registerObjectType (engine);
    asRegularExpression::registerObjectType (engine);
	asURL::registerObjectType (engine);

	// register xml classes
	asXmlElement::registerObjectType (engine);
	asXmlDocument::registerObjectType (engine);

	// register basic system utils
	asMath::registerObjectType (engine);
	asRandom::registerObjectType (engine);
	asSystemStats::registerObjectType (engine);
	asCore::registerObjectType (engine);

	// register imaging support (keep the order!)
	asColour::registerObjectType (engine);
	asImage::registerObjectType (engine);
    asImageConvolutionKernel::registerObjectType (engine);
    asFont::registerObjectType (engine);
	asAffineTransform::registerObjectType (engine);
	asPath::registerObjectType (engine);
    asPathStrokeType::registerObjectType (engine);
    asPoint::registerObjectType (engine);
    asLine::registerObjectType (engine); // does not compile on macosx
	asRectangle::registerObjectType (engine);
	asGraphics::registerObjectType (engine);
	asOpenGL::registerObjectType (engine);

	asImagePreview::registerObjectType (engine);

	// components
	asModifierKeys::registerObjectType (engine);
	asKeyPress::registerObjectType (engine);
	asMouseEvent::registerObjectType (engine);
	asComponent::registerObjectType (engine);
	asComponentBoundsConstrainer::registerObjectType (engine);
	asComponentDragger::registerObjectType (engine);
	asDesktop::registerObjectType (engine);

	asTextButton::registerObjectType (engine);

	// register default debugger output
	outputFunction = func;
	r = engine->RegisterGlobalFunction ("void clear()",                asFUNCTION(clearFunctionWrapper),   asCALL_CDECL); jassert (r >= 0);
	r = engine->RegisterGlobalFunction ("void print(const String&)",   asFUNCTION(printFunctionWrapper),   asCALL_CDECL); jassert (r >= 0);
	r = engine->RegisterGlobalFunction ("void println(const String&)", asFUNCTION(printlnFunctionWrapper), asCALL_CDECL); jassert (r >= 0);

	return asSUCCESS;
}

int ScriptableExtension::compileCallback (asIScriptEngine* engine)
{
	// hack for the component bindings
	asComponentManager::getInstance()->releaseComponents();

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

	if (typeDecl == T("String"))
	{
		asString* object = *(asString**) varPointer;
		if (object)
		{
			ALLOCATE (stringToFill, object->buffer.length(), (const char*) object->buffer);
		}
	}
	if (typeDecl == T("File"))
	{
		asFile* object = *(asFile**) varPointer;
		if (object)
		{
			ALLOCATE (stringToFill, object->file.getFullPathName().length(), (const char*) object->file.getFullPathName());
		}
	}
	else if (typeDecl == T("URL"))
	{
		asURL* object = *((asURL**) varPointer);
		if (object)
		{
			ALLOCATE (stringToFill, object->url.toString (true).length(), (const char*) object->url.toString (true));
		}
	}
	else if (typeDecl == T("Colour"))
	{
		asColour* object = *((asColour**) varPointer);
		if (object)
		{
			varValue << "[" <<
				object->col.getRed() << "," <<
				object->col.getGreen() << "," <<
				object->col.getBlue() << "," <<
				object->col.getAlpha() << "]";

			ALLOCATE (stringToFill, varValue.length(), (const char*) varValue);
		}
	}
	else if (typeDecl == T("Point"))
	{
		asPoint* object = *((asPoint**) varPointer);
		if (object)
		{
			varValue << "[" <<
				object->point.getX() << "," <<
				object->point.getY() << "]";

			ALLOCATE (stringToFill, varValue.length(), (const char*) varValue);
		}
	}
	else if (typeDecl == T("Line"))
	{
		asLine* object = *((asLine**) varPointer);
		if (object)
		{
			varValue << "[" <<
				object->line.getStartX() << "," <<
				object->line.getStartY() << " - " <<
				object->line.getEndX() << "," <<
				object->line.getEndY() << "]";

			ALLOCATE (stringToFill, varValue.length(), (const char*) varValue);
		}
	}
	else if (typeDecl == T("Rectangle"))
	{
		asRectangle* object = *((asRectangle**) varPointer);
		if (object)
		{
			varValue << "[" <<
				object->rect.getX() << "," <<
				object->rect.getY() << "," <<
				object->rect.getWidth() << "," <<
				object->rect.getHeight() << "]";

			ALLOCATE (stringToFill, varValue.length(), (const char*) varValue);
		}
	}
	else if (typeDecl == T("Font"))
	{
		asFont* object = *((asFont**) varPointer);
		if (object)
		{
			ALLOCATE (stringToFill, object->font.getTypefaceName().length(), (const char*) object->font.getTypefaceName());
		}
	}

	return stringToFill;
}
