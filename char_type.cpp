/********************************************************
 * char_type -- Defines the class char_type that is used*
 * to tell the type of characters.						*
 *														*
 * Author: Adam Pearce									*
 ********************************************************/
#include "char_type.h"
#include <cassert>
#include <iostream>
#include <cstdio>

// Information stored on each type
char_type::CHAR_TYPE char_type::type_information[256];

/********************************************************
 * char_type -- Initialize char_type					*
 ********************************************************/
char_type::char_type()
{
	/*
	* Fill with whitespace, so that any unknown or 
	* un-assigned types default to whitespace
	*/
	fill(0, 255, C_WHITESPACE);

	fill('a', 'z', C_ALPHA);
	fill('A', 'Z', C_ALPHA);
	type_information['_'] = C_ALPHA;

	fill('0', '9', C_DIGIT);

	type_information['+'] = C_OPERATOR;
	type_information['-'] = C_OPERATOR;
	type_information['*'] = C_OPERATOR;
	type_information['='] = C_OPERATOR;
	type_information['['] = C_OPERATOR;
	type_information[']'] = C_OPERATOR;
	type_information['&'] = C_OPERATOR;
	type_information['>'] = C_OPERATOR;
	type_information['<'] = C_OPERATOR;
	type_information['~'] = C_OPERATOR;
	type_information['#'] = C_OPERATOR;
	type_information['!'] = C_OPERATOR;
	type_information['|'] = C_OPERATOR;
	type_information['?'] = C_OPERATOR;
	type_information[','] = C_OPERATOR;
	type_information['^'] = C_OPERATOR;
	type_information['%'] = C_OPERATOR;
	type_information[':'] = C_OPERATOR;
	type_information['.'] = C_OPERATOR;
	type_information[';'] = C_OPERATOR;

	type_information['/'] = C_FORWARD_SLASH;

	type_information['('] = C_OPEN_PARENTHESIS;
	type_information[')'] = C_CLOSE_PARENTHESIS;

	type_information['{'] = C_OPEN_CURLY_BRACE;
	type_information['}'] = C_CLOSE_CURLY_BRACE;

	type_information['\n'] = C_NEWLINE;

	type_information['\''] = C_SINGLE_QUOTE;
	type_information['"'] = C_DOUBLE_QUOTE;
}

/********************************************************
 * fill -- Fills the type_information array with a given*
 *			type within a range.						*
 *														*
 * Parameters											*
 *		begin -- the character to begin filling from.	*
 *		end -- the character to stop filling at.		*
 *		type -- the type to fill with.					*
 ********************************************************/
void char_type::fill(int begin, int end, CHAR_TYPE type)
{
	for (int current_ch = begin; current_ch <= end; ++current_ch)
	{
		assert(begin >= 0);
		assert(end < sizeof(type_information) / sizeof(type_information[0]));

		type_information[current_ch] = type;
	}
}

/********************************************************
 * is -- Is character a certain type.					*
 *														*
 * Parameters											*
 *		ch -- The character to check.					*
 *		type -- The type to compare the character to.	*
 *														*
 * Returns												*
 *		1 if character and type match.					*
 *		0 if character and type don't match.			*
 *		-1 if character is not recognized.				*
 ********************************************************/
bool char_type::is(int ch, char_type::CHAR_TYPE type)
{
	if ((ch < 0) || (ch > sizeof(type_information) / sizeof(type_information[0])))
		return (false);
	
	if (type_information[ch] == type)
		return (true);

	return (false);
}

/********************************************************
 * type -- Returns the type of the given character.		*
 *														*
 * Parameters											*
 *		ch -- The character to get the type of.			*
 *														*
 * Returns												*
 *		The CHAR_TYPE of the character.					*
 ********************************************************/
char_type::CHAR_TYPE char_type::type(int ch)
{
	if (ch == EOF)
		return (C_END_OF_FILE);

	return (type_information[ch]);
}
