#include "LinkedList.h"
#include <iostream>
#include <exception>
#include <stdexcept>
#include "Piece.h"
#include "Position.h"

template <typename T>
Node<T> *ULList<T>::getNode(const int index) const
{
    if (index < 0 || index >= s)
    {
        throw std::out_of_range("Index out of range");
    }

    Node<T> *temp = head;
    for (int i = 0; i < index; i++)
    {
        temp = temp->next;
    }

    return temp;
}

template <typename T>
void ULList<T>::push_back(T val)
{
    Node<T> *temp = new Node<T>(val);

    if (head == nullptr)
    {
        head = temp;
        tail = temp;
    }
    else
    {
        tail->next = temp;
        tail = temp;
    }

    s++;
}

template <typename T>
void ULList<T>::push_front(T val)
{
    Node<T> *temp = new Node<T>(val);

    if (head == nullptr)
    {
        head = temp;
        tail = temp;
    }
    else
    {
        temp->next = head;
        head = temp;
    }

    s++;
}

template <typename T>
void ULList<T>::pop_back()
{
    if (head == nullptr)
    {
        throw std::out_of_range("List is empty");
    }
    else if (head == tail)
    {
        delete head;
        head = nullptr;
        tail = nullptr;
    }
    else
    {
        Node<T> *temp = head;
        while (temp->next != tail)
        {
            temp = temp->next;
        }

        delete tail;
        tail = temp;
        tail->next = nullptr;
    }

    s--;
}

template <typename T>
void ULList<T>::pop_front()
{
    if (head == nullptr)
    {
        throw std::out_of_range("List is empty");
    }
    else if (head == tail)
    {
        delete head;
        head = nullptr;
        tail = nullptr;
    }
    else
    {
        Node<T> *temp = head;
        head = head->next;
        delete temp;
    }

    s--;
}

template <typename T>
void ULList<T>::insert(T val, int index)
{
    if (index < 0 || index > s)
    {
        throw std::out_of_range("Index out of range");
    }

    if (index == 0)
    {
        push_front(val);
    }
    else if (index == s)
    {
        push_back(val);
    }
    else
    {
        Node<T> *temp = new Node<T>(val);
        Node<T> *prev = getNode(index - 1);

        temp->next = prev->next;
        prev->next = temp;

        s++;
    }
}

template <typename T>
void ULList<T>::remove(int index)
{
    if (index < 0 || index >= s)
    {
        throw std::out_of_range("Index out of range");
    }

    if (index == 0)
    {
        pop_front();
    }
    else if (index == s - 1)
    {
        pop_back();
    }
    else
    {
        Node<T> *prev = getNode(index - 1);
        Node<T> *temp = prev->next;

        prev->next = temp->next;
        delete temp;

        s--;
    }
}

template <typename T>
void ULList<T>::clear()
{
    while (head != nullptr)
    {
        pop_front();
    }
}

template <typename T>
void ULList<T>::reverse()
{
    if (head == nullptr || head == tail)
    {
        return;
    }

    Node<T> *prev = nullptr;
    Node<T> *curr = head;
    Node<T> *next = nullptr;

    while (curr != nullptr)
    {
        next = curr->next;
        curr->next = prev;

        prev = curr;
        curr = next;
    }

    tail = head;
    head = prev;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const ULList<T> &list)
{
    Node<T> *temp = list.head;
    while (temp != nullptr)
    {
        os << temp->data << " ";
        temp = temp->next;
    }

    return os;
}

template <typename T>
ULList<T> &ULList<T>::operator=(const ULList<T> &other)
{
    if (this != &other)
    {
        clear();

        Node<T> *temp = other.head;
        while (temp != nullptr)
        {
            push_back(temp->data);
            temp = temp->next;
        }
    }

    return *this;
}

template <typename T>
ULList<T>::ULList(const ULList<T> &other)
{
    head = nullptr;
    tail = nullptr;
    s = 0;

    Node<T> *temp = other.head;
    while (temp != nullptr)
    {
        push_back(temp->data);
        temp = temp->next;
    }
}

template class ULList<sf::Text>;
template class ULList<sf::Color>;
template class ULList<sf::RectangleShape>;
template class ULList<Position>;
template class ULList<Piece>;
template class ULList<int>;