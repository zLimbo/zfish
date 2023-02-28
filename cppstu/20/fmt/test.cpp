#include <cassert>
#include <format>
#include <string>
 
int main()
{
    std::string message = std::format("The answer is {}.", 42);
    assert( message == "The answer is 42." );
}
