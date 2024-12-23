#include <vector>

#include "partylist.cpp"

#pragma once

namespace panachage
{

    class Vote
    {
    protected:
        int copies;

        inline Vote(const int copies = 1) : copies(copies) {}

    public:
        virtual void count(std::vector<partylist *> lists) = 0;
        virtual bool validate() = 0;

        inline void setCopies(const int copies) { this->copies = copies; }
    };

}