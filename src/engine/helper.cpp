#include "helper.h"

#include <unistd.h> // - F_OK

bool string_bool( std::string text) {
    if( text == "true" || text == "True" || text == "TRUE" || text == "1")
        return true;
    return false;
}

bool file_exist( std::string file) {
    if( access( file.c_str(), F_OK ) != -1 )
        return true;
    return false;
}


helper::helper()
{
    //ctor
}

helper::~helper()
{
    //dtor
}
