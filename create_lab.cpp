#include <cstdio>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#define LAB_SIZE 4

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
    int con_num_arr[LAB_SIZE][LAB_SIZE];

    // // int seed;
    // // std::cin >> seed;
    // // srand(seed);
    int seed;
    //std::cout << "wprowadz prawdopodob.:\n";
    //std::cin >> seed;
    seed = 10;
    //seed = 10;
    srand(time(NULL));
    for (int i = 0; i < LAB_SIZE; ++i)
        for (int j = 0; j < LAB_SIZE; ++j)
        {
            arr[i][j] = (double)rand() / RAND_MAX * 10; // generowanie wagi dla wierzchołków
            con_num_arr[i][j] = 0;
        }
    for (int i = 0; i < LAB_SIZE*LAB_SIZE; ++i)
        for (int j = 0; j < LAB_SIZE*LAB_SIZE; ++j)
            lab[i][j] = 0.0;
    //short options[5]; Prawo/Dół/Lewo/Góra. [5] - l. opcji
    bool options[4];
    int option_ctr, con_ctr;
    //bool down, right;
    int diff, sgn;
    for (int i = 0; i < LAB_SIZE; ++i)
    {
        for (int j = 0; j < LAB_SIZE; ++j)
        {
            //std::cout << "nr: " << i*LAB_SIZE + j << ' ' << i << ' ' << j << '\n';
            for (short k = 0; k < 5; ++k) options[k] = 0;
            //unsigned int my_rand = rand();
            // down = right = 1;
            // if (i == LAB_SIZE-1)  down = 0;
            // if (j == LAB_SIZE-1) right = 0;
            //std::cout << right << down << '\t';
            if (i != LAB_SIZE-1 && rand() % 16 < seed) // decyzja o polaczeniu na prawo
            {
                lab[i*LAB_SIZE+j][(i+1)*LAB_SIZE+j] = (arr[i][j]+arr[i+1][j])/2.0;
                lab[(i+1)*LAB_SIZE+j][i*LAB_SIZE+j] = (arr[i][j]+arr[i+1][j])/2.0;
                //std::cout << (arr[i][j]+arr[i+1][j])/2.0 << ' ' << '\n';
            }
            if (j != LAB_SIZE-1 && rand() % 16 < seed) // decyzja na polaczeniu w dol
            {
                lab[i*LAB_SIZE+j][i*LAB_SIZE+j+1] = (arr[i][j]+arr[i][j+1])/2.0;
                lab[i*LAB_SIZE+j+1][i*LAB_SIZE+j] = (arr[i][j]+arr[i][j+1])/2.0;
                //std::cout << (arr[i][j]+arr[i][j+1])/2.0 << ' ' << '\n';
            }
            for (int x = 0; x < 4; ++x) options[x] = 0;
            con_ctr = option_ctr = 0;
            if (j != 0)             {options[2] = 1; ++option_ctr;} // lewo dostepne
            if (j != LAB_SIZE - 1)  {options[0] = 1; ++option_ctr;} // prawo dostepne
            if (i != 0)             {options[3] = 1; ++option_ctr;} // gora dostepna
            if (i != LAB_SIZE - 1)  {options[1] = 1; ++option_ctr;} // dol dostepny
            for (int x = 0; x < option_ctr; ++x)
                if (options[x])
                {
                    sgn = (x/2?-1:1);
                    diff = (x%2?LAB_SIZE:1);
                    //std::cout << sgn << ' ' << diff << '\t';
                    if (lab[i*LAB_SIZE+j][i*LAB_SIZE+j+diff*sgn])
                    {
                        ++con_num_arr[i][j]; 
                        // std::cout << "znal: " << lab[i*LAB_SIZE+j][i*LAB_SIZE+j+diff*sgn] << '\t';
                        // std::cout << "test: ";
                    }
                }
            // std::cout << '\n' << con_ctr << ' ' << option_ctr << ' ' << i*LAB_SIZE + j << '\n';
            if (con_ctr > 0 && con_ctr < option_ctr) continue;
            int chosen_num = rand() % option_ctr;
            //std::cout << con_ctr << ' ' << option_ctr << ' ' << i*LAB_SIZE + j << ' ' << options[0] << options[1] << options[2] << options[3] << '\n';
            while (options[chosen_num] == 0) chosen_num = (chosen_num + 1) % 4;
            sgn = (chosen_num/2?-1:1);
            diff = (chosen_num%2?LAB_SIZE:1);
            // std::cout << "\nsgn chosen: " << sgn << ' ' << diff << '\n';
            if (con_ctr == 0) // jezeli nie istnieje polaczenie
                lab[i*LAB_SIZE+j][i*LAB_SIZE+j+diff*sgn] = lab[i*LAB_SIZE+j+diff*sgn][i*LAB_SIZE+j] = 1.0;//(arr[i][j]+arr[i][j])/2.0;
            // if (con_ctr == option_ctr && rand() % 16 < seed) // jezeli istnieje polaczenie z wszystkimi sasiadami - nie jest konieczne, ale lab wyglada lepiej - istnieje szansa usuniecia skrzyzowania
            //     lab[i*LAB_SIZE+j][i*LAB_SIZE+j+diff*sgn] = lab[i*LAB_SIZE+j+diff*sgn][i*LAB_SIZE+j] = 0.0; //std::cout <<  "zmienilem, bo: " << my_rand % 16 << con_ctr;}
            // std::cout << "nr: " << i*LAB_SIZE + j << '\n' << con_ctr << ' ' << option_ctr << ' ' << ' ' << chosen_num << "\n\n";
        }
    }
    //print_arr(lab);
    // print_arr(lab);
    print_lab(lab);
    return 0;
}