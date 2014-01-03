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

#include "AngelJuice_ScriptablePreprocessor.h"


using namespace Preprocessor;


static std::string IntToString(int i)
{
	std::stringstream sstr;
	sstr << i;
	std::string r;
	sstr >> r;
	return r;
}

std::string numbers = "0123456789";
std::string identifierStart = "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
std::string identifierBody = "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
std::string hexnumbers = "0123456789abcdefABCDEF";

std::string trivials = ",;\n\r\t [{(]})";

LexemType trivial_types[] =
{
	COMMA, 
	SEMICOLON, 
	NEWLINE, 
	WHITESPACE, 
	WHITESPACE, 
	WHITESPACE, 
	OPEN, 
	OPEN, 
	OPEN,
	CLOSE, 
	CLOSE, 
	CLOSE
};

static bool searchString(std::string str, char in)
{
	return (str.find_first_of(in) < str.length());
}

static bool isNumber(char in) { return searchString(numbers,in); }
static bool isIdentifierStart(char in)	{ return searchString(identifierStart,in); }
static bool isIdentifierBody(char in) { return searchString(identifierBody,in); }
static bool isTrivial(char in) { return searchString(trivials,in); }
static bool isHex(char in) { return searchString(hexnumbers,in); }

static char* parseIdentifier(char* start, char* end, Lexem& out)
{
	out.type = IDENTIFIER;
	out.value += *start;
	while(true)
	{
		++start;
		if (start == end) return start;
		if (isIdentifierBody(*start))
		{
			out.value += *start;
		} 
		else
		{
			return start;
		}
	}
};

static char* parseStringLiteral(char* start, char* end, Lexem& out)
{
	out.type = STRING;
	out.value += *start;
	while(true)
	{
		++start;
		if (start == end) return start;
		out.value += *start;
		//End of string literal?
		if (*start == '\"') return ++start;
		//Escape sequence? - Really only need to handle \"
		if (*start == '\\')	
		{
			++start;
			if (start == end) return start;
			out.value += *start;
		}
	}
}

static char* parseCharacterLiteral(char* start, char* end, Lexem& out)
{
	++start;
	if (start == end) return start;
	out.type = NUMBER;
	if (*start == '\\')
	{
		++start;
		if (start == end) return start;
		if (*start == 'n') out.value = IntToString('\n');
		if (*start == 't') out.value = IntToString('\t');
		if (*start == 'r') out.value = IntToString('\r');
		++start; 
		if (start == end) return start;
		++start; return start;
	} 
	else 
	{
		out.value = IntToString(*start);
		++start;
		if (start == end) return start;
		++start; return start;
	}
}

static char* parseFloatingPoint(char* start, char* end, Lexem& out)
{
	out.value += *start;
	while (true)
	{
		++start;
		if (start == end) return start;
		if (!isNumber(*start))
		{
			if (*start == 'f')
			{
				out.value += *start;
				++start;
				return start;
			}
			return start;
		} else {
			out.value += *start;
		}
	}
}

static char* parseHexConstant(char* start, char* end, Lexem& out)
{
	out.value += *start;
	while (true)
	{ 
		++start;
		if (start == end) return start;
		if (isHex(*start))
		{
			out.value += *start;
		} else {
			return start;
		}
	}
}

static char* parseNumber(char* start, char* end, Lexem& out)
{
	out.type = NUMBER;
	out.value += *start;
	while(true)
	{
		++start;
		if (start == end) return start;
		if (isNumber(*start)) {
			out.value += *start;
		} else if (*start == '.') {
			return parseFloatingPoint(start,end,out);
		} else if (*start == 'x') {
			return parseHexConstant(start,end,out);
		} else {
			return start;
		}
	}
}

static char* parseBlockComment(char* start, char* end, Lexem& out)
{
	out.type = COMMENT;
	out.value += "/*";

	int newlines = 0;
	while(true)
	{
		++start;
		if (start == end) break;
		if (*start == '\n')
		{
			newlines++;
		}
		out.value += *start;
		if (*start == '*')
		{
			++start;
			if (start == end) break;
			if (*start == '/') 
			{
				out.value += *start;
				++start;
				break;
			} else 
			{
				--start;
			}
		}
	}
	while (newlines > 0) 
	{
		--start;
		*start = '\n';
		--newlines;
	}
	return start;
}

static char* parseLineComment(char* start, char* end, Lexem& out)
{
	out.type = COMMENT;
	out.value += "//";
	
	while(true)
	{
		++start;
		if (start == end) return start;
		out.value += *start;
		if (*start == '\n') return start;
	}
}

