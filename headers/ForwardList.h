#pragma once

#include "ForwardListNode.h"

template <typename T>
class ForwardList
{
private:
	Node<T>	*head;
	int length;

	Node<T>	*create_new_node(const T& value);

public:
	class iterator
	{
	private:
		Node<T>	*ptr;

	public:
		iterator() : ptr(nullptr) {}
		iterator(Node<T> *ptr) : ptr(ptr) {}
		iterator(const iterator& iter) : ptr(iter.ptr) {}
		~iterator() {}

		T& operator*()
		{
			return (ptr->data);
		}
		bool operator==(const iterator& rhs) const
		{
			return (this->ptr == rhs.ptr);
		}
		bool operator!=(const iterator& rhs) const
		{
			return (this->ptr != rhs.ptr);
		}
		iterator& operator=(const iterator& rhs)
		{
			this->ptr = rhs.ptr; return (*this);
		}
		iterator& operator++()
		{
			this->ptr = this->ptr->next; return (*this);
		}
		iterator operator++(int)
		{
			iterator copy = *this;
			this->ptr = this->ptr->next;
			return (copy);
		}
	};
		
	ForwardList();
	~ForwardList();

	int size() const;
	bool empty() const;
	T& front();		
	T& back();
	void clear();
	void push_back(const T& value);
	void pop_back();
	iterator begin() const;
	iterator end() const;
	iterator find(const T& value) const;
};

template <typename T>
ForwardList<T>::ForwardList()
{
	head = nullptr;
	length = 0;
}

template <typename T>
ForwardList<T>::~ForwardList()
{
	clear();
}

template <typename T>
Node<T>	*ForwardList<T>::create_new_node(const T& value)
{
	Node<T>	*new_node = nullptr;

	new_node = new Node<T>(value);
	if (!new_node)
		return nullptr;
	return new_node;
}

template <typename T>
int	ForwardList<T>::size() const
{
	return length;
}

template <typename T>
bool ForwardList<T>::empty() const
{
	return head == nullptr;
}

template <typename T>
T& ForwardList<T>::front()
{
	return head->data;
}

template <typename T>
T& ForwardList<T>::back()
{
	Node<T>	*temp_ptr;

	temp_ptr = head;
	while (temp_ptr->next != nullptr)
	{
		temp_ptr = temp_ptr.next;
	}
	return temp_ptr->data;
}

template <typename T>
void ForwardList<T>::clear()
{
	Node<T>	*tempptr;

	if (head != nullptr)
	{
		while (head != nullptr)
		{
			tempptr = head;
			head = head->next;
			delete tempptr;
		}
		head = nullptr;
		length = 0;
	}
}

template <typename T>
void ForwardList<T>::push_back(const T& value)
{
	Node<T> *temp_ptr;
	Node<T>	*new_node = nullptr;

	new_node = create_new_node(value);
	if (new_node != nullptr)
	{
		if (!head)
			head = new_node;
		else
		{
			temp_ptr = head;
			while (temp_ptr->next != nullptr)
			{
				temp_ptr = temp_ptr->next;
			}
			temp_ptr->next = new_node;
		}
		length++;
	}
}

template <typename T>
void ForwardList<T>::pop_back()
{
	Node<T>	*temp_ptr;

	if (!head)
		return ;
	else
	{
		temp_ptr = head;
		while (temp_ptr->next != nullptr)
		{
			temp_ptr = temp_ptr->next;
		}
		delete temp_ptr;
	}
}

template <typename T>
typename ForwardList<T>::iterator ForwardList<T>::begin() const
{
	return iterator(head);
}

template <typename T>
typename ForwardList<T>::iterator ForwardList<T>::end() const
{
	return nullptr;
}

template <typename T>
typename ForwardList<T>::iterator ForwardList<T>::find(const T& value) const
{
	ForwardList<T>::iterator	iter;

	iter = begin();
	while (iter != end())
	{
		if (*iter == value)
			return (iter);
		iter++;
	}
	return end();
}
