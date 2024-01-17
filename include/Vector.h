#pragma once

#include <SFML/Graphics.hpp>

template <typename T>
class vector
{
    T *arr;
    int capacity;
    int current;

public:
    vector();
    ~vector();

    void push_back(T data);
    T get(int index);
    void pop_back();

    T *begin();
    T *end();
    const T *begin() const;
    const T *end() const;

    int size();
    int getcapacity();
    void clear();
    bool empty();

    void insert(T data, int index);
    void erase(int index);
    void erase(T *pos);

    T &operator[](int index);
    vector<T> &operator=(const vector<T> &other);
};
