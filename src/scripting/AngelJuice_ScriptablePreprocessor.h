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

   This library was heavily tweaked and modified by kRAkEn/gORe
   which not claims to be the owner of this piece of crap.

  ==============================================================================
*/

#ifndef __ANGELJUICE_PREPROCESSOR_HEADER__
#define __ANGELJUICE_PREPROCESSOR_HEADER__

#include <string>
#include <vector>
#include <list>
#include <map>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>

#include "juce.h"


namespace Preprocessor
{
	//  ==============================================================================
	class OutStream
	{
    public:
		virtual void Write(const char* msg, unsigned int size) = 0;
        virtual void ReportErrors(const char* msgType,
                                  const char* msgText,
                                  const char* fileName,
                                  unsigned int line) = 0;
		
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

	
	class NullOutStream: public OutStream
	{
	protected:
		virtual void Write(const char*, unsigned int) {}
        virtual void ReportErrors(const char* msgType,
                                  const char* msgText,
                                  const char* fileName,
                                  unsigned int line) {}
	};


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

	int lex(char* begin, char* end, std::list<Lexem>& results);
	
	
	//  ==============================================================================
	typedef std::list<Lexem> LexemList;
	typedef LexemList::iterator LLITR;
	
	void printLexemList(LexemList& out, OutStream& destination);	
	

	//  ==============================================================================
	typedef std::map<std::string,int> ArgSet;
	
	class DefineEntry
	{
	public:
		LexemList lexems;
		ArgSet arguments;
	}; //end class DefineEntry
	
	typedef std::map<std::string,DefineEntry> DefineTable;

	
	//  ==============================================================================
	class FileSource
	{
	public:
		virtual ~FileSource() {}

		virtual bool LoadFile(const std::string& filename, std::vector<char>&) = 0;
	};

	int preprocess(
		const String& filename, 
		const String& filedata, 
		FileSource& file_source,
		OutStream& destination, 
		OutStream& err,
		LineNumberTranslator* = 0
		);

	void define (const std::string&);
	void registerPragma (const std::string&, PragmaModel*);

	
} //  Preprocessor


using namespace Preprocessor;

#endif // __ANGELJUICE_PREPROCESSOR_HEADER__
