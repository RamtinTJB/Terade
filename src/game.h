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

class game {
	private:
		player player_ {"default"};
		std::unique_ptr<view> view_ = nullptr;
		CoinGeckoApi api_ {{{"bitcoin"}, {"ethereum"}, {"cardano"}}};
		Error error_ = Error::NO_ERROR;
		long epoch_time_index_ = 1;
		std::string file_path_;
		std::map<std::string, std::function<void(void)>> commands_;
		Timer timer_;

		//for test purposes (prototype)
		int get_input_num(const std::string& prompt);
		transaction get_input_tx();
		void evaluate_tx_error(transaction& tx);
		void execute_transaction(transaction& tx, std::function<void(const transaction&)>);
		void show_portfolio();
		void show_portfolios();
		void show_transactions(const portfolio&);
		void show_assets();

		void show_tx_error(const transaction&);

		void reset();
		void init_commands();

		void save_to_file(const std::string&);
		void load_from_file(const std::string&);

		void new_game();
	public:
		game() = delete;
		game(const std::string& file_path);

		void start();

		void set_view(std::unique_ptr<view> view);		
};

#endif
