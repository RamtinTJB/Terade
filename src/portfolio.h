#ifndef TERADE_PORTFOLIO_H
#define TERADE_PORTFOLIO_H

#include <string>
#include <iostream>
#include <map>

#include "asset.h"
#include "utils.h"

class portfolio {
	private:
		std::string portfolio_name_ = "Default Portfolio";
		std::map<asset_id, double> assets_;
	public:
		portfolio() = default;
		portfolio(const std::string& name) : portfolio_name_{name} {}

		double get_quantity(const asset_id& id);
		std::string portfolio_name() const { return portfolio_name_; }
		std::map<asset_id, double> assets() const { return assets_; }
		bool contains(const asset_id& id);

		void add_asset(const asset_id& id, const double quantity);
		void remove_asset(const asset_id& id, const double quantity);
};

inline std::ostream& operator<< (std::ostream& os, const portfolio& p) {
	os << p.portfolio_name() << ":" << std::endl;
	for (auto const& [id, quantity]: p.assets()) {
		os << std::string(id) << "    " << quantity << std::endl;
	}
	return os;
}

#endif
