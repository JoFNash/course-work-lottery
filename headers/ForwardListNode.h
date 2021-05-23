#pragma once

template <typename T>
class Node
{
template <typename U> friend class ForwardList;

private:
	T data;
	Node *next;

public:
	Node(const T& value);
	Node(T&& value);
	~Node() {};
};

template <typename T>
Node<T>::Node(const T& value)
{
	this->data = value;
	this->next = nullptr;
}

template <typename T>
Node<T>::Node(T&& value)
{
	this->data = move(value);
	this->next = nullptr;
}
