// Token Header file
// This is for the beginning of an object-oriented string tokenizer
// to be used for arithmetic expressions.    The tokenizer is an
// object that returns a linked list of object tokens, which are these.

// Since lots of files want to know what a token is, there is the
// danger of redeclaration, which these next couple lines will neutralize.
// (There is an #endif at the bottom as well)
#ifndef TOKEN
#define TOKEN

// Provides some helpful functionality for understanding tokens
#include <iostream>
#include <string>
#include <stdlib.h>
#include <ctype.h>
using namespace std;
 
class Token {
    private:
	bool    isInt;		// to identify the token type later
	int	value;		// value for an integer token
	string	text;		// character for an operator token


    public:			
	Token(char c)		// single character
	{
	    text = "" ;   
	    text += c;
	    isInt = false;
	    value = 0;		
	}
	Token(string s)		// full string
	{			
	    text =  s;     
	    isInt = false;
	    value = 0;		
	}
	Token(int i)		// integer value
	{		
	    value = i;
	    isInt = true;
	    text = "";		// initialize unused value
	}

	Token()			// default constructor
	{
	    value = 0;
	    text = "";
	    isInt = false;
	}

	bool isNull() const
	{
	    return !isInt && text=="";
	}

	bool isInteger() const
	{
	    return isInt;
	}

	int integerValue() const
	{
	    return value;
	}
	
	string tokenText() const
	{
	    return text;
	}

	char tokenChar() const
	{
	    return text[0];
	}

	friend ostream& operator <<( ostream& stream, Token &t);
};

#endif
