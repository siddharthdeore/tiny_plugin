
#include <memory>

#include <tiny_plugin/SharedLibrary.h>

int main()
{
    SharedLibrary simple("SimplePlugin");

    if (simple.is_loaded())
    {
        auto instance = simple.create_instance_sptr<void *>();
    }

    return 0;
}
