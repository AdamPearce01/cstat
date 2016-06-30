/******************************************************** 
 * token module -- Generates token from a file stream	*
 *														*
 * Author: Adam Pearce									*
 ********************************************************/
#ifndef __TOKEN_H__
#define __TOKEN_H__

#include <fstream>
#include <iostream>

/********************************************************
 * class input_file -- Reads data from a file.			*
 *														*
 * Member functions										*
 *		reach_char -- Reads a character from the file	*
 *		current_char -- Returns the current character	*
 *		next_char -- Returns the next character			*
 *		write_line -- Outputs the line so far			*
 ********************************************************/
class input_file: public std::ifstream {
public:
	// Initialize the current and next characters
	input_file(const char* filename) : 
		std::ifstream(filename) 
	{
		if (bad())
		{
			std::cout << "Error: Unable to open file: " << filename << '\n';
			return;
		}

		line = "";
		current_ch = get();
		next_ch = get();
	}

	~input_file() {
		close();
	}

	// input_file(const input_file& other_input_file)
	//		Use default copy constructor

	// input_file operator =(const input_file& other_input_file)
	//		Use default assignment operator

	// Read the next character in the file
	void read_char();

	// Return the current character in the file
	int current_char() { return (current_ch); }

	// Return the next character in the file
	int next_char() { return (next_ch); }

	// Write the line to the screen
	void write_line();

private:
	std::string line;	// The line of characters
	int current_ch;		// Current character in the file
	int next_ch;		// Next character in the file
};

/********************************************************
 * class token -- Generates tokens from the input file	*
 *				stream.									*
 *														*
 * Member functions										*
 *		read_comment -- Reads through a multiple line	*
 *						comment returning comment and	*
 *						newline tokens.					*
 *		next_token -- Collects the next token from the	*
 *						file stream.					*
 *		is_inside_comment -- Returns true if we are		*
 *						currently inside a comment and	*
 *						false if not.					*
 ********************************************************/
class token {
public:
	// List of available tokens
	enum TOKEN_TYPE {
		T_COMMENT,
		T_STRING,
		T_NEWLINE,
		T_OPERATOR,
		T_OPEN_PARENTHESIS,
		T_CLOSE_PARENTHESIS,
		T_OPEN_CURLY_BRACE,
		T_CLOSE_CURLY_BRACE,
		T_NUMBER,
		T_END_OF_FILE,
		T_ID
	};

	// Initialize inside comment 
	token() {
		inside_comment = false;
	}

	// token(const token& other_token)
	//		Use default copy constructor

	// token operator =(const token& other_token)
	//		Use default assignment operator

	// ~token()
	//		Use default destructor

	// Reads through a comment
	TOKEN_TYPE read_comment(input_file& file);

	// Returns the next token
	TOKEN_TYPE next_token(input_file& file);

	// Returns true if we are inside a comment
	bool is_inside_comment() { return (inside_comment); }

private:
	bool inside_comment;	// Are we currently inside a comment
};

#endif /* __TOKEN_H__ */