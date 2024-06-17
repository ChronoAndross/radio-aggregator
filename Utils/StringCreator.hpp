#include <sstream>
#include <string>
#include <memory>

class StringCreator {
public:
    static std::string itos(int input) {
        std::stringstream ss;
        ss << input;
        return std::string(ss.str()) ;
    }

    static std::string uitos(uint32_t input) {
        std::stringstream ss;
        ss << input;
        return std::string(ss.str()) ;
    }

    // ripped from https://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
    template<typename ... Args>
    static std::string stringFormat( const std::string& format, Args ... args )
    {
        int size_s = std::snprintf( nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'
        if( size_s <= 0 ){ throw std::runtime_error( "Error during formatting." ); }
        auto size = static_cast<size_t>( size_s );
        std::unique_ptr<char[]> buf( new char[ size ] );
        std::snprintf( buf.get(), size, format.c_str(), args ... );
        return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
    }
};