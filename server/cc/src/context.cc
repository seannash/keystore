#include "context.h"

Context::Context(int id)
: id_(id)
, store_() {
}

model::Store& Context::store() {
    return store_;
}
