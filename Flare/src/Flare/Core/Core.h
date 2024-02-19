#pragma once 

#include <memory>

/*header file in same foloder use #include "header.h" */
/*header file in different folder use #include <Flare/../..> */

#define BIT(x) (1 <<x ) // BIT(1)00001 , BIT(2)00010, BIT(3)00100 

#define BIND_EVENT_FN(fn)    	std::bind(&fn,this,std::placeholders::_1)

namespace Flare {

    template<typename T>
    using Scope = std::unique_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Scope<T> CreateScope(Args&& ... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}
