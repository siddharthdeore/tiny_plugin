#include <iostream>

#include "SimplePlugin.h"

SimplePlugin::SimplePlugin()
{
 std::cout << " SimplePlugin constructor " << std::endl;
}

SimplePlugin::~SimplePlugin()
{
 std::cout << " ~SimplePlugin destructor " << std::endl;

}