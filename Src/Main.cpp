#include <SSTL/Types.h>
#include <SSTL/Memory.h>
#include <SSTL/Config.h>

#include <iostream>
#include <stdexcept>

int main()
{
    static_assert(SSTL_DEBUG != SSTL_RELEASE, "SSTL_DEBUG and SSTL_RELEASE must be mutually exclusive.");

#if SSTL_DEBUG
    std::cout << "SSTL_DEBUG build" << std::endl;
#else
    std::cout << "SSTL_RELEASE build" << std::endl;
#endif

    try
    {
        SSTL_THROW(std::runtime_error("SSTL_THROW test"));
    }
    catch (const std::exception& e)
    {
        std::cout << "Caught: " << e.what() << std::endl;
    }

    std::cin.get();
    return(0);
}
