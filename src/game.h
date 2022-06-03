#ifndef TERADE_GAME_H
#define TERADE_GAME_H

#include <iostream>
#include <string>
#include <memory>
#include <functional>
#include <map>

#include "view.h"
#include "portfolio.h"
#include "player.h"
#include "api.h"
#include "utils.h"
#include "transaction.h"
#include "output.h"
#include "timer.h"

enum class Error {
	NO_ERROR = 0, BAD_INPUT = 1, INSUFFICIENT_FUNDS = 2
};

constexpr int starting_cash = 10000;
constexpr int TIMER_INTERVAL_MS = 5000;

/*
 * game class is the main controller of the program.
 */
class game {
	private:
		player player_ {"default"};
		std::unique_ptr<view> view_ = nullptr;

		// Since the program cannot retireve data at runtime, there is a limited number of tokens supported.
		// To add more, just download the json file from the CoinGecko API containing all the historical price data
		// and make the appropriate modifications to CMakeLists.txt and then add the id of the token to the vector below.
		CoinGeckoApi api_ {{{"bitcoin"}, {"ethereum"}, {"cardano"}, {"dogecoin"}, {"binancecoin"}, {"stellar"}, {"maker"}}};

		Error error_ = Error::NO_ERROR;
		
		/*
		 * This is not the epoch time, but it's an index for the JSON array in the data files.
		 * so index 1 is 1st Jan 2018, 16pm
		 */
		long epoch_time_index_ = 1;

		std::string file_path_;
		Timer timer_;

		// A jump table to execute commands supported by the program
		std::map<std::string, std::function<void(void)>> commands_;

		int get_input_num(const std::string& prompt);
		transaction get_input_tx();
		void evaluate_tx_error(transaction& tx);
		void execute_transaction(transaction& tx, std::function<void(const transaction&)>);

		/*
		 * Populate the main list with various data.
		 * show_portfolio()     --> displays all the assets and the total value of the active portfolio
		 * show_portfolios()    --> displays all the portfolios and their total value.
		 * show_transactions()  --> displays all the transactions (Buy, Sell) for the active portfolio
		 * show_assets()        --> displays a list of all the assets with their current market data
		 */
		void show_portfolio();
		void show_portfolios();
		void show_transactions(const portfolio&);
		void show_assets();

		void show_tx_error(const transaction&);

		/* Resets error_ to Error::NO_ERROR */
		void reset();

		/* Initialize the jump table with all the supported commands
		 * Defined in commands.cpp
		 */
		void init_commands();

		// These two member functions are defined in file_manager.cpp
		void save_to_file(const std::string&);
		void load_from_file(const std::string&);

		void new_game();
	public:
		game() = delete;

		// Load the simulation from a saved state
		game(const std::string& file_path);

		void start();

		void set_view(std::unique_ptr<view> view);		
};

#endif
