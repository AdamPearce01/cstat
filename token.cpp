/********************************************************
 * token module -- Generates tokens from a file stream	*
 *														*
 * Author: Adam Pearce									*
 ********************************************************/
#include "token.h"
#include "char_type.h"
#include <cassert>
#include <string>

static class char_type char_type;

/********************************************************
 * input_file::read_char -- Read a single character from*
 *							the file.					*
 ********************************************************/
void input_file::read_char()
{
	line += current_ch;

	current_ch = next_ch;
	next_ch = get();
}

/********************************************************
 * input_file::write_line -- Output the current line	*
 ********************************************************/
void input_file::write_line()
{
	std::cout << line;
	std::cout.flush();

	line = "";
}

/********************************************************
 * read_comment -- Reads through a multiple line comment*
 *														*
 * Parameters											*
 *		file -- The file to read the comment from		*
 *														*
 * Returns												*
 *		T_COMMENT if a comment was read					*
 *		T_NEWLINE if a newline was reached				*
 *		T_END_OF_FILE if the eof was reached before the	*
 *		comment ended.									*
 ********************************************************/
token::TOKEN_TYPE token::read_comment(input_file& file)
{
	if (file.current_char() == '\n')
	{
		file.read_char();
		return (T_NEWLINE);
	}

	inside_comment = true;

	while (true)
	{
		// Check to see if we have reached the end of the comment
		if (file.current_char() == '*')
		{
			if (file.next_char() == '/')
			{
				// Reached the end of the comment
				inside_comment = false;

				// Move through the end of the comment
				file.read_char();
				file.read_char();

				return (T_COMMENT);
			}
		}

		if (file.current_char() == '\n')
			return (T_COMMENT);

		if (file.current_char() == EOF)
			return (T_END_OF_FILE);

		file.read_char();
	}
}

/********************************************************
 * next_token -- Returns the next token in the stream	*
 *														*
 * Parameters											*
 *		file -- The file being used						*
 *														*
 * Returns												*
 *		A TOKEN type									*
 ********************************************************/
token::TOKEN_TYPE token::next_token(input_file& file)
{
	// If we are still inside a comment continue reading comment
	if (inside_comment)
		return (read_comment(file));

	// Skip through any whitespace
	while (char_type.is(file.current_char(), char_type::C_WHITESPACE)) {
		file.read_char();
	}

	if (file.current_char() == EOF)
		return (T_END_OF_FILE);

	switch (char_type.type(file.current_char())) 
	{
		case char_type::C_ALPHA:
			while (char_type.is(file.current_char(), char_type::C_ALPHA) ||
				char_type.is(file.current_char(), char_type::C_DIGIT))
			{
				file.read_char();

				if (file.current_char() == EOF)
					return (T_END_OF_FILE);
			}
			return (T_ID);

		case char_type::C_DIGIT:
			while (char_type.is(file.current_char(), char_type::C_DIGIT)) {
				file.read_char();

				if (file.current_char() == EOF)
					break;
			}
			return (T_NUMBER);

		case char_type::C_OPEN_PARENTHESIS:
			file.read_char();
			return (T_OPEN_PARENTHESIS);
		case char_type::C_CLOSE_PARENTHESIS:
			file.read_char();
			return (T_CLOSE_PARENTHESIS);
		case char_type::C_OPEN_CURLY_BRACE:
			file.read_char();
			return (T_OPEN_CURLY_BRACE);
		case char_type::C_CLOSE_CURLY_BRACE:
			file.read_char();
			return (T_CLOSE_CURLY_BRACE);

		case char_type::C_DOUBLE_QUOTE:
			while (true) {
				file.read_char();

				if (file.current_char() == EOF)
					return (T_END_OF_FILE);

				if (file.current_char() == '"')
					break;

				if (file.current_char() == '\\')
					file.read_char();
			}
			file.read_char();
			return (T_STRING);

		case char_type::C_SINGLE_QUOTE:
			while (true) {
				file.read_char();

				if (file.current_char() == EOF)
					return (T_END_OF_FILE);

				if (file.current_char() == '\'')
					break;

				if (file.current_char() == '\\')
					file.read_char();
			}
			file.read_char();
			return (T_STRING);
		
		case char_type::C_END_OF_FILE:
			return (T_END_OF_FILE);

		case char_type::C_FORWARD_SLASH:
			if (file.next_char() == '*')
				return (read_comment(file));

			if (file.next_char() == '/')
			{
				while (true)
				{
					if (file.current_char() == EOF)
						return (T_COMMENT);
					if (file.current_char() == '\n')
						return (T_COMMENT);

					file.read_char();
				}
			}
			// Fall through to return an operator 
		case char_type::C_OPERATOR:
			file.read_char();
			return (T_OPERATOR);
		case char_type::C_NEWLINE:
			file.read_char();
			return (T_NEWLINE);

		default:
			assert("Error: Unknown character" != 0);
	}

	assert("Error: This line should not be reached." != 0);
	return (T_END_OF_FILE);	// Return the end of the file, error for this to happen
}
