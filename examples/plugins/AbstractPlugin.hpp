#ifndef ABSTRACT_PLUGIN_H
#define ABSTRACT_PLUGIN_H

#pragma once

class AbstractPlugin
{
private:
    /* data */
public:
    template <typename... Args>
    AbstractPlugin(Args... args){}
    ~AbstractPlugin(){}
};

#endif