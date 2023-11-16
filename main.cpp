
#include <memory>

#include <tiny_plugin/SharedLibrary.h>
//#include "examples/plugins/SimplePlugin.h"

int main()
{
    SharedLibrary myLibrary("simple_function");

    // Check if the library is loaded successfully
    if (myLibrary.is_loaded())
    {
        // Use the loaded library symbol
        void *addSymbol = myLibrary.get_symbol("add");

        if (addSymbol != nullptr)
        {
            // Typecast the function pointer to the correct type
            using AddFunction = int (*)(int, int);
            AddFunction addFunction = reinterpret_cast<AddFunction>(addSymbol);

            // Use the function from the loaded library
            int result = addFunction(5, 7);
            std::cout << "Result of adding 5 and 7: " << result << std::endl;
        }
        else
        {
            std::cerr << "Failed to get symbol 'add' from the library." << std::endl;
        }
    }
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
            auto i3 = simple.make_plugin_instance<void *>();
            simple.destroy_plugin(i3);
        }
        {
            auto i4 = simple.make_plugin_sptr<void *>();
        }
        {
            auto i5 = simple.make_plugin_sptr<void>();
        }
        {
            auto i6 = simple.make_plugin_instance<void>();
            delete i6;
        }
    }

    return 0;
}
