/********************************************************
 * cpp_stat module -- Generates statistics from c++		*
 *						source files using tokens.		*
 *														*
 * Author: Adam Pearce									*
 ********************************************************/
#include "cpp_stat.h"
#include "token.h"

#include <iostream>
#include <iomanip>
#include <string>

/********************************************************
 * line_counter::take_token -- Takes a newline token and*
 *							increases the line count.	*
 *														*
 * Parameters											*
 *		token -- Uses T_NEWLINE to track line number	*
 ********************************************************/
void line_counter::take_token(token::TOKEN_TYPE token)
{
	if (token == token::T_NEWLINE)
		++count;
}

/********************************************************
 * line_counter::output_line_stats						*
 *														*
 * At the start of the line output the line number.		*
 ********************************************************/
void line_counter::output_line_stats()
{
	std::cout << std::setw(4) << count << ' ' << std::setw(0);
}

/********************************************************
 * line_counter::output_file_stats						*
 *														*
 * At the end of the file output the number of lines.	*
 ********************************************************/
void line_counter::output_file_stats()
{
	std::cout << "Total number of lines: " << count << '\n';
}

/********************************************************
 * nest_counter::take_token -- Counts the number of open*
 *				vs close parenthesis and curly braces as*
 *				well as finding the maximum nesting of  *
 *				each.									*
 *														*
 * Parameters											*
 *		token -- Uses parenthesis and brace tokens		*
 ********************************************************/
void nest_counter::take_token(token::TOKEN_TYPE token)
{
	if (token == token::T_OPEN_PARENTHESIS)
		++parenthesis_count;

	if (token == token::T_CLOSE_PARENTHESIS)
		--parenthesis_count;

	if (token == token::T_OPEN_CURLY_BRACE)
		++curly_brace_count;

	if (token == token::T_CLOSE_CURLY_BRACE)
		--curly_brace_count;

	if (curly_brace_count > max_curly_brace)
		max_curly_brace = curly_brace_count;

	if (parenthesis_count > max_parenthesis)
		max_parenthesis = parenthesis_count;
}

/********************************************************
 * nest_counter::output_line_stats						*
 *														*
 * At the start of the line output the current level of	*
 * nested curly braces and parenthesis.					*
 ********************************************************/
void nest_counter::output_line_stats()
{
	std::cout.setf(std::ios::left);

	std::cout << "( " << std::setw(2) << parenthesis_count << ' ';
	std::cout << "{ " << std::setw(2) << curly_brace_count << ' ';

	std::cout.unsetf(std::ios::left);
}

/********************************************************
 * nest_counter::output_file_stats						*
 *														*
 * At the end of the file output the maximum level of	*
 * nesting for both the curly braces and parenthesis.	*
 ********************************************************/
void nest_counter::output_file_stats()
{
	std::cout << "Maximum nesting of {}: " << max_curly_brace << '\n';
	std::cout << "Maximum nesting of (): " << max_parenthesis << '\n';
}

/********************************************************
 * comment_counter::take_token -- Receives tokens and	*
 *			divides them into code lines, comment lines *
 *			and comment and code lines then calculates	*
 *			the ratio of comments to code.				*
 *														*
 * Parameters											*
 *		token -- Token to divide						*
 ********************************************************/
void comment_counter::take_token(token::TOKEN_TYPE token)
{
	switch (token)
	{
	case token::T_COMMENT:
		comment = true;
		break;
	case token::T_NEWLINE:
		// comment and code seen
		if ((code == true) && (comment == true)) {
			++comment_and_code_count;
		} else {
			// Code only
			if (code)
				++code_count;
			// Comment only
			if (comment)
				++comment_count;
		}

		// Empty line
		if ((code == false) && (comment == false))
			++blank_count;

		// Reset for next line
		code = false;
		comment = false;
		break;

	default:
		code = true;
		break;
	}
}

/********************************************************
 * comment_counter::output_file_stats					*
 *														*
 * Output the results of the stats generated for code,	*
 * comments, comments and code and the ratio of comments*
 * to code at the end of the file.						*
 ********************************************************/
void comment_counter::output_file_stats()
{
	std::cout << "Number of blank lines ................." << blank_count << '\n';
	std::cout << "Number of comment only lines .........." << comment_count << '\n';
	std::cout << "Number of code only lines ............." << code_count << '\n';
	std::cout << "Number of lines with code and comments " << comment_and_code_count << '\n';
	std::cout << "Comment to code ratio ................." <<
		float(code_count + comment_and_code_count) /
		float(comment_count + comment_and_code_count) * 100 << "%\n";
}

/********************************************************
 * process_file -- Process a file to generate statistics*
 *					for it.								*
 *														*
 * Parameters											*
 *		filename -- The name of the file to process		*
 ********************************************************/
void process_file(const char* filename)
{
	input_file in_file(filename);
	token token;
	token::TOKEN_TYPE current_token;
	line_counter line_stats;
	nest_counter nest_stats;
	comment_counter comment_stats;

	current_token = token.next_token(in_file);

	while (current_token != token::T_END_OF_FILE)
	{
		line_stats.take_token(current_token);
		nest_stats.take_token(current_token);
		comment_stats.take_token(current_token);

		if (current_token == token::T_NEWLINE) {
			line_stats.output_line_stats();
			nest_stats.output_line_stats();
			in_file.write_line();
		}
		current_token = token.next_token(in_file);
	}

	line_stats.output_file_stats();
	nest_stats.output_file_stats();
	comment_stats.output_file_stats();
}

