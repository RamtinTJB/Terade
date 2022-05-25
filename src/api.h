#ifndef TERADE_API_H
#define TERADE_API_H

#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

#include "asset.h"

/* #undef OK

#include <cpr/cpr.h>

#define OK (0) */

struct asset_header {
	std::string symbol;
	std::string name;

	asset_header() = default;

	asset_header(const std::string& symbol, const std::string& name):
		symbol {symbol},
		name {name} {}
};

class CoinGeckoApi {
	private:
		std::map<asset_id, asset_header> all_assets_;
		std::map<asset_id, nlohmann::json> json_files_;
		std::vector<asset_id> supported_assets_;
		nlohmann::json get_asset_json(const asset_id& id);
		nlohmann::json get_top_assets_json(int num = 5);
		nlohmann::json get_all_assets_json();
		void init_all_assets();
		void init_json_files();
	public:
		std::vector<asset> get_assets(const long epoch_time);
		double get_price(const asset_id& id, const long epoch_time);

		CoinGeckoApi() = delete;
		CoinGeckoApi(const std::vector<asset_id>&);

		asset_header get_asset_header(const asset_id& id) { return all_assets_[id]; }
		bool asset_exists(const asset_id& id);
};

#endif
