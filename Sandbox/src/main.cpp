#include <Primitive/Core/Application.hpp>
#include <iostream>
#include <exception>

int main()
{
    try
    {
        primitive::Application application;
        application.Run();
    }
    catch (const std::exception& e)
    {
        std::cerr << "\n[ENGINE CRITICAL ERROR] " << e.what() << "\n" << std::endl;
        return -1;
    }
    std::cin.get();
    return 0;
}