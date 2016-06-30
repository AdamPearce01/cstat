/********************************************************
 * cpp_stat module -- Generates statistics from c++		*
 *						source files using tokens.		*
 *														*
 * Author: Adam Pearce									*
 ********************************************************/
#ifndef __CPP_STAT_H__
#define __CPP_STAT_H__

#include "token.h"

/********************************************************
 * class cpp_stat -- Collects statistics on c++ files.	*
 *														*
 * Member functions										*
 *		take_token -- Uses tokens to generate stats		*
 *		output_line_stats -- Outputs the stats collected*
 *							for the line.				*
 *		output_file_stats -- Outputs the stats collected*
 *							for the file.				*
 ********************************************************/
class cpp_stat {
public:
	// cpp_stat()
	//		Use default constructor

	// cpp_stat(const cpp_stat& other)
	//		Use default copy constructor

	// cpp_stat operator =(const cpp_stat& oper2)
	//		Use default assignment operator

	// ~cpp_stat()
	//		Use default destructor

	// Takes a token to generate stats
	virtual void take_token(token::TOKEN_TYPE token) = 0;

	// Outputs stats for a line
	virtual void output_line_stat() {}

	// Outputs the files stats
	virtual void output_file_stat() {}
};

/********************************************************
 * class line_counter									*
 *														*
 * Counts the number of newline tokens to keep track of	*
 * the current line and total number of lines in a file *
 ********************************************************/
class line_counter : public cpp_stat {
public:
	line_counter()
	{
		count = 0;
	}

	// line_counter(const line_counter& other)
	//		Use default copy constructor

	// line_counter operator =(const line_counter& oper2)
	//		Use default assignment operator

	// ~line_counter()
	//		Use default destructor

	// Takes a newline token and increases the line count
	void take_token(token::TOKEN_TYPE token);

	// Output the line number
	void output_line_stats();

	// Output the total number of lines 
	void output_file_stats();

private:
	int count;	// The current line number
};

/********************************************************
 * class nest_counter									*
 *														*
 * Counts the number of open parentheses and open curly	*
 * braces to the number of close parenthesis and close	*
 * curly braces.										*
 ********************************************************/
class nest_counter : public cpp_stat {
public:
	nest_counter()
	{
		parenthesis_count = 0;
		curly_brace_count = 0;
		max_parenthesis = 0;
		max_curly_brace = 0;
	}

	// nest_counter(const nest_counter& other)
	//		Use default copy constructor

	// nest_counter operator =(const nest_counter& oper2)
	//		Use default assignment operator

	// ~nest_counter()
	//		Use default destructor

	// Takes curly brace and parenthesis tokens
	void take_token(token::TOKEN_TYPE token);

	// Output the nesting of '{' and '(' at the start of the line
	void output_line_stats();

	// Output the maximum nesting of '{' and '(' at the end of the file
	void output_file_stats();

private:
	int parenthesis_count;	// Current nesting of parenthesis
	int curly_brace_count;	// Current nesting of curly braces
	int max_parenthesis;	// Maximum nesting of parenthesis
	int max_curly_brace;	// Maximum nesting of curly braces
};

/********************************************************
 * class comment_counter								*
 *														*
 * Counts the number of code lines, comment lines,		*
 * comment and code lines. It also calculates the ratio	*
 * of comments to code									*
 ********************************************************/
class comment_counter : public cpp_stat {
public:
	comment_counter() {
		code = false;
		comment = false;
		code_count = 0;
		comment_count = 0;
		blank_count = 0;
		comment_and_code_count = 0;
	}

	// comment_counter(const comment_counter& other)
	//		Use default copy constructor

	// comment_counter operator =(const comment_counter& oper2)
	//		Use default assignment operator

	// ~comment_counter()
	//		Use default destructor

	// Takes tokens to count comment and code lines
	void take_token(token::TOKEN_TYPE token);

	// No comment statistics needed for the start of the line
	// void output_line_stats()

	// Output the number of lines of code, comments and there ratio,
	// at the end of the file
	void output_file_stats();

private:
	bool code;			// Has code been seen on the line
	bool comment;		// Has a comment been seen on the line
	int code_count;		// The number of lines with code only
	int comment_count;	// The number of lines with comments only
	int blank_count;	// The number of blank lines

	// The number of lines with comments and code in
	int comment_and_code_count;
};

/********************************************************
* process_file -- Process a file to generate statistics	*
*					for it.								*
*														*
* Parameters											*
*		filename -- The name of the file to process		*
********************************************************/
void process_file(const char* filename);

#endif /* __CPP_STAT_H__ */