#ifndef TERADE_PLAYER_H
#define TERADE_PLAYER_H

#include <string>
#include <iostream>
#include <vector>

#include "portfolio.h"
#include "utils.h"
#include "transaction.h"

/*
 *   The player class stores all the information relevant to the player of the simlutor.
 *   Each player has a name, an arbitrary number of portfolios, and some disposable cash at any time.
 */

class player {
	private:
		std::string name_;

		// Maps portfolio's name to the portfolio. I used the map for easier retrieval.
		std::map<std::string, portfolio> portfolios_;

		double available_cash_ {0};

		// Curerntly active portfolio. All buy and sell operations are done on the selected portfolio
		std::string selected_portfolio_;
	public:
		player() = delete;
		player(const std::string& name) : name_{name} {}
		player(const std::string& name, double available_cash) :
			name_{name},
			available_cash_{available_cash} {}

		std::string name() const { return name_; }
		double available_cash() const { return available_cash_; }

		void create_portfolio(const std::string& name);
		void select_portfolio(const std::string& name);
		void purchase_asset(const transaction& tx);
		void sell_asset(const transaction& tx);

		portfolio get_selected_portfolio() { return portfolios_[selected_portfolio_]; }
		std::vector<portfolio> get_portfolios();

		// Evaluate each portfolio at current time and update their status
		void evaluate_portfolios(CoinGeckoApi& api, const double epoch_time_index);
};

#endif
