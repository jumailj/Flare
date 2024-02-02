#include "TestLayer.h"
#include "../Core/KeyCodes.h"

void TestLayer::OnUpdate() {
        LOG_INFO("hello world");       

}

TestLayer::TestLayer()
: Layer("testlayer")
 {
        LOG_INFO("i'm on consturctor");
}


void TestLayer::OnAttach(){

}

void TestLayer::OnDetach(){

}

void TestLayer::OnEvent(Flare::Event& e)
{
	LOG_INFO("EVENT: {0}", e.ToString());


}