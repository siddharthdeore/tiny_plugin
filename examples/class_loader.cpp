
#include <memory>

#include <tiny_plugin/SharedLibrary.h>
#include "plugins/AbstractPlugin.hpp"
#include "plugins/ComplexPlugin.h"
int main()
{

    // following sub snipets represents diffrent ways to load and create instance of class
    SharedLibrary simple("SimplePlugin");
    if (simple.is_loaded())
    {

        {
            // class constructor
            using Consturctor = void *(*)();
            Consturctor constructor = nullptr;
            constructor = reinterpret_cast<Consturctor>(simple.get_symbol("class_constructor"));
            auto instance = constructor();

            // class destructor
            using DestroyFunc = void *(*)(void *);
            DestroyFunc destructFunc = nullptr;
            destructFunc = reinterpret_cast<DestroyFunc>(simple.get_symbol("class_destructor"));
            destructFunc(instance);
        }
        {
            auto inst = (simple.create_instance_ptr<void>());
            simple.destroy_instance(inst);
        }
        {
            auto inst = simple.create_instance_ptr<void>();
            simple.destroy_instance(inst);
        }
        {
            auto inst = simple.create_instance_ptr<void>();
            simple.destroy_instance(inst);
        }

        {
            auto inst = simple.create_instance_sptr<void *>();
        }
        {
            auto inst = simple.create_instance_sptr<AbstractPlugin *>();
        }
        {
            auto inst = simple.create_instance_sptr<AbstractPlugin>();
        }
    }
    ComplexPlugin *inst1;
    {
        SharedLibrary complex("ComplexPlugin");
        if (complex.is_loaded())
        {
            // class constructor defination
            using Consturctor = void *(*)(const std::shared_ptr<int>);
            Consturctor constructor = nullptr;
            constructor = reinterpret_cast<Consturctor>(complex.get_symbol("class_constructor"));
            auto instance = constructor(std::make_shared<int>(5));
            complex.destroy_instance(instance);

            auto inst = complex.create_instance_ptr<void>(std::make_shared<int>(55));
            std::cout << Type2Name(inst) << std::endl;
            inst1 = complex.create_instance_ptr<ComplexPlugin>(std::make_shared<int>(75));
        }
    }
    std::cout << Type2Name(inst1) << inst1->y << std::endl;

    return 0;
}
