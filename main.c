#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#define NUM_VERTEX 5
#define K_CLIQUE 5

int nondet_int();

bool is_clique(int graph[][NUM_VERTEX], int vertex[], int length)
{
    int i = 0;
    while (i < length && vertex[i] != -1)
    {
        int j = i + 1;

        while (j < length && vertex[i] != -1)
        {
            if (vertex[j] != -1)
            {
                if (graph[vertex[i]][vertex[j]] == 0)
                {
                    return false;
                }
            }

            j++;
        }

        i++;
    }

    return true;
}

int main(int argc, char const *argv[])
{
    int graph[NUM_VERTEX][NUM_VERTEX] = {
        {0, 1, 0, 1, 1},
        {1, 0, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {1, 1, 1, 0, 1},
        {1, 0, 0, 1, 0}};

    int vertex[NUM_VERTEX];

    for (int i = K_CLIQUE - 1; i >= 0; i--)
    {
        __CPROVER_array_set(vertex, -1);

        for (int j = 0; j <= i; j++)
        {
            int guess = nondet_int();
            __VERIFIER_assume(guess >= 0 && guess <= NUM_VERTEX - 1);

            for (int l = 0; l < NUM_VERTEX; l++)
            {
                __VERIFIER_assume(guess != vertex[l]);
            }

            vertex[j] = guess;
        }

        assert(!is_clique(graph, vertex, K_CLIQUE));
    }

    return 0;
}
