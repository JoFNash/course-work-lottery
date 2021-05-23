#include "../headers/Generator.h"

Ticket	*TicketsGenerator::generate(const LotterySettings& settings) const
{
	Ticket	*new_ticket;
	static int ticket_ID = 0;
	int secret_numbers_amount;
	int	generated_number;

	secret_numbers_amount = settings.get_numbers_amount();
	new_ticket = new Ticket(secret_numbers_amount);
	if (!new_ticket)
		return (nullptr);
	new_ticket->set_id(ticket_ID);

    std::random_device random_device;
    std::mt19937 generator(random_device());
	std::uniform_int_distribution<> distribution(MIN_RANGE, MAX_RANGE);

	for (int i = 0; i < secret_numbers_amount; i++)
	{
		generated_number = distribution(generator);
		if (new_ticket->check_repeats_in_numbers(generated_number) == true)
			while (new_ticket->check_repeats_in_numbers(generated_number) != false)
				generated_number = distribution(generator);
		new_ticket->insert_number(generated_number);
	}
	ticket_ID++;
	return (new_ticket);
}

Product	*TicketsGeneratorCreator::factory_method() const
{
	return (new TicketsGenerator());
}
