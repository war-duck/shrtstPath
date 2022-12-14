#include "lab.hpp"

void add_path_anim (std::string* lab_str, std::vector<int> path)
{
    if (path.size() < 2) return;
    COORD cord;
	cord.X = 0;
	cord.Y = 5+2*LAB_SIZE;
    int prev, diff, current_pos = 4*LAB_SIZE+3 + 4*path[0]+2, pm;
    (*lab_str)[4*path[0]+2] = (*lab_str)[4*path[0]+3] = char(177);
    for (int i = 1; i < path.size(); ++i)
    {
        pm = path[i] > path[i-1] ? 1 : -1;
        diff = pm*(path[i] - path[i-1]) > 1 ? 4*LAB_SIZE+3 : 2;
        (*lab_str)[current_pos] = (*lab_str)[current_pos+1] = char(177); // obecny wierzcholek
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord); // kursor na (0, 2)
        std::cout << *lab_str;
        Sleep (100);
        (*lab_str)[current_pos+pm*diff] = (*lab_str)[current_pos+pm*diff+1] = char(177);
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord); // kursor na (0, 2)
        std::cout << *lab_str;
        Sleep (100);
        current_pos += 2*diff*pm;
    }
    (*lab_str)[current_pos] = (*lab_str)[current_pos+1] = (*lab_str)[current_pos+4*LAB_SIZE+3] = (*lab_str)[current_pos+4*LAB_SIZE+4] = char(177);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord); // kursor na (0, 2)
    std::cout << *lab_str;
}

void create_lab (double lab[LAB_SIZE*LAB_SIZE][LAB_SIZE*LAB_SIZE], std::string *lab_str, int start = -1, int end = -1)
{
    for (int i = 0; i < 2*LAB_SIZE; ++i)
    {
        (*lab_str)[(i+1)*(4*LAB_SIZE+3)-1] = '\n';
        if (i%2)
        {
            for (int j = 0; j < LAB_SIZE; ++j)
            {
                (*lab_str)[i*(4*LAB_SIZE+3)+4*j+2] = ((i/2)*LAB_SIZE+j>9?(((i/2)*LAB_SIZE+j)%100)/10:0)+'0';
                (*lab_str)[i*(4*LAB_SIZE+3)+4*j+3] = (((i/2)*LAB_SIZE+j)%10+'0');
                //(*lab_str)[i*(4*LAB_SIZE+3)+4*j+2] = (*lab_str)[i*(4*LAB_SIZE+3)+4*j+3] = ' '; // alt dla l. 39-40 - bez numerow
                if (j != LAB_SIZE-1 && lab[(i/2)*LAB_SIZE+j][(i/2)*LAB_SIZE+j+1])
                    (*lab_str)[i*(4*LAB_SIZE+3)+4*j+4] = (*lab_str)[i*(4*LAB_SIZE+3)+4*j+5] = ' ';
                if (i != 2*LAB_SIZE-1 && lab[(i/2)*LAB_SIZE+j][(i/2+1)*LAB_SIZE+j])
                    (*lab_str)[(i+1)*(4*LAB_SIZE+3)+4*j+2] = (*lab_str)[(i+1)*(4*LAB_SIZE+3)+4*j+3] = ' ';
            }    
        }
    }
    (*lab_str)[(4*LAB_SIZE + 3) * (2*LAB_SIZE+1) - 1] = '\n';
    return;
}

void add_start_end (std::string *lab_str, int* start, int* end)
{
    unsigned int tmp;
    system("CLS");
    do // wybieranie poczatku
    {

        std::cout << "wybierz wezel poczatkowy (liczba 0 - " << LAB_SIZE-1 << "): \n";
        for (int x = 0; x < LAB_SIZE; ++x) {std::cout.width(4); std::cout << x;}
        std::cout << '\n' << *lab_str;
        std::cin >> tmp;
        std::cin.clear();
        std::cin.ignore(1000, '\n');
    } while (tmp >= LAB_SIZE);
    (*lab_str)[4*tmp+2] = (*lab_str)[4*tmp+3] = ' ';
    *start = tmp;
    system("CLS");
    do // wybieranie konca
    {
        std::cout << "\nwybierz wezel koncowy (liczba " << LAB_SIZE*(LAB_SIZE-1) << " - " << LAB_SIZE*LAB_SIZE-1 << "): \n";
        std::cout<< *lab_str << '\n' ;
        for (int x = LAB_SIZE*(LAB_SIZE-1); x < LAB_SIZE*LAB_SIZE; ++x) {std::cout.width(4); std::cout << x;}
        std::cout << '\n';
        std::cin >> tmp;
        std::cin.clear();
        std::cin.ignore(1000, '\n');
    } while (tmp < LAB_SIZE*(LAB_SIZE-1) || tmp >= LAB_SIZE*LAB_SIZE);
    (*lab_str)[(2*LAB_SIZE)*(4*LAB_SIZE+3)+4*(tmp%LAB_SIZE)+2] = (*lab_str)[(2*LAB_SIZE)*(4*LAB_SIZE+3)+4*(tmp%LAB_SIZE)+3] = ' ';
    *end = tmp;
    system("CLS");
    return;
}

