/********************************************************
 * char_type -- Defines the class char_type that is used*
 * to tell the type of characters.						*
 *														*
 * Author: Adam Pearce									*
 ********************************************************/
#ifndef __CHAR_TYPE_H__
#define __CHAR_TYPE_H__

/********************************************************
 * class char_type										*
 *														*
 * Member functions										*
 *		char_type -- Class constructor					*
 *		fill -- Fill type_information with a range of	*
 *				characters types.						*
 *		is -- Checks if character is a certain type		*
 *		type -- Returns the type of a character			*
 ********************************************************/
class char_type {
public:
	// List of character types
	enum CHAR_TYPE {
		C_ALPHA,				// A letter also includes "_"
		C_DIGIT,				// A single digit 0-9
		C_OPERATOR,				// Any operators (+, -, etc)
		C_OPEN_PARENTHESIS,		// '('
		C_CLOSE_PARENTHESIS,	// ')'
		C_OPEN_CURLY_BRACE,		// '{'
		C_CLOSE_CURLY_BRACE,	// '}'
		C_FORWARD_SLASH,		// '/'
		C_NEWLINE,				// A newline character
		C_END_OF_FILE,			// A end of file character
		C_WHITESPACE,			// Whitespace or control characters
		C_SINGLE_QUOTE,			// '\''
		C_DOUBLE_QUOTE			// '\"'
	};

	// Type information on each character stored
	static CHAR_TYPE type_information[256];

	// Initialize type information
	char_type();

	// char_type(const char_type& other_char_type)
	//		Use default copy constructor

	// char_type operator =(const char_type& other_char_type)
	//		Use default assignment operator

	// ~char_type()
	//		Use default destructor

	// Fill type_information with characters of a type
	void fill(int begin, int end, CHAR_TYPE type);

	// Returns true if character is of type, false otherwise
	bool is(int ch, CHAR_TYPE type);

	// Return the type character is of.
	CHAR_TYPE type(int ch);
};

#endif /* __CHAR_TYPE_H__ */