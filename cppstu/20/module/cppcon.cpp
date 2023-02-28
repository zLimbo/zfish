// cppcon.cpp 
export module cppcon; 
namespace CppCon { 
    auto GetWelcomeHelper() {  return "Welcome to CppCon 2019!";  } 
    export auto GetWelcome() { return GetWelcomeHelper();} 
}