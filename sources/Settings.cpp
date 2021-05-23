#include "../headers/Settings.h"

LotterySettings::LotterySettings()
{
	tickets_amount = 0;
	ticket_price = 0;
	numbers_amount = 0;
}

void	LotterySettings::set_ticket_price(const int& value)
{
	this->ticket_price = value;
}

void	LotterySettings::set_tickets_amount(const int& value)
{
	this->tickets_amount = value;
}

void	LotterySettings::set_numbers_amount(const int& value)
{
	this->numbers_amount = value;
}

int	LotterySettings::get_ticket_price() const
{
	return (this->ticket_price);
}

int	LotterySettings::get_tickets_amount() const
{
	return (tickets_amount);
}

int	LotterySettings::get_numbers_amount() const
{
	return (numbers_amount);
}
