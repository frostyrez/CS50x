#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;
int winner;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
int find_source(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                // return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    // printf("Add pairs done\n");
    sort_pairs();
    // printf("Sort pairs done\n");
    lock_pairs();
    // printf("Lock pairs done\n");
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i],name) == 0)
        {
            // candidates[i].votes = candidates[i].votes + 1;
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < (candidate_count-1); i++)
    {
        for (int j = i+1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] = preferences[ranks[i]][ranks[j]] + 1;
        // printf("Preferences[%i][%i] updated to %i.\n",ranks[i],ranks[j],
        //     preferences[ranks[i]][ranks[j]]);
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                // Log the winner
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                // The below doesnt matter!
                // pairs[pair_count].winner = preferences[i][j];
                // pairs[pair_count].loser = preferences[j][i];
                // printf("Pair number %i: %s beats %s by a score of %i to %i\n",
                    // pair_count,candidates[i],candidates[j],
                    // pairs[pair_count].winner,pairs[pair_count].loser);
                pair_count = pair_count + 1;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int flag;
    int loop_count = 0;
    // printf("Initial order: \n");
    for (int i = 0; i < pair_count; i++)
    {
        //  printf("%s beats %s by a margin of %i-%i\n",
        //     candidates[pairs[i].winner],candidates[pairs[i].loser],
        //     preferences[pairs[i].winner][pairs[i].loser],
        //     preferences[pairs[i].loser][pairs[i].winner]);
    }
    do
    {
        flag = 0;
        for (int i = 0; i < (pair_count - 1); i++)
        {
            int diff1;
            int diff2;
            // printf("Comparing cand %i - cand %i to cand %i - cand %i\n",
            //     pairs[i].winner,pairs[i].loser,pairs[i+1].winner,pairs[i+1].loser);
            pair temp;
            diff1 = preferences[pairs[i].winner][pairs[i].loser];
            diff2 = preferences[pairs[i+1].winner][pairs[i+1].loser];
            // printf("diff1 = %i, diff2 = %i\n",diff1,diff2);
            if (diff2 > diff1)
            {
                temp.winner = pairs[i].winner;
                temp.loser = pairs[i].loser;
                pairs[i].winner = pairs[i+1].winner;
                pairs[i].loser = pairs[i+1].loser;
                pairs[i+1].winner = temp.winner;
                pairs[i+1].loser = temp.loser;
                flag = 1;
                // printf("Swapped.\n");
            }
        }
        loop_count++;
    } while (flag == 1);

    // printf("Post-loop margins:\n");
    for (int i = 0; i < pair_count; i++)
    {
        // printf("%s beats %s by a margin of %i-%i\n",
        //     candidates[pairs[i].winner],candidates[pairs[i].loser],
        //     preferences[pairs[i].winner][pairs[i].loser],
        //     preferences[pairs[i].loser][pairs[i].winner]);
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    int i;
    for (i = 0; i < pair_count; i++) // Lock in all pairs
    {
        locked[pairs[i].winner][pairs[i].loser] = true;
        // printf("Locked in %s over %s.\n",candidates[pairs[i].winner],candidates[pairs[i].loser]);
    }

    // print locked graph
    for (i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // printf("%d ",locked[i][j]);
        }
        // printf("\n");
    }

    // If there's a cycle
    winner = find_source();
    if (winner == 99)
    {
        // Remove last lock
        locked[pairs[pair_count-1].winner][pairs[pair_count-1].loser] = false;
        winner = find_source();
    }
    else
    {
        print_winner();
    }

    // print locked graph
    for (i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // printf("%d ",locked[i][j]);
        }
        // printf("\n");
    }

    return;
}

// Find source
int find_source(void)
{
    int flag;
    // printf("Finding source.\n");
    // Check each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        flag = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            flag = flag + locked[i][j];
        }
        if (flag == 0)
            {
                return i;
            }
    }
    // printf("seems to be a cycle.\n");
    return 99;
}


// Print the winner of the election
void print_winner(void)
{
    printf("%s\n", candidates[winner]);
    return;
}