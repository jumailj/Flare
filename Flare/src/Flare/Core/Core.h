#pragma once 

#include <memory>

#define BIT(x) (1 <<x ) // BIT(1)00001 , BIT(2)00010, BIT(3)00100 


#define BIND_EVENT_FN(fn)    	std::bind(&fn,this,std::placeholders::_1)
// #define BIND_EVENT_FN(fn)   [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
// not sure how this code work


namespace Flare {

    template<typename T>
    using Scope = std::unique_ptr<T>;

    template <typename T>
    using Ref = std::shared_ptr<T>;
}
