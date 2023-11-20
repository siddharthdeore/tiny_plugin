
#include <memory>

#include "examples/PluginManager.h"

int main()
{
    PluginManager manager;

    manager.load_library("SimplePlugin");
    manager.load_library("ComplexPlugin");

    // simple shared library instance
    auto instance_simple = manager.create_instance_sptr<void *>("SimplePlugin");

    // shared library instance with arguments, make sure to pass valid arguments
    auto x = std::make_shared<int>(123);
    auto instance_complex = manager.create_instance_sptr<void *>("ComplexPlugin", x);
    auto instance_simple2 = manager.create_instance_sptr<void *>("SimplePlugin2");

    return 0;
}
