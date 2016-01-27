// Token List Header file
// This is a linked list for use with the tokens for an
// arithmetic expression.  Although it is used for that
// particular application, this implementation mroe
// resembles a generic linked list, which may be used
// either as a stack or a queue.

#include <iostream>
using namespace std;

#include "token.h"

struct ListElement {
	Token		token;	
	struct ListElement *next;	
};

class ListIterator;		

class TokenList  {
	friend class ListIterator;
	friend ostream& operator<<(ostream &, TokenList &);
private:
	ListElement *head, 	// front of the list
		*tail;	// tail of the list
public:
	TokenList()		// create an empty list
	{
		head = NULL;
		tail = NULL;
	}
	TokenList(const char[]);	// or create initial list
	~TokenList()			// destructor -- clear the list
	{
		ListElement *remove;
		while ((remove = head) != NULL)
		{
			head = head->next;
			delete remove;	
		}
	}

	bool empty() const
	{
		return head == NULL;
	}

	Token first() const
	{
		return head->token;
	}

	void push_back(Token t);
	void push_front(Token t);
	Token pop_front();

	ListIterator begin();
	ListIterator end();
};

class ListIterator
{
	friend class TokenList;	
private:
	TokenList *list;	
	ListElement *curr;	// pointer to current node
	ListIterator(TokenList *l, ListElement *le)
	{
		list = l;
		curr = le;
	}
public:
	Token& token() const
	{
		return curr->token;
	}
	char tokenChar()
	{
		if (curr != NULL)
			return curr->token.tokenChar();
		else
			return 0;
	}
	bool currentIsInteger()
	{
		return curr->token.isInteger();
	}
	int integerValue()
	{
		return curr->token.integerValue();
	}
	void advance()
	{
		if (curr != NULL)
			curr = curr->next;
	}
	int operator !=(const ListIterator &other) const
	{
		return list != other.list || curr != other.curr;
	}
};

