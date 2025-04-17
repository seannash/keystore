#pragma once

#include <string>
#include <unordered_map>
#include <shared_mutex>
namespace model {

class Store {
public:
    void put(const std::string& key, const std::string& value);
    std::string get(const std::string& key);

private:
    std::unordered_map<std::string, std::string> store_;
    mutable std::shared_mutex mutex_;
};

} // namespace model