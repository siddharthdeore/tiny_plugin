
#include <memory>

#include <tiny_plugin/SharedLibrary.h>

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

    return 0;
}
