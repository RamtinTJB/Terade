#ifndef TERADE_TRANSACTION_H
#define TERADE_TRANSACTION_H

#include <string>

#include "asset.h"

enum class TxType {
	BUY, SELL
};

// Global namespace (symbol names)
enum TxError {
	NO_ERROR = 0, ASSET_DOES_NOT_EXIST = 1, INVALID_QUANTITY = 2, INSUFFICIENT_FUNDS = 4,
	INSUFFICIENT_HOLDING = 8
};

class transaction {
	private:
		TxType type_;
		asset_id id_;
		double quantity_;
		double price_;
		bool valid_ = true;
		int error_ = TxError::NO_ERROR;
	public:
		transaction() = delete;
		transaction(const asset_id& id): id_{id} {}

		TxType type() const { return type_; }
		asset_id id() const { return id_; }
		double quantity() const { return quantity_; }
		double price() const { return price_; }
		bool is_valid() const { return valid_; }
		int error() const { return error_; }

		void type(const TxType& t) { type_ = t; }
		void id(const asset_id& id) { id_ = id; }
		void quantity(const double q) { quantity_ = q; }
		void price(const double p) { price_ = p; }
		void invalidate() { valid_ = false; }
		void error(TxError e) { error_ |= e; }

		double value() const { return quantity_ * price_; }
};

#endif
