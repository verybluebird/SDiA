#include <iostream>
using namespace std;

struct stack{
    int pole1;
    stack* pole2;
};

void create_stack(stack** s) {
    *s = NULL;
}

void add_elStack(stack** s, int el) {
    stack* a;
    a = new stack;

    a->pole2 = *s;
    a->pole1 = el;
    *s = a;
}
int checkEmpty(stack* s) {
    if (s == NULL) {
        return 1;
    }
    else {
        return 0;
    }
}

int take_elStack(stack** s) {   
    if (checkEmpty(*s)) {
        return 0;
    } else {
        int a;
        a = (*s)->pole1;
        *s = (*s)->pole2;
        return a;
    }
}



void printStack(stack* s) {
    cout << "Stack: ";
    if (checkEmpty(s)){
        cout <<"NULL\n";
    }
    else {
        while (!checkEmpty(s)) {
            cout << take_elStack(&s)<<" ";
        }
    }
    cout <<  "\n";
}


