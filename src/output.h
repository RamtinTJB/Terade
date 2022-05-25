#ifndef TERADE_OUTPUT_H
#define TERADE_OUTPUT_H

#include <string>
#include <iomanip>
#include <iostream>
#include <cctype>
#include <sstream>

#include "utils.h"
#include "asset.h"
#include "portfolio.h"
#include "transaction.h"

std::string asset_formatter(const asset& a);
std::string asset_list_header();

std::string portfolio_formatter(const portfolio_entry& o);
std::string portfolio_list_header();

std::string portfolio_list_formatter(const portfolio& p);
std::string portfolios_header();

std::string transaction_formatter(const transaction& tx);
std::string transaction_header();

#endif
