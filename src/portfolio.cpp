#include "portfolio.h"

double portfolio::get_quantity(const asset_id& id) {
	if (contains(id)) {
		return assets_[id].quantity;
	} else {
		return -1;
	}
}

void portfolio::add_asset(const asset_id& id, const double quantity, const double price) {
	if (map_contains(assets_, id)) {
		portfolio_entry& entry = assets_[id];
		double total_spent_before_tx = entry.quantity * entry.avg_buy_price;
		entry.quantity += quantity;
		entry.avg_buy_price = (total_spent_before_tx + quantity*price) / entry.quantity;
	} else {
		portfolio_entry entry {id, quantity, price};
		assets_[id] = entry;
	}
}

void portfolio::remove_asset(const asset_id& id, const double quantity, const double price) {
	if (map_contains(assets_, id)) 
	{
		portfolio_entry& entry = assets_[id];
		double total_spent_before_tx = entry.quantity * entry.avg_buy_price;
		entry.quantity -= quantity;
		entry.avg_buy_price = (total_spent_before_tx - quantity*price) / entry.quantity;
	}
}

void portfolio::add_tx(const transaction& tx) {
	if (tx.type() == TxType::BUY) {
		add_asset(tx.id(), tx.quantity(), tx.price());
	} else if (tx.type() == TxType::SELL) {
		remove_asset(tx.id(), tx.quantity(), tx.price());
	}
	transactions_.push_back(tx);
}

std::vector<portfolio_entry> portfolio::get_entries() {
	std::vector<portfolio_entry> entries;
	for (const auto& [key, value]: assets_) {
		entries.push_back(value);
	}
	return entries;
}

bool portfolio::contains(const asset_id& id) {
	return map_contains(assets_, id);
}

void portfolio::evaluate(CoinGeckoApi& api, const double epoch_time_index) {
	for (auto& [id, entry]: assets_) {
		double price = api.get_price(id, epoch_time_index);
		entry.value = entry.quantity*price;
		entry.price = price;
	}
}

double portfolio::total_value() const {
	double res = 0;
	for (const auto& [id, entry]: assets_) {
		res += entry.value;
	}
	return res;
}
