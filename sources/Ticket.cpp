#include "../headers/Ticket.h"

int	Ticket::get_prize() const
{
	return (prize);
}

int	Ticket::get_id() const
{
	return (this->id);
}

int	Ticket::get_numbers_amount() const
{
	return (available_numbers);
}

void Ticket::update_available_numbers()
{
	if (available_numbers == 0)
		return ;
	this->available_numbers--;
}

void Ticket::set_prize(const int& value)
{
	this->prize = value;
}

void Ticket::set_id(const int& value)
{
	this->id = value;
}

void Ticket::insert_number(const int& value)
{
	if (this->secret_numbers.size() == this->available_numbers)
		return ;
	this->secret_numbers.push_back(value);
}

bool Ticket::check_repeats_in_numbers(const int& value) const
{
	for (int i = 0; i < this->secret_numbers.size(); i++)
		if (secret_numbers[i] == value)
			return (true);
	return (false);
}

bool Ticket::equility_of_numbers(const std::vector<int>& vec) const
{
	std::vector<int>::const_iterator	it;
	std::vector<int>					secret_numbers_copy;

	if (this->secret_numbers.size() != vec.size())
		return (false);
	secret_numbers_copy = this->secret_numbers;
	for (int i = 0; i < vec.size(); i++)
	{
		it = std::find(secret_numbers_copy.begin(),
									secret_numbers_copy.end(), vec[i]);
		if (it == secret_numbers_copy.end())
			return (false);
		secret_numbers_copy.erase(it);
	}
	return (true);
}

std::ostream& Ticket::print_info(std::ostream& stream)
{
	stream << "Number - " << id << " =";
	for (int i = 0; i < secret_numbers.size(); i++)
	{
		stream << " " << secret_numbers[i];
	}
	stream << "\tprize = " << prize << "\n";
	return (stream);
}
