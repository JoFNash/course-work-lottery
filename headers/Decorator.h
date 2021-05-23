#include "ForwardList.h"
#include <iostream>
#include <memory>
#include <vector>
#include <list>

template <template <typename T, class _allocator = std::allocator<T>> 
	class Container, typename T>											
class Interface
{
private:
	Container<T> *decorated_container;

public:
	Interface(Container<T> *container) : decorated_container(container)
	{}
	~Interface()
	{}

	int size() const
	{
		return this->decorated_container->size();
	}

	bool empty() const
	{
		return this->decorated_container->empty();
	}

	void insert_back(const T& value)
	{
		this->decorated_container->insert_back(value);
	}

	void remove_back()
	{
		this->decorated_container->remove_back();
	}

	void clear_memory()
	{
		this->decorated_container->clear_memory();
	}

	void clear()
	{
		this->decorated_container->clear();
	}

	void print(std::ostream& stream) const
	{
		this->decorated_container->print(stream);
	}

	void check_repetitions(const int& value)
	{
		this->decorated_container->check_repetitions(value);
	}

	int find_winners() const
	{
		return this->decorated_container->find_winners();
	}

	void set_winners_prize(const int& value)
	{
		this->decorated_container->set_winners_prize(value);
	}

	void find_by_id(const int& value) const
	{
		this->decorated_container->find_by_id(value);
	}

	void find_by_prize(const int& value) const
	{
		this->decorated_container->find_by_prize(value);
	}

	void find_by_numbers(const std::vector<int>& vec) const
	{
		this->decorated_container->find_by_numbers(vec);
	}
};

template <typename T, class _allocator = std::allocator<T>>
class	ListDecorator
{
private:
	std::list<T> list;

public:
	ListDecorator()
	{}
	
	~ListDecorator()
	{}
	
	int	size() const
	{
		return list.size();
	}

	bool empty() const
	{
		return list.empty();
	}

	void insert_back(const T& value)
	{
		list.push_back(value);
	}

	void remove_back()
	{
		list.pop_back();
	}

	void clear_memory()
	{
		typename std::list<T>::iterator	iter;

		if (list.empty())
			return ;
		iter = list.begin();
		while (iter != list.end())
		{
			delete(*iter);
			iter++;
		}
	}

	void clear()
	{
		if (list.empty())
			return ;
		this->list.clear();
	}

	void print(std::ostream& stream) const 
	{
		typename std::list<T>::const_iterator	iter;

		iter = list.begin();
		while (iter != list.end())
		{
			(*iter)->print_info(stream);
			iter++;
		}
	}

	void check_repetitions(const int& value)
	{
		typename std::list<T>::iterator	iter;

		iter = list.begin();
		while (iter != list.end())
		{
			if ((*iter)->check_repeats_in_numbers(value))
				(*iter)->update_available_numbers();
			iter++;
		}
	}

	int	 find_winners() const
	{
		typename std::list<T>::const_iterator	iter;
		int								winners;

		winners = 0;
		iter = list.begin();
		while (iter != list.end())
		{
			if ((*iter)->get_numbers_amount() == 0)
				winners++;
			iter++;
		}
		return winners;
	}

	void set_winners_prize(const int& value)
	{
		typename std::list<T>::iterator	iter;

		iter = list.begin();
		std::cout << "\n";
		while (iter != list.end())
		{
			if ((*iter)->get_numbers_amount() == 0)
			{
				(*iter)->set_prize(value);
				std::cout << "Winners is ID: ";
				(*iter)->print_info(std::cout);
			}
			iter++;
		}
		std::cout << "\n";
	}

	void find_by_id(const int& value) const
	{
		typename std::list<T>::const_iterator	iter;
		int						found_counter;

		found_counter = 0;
		iter = list.begin();
		while (iter != list.end())
		{
			if ((*iter)->get_id() == value)
			{
				std::cout << "\nFound ticket with ID ";
				(*iter)->print_info(std::cout);
				found_counter++;
				break ;
			}
			iter++;
		}
		if (found_counter == 0)
			std::cout << "\nNo tickets found for the specified ID\n";
	}

	void find_by_prize(const int& value) const
	{
		typename std::list<T>::const_iterator	iter;
		int						found_counter;

		found_counter = 0;
		iter = list.begin();
		while (iter != list.end())
		{
			if ((*iter)->get_prize() == value)
			{
				std::cout << "\nFound ticket with ID ";
				(*iter)->print_info(std::cout);
				found_counter++;
				break ;
			}
			iter++;
		}
		if (found_counter == 0)
			std::cout << "\nNo tickets found for the specified prize\n";
	}

