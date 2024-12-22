#include <string>

#pragma once

namespace panachage
{

    typedef struct
    {
        typedef unsigned int id_type;

        const id_type id;
        const std::string name;
    } candidate;

}