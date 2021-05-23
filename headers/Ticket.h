#pragma once

#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <ostream>

class Ticket
{
private:
	int id;
	int prize;
	int available_numbers;
	std::vector<int> secret_numbers;

public:
	Ticket(int n) : available_numbers(n), id(0) , prize(0)
	{}
	~Ticket()
	{}

	int	get_id() const;
	void set_id(const int& value);
	int	get_prize() const;
	void set_prize(const int& value);
	int	get_numbers_amount() const;
	void update_available_numbers();
	void insert_number(const int& value);
	bool check_repeats_in_numbers(const int& value) const;
	bool equility_of_numbers(const std::vector<int>& vec) const;
	std::ostream& print_info(std::ostream& stream);
};
