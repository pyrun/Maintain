#include "helper.h"

bool string_bool( std::string text) {
    if( text == "true" || text == "True" || text == "TRUE" || text == "1")
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
