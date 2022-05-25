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
	//portfolios_[selected_portfolio_].add_asset(tx.id(), tx.price());
	portfolios_[selected_portfolio_].add_tx(tx);
	available_cash_ -= tx.quantity()*tx.price();
}

void player::sell_asset(const transaction& tx) {
	//portfolios_[selected_portfolio_].remove_asset(tx.id(), tx.quantity());
	portfolios_[selected_portfolio_].add_tx(tx);
	available_cash_ += tx.quantity()*tx.price();
}

std::vector<portfolio> player::get_portfolios() {
	std::vector<portfolio> res;
	for (const auto& [key, value]: portfolios_) {
		res.push_back(value);
	}
	return res;
}

void player::evaluate_portfolios(CoinGeckoApi& api, const double epoch_time_index) {
	for (auto& [name, p]: portfolios_) {
		p.evaluate(api, epoch_time_index);
	}
}
