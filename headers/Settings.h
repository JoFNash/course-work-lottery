#pragma once

#define MIN_RANGE 1
#define MAX_RANGE 99

#include <stdlib.h>

class	LotterySettings
{
private:
	int	numbers_amount;
	int	tickets_amount;
	int	ticket_price;

public:
	LotterySettings();
	~LotterySettings() {}

	void set_ticket_price(const int& value);
	void set_tickets_amount(const int& value);
	void set_numbers_amount(const int& value);
	int	get_ticket_price() const;
	int	get_tickets_amount() const;
	int	get_numbers_amount() const;
};
