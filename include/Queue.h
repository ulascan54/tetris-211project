#pragma once
#include "LinkedList.h"
#include "Node.h"
#include <iostream>

template <typename T>
class Queue
{
private:
    LinkedList<T> list;
    int size;

public:
    Queue() : list(), size(0) {}

    ~Queue() {}

    void enqueue(T val)
    {
        list.addToTail(val);
        size++;
    }

    void dequeue()
    {
        if (!isEmpty())
        {
            list.removeFromHead();
            size--;
        }
    }

    T front()
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

    friend std::ostream &operator<<(std::ostream &os, const Queue<T> &queue)
    {
        os << "Queue: ";
        queue.list.print(os);
        return os;
    }
};
