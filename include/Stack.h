#pragma once
#include "Node.h"
#include "LinkedList.h"
#include <iostream>

template <typename T>
class Stack
{
private:
    LinkedList<T> list;

public:
    Stack() : list(), size(0) {}

    ~Stack() {}

    void push(T val)
    {
        list.addToHead(val);
        size++;
    }

    void pop()
    {
        if (!isEmpty())
        {
            list.removeFromHead();
            size--;
        }
    }

    T top()
    {
        if (!isEmpty())
        {
            return list.getHead()->getData();
        }

        return T();
    }

    bool isEmpty()
    {
        return size == 0;
    }

    int getSize()
    {
        return size;
    }

    void print()
    {
        list.print();
    }

    friend std::ostream &operator<<(std::ostream &os, const Stack<T> &stack)
    {
        os << "Stack: ";
        stack.list.print(os);
        return os;
    }
};
