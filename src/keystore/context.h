#pragma once

#include <keystore/model/store.h>
#include <memory>

namespace keystore {

class Context {
private:
    int id_;
    model::Store store_;
    
    // Private constructor for builder
    
    
public:
    Context(int id);
    ~Context() = default;
    int id() const;
    model::Store& store();
    
    // Builder class
    class Builder {
    private:
        int id_;
        
    public:
        Builder();
        
        Builder& withId(int id);
        std::unique_ptr<Context> build();
    };
};

} // namespace keystore