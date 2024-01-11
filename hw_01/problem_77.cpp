#include <cctype>     // Provides isdigit
#include <cstdlib>    // Provides EXIT_SUCCESS
#include <cstring>    // Provides strchr
#include <iostream>   // Provides cout, cin, peek, ignore
#include <stack>      // Provides the stack template class
using namespace std;

const char DECIMAL = '.';
const char RIGHT_PARENTHESIS = ')';

double read_and_evaluate(istream& ins);
void evaluate_stack_tops(stack<double>& numbers, stack<char>& operations);
void new_line(); //consumes a newline

int main() {

    double answer;
    string ans;

    do
    {
        cout << "Type a fully parenthesized arithmetic expression:" << endl;
        answer = read_and_evaluate(cin);
        cout << "That evaluates to " << answer << endl;
        cout << "Would you like to evluate a new expression? (yes/no)" << endl;
        cin>>ans;
        new_line();
    } while ((ans[0] == 'Y') || (ans[0] == 'y'));
  
    return 0;
}

void new_line() {
    char temp;

    do
    {
        cin.get(temp);
    } while (temp != '\n');
}

double read_and_evaluate(istream& ins) {

    stack<double> numbers;
    stack<char> operations;
    double number;
    char symbol;
    
    while (ins && ins.peek() != '\n') {
        if (isdigit(ins.peek()) || (ins.peek() == DECIMAL))
        {
            ins >> number;
            numbers.push(number);
        }
        else if (strchr("&|", ins.peek()) != NULL)
        {
            ins >> symbol;
            ins >> symbol;
            operations.push(symbol);
        }


        else if (strchr("!", ins.peek()) != NULL)
        {
            ins >> symbol;
            operations.push(symbol);
        }







        else if (ins.peek() == RIGHT_PARENTHESIS)
        {
            ins.ignore();
            evaluate_stack_tops(numbers, operations);
        }
        else
            ins.ignore();
    }

    return numbers.top();
}

void evaluate_stack_tops(stack<double>& numbers, stack<char>& operations) {

    double operand1, operand2;

    operand2 = numbers.top();
    numbers.pop();
    operand1 = numbers.top();
    numbers.pop();
    switch (operations.top())
    {
        case '+': numbers.push(operand1 + operand2);
                  break;
        case '-': numbers.push(operand1 - operand2);
                  break;
        case '*': numbers.push(operand1 * operand2);
                  break;
        case '/': numbers.push(operand1 / operand2);
                  break;
    }
    operations.pop();
}

