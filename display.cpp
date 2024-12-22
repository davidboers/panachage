#include <math.h>
#include <stdio.h>

#include <string>

#include "partylist.cpp"
#include "settings.h"

namespace panachage
{

    void displayAllCandidates(std::vector<partylist *> lists)
    {
        const int cols = 3;
        const int rows = floor(lists.size() / cols) + 1;

        std::string margin(3, ' ');

        partylist *row_lists[cols];
        int row_length = cols;
        int index;
        for (int row = 0; row < rows; row++)
        {
            for (int i = 0; i < cols; i++)
            {
                index = row * cols + i;
                if (index >= lists.size())
                {
                    row_length = i;
                    break;
                }
                row_lists[i] = lists[index];
            }

            for (int i = 0; i < row_length; i++)
            {
                printf("| List: %-3i ALV: %-6i", row_lists[i]->id, row_lists[i]->at_large_votes);
                printf(margin.c_str());
            }
            printf("\n");

            for (int r = 1; r <= seats; r++)
            {
                for (int i = 0; i < row_length; i++)
                {
                    partylist *list = row_lists[i];
                    if (r <= list->candidate_votes.size())
                    {
                        std::vector<candidate::id_type> cs = list->candidateList();
                        const candidate::id_type cand_id = cs[r - 1];
                        printf("| %-3i | %-5i | %-5i |", r, cand_id, list->candidate_votes[cand_id]);
                        printf(margin.c_str());
                    }
                }
                printf("\n");
            }
        }
    }

}