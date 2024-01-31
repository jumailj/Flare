#pragma once 
#include <memory>
// toto platform setup.
#define BIT(x) (1 <<x ) // BIT(1)00001 , BIT(2)00010, BIT(3)00100 
#define BIND_EVENT_FN(fn)    	std::bind(&fn,this,std::placeholders::_1)