#include <cstdio>
#include <iostream>
#include <cstdlib>
#define LAB_SIZE 4

void print_arr (double arr[LAB_SIZE][LAB_SIZE])
{
    for (int i = 0; i < LAB_SIZE; ++i)
    {
        for (int j = 0; j < LAB_SIZE; ++j)
            printf ("%6.4f\t", arr[i][j]);
        printf ("\n");
    }
}

void print_lab (double lab[LAB_SIZE*LAB_SIZE][LAB_SIZE*LAB_SIZE])
{
    for (int i = 0; i < LAB_SIZE-1; ++i)
    {
        for (int j = 0; j < LAB_SIZE-1; ++j)
        {
            printf("%d\t%c\t", i*LAB_SIZE+j, lab[i*LAB_SIZE+j][i*LAB_SIZE+j+1]?'=':'\0');
        }
        std::cout << (i+1)*LAB_SIZE-1 << '\n';
    }
}

int main()
{
    double arr[LAB_SIZE][LAB_SIZE];
    double lab[LAB_SIZE*LAB_SIZE][LAB_SIZE*LAB_SIZE];   /* matryca ze wszystkimi łukami - [poczatek][koniec]
                                                         * wartość 0 - brak polaczenia, !0 - waga łuku */
    srand(0);
    for (int i = 0; i < LAB_SIZE; ++i)
        for (int j = 0; j < LAB_SIZE; ++j)
            arr[i][j] = (double)rand() / RAND_MAX * 10; // generowanie wagi dla wierzchołków
    print_arr(arr);

    for (int i = 0; i < LAB_SIZE*LAB_SIZE; ++i)
        for (int j = 0; j < LAB_SIZE*LAB_SIZE; ++j)
            lab[i][j] = 0.0;
    short options[5]; // 1/2/3/4 - Prawo/Dół/Lewo/Góra   
    short connection_exists;
    signed int diff;
    for (int i = 0; i < LAB_SIZE; ++i)
        for (int j = 0; j < LAB_SIZE; ++j)
        {
            connection_exists = 0;
            for (short k = 0; k < 5; ++k) options[k] = 0; // options[4] - poczatkowa liczba opcji
            unsigned int my_rand = rand();
            if (j != 0)             options[options[4]++] = 3; // lewo dostepne
            if (j != LAB_SIZE - 1)  options[options[4]++] = 1; // prawo dostepne
            if (i != 0)             options[options[4]++] = 4; // gora dostepna
            if (i != LAB_SIZE - 1)  options[options[4]++] = 2; // dol dostepny
            for (int k = 0; k < options[4]; ++k) std::cout << options[k];
            std::cout << '\n';
            std::cout << i*LAB_SIZE+j << ": ";
            for (int k = 0; k < options[4]; ++k) // dla każdego dostępnego kierunku decyduję, czy istnieje połączenie
            {
                // diff = (options[k]/3>=1?-1:1)*(options[k]%2?LAB_SIZE:1);
                // std::cout << "diff: " << diff << '\n';
                if (my_rand % 16 < 3) // przyjalem prawdopodobienstwo polaczenia 9/16
                {
                    switch (options[k])
                    {
                        case 1: lab[i*LAB_SIZE+j][i*LAB_SIZE+j+1]   = lab[i*LAB_SIZE+j+1][i*LAB_SIZE+j]   = (arr[i][j]+arr[i][j+1])/2.0; std::cout << 'P'; break;
                        case 2: lab[i*LAB_SIZE+j][(i+1)*LAB_SIZE+j] = lab[(i+1)*LAB_SIZE+j][i*LAB_SIZE+j] = (arr[i][j]+arr[i+1][j])/2.0; std::cout << 'D'; break;
                        case 3: lab[i*LAB_SIZE+j][i*LAB_SIZE+j-1]   = lab[i*LAB_SIZE+j-1][i*LAB_SIZE+j]   = (arr[i][j]+arr[i][j-1])/2.0; std::cout << 'L'; break;
                        case 4: lab[i*LAB_SIZE+j][(i-1)*LAB_SIZE+j] = lab[(i-1)*LAB_SIZE+j][i*LAB_SIZE+j] = (arr[i][j]+arr[i-1][j])/2.0; std::cout << 'G'; break;
                    }
                    //lab[i*LAB_SIZE+j][i*LAB_SIZE+j+diff] = lab[i*LAB_SIZE+j+diff][i*LAB_SIZE+j] = (arr[i][j] + (options[k]%2?arr[i+diff/LAB_SIZE][j]:arr[i][diff])) / 2;
                    std::cout << options[k];
                    connection_exists = 1;
                }
                my_rand >>=4;
            }
            if (! connection_exists)
                switch (options[my_rand%options[4]+1])
                {
                    case 1: lab[i*LAB_SIZE+j][i*LAB_SIZE+j+1]   = lab[i*LAB_SIZE+j+1][i*LAB_SIZE+j]   = (arr[i][j]+arr[i][j+1])/2.0; std::cout << "\t dolosowano P"; break;
                    case 2: lab[i*LAB_SIZE+j][(i+1)*LAB_SIZE+j] = lab[(i+1)*LAB_SIZE+j][i*LAB_SIZE+j] = (arr[i][j]+arr[i+1][j])/2.0; std::cout << "\t dolosowano D"; break;
                    case 3: lab[i*LAB_SIZE+j][i*LAB_SIZE+j-1]   = lab[i*LAB_SIZE+j-1][i*LAB_SIZE+j]   = (arr[i][j]+arr[i][j-1])/2.0; std::cout << "\t dolosowano L"; break;
                    case 4: lab[i*LAB_SIZE+j][(i-1)*LAB_SIZE+j] = lab[(i-1)*LAB_SIZE+j][i*LAB_SIZE+j] = (arr[i][j]+arr[i-1][j])/2.0; std::cout << "\t dolosowano G"; break;
                }
            std::cout << "\n\n";
        }
    print_lab(lab);
    return 0;
}