static char* parseLexem(char* start, char* end, Lexem& out) 
{	
	if (start == end) return start;
	char current_char = *start;
	
	if (isTrivial(current_char)) 
	{
		out.value += current_char;
		out.type = trivial_types[trivials.find_first_of(current_char)];
		return ++start;
	}
	
	if (isIdentifierStart(current_char)) return parseIdentifier(start,end,out);
	
	if (current_char == '#')
	{
		start = parseIdentifier(start,end,out);
		out.type = PREPROCESSOR;
		return start;
	}
	
	if (isNumber(current_char)) return parseNumber(start,end,out);
	if (current_char == '\"') return parseStringLiteral(start,end,out);
	if (current_char == '\'') return parseCharacterLiteral(start,end,out);	
	if (current_char == '/')
	{
		//Need to see if it's a comment.
		++start;
		if (start == end) return start;
		if (*start == '*') return parseBlockComment(start,end,out);
		if (*start == '/') return parseLineComment(start,end,out);
		//Not a comment - let default code catch it as MISC
		--start;
	}
				
	out.value = current_char;
	out.type = IGNORE;
	return ++start;
}

int Preprocessor::lex(char* begin, char* end, std::list<Lexem>& results)
{
	jassert(begin != 0 && end != 0);
	jassert(begin <= end);
	while (true)
	{
		Lexem current_lexem;
		begin = parseLexem(begin,end,current_lexem);
		if (current_lexem.type != WHITESPACE &&
			current_lexem.type != COMMENT ) results.push_back(current_lexem);
		if (begin == end) return 0;
	}
};

void Preprocessor::printLexemList( LexemList& out, OutStream& destination)
{
	bool need_a_space = false;
	for (LLITR ITR = out.begin(); ITR != out.end(); ++ITR)
	{
		if (ITR->type == IDENTIFIER || ITR->type == NUMBER) 
		{
			if (need_a_space) destination << " ";
			need_a_space = true;
			destination << ITR->value;
		}
		else 
		{
			need_a_space = false;
			destination << ITR->value;
		}
	}
}

namespace
{
	DefineTable application_specified;

	OutStream* error_stream;

	typedef std::map<std::string,PragmaModel*> PragmaMap;
	typedef PragmaMap::iterator PragmaIterator;

	PragmaMap registered_pragmas;

	LineNumberTranslator::Table* LNT;
	std::string root_file;
	std::string current_file;
	unsigned int current_line;
	unsigned int lines_this_file;

	unsigned int number_of_errors;

	void PrintErrorMessage(const std::string& errmsg)
	{
        error_stream->ReportErrors ("Error",
                                    (const char*)errmsg.c_str(),
                                    (const char*) current_file.c_str(),
                                    (int) (lines_this_file + 1));
		number_of_errors++;
	}

	void PrintWarningMessage(const std::string& errmsg)
	{
        error_stream->ReportErrors ("Warning",
                                    (const char*)errmsg.c_str(),
                                    (const char*) current_file.c_str(),
                                    (int) (lines_this_file + 1));
	}

	std::string removeQuotes(const std::string& in)
	{
		return in.substr(1,in.size()-2);
	}

	class CleanUpPragmas
	{
	public:
		~CleanUpPragmas()
		{
			registered_pragmas.clear();
		}
	};

	CleanUpPragmas nasty_little_hack_this_is;
}

void Preprocessor::registerPragma(const std::string& name, Preprocessor::PragmaModel* pc)
{
	if (pc == 0) return;
	PragmaIterator I = registered_pragmas.find(name);
	if (I != registered_pragmas.end()) 
	{
		// I->second = 0;
		registered_pragmas.erase(I);
	}
	registered_pragmas[name] = pc;
}

static void callPragma(const std::string& name, const Preprocessor::PragmaInstance& parms)
{
	PragmaIterator I = registered_pragmas.find(name);
	if (I == registered_pragmas.end())
	{
		PrintErrorMessage("Unknown pragma command.");
		return;
	}
	if (I->second) I->second->handlePragma(parms);
}

class Preprocessor::LineNumberTranslator::Table
{
public:
	struct Entry
	{
		std::string file;
		unsigned int start_line;
		unsigned int offset;
	};

	std::vector<Entry> lines;

	//Assuming blocks were entered in the proper order.
	Entry& search(unsigned int linenumber)
	{
		for (size_t i = 1; i < lines.size(); ++i)
		{
			if (linenumber < lines[i].start_line)
			{
				//Found the first block after our line.
				return lines[i-1];
			}
		}
		return lines[lines.size()-1]; //Line must be in last block.
	}

