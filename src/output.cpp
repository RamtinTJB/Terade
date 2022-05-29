#include "output.h"

using std::setw;
using std::right;
using std::left;

std::string asset_formatter(const asset& a) {
	std::stringstream ss;
	ss << left << setw(10) << a.name() << setw(10) << upper_case_str(a.tick()) << setw(15) << prettify_price(a.data().price()) << setw(20) << prettify_price(a.data().volume()) << setw(20) << prettify_price(a.data().market_cap());
	
	return ss.str();
}

std::string asset_list_header() {
	std::stringstream ss;
	ss << left << setw(10) << "Name" << setw(10) << "Tick" << setw(15) << "Price ($)" << setw(20) << "Volume ($)" << setw(20) << "Market Cap ($)";
	
	return ss.str();
}

std::string portfolio_formatter(const portfolio_entry& p) {
	std::stringstream ss;
	ss << left << setw(10) << p.id.id() << setw(10) << p.quantity << setw(10) << prettify_price(p.price) << setw(10) << prettify_price(p.value) << setw(20) << prettify_price(p.avg_buy_price) << setw(15) << prettify_price(p.quantity * p.avg_buy_price);

	return ss.str();
}

std::string portfolio_list_header() {
	std::stringstream ss;
	ss << left << setw(10) << "Name" << setw(10) << "Quantity" << setw(10) << "Price" << setw(10) << "Value" << setw(20) << "Avg Buy Price" << setw(15) << "Total Spent";

	return ss.str();
}

std::string portfolio_list_formatter(const portfolio& p) {
	std::stringstream ss;
	ss << left << setw(20) << p.portfolio_name() << setw(20) << prettify_price(p.total_value());

	return ss.str();
}

std::string portfolios_header() {
	std::stringstream ss;
	ss << left << setw(20) << "Name" << setw(20) << "Value ($)";

	return ss.str();
}

std::string transaction_formatter(const transaction& tx) {
	std::stringstream ss;
	ss << left << setw(10) << (tx.type() == TxType::SELL ? "S" : "B") <<
		setw(20) << tx.quantity() << setw(20) << prettify_price(tx.price());

	return ss.str();
}

std::string transaction_header() {
	std::stringstream ss;
	ss << left << setw(10) << "Type" << setw(20) << "Quantity" << setw(20) << "Price";

	return ss.str();
}
