#include "ComplexPlugin.h"
#include <iostream>

ComplexPlugin::ComplexPlugin(std::shared_ptr<int> x)
{
    std::cout << " Complex Plugin constructor " << *x << std::endl;
}

ComplexPlugin::~ComplexPlugin()
{
    std::cout << " ~Complex Plugin destructor " << std::endl;
}
