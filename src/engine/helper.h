#ifndef HELPER_H
#define HELPER_H

#include <string>

bool string_bool( std::string text);
bool file_exist( std::string file);

#define vec3 irr::core::vector3df

class helper
{
    public:
        helper();
        virtual ~helper();

    protected:

    private:
};

#endif // HELPER_H
