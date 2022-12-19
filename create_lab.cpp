#include <cstdio>
#include <iostream>
#include <string>
#include <cstdlib>
#define LAB_SIZE 6

void print_arr (double lab[LAB_SIZE*LAB_SIZE][LAB_SIZE*LAB_SIZE])
{
    for (int i = 0; i < LAB_SIZE*LAB_SIZE; ++i)
    {
        for (int j = 0; j < LAB_SIZE*LAB_SIZE; ++j)
            printf ("%3.2f ", lab[i][j]);
        printf ("\n\n");
    }
}

void print_lab (double lab[LAB_SIZE*LAB_SIZE][LAB_SIZE*LAB_SIZE])
{
    std::string full (2, char(219)), empty = "  ";
    for (int i = 0; i < LAB_SIZE; ++i)
    {
        //if (i != 0 && i != LAB_SIZE-1)
        {
            for (int j = 0; j < LAB_SIZE; ++j)
            {
                if (j == 0) std::cout << full;
                if (j != LAB_SIZE-1)
                    std::cout << empty << (lab[i*LAB_SIZE+j][i*LAB_SIZE+j+1]?empty:full);
                else std::cout << empty;
            }
            for (int j = 0; j < LAB_SIZE; ++j)
            {
                if (j == 0 || j == LAB_SIZE-1)
                {
                    std::cout << full;
                }
                std::cout << (lab[i*LAB_SIZE+j][(i+1)*LAB_SIZE+j]?empty:full) << full;
            }
            std::cout << '\n';
            continue;
        }
        
    }std::cout << std::string(4*LAB_SIZE-4, char(219)) << '\n';
    //std::cout << full << empty << full << empty << full;
}

