/*
  ==============================================================================
   
   Preprocessor 0.5
   Copyright (c) 2005 Anthony Casteel

   This software is provided 'as-is', without any express or implied 
   warranty. In no event will the authors be held liable for any
   damages arising from the use of this software.

   Permission is granted to anyone to use this software for any 
   purpose, including commercial applications, and to alter it and
   redistribute it freely, subject to the following restrictions:

   1. The origin of this software must not be misrepresented; you 
      must not claim that you wrote the original software. If you use
      this software in a product, an acknowledgment in the product
      documentation would be appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and 
      must not be misrepresented as being the original software.

   3. This notice may not be removed or altered from any source 
      distribution.

   The original version of this library can be located at:
   http://www.angelcode.com/angelscript/
   under addons & utilities or at
   http://www.omnisu.com

   Anthony Casteel
   jm@omnisu.com
  
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

#ifndef __ANGELJUICE_PREPROCESSOR_H_INCLUDED__
#define __ANGELJUICE_PREPROCESSOR_H_INCLUDED__

#include <string>
#include <vector>
#include <list>
#include <map>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>

#include "../../JuceLibraryCode/JuceHeader.h"


class Preprocessor
{
public:

	//  ==============================================================================
	class OutStream
	{
    public:
		virtual void Write(const char* msg, unsigned int size) = 0;
        virtual void ReportErrors(const char* msgType,
                                  const char* msgText,
                                  const char* fileName,
                                  unsigned int line) = 0;
		
        OutStream() {}
		virtual ~OutStream() {}

		template<typename T>
		OutStream& operator<<(const T& in)
		{
			std::stringstream strstr;
			strstr << in;
			std::string str;
			strstr >> str;
			Write(str.c_str(),str.length());
			return *this;
		}

		OutStream& operator<<(const std::string& in)
		{
			Write(in.c_str(),in.length());
			return *this;
		}		

		OutStream& operator<<(const char* in)
		{
			return operator<<(std::string(in));
		}

		virtual bool valid() { return true; }
	};

	class VectorOutStream: public OutStream
	{
	private:
		std::vector<char> m_data;
	protected:
		virtual void Write(const char* d, unsigned int size)
		{
			m_data.insert(m_data.end(),d,d+size);
		}
        virtual void ReportErrors(const char* msgType,
                                  const char* msgText,
                                  const char* fileName,
                                  unsigned int line)
        {}

	public:
		const char* data() { return &m_data[0]; }
		size_t size() { return m_data.size(); }
	};

	/*
	class NullOutStream: public OutStream
	{
	protected:
		virtual void Write(const char*, unsigned int) {}
        virtual void ReportErrors(const char* msgType,
                                  const char* msgText,
                                  const char* fileName,
                                  unsigned int line) {}
	};
	*/


	//  ==============================================================================
	class LineNumberTranslator
	{
	public:
		class Table;
	private:
		Table* pimple;
	public:
		LineNumberTranslator();
		~LineNumberTranslator();
		std::string ResolveOriginalFile(unsigned int linenumber);
		unsigned int ResolveOriginalLine(unsigned int linenumber);
		void SetTable(Table*);
	};

	
	//  ==============================================================================
	class PragmaInstance
	{
	public:
		std::string name;
		std::string text;
		std::string current_file;
		unsigned int current_file_line;
		std::string root_file;
		unsigned int global_line;
	};

	class PragmaModel
	{
	public:
		virtual ~PragmaModel() {}
	
		virtual void handlePragma(const PragmaInstance&) = 0;
	};


	//  ==============================================================================
	class FileSource
	{
	public:
		virtual ~FileSource() {}

		virtual bool LoadFile(const std::string& filename, std::vector<char>&) = 0;
	};
	

public:
    //  ==============================================================================
	enum LexemType
	{
		IDENTIFIER,		//Names which can be expanded.
		COMMA,			//,
		SEMICOLON,
		OPEN,			//{[(
		CLOSE,			//}])
		PREPROCESSOR,	//Begins with #
		NEWLINE,
		WHITESPACE,
		IGNORE,
		COMMENT,
		STRING,
		NUMBER
	}; //End enum LexemType

	class Lexem
	{
	public:
		std::string value;
		LexemType type;
	}; //End class Lexem

	
	//  ==============================================================================
	typedef std::list<Lexem> LexemList;
	typedef LexemList::iterator LLITR;
	

	//  ==============================================================================
	typedef std::map<std::string, int> ArgSet;
	
	class DefineEntry
	{
	public:
		LexemList lexems;
		ArgSet arguments;
	}; //end class DefineEntry
	
	typedef std::map<std::string, DefineEntry> DefineTable;

	//  ==============================================================================
    typedef std::map<std::string, PragmaModel*> PragmaMap;
	typedef PragmaMap::iterator PragmaIterator;

public:

    //  ==============================================================================
    Preprocessor();
    ~Preprocessor();

    //  ==============================================================================
	int preprocess(
		const String& filename, 
		const String& filedata, 
		FileSource& file_source,
		OutStream& destination, 
		OutStream& err,
		LineNumberTranslator* lnt = nullptr);

	void define(const std::string&);
	void registerPragma(const std::string&, PragmaModel*);

	
protected:
    void PrintErrorMessage(const std::string& errmsg);
    void PrintWarningMessage(const std::string& errmsg);
    
    void callPragma(const std::string& name, const PragmaInstance& parms);

    LLITR findLexem(LLITR ITR, LLITR END, LexemType type);
    LLITR parseStatement(LLITR ITR, LLITR END, LexemList& dest);
    LLITR parseDefineArguments(LLITR ITR, LLITR END, LexemList& lexems, std::vector<LexemList>& args);
    LLITR expandDefine(LLITR ITR, LLITR END, LexemList& lexems, DefineTable& define_table);
    void parseDefine(DefineTable& define_table, LexemList& def_lexems);
    LLITR parseIfDef(LLITR ITR, LLITR END);
    void parseIf(LexemList& directive, std::string& name_out);
    void parsePragma(LexemList& args);

    void recursivePreprocess(	
	    std::string filename,
	    std::string filedata,
	    FileSource& file_source,
	    LexemList& lexems,
	    DefineTable& define_table,
	    const bool fromString);
    
	DefineTable application_specified;

	OutStream* error_stream;

	PragmaMap registered_pragmas;

	LineNumberTranslator::Table* LNT;
	std::string root_file;
	std::string current_file;
	unsigned int current_line;
	unsigned int lines_this_file;

	unsigned int number_of_errors;
};


#endif // __ANGELJUICE_PREPROCESSOR_H_INCLUDED__
