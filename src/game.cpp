#include "game.h"

void game::start() {
	view_->update_status_bar(player_);
	std::string input = view_->get_entry();
	while (input != "exit") {
		reset();
		if (input == "show assets") {
			show_assets();
		} else if (input == "buy") {
			buy_asset();
		} else if (input == "sell") {
			sell_asset();
		} else if (input == "portfolio") {
			show_portfolio();
		} else if (input == "info") {
			std::cout << player_.name() << " " << player_.available_cash() << std::endl;	
		} else if (input == "help") {
			view_->show_help();
		} else {
			view_->show_error("Invalid Command. Type 'help' for more info.");
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
	tx.price(api_.get_price(id));
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

void game::show_tx_error(transaction tx) {
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

// void with no input =|
void game::show_assets() {
	std::vector<asset> assets = api_.get_assets();
	view_->update_token_list(assets);
}

// transaction could be passed in as a parameter
void game::buy_asset() {
	transaction tx = get_input_tx();
	tx.type(TxType::BUY);
	if (tx.value() > player_.available_cash()) {
		tx.invalidate();
		tx.error(TxError::INSUFFICIENT_FUNDS);
	}
	if (tx.is_valid()) {
		player_.purchase_asset(tx);
	} else {
		show_tx_error(tx);
	}
}

// void game::execute_transaction(transaction, function pointer)
// function pointer = sell_asset or purchase_asset (Lambda or std::function)
// function pointer = std::function<void(const transaction&)>
// using tx_function = void (*)(const transaction&)
// [](const transaction& tx) { player_.purchase_asset(tx); }

// consider returning the transaction
void game::sell_asset() {
	transaction tx = get_input_tx();
	tx.type(TxType::SELL);
	if (!player_.get_selected_portfolio().contains(tx.id())) {
		tx.invalidate();
		tx.error(TxError::INSUFFICIENT_HOLDING);	
	} else if (player_.get_selected_portfolio().get_quantity(tx.id()) < tx.quantity()) {
		tx.invalidate();
		tx.error(TxError::INSUFFICIENT_HOLDING);
	}
	if (tx.is_valid()) {
		player_.sell_asset(tx);
	} else {
		show_tx_error(tx);
	}
}

void game::show_portfolio() {
	std::cout << player_.get_selected_portfolio() << std::endl;
}

void game::set_view(std::unique_ptr<view> view) {
	view_ = std::move(view);
}
