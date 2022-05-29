#include "game.h"

using nlohmann::json;

namespace {
	std::string tx_type_to_string(const TxType& type) {
		switch (type) {
			case TxType::BUY: return "BUY";
			case TxType::SELL: return "SELL";
		}
	}

	TxType string_to_tx_type(const std::string& str) {
		if (str == "BUY") return TxType::BUY;
		if (str == "SELL") return TxType::SELL;
	}

	json tx_to_json_array(const transaction& tx) {
		return json::array({tx_type_to_string(tx.type()), tx.id(), tx.quantity(), tx.price(), tx.error()});
	}

	transaction json_array_to_tx(const json& j) {
		transaction tx(j[1].get<std::string>());
		tx.type(string_to_tx_type(j[0]));
		tx.quantity(j[2]);
		tx.price(j[3]);
		tx.error(j[4]);
		return tx;
	}
}

void game::save_to_file(const std::string& file_path) {
	json j;
	j["epoch_time"] = epoch_time_index_;
	j["name"] = player_.name();
	j["cash"] = player_.available_cash();
	j["selected_portfolio"] = player_.get_selected_portfolio().portfolio_name();
	for (const auto& p: player_.get_portfolios()) {
		j["portfolios"][p.portfolio_name()] = json::array();
		for (const auto& tx: p.get_transactions()) {
			j["portfolios"][p.portfolio_name()].push_back(tx_to_json_array(tx));	
		}
	}

	std::ofstream out_file(file_path, std::ios::trunc);
	out_file << j.dump(4);
	out_file.close();
}

void game::load_from_file(const std::string& file_path) {
	std::ifstream in_file(file_path);
	json j; in_file >> j;

	epoch_time_index_ = j["epoch_time"];
	player_ = player(j["name"], starting_cash);
	for (json::iterator it = j["portfolios"].begin(); it != j["portfolios"].end(); it++) {
		player_.create_portfolio(it.key());
		player_.select_portfolio(it.key());
		for (auto& element: j["portfolios"][it.key()]) {
			transaction tx = json_array_to_tx(element);
			if (tx.type() == TxType::BUY) {
				player_.purchase_asset(tx);
			} else {
				player_.sell_asset(tx);
			}
		}
	}
	player_.select_portfolio(j["selected_portfolio"]);
	in_file.close();
}
