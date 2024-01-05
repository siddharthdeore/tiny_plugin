#ifndef SIMPLEPLUGIN_H
#define SIMPLEPLUGIN_H

#pragma once

#include <tiny_plugin/plugin_helper.h>
#include "AbstractPlugin.hpp"

class SimplePlugin : public AbstractPlugin
{
public:
    SimplePlugin();
    ~SimplePlugin();

private:
};

EXPORT_CLASS_NOARG(SimplePlugin)
#endif