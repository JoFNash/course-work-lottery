#pragma once

#include "Ticket.h"
#include "Settings.h"
#include <stdlib.h>
#include <ctime>
#include <random>

class	Product
{
public:
	virtual Ticket	*generate(const LotterySettings& settings) const = 0;
	virtual ~Product() {}
};

class	TicketsGenerator : public Product
{
public:
	Ticket	*generate(const LotterySettings& settings) const override;
	~TicketsGenerator() {}
};

class	Creator
{
public:
	virtual Product	*factory_method() const = 0;
	virtual ~Creator() {};
};

class	TicketsGeneratorCreator : public Creator
{
public:
	Product	*factory_method() const override;
	~TicketsGeneratorCreator() {}
};
