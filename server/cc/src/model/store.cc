#include "store.h"

namespace model {

void Store::put(const std::string& key, const std::string& value) {
    store_[key] = value;
}

std::string Store::get(const std::string& key) {
    return store_[key];
}

} // namespace model