	void AddLineRange(const std::string& file, unsigned int start_line, unsigned int offset)
	{
		Entry e;
		e.file = file;
		e.start_line = start_line;
		e.offset = offset;
		lines.push_back(e);
	}
};

std::string Preprocessor::LineNumberTranslator::ResolveOriginalFile(unsigned int linenumber)
{
	if (!pimple) return "ERROR";
	return pimple->search(linenumber).file;
}

unsigned int Preprocessor::LineNumberTranslator::ResolveOriginalLine(unsigned int linenumber)
{
	if (!pimple) return 0;
	return linenumber - pimple->search(linenumber).offset;
}

Preprocessor::LineNumberTranslator::LineNumberTranslator() : pimple(0) {}

Preprocessor::LineNumberTranslator::~LineNumberTranslator()
{
	delete pimple;
}

void Preprocessor::LineNumberTranslator::SetTable(Preprocessor::LineNumberTranslator::Table *t)
{
	if (pimple)
		delete pimple;
	pimple = t;
}

static LLITR findLexem(LLITR ITR, LLITR END, LexemType type)
{
	while(ITR != END && ITR->type != type)
	{
		++ITR;
	}
	return ITR;
}

static LLITR parseStatement(LLITR ITR, LLITR END, LexemList& dest)
{
	int depth = 0;
	while (ITR != END)
	{
		if (ITR->value == "," && depth == 0) return ITR;
		if (ITR->type == CLOSE && depth == 0) return ITR;
		if (ITR->type == SEMICOLON && depth == 0) return ITR;
		dest.push_back(*ITR);
		if (ITR->type == OPEN) depth++;
		if (ITR->type == CLOSE) {
			if (depth == 0) PrintErrorMessage("Mismatched braces while parsing statement.");
			depth--;
		}
		++ITR;
	}
	return ITR;
}

static LLITR parseDefineArguments(LLITR ITR, LLITR END, LexemList& lexems,
	std::vector<LexemList>& args)
{
	if (ITR == END || ITR->value != "(") 
	{
		PrintErrorMessage("Expected argument list.");
		return ITR;
	}
	LLITR begin_erase = ITR;
	++ITR;

	while (ITR != END)
	{
		LexemList argument;
		ITR = parseStatement(ITR,END,argument);
		args.push_back(argument);

		if (ITR == END) {
			PrintErrorMessage("0x0FA1 Unexpected end of file.");
			return ITR;
		}
		if (ITR->value == ",")
		{
			++ITR;
			if (ITR == END) {
				PrintErrorMessage("0x0FA2 Unexpected end of file.");
				return ITR;
			}
			continue;
		}
		if (ITR->value == ")")
		{
			++ITR;
			break;
		}
	}

	return lexems.erase(begin_erase,ITR);
}

static LLITR expandDefine(LLITR ITR, LLITR END, LexemList& lexems, DefineTable& define_table)
{
	DefineTable::iterator define_entry = define_table.find(ITR->value);
	if (define_entry == define_table.end()) return ++ITR;
	ITR = lexems.erase(ITR);
	if (define_entry->second.arguments.size() == 0) 
	{
		lexems.insert(ITR,
			define_entry->second.lexems.begin(),
			define_entry->second.lexems.end());
		return ITR;
	}

	//define has arguments.
	std::vector<LexemList> arguments;
	ITR = parseDefineArguments(ITR,END,lexems,arguments);

	if (define_entry->second.arguments.size() != arguments.size()) 
	{
		PrintErrorMessage("Didn't supply right number of arguments to define.");
		return ITR;
	}

	LexemList temp_list(define_entry->second.lexems.begin(),define_entry->second.lexems.end());

	LLITR TLI = temp_list.begin();
	while (TLI != temp_list.end())
	{
		ArgSet::iterator arg = define_entry->second.arguments.find(TLI->value);
		if (arg == define_entry->second.arguments.end()) 
		{
			++TLI;
			continue;
		}

		TLI = temp_list.erase(TLI);
		temp_list.insert(TLI,arguments[arg->second].begin(),arguments[arg->second].end());
	}

	lexems.insert(ITR,temp_list.begin(),temp_list.end());

	return ITR;
}

