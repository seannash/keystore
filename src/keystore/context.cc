#include "keystore/context.h"

namespace keystore {

Context::Context(int id)
: id_(id)
, store_() {
}

model::Store& Context::store() {
    return store_;
}

int Context::id() const {
    return id_;
}


// Builder implementation
Context::Builder::Builder()
: id_(0) {
}

Context::Builder& Context::Builder::withId(int id) {
    id_ = id;
    return *this;
}

std::unique_ptr<Context> Context::Builder::build() {
    return std::make_unique<Context>(id_);
}

} // namespace keystore
