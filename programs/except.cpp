#include "except.h"

namespace except
{

void react()
{
    try
    {
        throw;
    }
    catch (std::exception& exc)
    {
        std::cerr << "exception: " << exc.what();
    }
    catch (...)
    {
        std::cerr << "unknown exception thrown";
    }
}

}
