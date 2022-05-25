#include "api.h"

using nlohmann::json;

std::vector<asset> CoinGeckoApi::get_assets(const long epoch_time) {
	std::vector<asset> result;
	for (const auto& [id, j]: json_files_) {
		market_data::Builder b;
		std::string id_str = id.id();
		b.price(j["prices"][epoch_time][1])
			.market_cap(j["market_caps"][epoch_time][1])
			.volume(j["total_volumes"][epoch_time][1]);

		result.push_back(asset(id, all_assets_[id].name, all_assets_[id].symbol, b.build()));
	}
	return result;
}

double CoinGeckoApi::get_price(const asset_id& id, const long epoch_time) {
	json j = json_files_[id];
	return j["prices"][epoch_time][1];
}

CoinGeckoApi::CoinGeckoApi(const std::vector<asset_id>& supported_assets): supported_assets_ {supported_assets} {
	init_all_assets();
	init_json_files();
}

json CoinGeckoApi::get_all_assets_json() {
	//cpr::Response r = cpr::Get(cpr::Url{"https://api.coingecko.com/api/v3/ping"});
	//std::cout << (int)r.error.code << std::endl;
	std::ifstream i("all_coins.json");
	json j;
	i >> j;
	return j;
}

void CoinGeckoApi::init_json_files() {
	for (const auto& a_id: supported_assets_) {
		std::ifstream i(a_id.id() + ".json");
		json j;
		i >> j;
		json_files_[a_id] = j;
	}
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
