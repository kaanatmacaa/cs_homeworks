#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

// KAAN ATMACA'S CS307 HW2

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

typedef int bool;

struct arg_struct
{
    int **array;
    int n;
    char *player;
} * p1, *p2, *args;

void printarray(int **array, int SIZE)
{
    int i;
    int j;
    int val;
    char *v;
    for (j = 0; j < SIZE; j++)
    {
        for (i = 0; i < SIZE; i++)
        {
            val = array[j][i];
            if (val == 1)
                v = "x";
            else if (val == 2)
                v = "o";
            else
                v = " ";
            printf("[%s] ", v);
        }
        printf("\n");
    }
}

int checkForP(int **array, int n, int player)
{
    int check;
    for (int i = 0; i < n; i++) // checking rows
    {
        check = 1;
        for (int j = 0; j < n; j++)
        {
            if (array[i][j] != player)
                check = 0;
        }
        if (check == 1)
            return player; // wins
    }
    for (int i = 0; i < n; i++) // checking columns
    {
        check = 1;
        for (int j = 0; j < n; j++)
        {
            if (array[j][i] != player)
                check = 0;
        }
        if (check == 1)
            return player; // wins
    }

    for (int i = 0; i < n; i++) // checking diagonal
    {
        check = 1;
        if (array[i][i] != player)
        {
            check = 0;
            break;
        }
    }
    if (check == 1)
        return player;

    for (int i = n - 1; i >= 0; i--)
    {
        check = 1;
        if (array[i][n - i] != player)
        {
            check = 0;
            break;
        }
    }
    if (check == 1)
        return player;
    return 3;
}

void *game(void *arguments)
{
    pthread_mutex_lock(&mut);
    struct arg_struct *args = arguments;
    int **arr = args->array;
    int n = args->n;
    char *player = args->player;

    int ply;
    char *p = "X";
    if (player == p)
        ply = 1;
    else
        ply = 2;

    for (int i = 0; i < 1; i++)
    {
        int check = checkForP(arr, n, ply);
        if (check != 3)
            break;

        int row, column;
        row = rand() % n;
        column = rand() % n;
        while (arr[row][column] != 3)
        {
            row = rand() % n;
            column = rand() % n;
        }
        arr[row][column] = ply;
        printf("Player %s played on: (%d,%d)\n", player, row, column);
    }

    pthread_mutex_unlock(&mut);
}

int main(int argc, char *argv[]) // in arr 0 = O, 1 = X, 2 = Empty
{
    int n = atoi(argv[1]);
    printf("Board Size: %dx%d\n", n, n);
    int row, column;
    int **arr = malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++)
    {
        arr[i] = malloc(sizeof(int) * n);
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            arr[i][j] = 3;
        }
    }

    int count = 0;
    int total = n * n;

    bool check = 3;
    pthread_t x_thread, o_thread;
    p1 = malloc(sizeof(struct arg_struct) * 1);
    p1->array = arr;
    p1->n = n;
    p1->player = "X";

    p2 = malloc(sizeof(struct arg_struct) * 1);
    p2->array = arr;
    p2->n = n;
    p2->player = "O";

    for (int i = 0; i <= total - 2; i += 2)
    {
        pthread_create(&x_thread, NULL, game, p1);
        pthread_create(&o_thread, NULL, game, p2);
        pthread_join(x_thread, NULL);
        check = checkForP(arr, n, 1);
        if (check == 1)
            break;
        check = checkForP(arr, n, 2);
        if (check == 2)
            break;
        pthread_join(o_thread, NULL);
    }
    if (check == 1)
        pthread_join(o_thread, NULL); // since it can not join there will be a break
    else if (check == 3 && total % 2 == 1)
    {
        pthread_create(&x_thread, NULL, game, p1);
        pthread_join(x_thread, NULL);
        check = checkForP(arr, n, 1);
    }

    printf("Game end\n");
    if (check == 1)
        printf("Winner is X\n");
    else if (check == 2)
        printf("Winner is O\n");
    else
        printf("It is a tie\n");

    printarray(arr, n);

    for (int i = 0; i < n; i++)
        free(arr[i]);
    free(arr);

    return 0;
}