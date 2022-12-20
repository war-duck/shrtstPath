#include <cstdio>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#define LAB_SIZE 5

void print_arr (double lab[LAB_SIZE*LAB_SIZE][LAB_SIZE*LAB_SIZE])
{
    for (int i = 0; i < LAB_SIZE*LAB_SIZE; ++i)
    {
        for (int j = 0; j < LAB_SIZE*LAB_SIZE; ++j)
            printf ("%3.2f ", lab[i][j]);
        printf ("\n\n");
    }
}

void print_lab (double lab[LAB_SIZE*LAB_SIZE][LAB_SIZE*LAB_SIZE], int start = -1, int end = -1)
{
    std::string full (2, char(219)), empty = "  ";
    std::cout << std::string(4*LAB_SIZE+2, char(219));
    for (int i = 0; i < LAB_SIZE; ++i)
    {
        //if (i != 0 && i != LAB_SIZE-1)
            std::cout << '\n';
            for (int j = 0; j < LAB_SIZE; ++j)
            {
            if (j == 0) std::cout << full;
                if (j != LAB_SIZE-1)
                    std::cout << empty << (lab[i*LAB_SIZE+j][i*LAB_SIZE+j+1]?empty:full);
                else std::cout << empty << full;
            }
            if (i == LAB_SIZE-1) break;
            std::cout << '\n' << full;
            for (int j = 0; j < LAB_SIZE; ++j)
            {
                std::cout << (lab[i*LAB_SIZE+j][(i+1)*LAB_SIZE+j]?empty:full) << full;
            }
        
    }
    std::cout << '\n' << std::string(4*LAB_SIZE+2, char(219)) << '\n';
    //std::cout << full << empty << full << empty << full;
}

int main()
{
    double arr[LAB_SIZE][LAB_SIZE];
    double lab[LAB_SIZE*LAB_SIZE][LAB_SIZE*LAB_SIZE];   /* matryca ze wszystkimi łukami - [poczatek][koniec]
                                                         //* wartość 0 - brak polaczenia, !0 - waga łuku */
    // // int seed;
    // // std::cin >> seed;
    // // srand(seed);
    int seed;
    std::cin >> seed;
    srand(time(NULL));
    for (int i = 0; i < LAB_SIZE; ++i)
        for (int j = 0; j < LAB_SIZE; ++j)
            arr[i][j] = (double)rand() / RAND_MAX * 10; // generowanie wagi dla wierzchołków
    //print_arr(arr);

    for (int i = 0; i < LAB_SIZE*LAB_SIZE; ++i)
        for (int j = 0; j < LAB_SIZE*LAB_SIZE; ++j)
            lab[i][j] = 0.0;
    short options[5]; // 1/2/3/4 - Prawo/Dół/Lewo/Góra. [5] - l. opcji
    //bool down, right;
    short connection_exists;
    int diff, sgn;
    for (int i = 0; i < LAB_SIZE; ++i)
    {
        for (int j = 0; j < LAB_SIZE; ++j)
        {
            connection_exists = 0;
            //for (short k = 0; k < 5; ++k) options[k] = 0; // options[4] - poczatkowa liczba opcji
            unsigned int my_rand = rand();

            // down = right = 1;
            // if (i == LAB_SIZE-1)  down = 0;
            // if (j == LAB_SIZE-1) right = 0;
            //std::cout << right << down << '\t';
            if (i != LAB_SIZE-1 && my_rand % 16 < seed) // decyzja o polaczeniu na prawo
            {
                lab[i*LAB_SIZE+j][(i+1)*LAB_SIZE+j] = lab[(i+1)*LAB_SIZE+j][i*LAB_SIZE+j] = (arr[i][j]+arr[i+1][j])/2.0;
                my_rand >>= 1;
                connection_exists = 1;
            }
            if (j != LAB_SIZE-1 && my_rand % 16 < seed) // decyzja na polaczeniu w dol
            {
                lab[i*LAB_SIZE+j][i*LAB_SIZE+j+1]   = lab[i*LAB_SIZE+j+1][i*LAB_SIZE+j]   = (arr[i][j]+arr[i][j+1])/2.0;
                my_rand >>= 1;
                connection_exists = 1;
            }
            if (!connection_exists)
            {
                for (int x = 0; x < 5; ++x) options[x] = 0;
                if (j != 0)             options[options[4]++] = 3; // lewo dostepne
                if (j != LAB_SIZE - 1)  options[options[4]++] = 1; // prawo dostepne
                if (i != 0)             options[options[4]++] = 4; // gora dostepna
                if (i != LAB_SIZE - 1)  options[options[4]++] = 2; // dol dostepny
                for (int x = 0; x < options[x]; ++x);
                sgn = (options[my_rand%options[4]]/3>=1?-1:1);
                diff = (options[my_rand%options[4]]%2?1:LAB_SIZE);
                lab[i*LAB_SIZE+j][i*LAB_SIZE+j+diff*sgn] = lab[i*LAB_SIZE+j+diff*sgn][i*LAB_SIZE+j] = (arr[i][j]+arr[i+(diff/4?1:0)*sgn][j+(diff%4?1:0)*sgn])/2.0;
            }
        }
    }
    //print_arr(lab);
    print_lab(lab);
    return 0;
}