#include "head.h"
#include <iostream>
using namespace std;

void printStack(stack* s);
int main() {
    stack* s;
    create_stack(&s);
    cout << "Creating dynamic stack:\n";
    printStack(s);
    cout << "Checking if dynamic stack is empty:\n";
    cout << checkEmpty(s) << "\n";
    add_elStack(&s, 5);
    add_elStack(&s, 6);
    add_elStack(&s, 7);
    cout << "Adding elements a=5, a=6, a=7 to dynamic stack:\n";
    printStack(s);
    cout << "Taking element from dynamic stack:\n";
    cout << take_elStack(&s) << "\n";
    cout << "Stack after taking element:\n";
    printStack(s);

}