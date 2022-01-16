#pragma once

struct stack;
void create_stack(stack** s);

void add_elStack(stack** s, int el);
int checkEmpty(stack* s);

int take_elStack(stack** s);



void printStack(stack* s);
