#include "./headers/Ticket.h"
#include "./headers/Generator.h"
#include "./headers/Settings.h"
#include "./headers/Decorator.h"
#include <memory>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

void user_options()
{
	cout << "\n";
	cout << "1. Start lottery\n";
	cout << "2. Search ticket by ID\n";
	cout << "3. Search tickets by prize\n";
	cout << "4. Search by numbers\n";
	cout << "5. Save info and exit\n\n";
	cout << "Enter operation: ";
}

void print_game_info(const int& players,
											const int& prize_pool)
{
	cout << "\nLottery players: " << players << "\n";
	cout << "Prize pool: " << prize_pool << "\n";
}

template <template <typename T, class _allocator = std::allocator<T> >
	class Container, typename T>
void begin_lottery(const LotterySettings& settings,
							Interface<Container, T>& tickets_container)
{
	const int min_players = settings.get_tickets_amount() * 0.5;
	const int max_players = settings.get_tickets_amount();
	int active_players;
	int prize_pool;

    std::random_device random_device;
    std::mt19937 generator(random_device());
	std::uniform_int_distribution<> distribution1(min_players, max_players);
	std::uniform_int_distribution<> distribution2(MIN_RANGE, MAX_RANGE);

	active_players = distribution1(generator);
	prize_pool = (active_players * settings.get_ticket_price()) * 0.5;
	print_game_info(active_players, prize_pool);

	std::vector<int>::iterator iter;
	std::vector<int> numbers_drawn_vec;
	int number_drawn;

	for (int i = 0; i < settings.get_numbers_amount(); i++)
	{
		number_drawn = active_players = distribution2(generator);
		iter = std::find(numbers_drawn_vec.begin(),
									numbers_drawn_vec.end(), number_drawn);
		while (iter != numbers_drawn_vec.end())
		{
			number_drawn = distribution2(generator);
			iter = std::find(numbers_drawn_vec.begin(),
									numbers_drawn_vec.end(), number_drawn);
		}
		numbers_drawn_vec.push_back(number_drawn);
		cout << "\nNumber drawn - " << number_drawn << "!\n";	
		tickets_container.check_repetitions(number_drawn);
	}
	int	winners_amount = tickets_container.find_winners();
	int	prize_for_winner;

	if (winners_amount != 0)
	{
		prize_for_winner = prize_pool / winners_amount;
		cout << "\nWinners:\n";
		tickets_container.set_winners_prize(prize_for_winner);
	}
}

template <template <typename T, class _allocator = std::allocator<T> >
	class Container, typename T>
void generate_tickets(const LotterySettings& settings,
							Interface<Container, T>& tickets_container)
{
	TicketsGeneratorCreator	gen_creator;
    Creator* 			creator = &gen_creator;
	Product* 			gen = creator->factory_method();

	if (!gen)
		return ;
	for (int i = 0; i < settings.get_tickets_amount(); i++)
	{
		Ticket	*new_ticket = gen->generate(settings);
		if (new_ticket != nullptr)
			tickets_container.insert_back(new_ticket);
	}
	delete gen;
}

template <template <typename T, class _allocator = std::allocator<T> >
	class Container, typename T>
void search_by_id(const Interface<Container, T>& tickets_container)
{
	int	searching_ID;

	cout << "\nEnter ID = ";
	std::cin >> searching_ID;
	tickets_container.find_by_id(searching_ID);
}

template <template <typename T, class _allocator = std::allocator<T> >
	class Container, typename T>
void search_by_prize(const Interface<Container, T>& tickets_container)
{
	int	searching_prize;

	cout << "\nEnter concrete prize = ";
	std::cin >> searching_prize;
	tickets_container.find_by_prize(searching_prize);
}

template <template <typename T, class _allocator = std::allocator<T> >
	class Container, typename T>
void search_by_secret_numbers(const LotterySettings& settings,
							const Interface<Container, T>& tickets_container)
{
	int				input_number;
	int				numbers_amount = settings.get_numbers_amount();
	std::vector<int>	secret_numbers_vec;

	cout << "\nEnter " << numbers_amount << " secret numbers = ";
	for (int i = 0; i < numbers_amount; i++)
	{
		std::cin >> input_number;
		secret_numbers_vec.push_back(input_number);
	}
	tickets_container.find_by_numbers(secret_numbers_vec);
}

template <template <typename T, class _allocator = std::allocator<T> >
	class Container, typename T>
void save_to_file(const LotterySettings& settings,
							const Interface<Container, T>& tickets_container)
{
	const string filename = "lottery_info.txt";
	ofstream stream(filename);

	if (stream.is_open())
	{
		stream << "Lottery info:\n";
		stream << "All tickets amount - "
				<< settings.get_tickets_amount() << "\n";
		stream << "One ticket price - "
				<< settings.get_ticket_price() << "\n";
		stream << "Numbers amount in every ticket - "
				<< settings.get_numbers_amount() << "\n";
		stream << "Tickets info:\n";
		tickets_container.print(stream);	
		stream.close();
	}
}

int main()
{
	// ForwardListDecorator<Ticket *>			tickets_list;
	// Interface<ForwardListDecorator, Ticket *>	tickets_container(&tickets_list);
	
	ListDecorator<Ticket *>				tickets_list;
	Interface<ListDecorator, Ticket *>	tickets_container(&tickets_list);
	
	LotterySettings settings;
	int tickets_amount, price;

	cout << "\n=================== Lottery Settings ===================\n";
	cout << "Enter tickets amount = ";
	cin >> tickets_amount;
	cout << "Enter ticket price = ";
	cin >> price;

	if (tickets_amount < 1 || price < 1)
	{
		cout << "Incorrect settings\n";
		return -1;
	}
	settings.set_numbers_amount(4);
	settings.set_tickets_amount(tickets_amount);
	settings.set_ticket_price(price);

	generate_tickets(settings, tickets_container);
	// tickets_container.print(cout);

	if (tickets_container.empty())
		return -1;
	
	int user_operation = 0;
	bool is_finished	= false;

	while (user_operation != 5)
	{
		user_options();
		std::cin >> user_operation;
		if (user_operation == 1 && !is_finished)
		{
			is_finished = true;
			begin_lottery(settings, tickets_container);
		}
		else if (user_operation == 2 && is_finished)
			search_by_id(tickets_container);
		else if (user_operation == 3 && is_finished)
			search_by_prize(tickets_container);
		else if (user_operation == 4 && is_finished)
			search_by_secret_numbers(settings, tickets_container);
		else if (user_operation == 5)
			break ;
		else
			cout << "\nIncorrect command\n";
	}
	if (is_finished)
	{
		save_to_file(settings, tickets_container);
	}
	tickets_container.clear();
	tickets_container.clear_memory();
	return 0;
}
