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

#ifdef WIN32
  #include <windows.h>
#elif defined LINUX
  #include <dlfcn.h>
#else
#endif

#include "AngelJuice_DynamicLibraryLoader.h"

//==============================================================================
DynamicLibraryLoader::DynamicLibraryLoader (const String& name)
{
	libHandle = 0;

#ifdef JUCE_WIN32
	libHandle = LoadLibrary (name);
#else
	int len = strlen ((const char*) name);
	len += 6; // Add room for ./, .so, and null.
	char* libname = new char[len];
	libname[0] = 0;
	strcat (libname, "./");
	strcat (libname, (const char*) name);
	strcat (libname, ".so");
	libHandle = dlopen (libname, RTLD_LAZY);
	delete[] libname;
#endif
}

DynamicLibraryLoader::~DynamicLibraryLoader()
{
	if (libHandle)
	{
#ifdef JUCE_WIN32
		FreeLibrary ((HINSTANCE) libHandle);
#else
		dlclose (libHandle);
#endif
	}
}

void* DynamicLibraryLoader::findProcAddress (const String& functionName)
{
	void* func = 0;

	if (libHandle)
	{
#ifdef JUCE_WIN32
		func = GetProcAddress ((HINSTANCE) libHandle, (const char*) functionName);
#else
		func = dlsym (libHandle, (const char*) functionName);
#endif
	}

	return func;
}

