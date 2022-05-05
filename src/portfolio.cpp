#include "portfolio.h"

double portfolio::get_quantity(const asset_id& id) {
	if (contains(id)) {
		return assets_[id];
	} else {
		return -1;
	}
}

void portfolio::add_asset(const asset_id& id, const double quantity) {
	if (map_contains(assets_, id)) {
		assets_[id] += quantity;
	} else {
		assets_[id] = quantity;
	}
}

void portfolio::remove_asset(const asset_id& id, const double quantity) {
	if (map_contains(assets_, id)) {
		assets_[id] -= quantity;
	}
}

bool portfolio::contains(const asset_id& id) {
	return map_contains(assets_, id);
}
