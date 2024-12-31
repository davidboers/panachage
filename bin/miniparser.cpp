#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string.h>

#include "../display.cpp"
#include "../votes.tab.h"
#include "../tests/templates.hpp"

using namespace panachage;

struct argument
{
    const char shorthand;
    const char *longhand;
    const bool takes_value;
    const char *help_guide;
};

static const argument version_arg = argument{'v', "version", false, "Display software version."};
static const argument help_arg = argument{'h', "help", false, "Display this menu."};
static const argument examples_arg = argument{'e', "examples", false, "Display some example expressions."};

static const int num_args = 3;
static const argument *arg_list[num_args] = {
    &version_arg,
    &help_arg,
    &examples_arg};

static const std::string unknown_arg_msg = "I don't recognize that argument. Try 'miniparser --help'.";

bool cmpArg(const char *passed, const argument *c)
{
    const int size_short = 2;
    char cmp_short[size_short];
    cmp_short[0] = '-';
    cmp_short[1] = c->shorthand;

    char cmp_long[255];
    strcpy(cmp_long, "--");
    strcat(cmp_long, c->longhand);
    const int size_long = strlen(cmp_long);

    return (strncmp(passed, cmp_short, size_short) == 0) ||
           (strncmp(passed, cmp_long, size_long) == 0);
}

void helpMsg(void)
{
    std::cout << "Mini-vote parser command line engine." << std::endl
              << std::endl;

    for (int i = 0; i < num_args; i++)
    {
        const argument *arg = arg_list[i];
        std::string full_short = "-" + std::string(&arg->shorthand);
        std::string full_long = "--" + std::string(arg->longhand);
        std::cout << std::setw(3) << full_short
                  << std::setw(11) << full_long
                  << "  " << std::string(arg->help_guide)
                  << std::endl;
    }
}

int main(int argc, char **argv)
{
    char *passed;
    std::vector<partylist *> lists;
    for (int i = 1; i < argc; i++)
    {
        passed = argv[i];

        if (cmpArg(passed, &version_arg))
        {
            std::cout << "1.0.0-dev" << std::endl;
            return 0;
        }
        else if (cmpArg(passed, &help_arg))
        {
            helpMsg();
            return 0;
        }
        else if (cmpArg(passed, &examples_arg))
        {
            std::string line;
            std::ifstream examplesFile("examples.txt");
            while (std::getline(examplesFile, line))
            {
                std::cout << line << std::endl;
            }
            examplesFile.close();
            return 0;
        }
        else if (passed[0] == '-')
        {
            std::cout << unknown_arg_msg << std::endl;
            return 1;
        }
        else
        {
            if (lists.size() == 0)
            {
                lists = {new TEMP_LIST_A,
                         new TEMP_LIST_B};
            }

            parseSingleVote(passed, lists);
        }
    }

    return 0;
}