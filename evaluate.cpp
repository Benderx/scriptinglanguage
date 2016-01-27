// Simple Expression Evaluation Implementation file
// This describes the functionality for evaluating very simple
// arithmetic expressions.  Given a string consisting of operators
// and operands, it will evaluate that expression and return its value.
//
// The expressions may consist of the following:
// -- single-digit integer values
// -- simple arithmetic operators ( +, -, *, /, % )
// -- matched parentheses for grouping

// This implementation consists of a set of mutually-recursive 
// functions. which will track the structure of the expression.
//
// A sum expression is the sum or difference of one or more products.
// A product expression is the product or quotient of one or more factors.
// A factor may be a number or a parenthesized sum expression.

#include <iostream>
using namespace std;
#include "tokenlist.h"
#include "vartree.h"

void getValue(ListIterator&, TokenList&);
void assignOp(ListIterator&, TokenList&);
void addOp(ListIterator&, TokenList&);
void multOp(ListIterator&, TokenList&);
int evalPost(ListIterator&, TokenList&, VarTree&);

//Takes in a constant character array of an arthimatic expression
//Returns the answer of the the character array expression
//Pre- Takes in an constant char array
//Post- Returns an integer that is the answer to the expression
int evaluate(const char data[], VarTree &vt)
{
	//We create a TokenList for the iterator we will make
	TokenList inFix(data);
	ListIterator iter(inFix.begin());

	cout << inFix << endl;

	//The TokenList that will hold the postFix notation
	TokenList postFix;
	getValue(iter, postFix);
	iter.advance();
	//The actual rewriting
	assignOp(iter, postFix);
	//Makes an iterator for the postFix linked list
	ListIterator iterPost(postFix.begin());

	cout << postFix << endl;

	//Returns the answer
	return evalPost(iterPost, postFix, vt);
}

//The function takes in an iterator and TokenList and will rewrite numbers at the iterator's
//Pre- The position is located at a number or a parethesis
//Post- It will write to the postFix TokenList and update the iterator
void getValue(ListIterator &iter, TokenList &postFix)
{
	//If parethesis are found this else if will rewrite the parenthesis in postFix
	if (iter.tokenChar() == '(')
	{
		iter.advance();
		getValue(iter, postFix);
		iter.advance();
		assignOp(iter, postFix);
	}
	//If the current position is an integer
	else
	{
		postFix.push_back(iter.token());
	}
}

//This function takes in the iterator and TokenList, and rewrite both sides of the sum expression in postFix
//Pre- The position is at a symbol =,+,-,*,/,%
//Post- It will change postFix and the iterator
void assignOp(ListIterator &iter, TokenList &postFix)
{
	int pos;
	Token saveToken;
	bool solved = false;

	while(solved == false)
	{
		if (iter.tokenChar() == '*' || iter.tokenChar() == '/' || iter.tokenChar() == '%')
		{
			//This means that a product operation was encountered immediately so the prgoram can finish the expression and return without
			multOp(iter, postFix);
		}
		else if (iter.tokenChar() == '+' || iter.tokenChar() == '-')
		{
			addOp(iter, postFix);
			//postFix.push_back(saveToken);
		}
		else if (iter.tokenChar() == '=')
		{
			//We advance to save the next number and then again to check the next character
			saveToken = iter.token();
			iter.advance();
			getValue(iter, postFix);
			iter.advance();
			if (iter.tokenChar() == '*' || iter.tokenChar() == '/' || iter.tokenChar() == '%')
			{
				//If a product expression is found it will calculate the entirety of that
				multOp(iter, postFix);
			}
			else if (iter.tokenChar() == '+' || iter.tokenChar() == '-')
			{
				//If a addition expression is found it will calculate the entirety of that
				addOp(iter, postFix);
			}
			postFix.push_back(saveToken);
		}
		else
		{
			solved = true;
		}
	}
}

