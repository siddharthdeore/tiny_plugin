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
    int y;

private:
};

EXPORT_CLASS(ComplexPlugin,std::shared_ptr<int>)
#endif