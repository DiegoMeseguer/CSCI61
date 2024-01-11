#ifndef EXPRESSION_TREE_H
#define EXPRESSION_TREE_H
#include <cstdlib>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <string>
#include <stack>
#include "expression_node.h"

using namespace std;

const char MULT = '*';
const char PLUS = '+'; 

class expression_tree {
public:

	//CONSTRUCTORS
	expression_tree(string expression);
	expression_tree(expression_tree_node* value);

	//MEMBER FUNCTIONS
	void print_expression_tree() const;
	int eval_expression_tree();

private:

	//MEMBER VARIABLES
	expression_tree_node *root;
};

//IMPLEMENTATION OF NON MEMBER FUNCTIONS
int char_to_int(char x);

int char_to_int(char x) {
	int result;

	result = x - '0';

	return result;

}

//IMPLEMENTATION OF MEMBER FUNCTIONS


//We need this for the recursion
expression_tree::expression_tree(expression_tree_node* value) {
	root = value;
}


//We are assuming input is postfix where each operator/operand
//is separated by a whitespace, and that operands are single digits.
expression_tree::expression_tree(string expression) {
	stack<expression_tree_node*> temp;
	expression_tree_node *operandA, *operandB, *oper;

	//Special case when we are given the emptry string
	if(expression.empty()) {
		root = new expression_tree_node();
		return;
	}

	//Special case when there is a single number
	if(expression.length() == 1) {
		root = new expression_tree_node(expression[0]);
		return;
	}

	for (int i = 0; i < expression.length(); ++i) {
		if(isspace(expression[i]))
			continue;
		else if(expression[i] == MULT || expression[i] == PLUS) {
			operandA = temp.top();
			temp.pop();
			operandB = temp.top();
			temp.pop();
			oper = new expression_tree_node(expression[i], operandA, operandB);
			temp.push(oper);
		}
		else
			temp.push(new expression_tree_node(expression[i]));
	}

	root = oper;
}


int expression_tree::eval_expression_tree() {

	//Base Case
	if(tree_size(root) == 1)
		return char_to_int(root->data());

	if(root->data() == PLUS) {
		expression_tree leftOperand(root->left());
		expression_tree rightOperand(root->right());
		return (leftOperand.eval_expression_tree() + rightOperand.eval_expression_tree());
	}

	else {
		expression_tree leftOperand(root->left());
		expression_tree rightOperand(root->right());
		return (leftOperand.eval_expression_tree() * rightOperand.eval_expression_tree());
	}
}


void expression_tree::print_expression_tree() const {
	size_t count = 0;
	print(root, count);

}


#endif

