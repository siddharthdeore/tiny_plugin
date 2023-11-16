
#include <memory>

#include <tiny_plugin/SharedLibrary.h>
#include "plugins/SimplePlugin.h"

int main()
{
    SharedLibrary simple("SimplePlugin");
    if (simple.is_loaded())
    {

        {
            using Consturctor = void *(*)();
            Consturctor constructor = nullptr;
            constructor = reinterpret_cast<Consturctor>(simple.get_symbol("plugin_constructor"));
            auto instance = constructor();

            using DestroyFunc = void *(*)(void *);
            DestroyFunc destructFunc = nullptr;
            destructFunc = reinterpret_cast<DestroyFunc>(simple.get_symbol("plugin_destructor"));
            destructFunc(instance);
        }
        {
            auto i1 = (simple.make_plugin_instance<void *>());
            simple.destroy_plugin(i1);
        }
        {
            auto i2 = simple.make_plugin_sptr<void *>();
        }
        {
            auto i3 = simple.make_plugin_instance<SimplePlugin *>();
            simple.destroy_plugin(i3);
        }
        {
            auto i4 = simple.make_plugin_sptr<SimplePlugin *>();
        }
        {
            auto i5 = simple.make_plugin_sptr<SimplePlugin>();
        }
        {
            auto i6 = simple.make_plugin_instance<SimplePlugin>();
            delete i6;
        }
    }

    return 0;
}
