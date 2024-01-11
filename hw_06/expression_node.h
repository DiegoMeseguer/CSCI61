#ifndef EXPRESSION_TREE_NODE_H
#define EXPRESSION_TREE_NODE_H
#include <cstdlib>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <string>
#include <stack>

using namespace std;

class expression_tree_node {
public:

	//CONSTRUCTORS
	expression_tree_node();
	expression_tree_node(char data);
	expression_tree_node(char data, expression_tree_node* left, expression_tree_node* right);

	// MODIFICATION MEMBER FUNCTIONS
	char& data( ) { return data_field; }
	expression_tree_node*& left( ) { return left_field; }
	expression_tree_node*& right( ) { return right_field; }
	void set_data(const char& new_data) { data_field = new_data; }
	void set_left(expression_tree_node* new_left) { left_field = new_left; }
	void set_right(expression_tree_node* new_right) { right_field = new_right; }

	// CONST MEMBER FUNCTIONS
	const char& data( ) const { return data_field; }
	const  expression_tree_node* left( ) const { return left_field; }
	const  expression_tree_node* right( ) const { return right_field; }
	bool is_number( ) const { 
		return (left_field == NULL) && (right_field == NULL);
	}
	void print_tree() const;


private:

	//MEMBER VARIABLES
	char data_field; //can be a number or the operator * or +
	expression_tree_node *left_field;
	expression_tree_node *right_field;
};

//NON-MEMBER FUNCTIONS for the expression tree:
void print(const expression_tree_node* node_ptr, size_t depth);
void tree_clear(expression_tree_node*& root_ptr);
expression_tree_node* tree_copy(const expression_tree_node* root_ptr);
std::size_t tree_size(const expression_tree_node* node_ptr);

//MEMBER FUNCTIONS for the expression tree:
expression_tree_node::expression_tree_node() {
	data_field = '0';
	left_field = NULL;
	right_field = NULL;
}

expression_tree_node::expression_tree_node(char data, expression_tree_node* left, expression_tree_node* right) {
	data_field = data;
	left_field = left;
	right_field = right;
}

expression_tree_node::expression_tree_node(char data) {
	data_field = data;
	left_field = NULL;
	right_field = NULL;
}

void expression_tree_node::print_tree() const {
	size_t count;
	print(this, count);
}

//IMPLEMENTATION OF NON-MEMBER FUNCTIONS

void print(const expression_tree_node* node_ptr, size_t depth) {
    if (node_ptr != NULL) {
	print(node_ptr->right( ), depth+1);
	std::cout << std::setw(4*depth) << ""; // Indent 4*depth spaces.
	std::cout << node_ptr->data( ) << std::endl;
	print(node_ptr->left( ),  depth+1);
    }
}

void tree_clear(expression_tree_node*& root_ptr) {
    expression_tree_node* child;

    if (root_ptr != NULL) {
	child = root_ptr->left( );
	tree_clear( child );
	child = root_ptr->right( );
	tree_clear( child );
	delete root_ptr;
	root_ptr = NULL;
    }
}

expression_tree_node* tree_copy(const expression_tree_node* root_ptr) {
    expression_tree_node *l_ptr;
    expression_tree_node *r_ptr;

    if (root_ptr == NULL)
	return NULL;
    else {
	l_ptr = tree_copy( root_ptr->left( ) );
	r_ptr = tree_copy( root_ptr->right( ) );
	return 
	new expression_tree_node( root_ptr->data( ), l_ptr, r_ptr);
    }
}

size_t tree_size(const expression_tree_node* node_ptr) {
    if (node_ptr == NULL)
	return 0;
    else 
	return 
	1 + tree_size(node_ptr->left( )) + tree_size(node_ptr->right( ));
}    

#endif

