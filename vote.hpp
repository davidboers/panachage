#include <vector>
#include <string>

#include "partylist.cpp"

#pragma once

namespace panachage
{
    class Vote
    {
    protected:
        int copies;
        int ln_parsed;
        bool from_file;

        inline Vote(const int copies = 1) : copies(copies), from_file(false) {}

    public:
        virtual void count(std::vector<partylist *> lists) = 0;
        virtual bool validate() = 0;
        /* Indicates whether the parameter vote is less than this vote. Ignores the number of copies.
         * If two votes of different implementing classes are compared, the comparison will return false.
         * @param vote The vote to compare to.
         */
        virtual bool operator<(const Vote &vote) const = 0;
        virtual std::string encode() const = 0;

        inline void setCopies(const int copies) { this->copies = copies; }
        inline int getCopies() const { return copies; }
        inline void setLnParsed(const int ln_parsed)
        {
            this->ln_parsed = ln_parsed;
            this->from_file = true;
        }
        inline int getLnParsed() const { return ln_parsed; }

        struct PtrComparator
        {
            inline bool operator()(const Vote *a, const Vote *b) const
            {
                return *a < *b;
            }
        };
    };
}