#include "game.h"

void game::init_commands() {
	commands_["portfolio"] = [this]() { show_portfolio(); };
	commands_["portfolios"] = [this]() { show_portfolios(); };
	commands_["tx"] = [this]() { show_transactions(player_.get_selected_portfolio()); };
	commands_["buy"] = [this]() {
		transaction tx = get_input_tx();
		tx.type(TxType::BUY);
		execute_transaction(tx,
				[this](const transaction& tx) { player_.purchase_asset(tx); });
	};
	commands_["sell"] = [this]() {
		transaction tx = get_input_tx();
		tx.type(TxType::SELL);
		execute_transaction(tx,
				[this](const transaction& tx) { player_.sell_asset(tx); });
	};
	commands_["assets"] = [this]() { show_assets(); };
	commands_["create"] = [this]() { player_.create_portfolio(view_->get_input("Name")); };
	commands_["select"] = [this]() { player_.select_portfolio(view_->get_input("Name")); };
	commands_["load"] = [this]() {
		std::string file_path = view_->get_input("Path");
		load_from_file(file_path);
		file_path_ = file_path;
	};
	commands_["save"] = [this]() {
		if (file_path_.empty()) {
			std::string file_path = view_->get_input("Path");
			save_to_file(file_path);
			file_path_ = file_path;
		} else {
			save_to_file(file_path_);
		}
	};
	commands_["help"] = [this]() {
		view_->show_help();
	};
}
