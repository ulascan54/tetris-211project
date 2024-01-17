#pragma once
#include "Node.h"
#include <iostream>
#include <exception>

template <typename T>
class ULList
{
private:
    Node<T> *head;
    Node<T> *tail;
    int s;
    Node<T> *getNode(const int index) const;

public:
    ULList() : head(nullptr), tail(nullptr), s(0) {}

    ~ULList()
    {
        clear();
    }

    ULList(const ULList<T> &other);

    T &operator[](int index)
    {
        return getNode(index)->data;
    }

    T get_head() const
    {
        if (head)
            return head->data;
        else
            throw std::out_of_range("List is empty");
    }

    T get_tail() const
    {
        if (tail)
            return tail->data;
        else
            throw std::out_of_range("List is empty");
    }

    Node<T> *begin() const
    {
        return head;
    }

    Node<T> *end() const
    {
        return tail;
    }

    void push_back(T val);

    void push_front(T val);

    void pop_back();

    void pop_front();

    void insert(T val, int index);

    void remove(int index);

    void clear();

    int size() const
    {
        return s;
    }

    void reverse();

    bool empty() const
    {
        return s == 0;
    }

    ULList<T> &operator=(const ULList<T> &other);

    template <typename U>
    friend std::ostream &operator<<(std::ostream &os, const ULList<U> &list);
};