//This function takes in the iterator, and rewrite both sides of the sum expression in postFix
//Pre- The position is at a symbol +,-,*,/,%
//Post- It will change postFix and the iterator
void addOp(ListIterator &iter, TokenList &postFix)
{
	int pos;
	Token saveToken;
	bool solved = false;

	while(solved == false)
	{
		if (iter.tokenChar() == '*' || iter.tokenChar() == '/' || iter.tokenChar() == '%')
		{
			//This means that a product operation was encountered immediately so the prgoram can finish the expression and return without
			multOp(iter, postFix);
		}
		else if (iter.tokenChar() == '+' || iter.tokenChar() == '-')
		{
			//We advance to save the next number and then again to check the next character
			saveToken = iter.token();
			iter.advance();
			getValue(iter, postFix);
			iter.advance();
			if (iter.tokenChar() == '*' || iter.tokenChar() == '/' || iter.tokenChar() == '%')
			{
				//If a product expression is found it will calculate the entirety of that
				multOp(iter, postFix);
			}
			postFix.push_back(saveToken);
		}
		else
		{
			solved = true;
		}
	}
}

//This function takes in the iterator, and the TokeList, and will rewrite any product expressions
//Pre- The position will be on a operation symbol that is either *, /, %
//Post- It will rewrite the infix to postFix product expression
void multOp(ListIterator &iter, TokenList &postFix)
{
	Token saveToken;

	//This loop will run indefinately and rewrite to postFix until the product expression ends
	while (iter.tokenChar() == '*' || iter.tokenChar() == '/' || iter.tokenChar() == '%')
	{
		saveToken = iter.token();
		iter.advance();

		getValue(iter, postFix);
		iter.advance();

		postFix.push_back(saveToken);
	}
}

//This function will solve a postFix notation TokenList.
//Pre- This function takes in an iterator for a postFix TokenList and a TokenList in postFix notation.
//Post- It will return the result of the entire postFix notation.
int evalPost(ListIterator &iter, TokenList &postFix, VarTree &vt)
{
	Token v1, v2;
	int value = 0, n1, n2;
	bool solved = false, solvedI = false;
	char saveChar;
	//Making the stack
	TokenList toSolve;

	//Runs until the equation is determined to be solved.
	while (solved == false)
	{
		//Will add all the consecutive integers onto the stack
		while (iter.tokenChar() != '=' && iter.tokenChar() != '+' && iter.tokenChar() != '-' && iter.tokenChar() != '*' && iter.tokenChar() != '/' && iter.tokenChar() != '%')
		{
			//Actually pushing onto the stack
			toSolve.push_front(iter.token());
			iter.advance();
		}

		//Getting 2 numbers from the stack
		v2 = toSolve.pop_front();
		v1 = toSolve.pop_front();

		//If it a normal integer
		if(v2.isInteger()) 
		{
			n2 = v2.integerValue();
		}
		//If it is a variable find it
		else
		{
			n2 = vt.lookup(v2.tokenText());
		}

		//If it a normal integer
		if(v1.isInteger())
		{
			n1 = v1.integerValue();
		}
		//If it is a variable find it
		else
		{
			n1 = vt.lookup(v1.tokenText());
		}

		//Grabbing the character operation from the originol TokenList
		saveChar = iter.tokenChar();
		iter.advance();

		if(saveChar == '+')
		{
			value = n1 + n2;
		}
		else if(saveChar == '-')
		{
			value = n1 - n2;
		}
		else if(saveChar == '*')
		{
			value = n1 * n2;
		}
		else if(saveChar == '/')
		{
			value = n1 / n2;
		}
		else if(saveChar == '%')
		{
			value = n1 % n2;
		}
		else if(saveChar == '=')
		{
			vt.assign(v1.tokenText(), n2);
			value = n2;
		}

		//Checks if the equation is done
		if(toSolve.empty() && !(iter != postFix.end()))
		{
			solved = true;
		}
		//If the equation is not done you push the current result and loop
		else
		{
			toSolve.push_front(Token(value));
		}
	}
	return value;
}