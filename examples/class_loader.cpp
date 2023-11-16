
#include <memory>

#include <tiny_plugin/SharedLibrary.h>
#include "plugins/AbstractPlugin.hpp"

int main()
{
    SharedLibrary simple("SimplePlugin");
    if (simple.is_loaded())
    {

        {
            // class constructor
            using Consturctor = void *(*)();
            Consturctor constructor = nullptr;
            constructor = reinterpret_cast<Consturctor>(simple.get_symbol("plugin_constructor"));
            auto instance = constructor();

            // class destructor
            using DestroyFunc = void *(*)(void *);
            DestroyFunc destructFunc = nullptr;
            destructFunc = reinterpret_cast<DestroyFunc>(simple.get_symbol("plugin_destructor"));
            destructFunc(instance);
        }
        {
            auto inst = (simple.create_instance<void *>());
            simple.destroy_instance(inst);
        }
        {
            auto inst = simple.create_instance<AbstractPlugin *>();
            simple.destroy_instance(inst);
        }
        {
            auto inst = simple.create_instance<AbstractPlugin>();
            simple.destroy_instance(inst);
        }

        {
            auto inst = simple.make_plugin_sptr<void *>();
        }
        {
            auto inst = simple.make_plugin_sptr<AbstractPlugin *>();
        }
        {
            auto inst = simple.make_plugin_sptr<AbstractPlugin>();
        }
    }

    return 0;
}
