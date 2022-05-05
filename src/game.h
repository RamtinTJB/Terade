#ifndef TERADE_GAME_H
#define TERADE_GAME_H

#include <iostream>
#include <string>
#include <memory>

#include "view.h"
#include "player.h"
#include "api.h"
#include "utils.h"
#include "transaction.h"

enum class Error {
	NO_ERROR = 0, BAD_INPUT = 1, INSUFFICIENT_FUNDS = 2
};

class game {
	private:
		player player_ {"default"};
		std::unique_ptr<view> view_ = nullptr;
		CoinGeckoApi api_;
		Error error_ = Error::NO_ERROR;

		//for test purposes (prototype)
		int get_input_num(const std::string& prompt);
		transaction get_input_tx();
		void buy_asset();
		void sell_asset();
		void show_portfolio();
		void show_assets();

		void show_tx_error(transaction tx);

		void reset();
	public:
		game() {
			player_ = player("Ramtin", 10000);
			player_.create_portfolio("Main Portfolio");
			player_.select_portfolio("Main Portfolio");
		};

		void start();

		void set_view(std::unique_ptr<view> view);		
};

#endif
