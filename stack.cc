#include <iostream>
#include <cassert>
#include "stack.h"

stack::node::node() {}  // node constructor leaving fields uninitialized
stack::node::node(const element & item, node * n) : data(item), next (n) {}

stack::stack() {
  _top = nullptr;
}

//CITE: Conversation with Julia Barkan '23 (CS 111 Student)
//DESC: Julia helped me with my node constructions (I called them incorrectly)
void stack::push(const element & e)
{
  node *baby = new node();
  baby -> data = e;
  baby -> next = _top;
  _top = baby;
}

void stack::pop()
{
  if(!empty()){
  node *p = new node;
  p = _top;
  _top = _top -> next;
  delete p;
  }
}

stack::element stack::top() const
{
  assert(!empty());
  return _top -> data;
}

bool stack::empty() const
{
  return _top == nullptr;
}
