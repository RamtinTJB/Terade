#include "api.h"

using nlohmann::json;

std::vector<asset> CoinGeckoApi::get_assets(int num_assets) {
	std::vector<asset> result;
	std::ifstream i("test_assets.json");
	json j;
	i >> j;
	for (json::iterator it = j.begin(); it != j.end(); it++) {
		market_data::Builder b;
		std::string id_str = it.key();
		b.price(j[id_str]["usd"])
			.market_cap(j[id_str]["usd_market_cap"])
			.volume(j[id_str]["usd_24h_vol"]);

		asset_id id(id_str);
		result.push_back(asset(id, all_assets_[id].name, all_assets_[id].symbol, b.build()));
	}
	return result;
}

double CoinGeckoApi::get_price(const asset_id& id) {
	std::ifstream i("test_assets.json");
	json j;
	i >> j;
	return j[id.id()]["usd"];
}

CoinGeckoApi::CoinGeckoApi() {
	init_all_assets();
}

json CoinGeckoApi::get_all_assets_json() {
	std::ifstream i("all_coins.json");
	json j;
	i >> j;
	return j;
}

void CoinGeckoApi::init_all_assets() {
	json j = get_all_assets_json();
	for (json::iterator it = j.begin(); it != j.end(); it++) {
		asset_id id((*it)["id"]);
		asset_header header((*it)["symbol"], (*it)["name"]);
		all_assets_[id] = header;
	}
}

bool CoinGeckoApi::asset_exists(const asset_id& id) {
	return all_assets_.count(id) > 0;
}
