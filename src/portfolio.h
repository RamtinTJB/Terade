#ifndef TERADE_PORTFOLIO_H
#define TERADE_PORTFOLIO_H

#include <string>
#include <iostream>
#include <map>

#include "asset.h"
#include "utils.h"
#include "transaction.h"
#include "api.h"

struct portfolio_entry {
	asset_id id = {"DEFAULT"};
	double quantity = 0;
	double avg_buy_price = 0;
	double price = 0;
	double value = 0;

	portfolio_entry() = default;
	portfolio_entry(const asset_id& id_, const double quantity_, const double price_):
		id {id_}, quantity {quantity_}, avg_buy_price {price_} {}
};

class portfolio {
	private:
		std::string portfolio_name_ = "Default Portfolio";
		std::map<asset_id, portfolio_entry> assets_;
		std::vector<transaction> transactions_;

		void add_asset(const asset_id& id, const double quantity,
				const double price);
		void remove_asset(const asset_id& id, const double quantity,
				const double price);
	public:
		portfolio() = default;
		portfolio(const std::string& name) : portfolio_name_{name} {}

		double get_quantity(const asset_id& id);
		std::string portfolio_name() const { return portfolio_name_; }
		std::map<asset_id, portfolio_entry> assets() const { return assets_; }
		bool contains(const asset_id& id);

		void evaluate(CoinGeckoApi&, const double);
		double total_value() const;

		void add_tx(const transaction& tx);

		std::vector<portfolio_entry> get_entries();
		std::vector<transaction> get_transactions() const { return transactions_; }
};

inline std::ostream& operator<< (std::ostream& os, const portfolio& p) {
	os << p.portfolio_name() << ":" << std::endl;
	for (auto const& [id, entry]: p.assets()) {
		os << std::string(id) << "    " << entry.quantity << std::endl;
	}
	return os;
}

#endif
