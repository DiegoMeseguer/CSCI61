#include <iostream>
#include <string>
#include "expression_tree.h"
#include "expression_node.h"
using namespace std;



int main() {

	//Build an expression tree using postfix expression
	cout<<"==Build an expression tree using postfix expression=="<<endl;
	string sample("8 9 2 + *");
	cout<<"First Postfix Expression: "<<sample<<endl;
	expression_tree a(sample);
	a.print_expression_tree();

	string sample2("3 9 * 5 1 + * 7 *");
	cout<<"Second Postfix Expression: "<<sample2<<endl<<endl;
	expression_tree b(sample2);
	b.print_expression_tree();

	//Evaluate expression tree
	cout<<"==Evaluate the expression tree=="<<endl;
	string sample3("7");
	expression_tree oneNode(sample3);
	cout<<"Result of expression tree when tree has only one node is: "<<oneNode.eval_expression_tree()<<endl;

	cout<<"Result of first postfix expression tree is: "<<a.eval_expression_tree()<<endl;
	cout<<"Result of second postfix expression tree is "<<b.eval_expression_tree()<<endl;	

	return 0;
}

