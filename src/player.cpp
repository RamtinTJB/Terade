#include "player.h"

void player::create_portfolio(const std::string& name) {
	if (!map_contains(portfolios_, name)) {
		portfolios_[name] = portfolio(name);
	}
}

void player::select_portfolio(const std::string& name) {
	if (map_contains(portfolios_, name)) {
		selected_portfolio_ = name;
	}
}

void player::purchase_asset(const transaction& tx) {
	portfolios_[selected_portfolio_].add_asset(tx.id(), tx.quantity());
	available_cash_ -= tx.quantity()*tx.price();
}

void player::sell_asset(const transaction& tx) {
	portfolios_[selected_portfolio_].remove_asset(tx.id(), tx.quantity());
	available_cash_ += tx.quantity()*tx.price();
}
