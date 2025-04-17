#pragma once

#include <model/store.h>

class Context {
private:
    int id_;
    model::Store store_;
    
public:
    Context(int id);
    ~Context() = default;
    
    model::Store& store();
};