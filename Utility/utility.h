#pragma once
#include <string>
#include <memory>

namespace Utility
{
    class IUtfConvertor
    {
    public:
        //utf8toutf16 function should be only used through IUtfConvertor interface - so the 
        //Tests of the classes using this function could easely provide its own mockups
        //For IUtfConvertor

        //Any class that wants to use utf8toutf16 has to provide 2 constructors
        //Default constructor used in production that will call the chain constructor with 
        //parameter IUtfConvertor and pass the IUtfConvertor::Create() to it
        //The second Constructor accepting IUtfConvertor::Create as a parameter will be used by Testing framework
        virtual std::wstring utf8toutf16(const std::string& input, bool ignore_invalid = true) = 0;
        virtual std::wstring utf8toutf16(const char* input, bool ignore_invalid = true) = 0;

        //The Factory function Used to create the real Converter object
        static std::unique_ptr<Utility::IUtfConvertor> Create();
    };
}//namespace Utility

std::wstring func(Utility::IUtfConvertor& iconv, std::string data);
