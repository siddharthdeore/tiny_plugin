#include "ComplexPlugin.h"
#include <iostream>

ComplexPlugin::ComplexPlugin(std::shared_ptr<int> x) : y(*x)
{
    std::cout << " Complex Plugin constructor " << y++ << std::endl;
}

ComplexPlugin::~ComplexPlugin()
{
    std::cout << " ~Complex Plugin destructor " << y << std::endl;
}
