#include "game.h"

game::game(const std::string& file_path) {
	init_commands();
	timer_.set_interval(TIMER_INTERVAL_MS)->
		set_func([this]() { epoch_time_index_++; });
	if (file_path.empty()) {
		new_game();
	} else {
		load_from_file(file_path);
		file_path_ = file_path;
	}
}

void game::new_game() {
	std::string input;
	while (input == "" ) {
		std::cout << "Player Name: ";
		std::getline(std::cin, input);
	}
	player_ = player(input, starting_cash);
	player_.create_portfolio("Main");
	player_.select_portfolio("Main");
}

void game::start() {
	view_->update_status_bar(player_);
	timer_.start();
	std::string input = view_->get_entry();
	while (input != "exit") {
		reset();
		if (map_contains(commands_, input)) {
			commands_[input]();
		} else {
			view_->show_error("Invalid Command");
			error_ = Error::BAD_INPUT;
		}
		if (error_ == Error::NO_ERROR) {
			view_->update_status_bar(player_);
		}
		input = view_->get_entry();
	}
}

void game::reset() {
	error_ = Error::NO_ERROR;
}

int game::get_input_num(const std::string& prompt) {
	std::string input = view_->get_input(prompt);
	if (is_num(input)) {
		return std::stoi(input);
	}
	error_ = Error::BAD_INPUT;
	return -1;
}

transaction game::get_input_tx() {
	std::string id = view_->get_input("Asset ID");
	transaction tx(id);
	if (!api_.asset_exists(id)) {
		error_ = Error::BAD_INPUT;
		tx.invalidate();
		tx.error(TxError::ASSET_DOES_NOT_EXIST);
		return tx;
	}
	tx.price(api_.get_price(id, epoch_time_index_));
	int quantity = get_input_num("Quantity");
	if (quantity > 0) {
		tx.quantity(quantity);
	}
	else {
		tx.invalidate();
		tx.error(TxError::INVALID_QUANTITY);
	}
	return tx;
}

void game::show_tx_error(const transaction& tx) {
	if (!tx.is_valid()) {
		if (tx.error() & TxError::ASSET_DOES_NOT_EXIST) {
			view_->show_error("Asset '" + tx.id().id() + "' Does Not Exist!");
		}
	   	if (tx.error() & TxError::INVALID_QUANTITY) {
			view_->show_error("Invalid Quantity!");
		}
	   	if (tx.error() & TxError::INSUFFICIENT_FUNDS) {
			view_->show_error("Insufficient Funds!");
		}
		if (tx.error() & TxError::INSUFFICIENT_HOLDING) {
			view_->show_error("Insufficient Holdings!");
		}
	}
}

void game::show_assets() {
	std::vector<asset> assets = api_.get_assets(epoch_time_index_);
	view_->update_list(format<asset>(assets, asset_formatter), asset_list_header());
	view_->set_list_title("Assets");
}

void game::show_portfolios() {
	player_.evaluate_portfolios(api_, epoch_time_index_);
	std::vector<portfolio> portfolios = player_.get_portfolios();
	view_->update_list(format<portfolio>(portfolios, portfolio_list_formatter), portfolios_header());
	view_->set_list_title("Portfolios (Active: " +
			player_.get_selected_portfolio().portfolio_name() + ")");
}

void game::evaluate_tx_error(transaction& tx) {
	if (tx.type() == TxType::BUY) {
		if (tx.value() > player_.available_cash()) {
			tx.invalidate();
			tx.error(TxError::INSUFFICIENT_FUNDS);
		}
	}
	if (tx.type() == TxType::SELL) {
		if (!player_.get_selected_portfolio().contains(tx.id())) {
			tx.invalidate();
			tx.error(TxError::INSUFFICIENT_HOLDING);
		} else if (player_.get_selected_portfolio().get_quantity(tx.id()) < tx.quantity()) {
			tx.invalidate();
			tx.error(TxError::INSUFFICIENT_HOLDING);
		}
	}
}

void game::execute_transaction(transaction& tx, std::function<void(const transaction&)> handler) {
	evaluate_tx_error(tx);
	if (tx.is_valid()) {
		handler(tx);
	} else {
		show_tx_error(tx);
	}
}

void game::show_portfolio() {
	player_.evaluate_portfolios(api_, epoch_time_index_);
	std::vector<portfolio_entry> entries = player_.get_selected_portfolio().get_entries();
	view_->update_list(format<portfolio_entry>(entries, portfolio_formatter), portfolio_list_header());
	view_->set_list_title(player_.get_selected_portfolio().portfolio_name() +
			" ($" + prettify_price(player_.get_selected_portfolio().total_value())  + ")");
}

void game::show_transactions(const portfolio& p) {
	std::vector<transaction> txs = p.get_transactions();
	view_->update_list(format<transaction>(txs, transaction_formatter), transaction_header());
	view_->set_list_title("Transactions (" + player_.get_selected_portfolio().portfolio_name() + ")");
}

void game::set_view(std::unique_ptr<view> view) {
	view_ = std::move(view);
}