result create_paths()
{
    double arr[LAB_SIZE][LAB_SIZE];
    static double lab[LAB_SIZE*LAB_SIZE][LAB_SIZE*LAB_SIZE];   /* matryca ze wszystkimi ??ukami - [poczatek][koniec]
                                                         //* warto???? 0 - brak polaczenia, !0 - waga ??uku */
    int con_num_arr[LAB_SIZE][LAB_SIZE]; // ilosc polaczen dla kazdego wierzcholka
    int seed = 10;
    int start, end;
    std::string lab_str ((4*LAB_SIZE + 3) * (2*LAB_SIZE+1), char(219));
    srand(time(NULL));
    for (int i = 0; i < LAB_SIZE; ++i)
        for (int j = 0; j < LAB_SIZE; ++j)
        {
            arr[i][j] = (double)rand() / RAND_MAX * 10; // generowanie wagi dla wierzcho??k??w
            con_num_arr[i][j] = 0;
        }
    for (int i = 0; i < LAB_SIZE*LAB_SIZE; ++i)
        for (int j = 0; j < LAB_SIZE*LAB_SIZE; ++j)
            lab[i][j] = 0.0;
    
    bool options[4];
    int option_ctr;
    int diff, sgn;
    for (int i = 0; i < LAB_SIZE; ++i)
    {
        for (int j = 0; j < LAB_SIZE; ++j)
        {
            if (i != LAB_SIZE-1 && rand() % 16 < seed) // decyzja o polaczeniu w dol
                lab[(i+1)*LAB_SIZE+j][i*LAB_SIZE+j] = lab[i*LAB_SIZE+j][(i+1)*LAB_SIZE+j] = (arr[i][j]+arr[i+1][j])/2.0;
            if (j != LAB_SIZE-1 && rand() % 16 < seed) // decyzja na polaczeniu na prawo
                lab[i*LAB_SIZE+j+1][i*LAB_SIZE+j] = lab[i*LAB_SIZE+j][i*LAB_SIZE+j+1] = (arr[i][j]+arr[i][j+1])/2.0;

            for (int x = 0; x < 4; ++x) options[x] = 0;
            option_ctr = 0;
            if (j != 0)             {options[2] = 1; ++option_ctr;} // lewo dostepne
            if (j != LAB_SIZE - 1)  {options[0] = 1; ++option_ctr;} // prawo dostepne
            if (i != 0)             {options[3] = 1; ++option_ctr;} // gora dostepna
            if (i != LAB_SIZE - 1)  {options[1] = 1; ++option_ctr;} // dol dostepny

            for (int x = 0; x < 4; ++x)
                if (options[x])
                {
                    sgn = (x/2?-1:1);
                    diff = (x%2?LAB_SIZE:1);
                    if (lab[i*LAB_SIZE+j][i*LAB_SIZE+j+diff*sgn])
                        ++con_num_arr[i][j];
                }

            if (con_num_arr[i][j] > 0 && con_num_arr[i][j] < option_ctr)
                continue;
            int chosen_num = rand() % option_ctr;
            while (options[chosen_num] == 0) chosen_num = (chosen_num + 1) % 4;
            sgn = (chosen_num/2?-1:1);
            diff = (chosen_num%2?LAB_SIZE:1);
            if (con_num_arr[i][j] == option_ctr && rand() % 16 < seed && con_num_arr[i+((diff>1)?sgn:0)][j+((diff==1)?sgn:0)] != 1) // jezeli istnieje polaczenie z wszystkimi sasiadami - nie jest konieczne, ale lab wyglada lepiej - istnieje szansa usuniecia skrzyzowania
            {
                lab[i*LAB_SIZE+j][i*LAB_SIZE+j+diff*sgn] = lab[i*LAB_SIZE+j+diff*sgn][i*LAB_SIZE+j] = 0.0;
                
                --con_num_arr[i][j];
                --con_num_arr[i+((diff>1)?sgn:0)][j+((diff==1)?sgn:0)];
            }
            if (con_num_arr[i][j] < 1) // jezeli nie istnieje polaczenie
            {
                lab[i*LAB_SIZE+j][i*LAB_SIZE+j+diff*sgn] = lab[i*LAB_SIZE+j+diff*sgn][i*LAB_SIZE+j] = (arr[i][j]+arr[i+((diff>1)?sgn:0)][j+((diff==1)?sgn:0)])/2.0;
                ++con_num_arr[i][j];
                ++con_num_arr[i+((diff>1)?sgn:0)][j+((diff==1)?sgn:0)];
            }
        }
    }
    create_lab(lab, &lab_str);
    add_start_end(&lab_str, &start, &end);
    static result my_result = new a;
    my_result->dest = end;
    my_result->start = start;
    my_result->lab = lab;
    my_result->lab_str = lab_str;

    return my_result;
}