static void parseDefine(DefineTable& define_table, LexemList& def_lexems)
{
	def_lexems.pop_front();	//remove #define directive
	if (def_lexems.empty()) {
		PrintErrorMessage("Define directive without arguments.");
		return;
	}
	Lexem name = *def_lexems.begin();
	if (name.type != IDENTIFIER) 
	{
		PrintErrorMessage("Define's name was not an identifier.");
		return;
	}
	def_lexems.pop_front();

	DefineEntry def;

	if (!def_lexems.empty())
	{
		if (def_lexems.begin()->type == PREPROCESSOR && def_lexems.begin()->value == "#")
		{
			//Macro has arguments
			def_lexems.pop_front();
			if (def_lexems.empty()) 
			{
				PrintErrorMessage("Expected arguments.");
				return;
			}
			if (def_lexems.begin()->value != "(")
			{
				PrintErrorMessage("Expected arguments.");
				return;
			}
			def_lexems.pop_front();

			int num_args = 0;
			while(!def_lexems.empty() && def_lexems.begin()->value != ")")
			{
				if (def_lexems.begin()->type != IDENTIFIER) 
				{
					PrintErrorMessage("Expected identifier.");
					return;
				}
				def.arguments[def_lexems.begin()->value] = num_args;
				def_lexems.pop_front();
				if (!def_lexems.empty() && def_lexems.begin()->value == ",")
				{
					def_lexems.pop_front();
				}
				num_args++;
			}

			if (!def_lexems.empty()) 
			{
				if (def_lexems.begin()->value != ")")
				{
					PrintErrorMessage("Expected closing parantheses.");
					return;
				}
				def_lexems.pop_front();
			}
			else 
			{
				PrintErrorMessage("0x0FA3 Unexpected end of line.");
				return;
			}
		}

		LLITR DLB = def_lexems.begin();
		while (DLB != def_lexems.end())
		{
			DLB = expandDefine(DLB,def_lexems.end(),def_lexems,define_table);
		}
	}
	
	def.lexems = def_lexems;
	define_table[name.value] = def;
}

static LLITR parseIfDef(LLITR ITR, LLITR END)
{
	int depth = 0;
	int newlines = 0;
	bool found_end = false;
	while (ITR != END)
	{
		if (ITR->type == NEWLINE) newlines++;
		else if (ITR->type == PREPROCESSOR)
		{
			if (ITR->value == "#endif" && depth == 0) 
			{
				++ITR;
				found_end = true;
				break;
			}
			if (ITR->value == "#ifdef" || ITR->value == "#ifndef") depth++;
			if (ITR->value == "#endif" && depth > 0) depth--;
		}
		++ITR;
	}
	if (ITR == END && !found_end) 
	{
		PrintErrorMessage("0x0FA4 Unexpected end of file.");
		return ITR;
	}
	while (newlines > 0)
	{
		--ITR;
		ITR->type = NEWLINE;
		ITR->value = "\n";
		--newlines;
	}
	return ITR;
}

static void parseIf(LexemList& directive, std::string& name_out)
{
	directive.pop_front();
	if (directive.empty()) 
	{
		PrintErrorMessage("Expected argument.");
		return;
	}
	name_out = directive.begin()->value;
	directive.pop_front();
	if (!directive.empty()) PrintErrorMessage("Too many arguments.");
}

static std::string addPaths(const std::string& first, const std::string& second)
{
	std::string result;
	size_t slash_pos = first.find_last_of('/');
	if (slash_pos == 0 || slash_pos >= first.size()) return second;
	result = first.substr(0,slash_pos+1);
	result += second;
	return result;
}

static void parsePragma(LexemList& args)
{
	args.pop_front();
	if (args.empty())
	{
		PrintErrorMessage("Pragmas need arguments.");
		return;
	}
	std::string p_name = args.begin()->value;
	args.pop_front();
	std::string p_args;
	if (!args.empty())
	{
		if (args.begin()->type != STRING) 
			PrintErrorMessage("Pragma parameter should be a string literal.");
		p_args = removeQuotes(args.begin()->value);
		args.pop_front();
	}
	if (!args.empty()) PrintErrorMessage("Too many parameters to pragma.");
	Preprocessor::PragmaInstance PI;
	PI.name = p_name;
	PI.text = p_args;
	PI.current_file = current_file;
	PI.current_file_line = lines_this_file;
	PI.root_file = root_file;
	PI.global_line = current_line;
	callPragma(p_name,PI);
}

static void setLineMacro(DefineTable& define_table, unsigned int line)
{
	DefineEntry def;
	Lexem l;
	l.type = NUMBER;
	std::stringstream sstr;
	sstr << (line+1);
	sstr >> l.value;
	def.lexems.push_back(l);
	define_table["__LINE__"] = def;
}

static void setFileMacro(DefineTable& define_table, const std::string& file)
{
	DefineEntry def;
	Lexem l;
	l.type = STRING;
	l.value = std::string("\"")+file+"\"";
	def.lexems.push_back(l);
	define_table["__FILE__"] = def;
}	

