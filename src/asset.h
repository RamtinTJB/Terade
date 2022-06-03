#ifndef TERADE_ASSET_H
#define TERADE_ASSET_H

#include <string>
#include <iostream>

/*
 * Initialize market_data using the builder class
 *
 * market_data::Builder b;
 * b.price(...).market_cap(...).volume(...);
 * asset a {"bitcoin", "Bitcoin", "BTC", b.build()};
 */
class market_data {
	private:
		double price_ = 0;             // $
		double market_cap_ = 0;        // $
		double volume_ = 0;            // $

		// These two member variables are currently not used in the program.
		double _7_day_change_ = 0;     // %change of the price in the past 7 days
		double _24_hour_change_ = 0;   // %change of the price in the past 24 hours
	public:
		market_data() = default;

		class Builder {
			private:
				friend market_data;
				double price_ = 0;
				double market_cap_ = 0;
				double volume_ = 0;
				double _7_day_change_ = 0;
				double _24_hour_change_ = 0;
			public:
				Builder() = default;

				market_data build() {
					return market_data(*this);
				}

				Builder& price(const double price) {
					price_ = price;
					return *this;
				}

				Builder& market_cap(const double market_cap) {
					market_cap_ = market_cap;
					return *this;
				}

				Builder& volume(const double volume) {
					volume_ = volume;
					return *this;
				}

				Builder& _7_day_change(const double _7_day) {
					_7_day_change_ = _7_day;
					return *this;
				}

				Builder& _24_hour_change(const double _24_hour) {
					_24_hour_change_ = _24_hour;
					return *this;
				}
		};	

		explicit market_data(const Builder& builder):
			price_ {builder.price_},
			market_cap_ {builder.market_cap_},
			volume_ {builder.volume_},
			_7_day_change_ {builder._7_day_change_},
			_24_hour_change_ {builder._24_hour_change_}
		{}

		double price() const { return price_; }
		double market_cap() const { return market_cap_; }
		double volume() const { return volume_; }
		double _7_day_change() const { return _7_day_change_; }
		double _24_hour_change() const { return _24_hour_change_; }
};

class asset_id {
	private:
		// id_ is the same id found in the json files returned but the CoinGecko API. e.g. bitcoin
		std::string id_;
	public:
		asset_id() = delete;
		asset_id(const std::string& id) : id_ {id} {}
		asset_id(const asset_id& other) { id_ = other.id_; }

		operator std::string() const { return id_; }
		std::string id() const { return id_; }

		bool operator== (const asset_id& other) {
			return id_ == other.id();
		}
};

inline bool operator< (const asset_id& lhs, const asset_id& rhs) {
	return lhs.id() < rhs.id();
}

class asset {
	private:
		asset_id id_;
		std::string name_;  // Name of the token: e.g. Bitcoin
		std::string tick_;  // e.g. BTC
		market_data data_;       // inforomation of an asset at a specific time
	public:
		asset() = delete;
		asset(const asset_id& id, const std::string& name,  const std::string& tick, market_data data) :
			id_ {id},
			name_ {name}, 
			tick_ {tick},
			data_ {data} {}

		std::string name() const { return name_; }
		std::string tick() const { return tick_; }
		market_data data() const { return data_; }

		void update_data(const market_data& data) { data_ = data; }
};

// Print asset and its current market data for debuggin purposes.
inline std::ostream& operator<< (std::ostream& os, const market_data& m) {
	return os << "Price: " << m.price() << std::endl
		<< "Market Cap: " << m.market_cap() << std::endl
		<< "Volume: " << m.volume() << std::endl
		<< "7 Day Change: " << m._7_day_change() << std::endl
		<< "24 Hour Change: " << m._24_hour_change();
}

inline std::ostream& operator<< (std::ostream& os, const asset& a) {
	return os << "Name: " << a.name() << "\tTick: " << a.tick()
		<< std::endl << a.data();
}

#endif