int main()
{
    double arr[LAB_SIZE][LAB_SIZE];
    double lab[LAB_SIZE*LAB_SIZE][LAB_SIZE*LAB_SIZE];   /* matryca ze wszystkimi łukami - [poczatek][koniec]
                                                         * wartość 0 - brak polaczenia, !0 - waga łuku */
    std::cout << "ziarno:\n";
    // int seed;
    // std::cin >> seed;
    // srand(seed);
    int seed;
    std::cin >> seed;
    srand(5);
    for (int i = 0; i < LAB_SIZE; ++i)
        for (int j = 0; j < LAB_SIZE; ++j)
            arr[i][j] = (double)rand() / RAND_MAX * 10; // generowanie wagi dla wierzchołków
    //print_arr(arr);

    for (int i = 0; i < LAB_SIZE*LAB_SIZE; ++i)
        for (int j = 0; j < LAB_SIZE*LAB_SIZE; ++j)
            lab[i][j] = 0.0;
    //short options[5]; // 1/2/3/4 - Prawo/Dół/Lewo/Góra   
    //bool down, right;
    short connection_exists;
    signed int diff;
    for (int i = 0; i < LAB_SIZE; ++i)
    {
        for (int j = 0; j < LAB_SIZE; ++j)
        {
            connection_exists = 0;
            //for (short k = 0; k < 5; ++k) options[k] = 0; // options[4] - poczatkowa liczba opcji
            unsigned int my_rand = rand();
            // if (j != 0)             options[options[4]++] = 3; // lewo dostepne
            // if (j != LAB_SIZE - 1)  options[options[4]++] = 1; // prawo dostepne
            // if (i != 0)             options[options[4]++] = 4; // gora dostepna
            // if (i != LAB_SIZE - 1)  options[options[4]++] = 2; // dol dostepny
            // down = right = 1;
            // if (i == LAB_SIZE-1)  down = 0;
            // if (j == LAB_SIZE-1) right = 0;
            //std::cout << right << down << '\t';
            if (i != LAB_SIZE-1 && rand() % 16 < seed)
            {
                lab[i*LAB_SIZE+j][(i+1)*LAB_SIZE+j] = lab[(i+1)*LAB_SIZE+j][i*LAB_SIZE+j] = (arr[i][j]+arr[i+1][j])/2.0;
                //my_rand >>= 4;
            }
            if (j != LAB_SIZE-1 && rand() % 16 < seed)
            {
                lab[i*LAB_SIZE+j][i*LAB_SIZE+j+1]   = lab[i*LAB_SIZE+j+1][i*LAB_SIZE+j]   = (arr[i][j]+arr[i][j+1])/2.0;
                my_rand >>= 4;
            }
            //std::cout << "\t\t";
            //std::cout << i*LAB_SIZE+j << ": ";
            //for (int k = 0; k < options[4]; ++k) std::cout << options[k];

            //for (int k = 0; k < options[4]; ++k) // dla każdego dostępnego kierunku decyduję, czy istnieje połączenie
            // {
            //     diff = (options[k]/3>=1?-1:1)*(options[k]%2?1:LAB_SIZE);
            //     std::cout << diff;
            //     if (my_rand % 16 < 9)

            // }
            // {
            //     // std::cout << "diff: " << diff << '\n';
            //     std::cout << "los: " << options[k] << '\t';
            //     if (my_rand % 16 < 9) // przyjalem prawdopodobienstwo polaczenia 9/16
            //     {
            //         switch (options[k])
            //         {
            //             case 1: lab[i*LAB_SIZE+j][i*LAB_SIZE+j+1]   = lab[i*LAB_SIZE+j+1][i*LAB_SIZE+j]   = (arr[i][j]+arr[i][j+1])/2.0; std::cout << 'P'; break;
            //             case 2: lab[i*LAB_SIZE+j][(i+1)*LAB_SIZE+j] = lab[(i+1)*LAB_SIZE+j][i*LAB_SIZE+j] = (arr[i][j]+arr[i+1][j])/2.0; std::cout << 'D'; break;
            //             case 3: lab[i*LAB_SIZE+j][i*LAB_SIZE+j-1]   = lab[i*LAB_SIZE+j-1][i*LAB_SIZE+j]   = (arr[i][j]+arr[i][j-1])/2.0; std::cout << 'L'; break;
            //             case 4: lab[i*LAB_SIZE+j][(i-1)*LAB_SIZE+j] = lab[(i-1)*LAB_SIZE+j][i*LAB_SIZE+j] = (arr[i][j]+arr[i-1][j])/2.0; std::cout << 'G'; break;
            //         }
            //         //lab[i*LAB_SIZE+j][i*LAB_SIZE+j+diff] = lab[i*LAB_SIZE+j+diff][i*LAB_SIZE+j] = (arr[i][j] + (options[k]%2?arr[i+diff/LAB_SIZE][j]:arr[i][diff])) / 2;
            //         std::cout << options[k] << '\n';
            //         connection_exists = 1;
            //     }
            //     my_rand >>=4;
            // }
            // std::cout << "conn:" << connection_exists << "op4:" << options[4];
            // if (! connection_exists)
            //     switch (options[my_rand%(options[4])+1])
            //     {
            //         case 1: lab[i*LAB_SIZE+j][i*LAB_SIZE+j+1]   = lab[i*LAB_SIZE+j+1][i*LAB_SIZE+j]   = (arr[i][j]+arr[i][j+1])/2.0; std::cout << "\t dolosowano P"; break;
            //         case 2: lab[i*LAB_SIZE+j][(i+1)*LAB_SIZE+j] = lab[(i+1)*LAB_SIZE+j][i*LAB_SIZE+j] = (arr[i][j]+arr[i+1][j])/2.0; std::cout << "\t dolosowano D"; break;
            //         case 3: lab[i*LAB_SIZE+j][i*LAB_SIZE+j-1]   = lab[i*LAB_SIZE+j-1][i*LAB_SIZE+j]   = (arr[i][j]+arr[i][j-1])/2.0; std::cout << "\t dolosowano L"; break;
            //         case 4: lab[i*LAB_SIZE+j][(i-1)*LAB_SIZE+j] = lab[(i-1)*LAB_SIZE+j][i*LAB_SIZE+j] = (arr[i][j]+arr[i-1][j])/2.0; std::cout << "\t dolosowano G"; break;
            //     }
        }
        std::cout << "\n";
    }
    //print_arr(lab);
    print_lab(lab);
    return 0;
}