#include "Vector.h"


template <typename T>
vector<T>::vector()
{
    capacity = 1;
    current = 0;
    arr = nullptr;
}

template <typename T>
vector<T>::~vector()
{
    if (arr != nullptr)
    {
        delete[] arr;
    }
}

template <typename T>
void vector<T>::push_back(T data)
{
    if (arr == nullptr)
    {
        arr = new T[capacity];
    }
    else
    {
        if (current == capacity)
        {
            T *temp = new T[2 * capacity];

            for (int i = 0; i < capacity; i++)
            {
                temp[i] = arr[i];
            }

            delete[] arr;
            capacity *= 2;

            arr = temp;
        }

        arr[current] = data;
        current++;
    }
}

template <typename T>
T vector<T>::get(int index)
{
    if (index >= 0 && index < current)
    {
        return arr[index];
    }
    else
    {
        throw std::out_of_range("Index out of range");
    }
}

template <typename T>
void vector<T>::pop_back()
{
    if (current > 0)
    {
        current--;
    }
}

template <typename T>
T *vector<T>::begin()
{
    return arr;
}

template <typename T>
T *vector<T>::end()
{
    return arr + current;
}

template <typename T>
const T *vector<T>::begin() const
{
    return arr;
}

template <typename T>
const T *vector<T>::end() const
{
    return arr + current;
}

template <typename T>
int vector<T>::size()
{
    return current;
}

template <typename T>
int vector<T>::getcapacity()
{
    return capacity;
}

template <typename T>
void vector<T>::clear()
{
    current = 0;
}

template <typename T>
bool vector<T>::empty()
{
    return current == 0;
}

template <typename T>
void vector<T>::insert(T data, int index)
{
    if (index >= 0 && index <= current)
    {
        if (index == current)
        {
            push_back(data);
        }
        else
        {
            arr[index] = data;
        }
    }
}

template <typename T>
void vector<T>::erase(int index)
{
    if (index >= 0 && index < current)
    {
        if (index == current - 1)
        {
            pop_back();
        }
        else
        {
            for (int i = index; i < current - 1; i++)
            {
                arr[i] = arr[i + 1];
            }
            current--;
        }
    }
}

template <typename T>
void vector<T>::erase(T *pos)
{
    if (pos >= begin() && pos < end())
    {
        for (T *i = pos; i < end() - 1; i++)
        {
            *i = *(i + 1);
        }
        delete &arr[current - 1];
        current--;
    }
}

template <typename T>
T &vector<T>::operator[](int index)
{
    return arr[index];
}

template <typename T>
vector<T> &vector<T>::operator=(const vector<T> &other)
{
    if (this != &other)
    {
        if (arr != nullptr)
        {
            delete[] arr;
        }

        capacity = other.capacity;
        current = other.current;
        arr = new T[capacity];

        for (int i = 0; i < current; i++)
        {
            arr[i] = other.arr[i];
        }
    }
    return *this;
}

template class vector<sf::Text>;
template class vector<sf::Color>;
template class vector<sf::RectangleShape>;
template class vector<int>;
