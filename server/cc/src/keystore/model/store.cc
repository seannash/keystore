#include "store.h"
#include <mutex>
#include <shared_mutex>

namespace keystore::model {

void Store::put(const std::string& key, const std::string& value) {
    std::unique_lock lock(mutex_);
    store_[key] = value;
}

std::string Store::get(const std::string& key) {
    std::shared_lock lock(mutex_);
    return store_[key];
}

} // namespace keystore::model