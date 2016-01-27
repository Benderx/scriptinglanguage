// Token List Implementation file
//
// This tokenizer will scan a character string representing
// an expression, and will return a list of tokens.
// --- only integers and operators are supported (no names)

// The standard C library has some useful functions for us
#include <string.h>
#include <ctype.h>

// And to get the definition of a token:
#include "tokenlist.h"

// TokenList constructor
// converts a character string into a list of tokens
// Parameter:
// 	expr	(input char pointer)	// string to examine
// Pre-condition:  str may not be a null pointer
//     and is assumed to actually point at a valid expression.
TokenList::TokenList(const char expr[])
{
	head = NULL;
	tail = NULL;
	const char *pos = expr;

	//Advances past all white space in the begining of the expression
	while (isspace(*pos))
	{
		pos++;
	}

	//Checking through the entire character array until it reaches the Null character
	while (*pos != '\0')
	{
		//Checks if its a digit or not so Token can store that information for later
		if (isdigit(*pos))
		{
			push_back(Token(atoi(pos)));
		}
		else if(*pos == '=' || *pos == '+' || *pos == '-' || *pos == '*' || *pos == '/' || *pos == '%' || *pos == '=' || *pos == '(' || *pos == ')')
		{
			push_back(Token(*pos));
		}
		else
		{
			string temp;
			while(!isdigit(*pos) && *pos != '=' && *pos != '+' && *pos != '-' && *pos != '*' && *pos != '/' && *pos != '%' && *pos != '=' && *pos != '(' && *pos != ')' && *pos != ' ' && *pos != '\0')
			{
				temp += *pos;
				pos++;
			}
			pos--;
			push_back(Token(temp));
		}

		//If it has just processed a multiple digit number, the iterator needs to pass past all the digits
		if (isdigit(*pos))
		{
			while (isdigit(*pos))
			{
				pos++;
			}
		}
		//If it was a single digit number then it advances one
		else
		{
			pos++;
		}
		//Advances past all the spaces
		while (isspace(*pos))
		{
			pos++;
		}
	}
}

//  output operation
//  Display all of the tokens in the list
ostream& operator<<(ostream &stream, TokenList &t)
{
	for (ListIterator iter = t.begin(); iter != t.end(); iter.advance())
	{
		stream << iter.token() << " ";
	}
	return stream;
}

//  Creates an iterator to refer to the beginning of the list
ListIterator TokenList::begin()
{
	return ListIterator(this, head);
}

//  Creates an iterator to refer after the end of the list
//  This list is simple:  it ends with NULL
ListIterator TokenList::end()
{
	return ListIterator(this, NULL);
}

//  Add a new element to the back of the list
//  Parameter:
//       t	(input Token)	the new item to add
void TokenList::push_back(Token t)
{
	//If both tail and head are equal to NULL
	if(empty())
	{
		head = new ListElement();
		head->token = t;
		head->next = NULL;
	}
	//If only head is defined, therefore after this there should only be 2 elements int he list, head and tail
	else if(tail == NULL)
	{
		tail = new ListElement();
		//Sets the new tail equal to the new element
		tail->token = t;
		tail->next = NULL;
		//Points head-> next to the tail
		head->next = tail;
	}
	//For all situations when there are 2 or more elemnts already in the list
	else
	{
		ListElement *element = new ListElement();
		element->token = t;
		element->next = NULL;
		tail->next = element;
		tail = element;
	}
}

//  Add a new element to the front of the list
//  Parameter:
//       t	(input Token)	the new item to add
void TokenList::push_front(Token t)
{
	//If both tail and head are equal to NULL
	if(empty())
	{
		head = new ListElement();
		head->token = t;
		head->next = NULL;
	}
	//If only head is defined, therefore after this there should only be 2 elements int he list, head and tail
	else if(tail == NULL)
	{
		tail = new ListElement();
		//Sets the new tail equal to the head
		tail->token = head->token;
		tail->next = NULL;
		//Sets the head equal to the new tail
		head->token = t;
		//Points the head to the tail
		head->next = tail;
	}
	//For all situations when there are 2 or more elemnts already in the list
	else
	{
		ListElement *element = new ListElement();
		element->token = t;
		element->next = head;
		head = element;
	}
}

//  Remove and return the element at the front of the list
Token TokenList::pop_front()
{
	Token tempToken(head->token);
	ListElement *toberemoved = head;
	//Checks if head is the only element left before using head = head->next;
	if(head->next != NULL)
	{
		head = head->next;
		//Checks if head is the only element left after updating head
		if(head->next == NULL) 
		{
			tail = NULL;
		}
	}
	//Sets the List to none again.
	else
	{
		head = NULL;
	}
	//Deletes the element
	delete toberemoved;
	return tempToken;
}