static void recursivePreprocess(	
	std::string filename,
	std::string filedata,
	FileSource& file_source,
	LexemList& lexems,
	DefineTable& define_table,
	const bool fromString)
{
	unsigned int start_line = current_line;
	lines_this_file = 0;
	current_file = filename;
	setFileMacro(define_table,current_file);
	setLineMacro(define_table,lines_this_file);

	std::vector<char> data;

	if (fromString)
	{
		data.resize (filedata.length());
		for (unsigned int i = 0; i < data.size(); i++)
			data[i] = filedata[i];
	}
	else
	{
		bool loaded = file_source.LoadFile(filename,data);
		if (!loaded) 
		{
			PrintErrorMessage(std::string("Could not open file ")+filename);
			return;
		}
	}

	if (data.size() == 0) return;
	data.push_back('\n');
	char* d_end = &data[data.size()-1];
	++d_end;
	lex(&data[0],d_end,lexems);

	LexemList::iterator ITR = lexems.begin();
	LexemList::iterator END = lexems.end();
	while ( ITR != END )
	{
		if (ITR->type == NEWLINE)
		{
			current_line++;
			lines_this_file++;
			++ITR;
			setLineMacro(define_table,lines_this_file);
		}
		else if (ITR->type == PREPROCESSOR)
		{
			LLITR start_of_line = ITR;
			LLITR end_of_line = findLexem(ITR,END,NEWLINE);
			LexemList directive(start_of_line,end_of_line);
			ITR = lexems.erase(start_of_line,end_of_line);
			
			std::string value = directive.begin()->value;
			if (value == "#define")
			{
				parseDefine(define_table,directive);
			} 
			else if (value == "#ifdef")
			{
				std::string def_name;
				parseIf(directive,def_name);
				DefineTable::iterator DTI = define_table.find(def_name);
				if (DTI == define_table.end())
				{
					LLITR splice_to = parseIfDef(ITR,END);
					ITR = lexems.erase(ITR,splice_to);
				}
			} 
			else if (value == "#ifndef")
			{
				std::string def_name;
				parseIf(directive,def_name);
				DefineTable::iterator DTI = define_table.find(def_name);
				if (DTI != define_table.end())
				{
					LLITR splice_to = parseIfDef(ITR,END);
					ITR = lexems.erase(ITR,splice_to);
				}
			}
			else if (value == "#endif")
			{
				//ignore
			}
			else if (value == "#include")
			{
				if (LNT) LNT->AddLineRange(filename,start_line,current_line-lines_this_file);
				unsigned int save_lines_this_file = lines_this_file;
				std::string file_name;
				parseIf(directive,file_name);
				LexemList next_file;
				recursivePreprocess(
					addPaths(filename,removeQuotes(file_name)),
					"",
					file_source,
					next_file,
					define_table,
					false);
				lexems.splice(ITR,next_file);
				start_line = current_line;
				lines_this_file = save_lines_this_file;
				current_file = filename;
				setFileMacro(define_table,current_file);
				setLineMacro(define_table,lines_this_file);
			}
			else if (value == "#pragma")
			{
				parsePragma(directive);
			}
			else if (value == "#warning")
			{
				std::string msg;
				parseIf(directive,msg);
				PrintWarningMessage(msg);
			}
			else 
			{
				PrintErrorMessage("Unknown directive.");
			}
		} 
		else if (ITR->type == IDENTIFIER)
		{ 
			ITR = expandDefine(ITR,END,lexems,define_table);
		} 
		else { ++ITR; }
	}

	if (LNT) LNT->AddLineRange(filename,start_line,current_line-lines_this_file);
}


int Preprocessor::preprocess(
	const String& source_file,
	const String& source_data,
	FileSource& file_source,
	OutStream& destination,
	OutStream& err,
	LineNumberTranslator* trans)
{
	if (trans) LNT = new LineNumberTranslator::Table;
	else LNT = 0;
	current_file = source_file;
	current_line = 0;
	DefineTable define_table = application_specified;
	LexemList lexems;
	error_stream = &err;
	number_of_errors = 0;
	root_file = source_file;
	
	recursivePreprocess((const char*)source_file, (const char*)source_data,file_source,lexems,define_table,true);
	printLexemList(lexems,destination);
	
	if (trans) 
	{
		trans->SetTable(LNT);
		LNT = 0;
	}
	return number_of_errors;
}

void Preprocessor::define(const std::string& str)
{
	if (str.length() == 0) return;
	std::string data = "#define ";
	data += str;
	char* d_end = &data[data.length()-1];
	++d_end;
	LexemList lexems;
	lex(&data[0],d_end,lexems);

	parseDefine(application_specified,lexems);
}
