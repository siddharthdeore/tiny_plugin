#ifndef SIMPLEPLUGIN_H
#define SIMPLEPLUGIN_H

#pragma once

#include <tiny_plugin/SharedLibrary.h>
#include "AbstractPlugin.hpp"

class SimplePlugin : public AbstractPlugin
{
public:
    SimplePlugin();
    ~SimplePlugin();

private:
};

EXPORT_PLUGIN(SimplePlugin)
#endif