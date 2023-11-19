#pragma once 
#include <memory>
// toto platform setup.
#define BIT(x) (1 <<x ) // 00001 , 00010, 00100
#define BIND_EVENT_FN(fn)    	std::bind(&fn,this,std::placeholders::_1)