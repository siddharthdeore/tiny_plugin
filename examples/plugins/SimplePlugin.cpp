#include <iostream>

#include "SimplePlugin.hpp"

SimplePlugin::SimplePlugin()
{
    std::cout << " SimplePlugin constructor " << std::endl;
}

SimplePlugin::~SimplePlugin()
{
    std::cout << " ~SimplePlugin destructor " << std::endl;
}