	void find_by_numbers(const std::vector<int>& vec) const
	{
		typename std::list<T>::const_iterator	iter;
		int						found_counter;

		iter = list.begin();
		found_counter = 0;
		while (iter != list.end())
		{
			if ((*iter)->equility_of_numbers(vec))
			{
				std::cout << "\nFound ticket with ID ";
				(*iter)->print_info(std::cout);
				found_counter++;
				break ;
			}
			iter++;
		}
		if (found_counter == 0)
			std::cout << "\nNo tickets found for the given secret numbers\n";
	}
};

template <typename T, class _allocator = std::allocator<T>>
class	ForwardListDecorator
{
private:
	ForwardList<T>	list;

public:
	ForwardListDecorator()
	{}
	
	~ForwardListDecorator()
	{}

	int	size() const
	{
		return list.size();
	}

	bool empty() const
	{
		return list.empty();
	}

	void insert_back(const T& value)
	{
		list.push_back(value);
	}
		
	void remove_back()
	{
		list.pop_back();
	}

	void clear_memory()
	{
		typename ForwardList<T>::iterator	iter;

		if (list.empty())
			return ;
		iter = list.begin();
		while (iter != list.end())
		{
			delete(*iter);
			iter++;
		}
	}

	void clear()
	{
		if (list.empty())
			return ;
		this->list.clear();
	}

	void print(std::ostream& stream) const
	{
		typename ForwardList<T>::iterator	iter;

		iter = list.begin();
		while (iter != list.end())
		{
			(*iter)->print_info(stream);
			iter++;
		}
	}

	void check_repetitions(const int& value)
	{
		typename ForwardList<T>::iterator	iter;

		iter = list.begin();
		while (iter != list.end())
		{
			if ((*iter)->check_repeats_in_numbers(value))
				(*iter)->update_available_numbers();
			iter++;
		}
	}

	int	find_winners() const
	{
		typename ForwardList<T>::iterator	iter;
		int						winners;

		winners = 0;
		iter = list.begin();
		while (iter != list.end())
		{
			if ((*iter)->get_numbers_amount() == 0)
				winners++;
			iter++;
		}
		return winners;
	}

	void set_winners_prize(const int& value)
	{
		typename ForwardList<T>::iterator	iter;

		iter = list.begin();
		std::cout << "\n";
		while (iter != list.end())
		{
			if ((*iter)->get_numbers_amount() == 0)
			{
				(*iter)->set_prize(value);
				std::cout << "Winners is ID: ";
				(*iter)->print_info(std::cout);
			}
			iter++;
		}
		std::cout << "\n";
	}

	void find_by_id(const int& value) const
	{
		typename ForwardList<T>::iterator	iter;
		int						found_counter;

		found_counter = 0;
		iter = list.begin();
		while (iter != list.end())
		{
			if ((*iter)->get_id() == value)
			{
				std::cout << "\nFound ticket with ID ";
				(*iter)->print_info(std::cout);
				found_counter++;
				break ;
			}
			iter++;
		}
		if (found_counter == 0)
			std::cout << "\nNo tickets found for the specified ID\n";
	}

	void find_by_prize(const int& value) const
	{
		typename ForwardList<T>::iterator	iter;
		int						found_counter;

		found_counter = 0;
		iter = list.begin();
		while (iter != list.end())
		{
			if ((*iter)->get_prize() == value)
			{
				std::cout << "\nFound ticket with ID ";
				(*iter)->print_info(std::cout);
				found_counter++;
				break ;
			}
			iter++;
		}
		if (found_counter == 0)
			std::cout << "\nNo tickets found for the specified prize\n";
	}

	void find_by_numbers(const std::vector<int>& vec) const
	{
		typename ForwardList<T>::iterator	iter;
		int						found_counter;

		iter = list.begin();
		found_counter = 0;
		while (iter != list.end())
		{
			if ((*iter)->equility_of_numbers(vec))
			{
				std::cout << "\nFound ticket with ID ";
				(*iter)->print_info(std::cout);
				found_counter++;
				break ;
			}
			iter++;
		}
		if (found_counter == 0)
			std::cout << "\nNo tickets found for the given secret numbers\n";
	}
};
