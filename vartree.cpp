// Variable Tree Implementation File
// This is a simple binary search tree associating variables
// with integer values.
#include <iostream>
#include <string>
using namespace std;

#include "vartree.h"

//  recursiveSearch
//  A recursive tree-traversal function to search for a variable.
//  If the variable does not exist, it is created with a value of 0.
//  Parameters:
//  	node	(modified TreeNode ptr)	root of sub-tree to search
//  	name	(input string)		name of variable
//  NOTE: node May be a null pointer, indicating an empty tree
//  Post-condition:
//      node points at a node with the given name,
//      even if it had to be created to do so
TreeNode* VarTree::recursiveSearch( TreeNode *&node, string name )
{
	//If the tree has nothing in it
	if (root == NULL)
	{
		root = new TreeNode(name, 0);
		root->left = NULL;
		root->right = NULL;
	}
	//If the name belongs to the right of the tree and we have reached the end, create a new one
	if (node && node->name > name && node->right == NULL)
	{
		node->right = new TreeNode(name, 0);
		return node->right;
	}
	//If the name belongs to the right of the tree recursivesearch again
	else if (node && node->name > name && node->right != NULL)
	{
		return recursiveSearch(node->right, name);
	}
	//If the name belongs to the left of the tree and we have reached the end, create a new one
	if (node && node->name < name && node->left == NULL)
	{
		node->left = new TreeNode(name, 0);
		return node->left;
	}
	//If the name belongs to the left of the tree recursivesearch again
	else if (node && node->name < name && node->left != NULL)
	{
		return recursiveSearch(node->left, name);
	}
	return node;	
}

//  lookup
//  Searches for a variable to get its value
//  If the variable does not yet exist, it is created with value 0.
//  Parameters:
//  	name	(input char array)	name of variable
//  Returns:				value of variable
int VarTree::lookup( string name )
{
    TreeNode *node = recursiveSearch( root, name );
    return node->value;
}

//  assign
//  Assigns a value to a variable.
//  If the variable does not yet exist, it is created.
//  Parameters:
//  	name	(input string)		name of variable
//  	value	(input integer)		value to assign
void VarTree::assign( string name, int value )
{
    TreeNode *node = recursiveSearch( root, name );
    node->value = value;
}

//  EXTRA CREDIT:  Implement the following, without any loops
ostream& operator<<( ostream& stream, VarTree &vt )
{
    return stream;
}

ostream& operator<<( ostream& stream, TreeNode &tn )
{
    return stream;
}