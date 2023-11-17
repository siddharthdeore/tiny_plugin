#ifndef COMPLEXPLUGIN_H
#define COMPLEXPLUGIN_H

#pragma once
#include <tiny_plugin/visibility.h>
#include <memory>
// plugin example class constructor argument
class ComplexPlugin
{
public:
    ComplexPlugin(std::shared_ptr<int> x);
    ~ComplexPlugin();

private:
};

EXPORT_PLUGIN(ComplexPlugin,std::shared_ptr<int>);
#endif