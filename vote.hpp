#include <vector>

#include "partylist.cpp"

namespace panachage
{

    class Vote
    {
        virtual void count(std::vector<partylist> lists) = 0;
        virtual bool validate() = 0;
    };

}