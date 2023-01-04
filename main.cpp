#include "create_lab.hpp"
#include "solver.hpp"
int main()
{
    result lab_data = create_paths();
    std::cout << lab_data->lab_str;
    // for (int i = 0; i < LAB_SIZE*LAB_SIZE; ++i)
    // {
        
    //     for (int j = 0; j < LAB_SIZE*LAB_SIZE; ++j)
    //         std::cout << (*(lab_data->lab+i))[j] << '\t';
    //     std::cout << '\n';
    // }
    solve(LAB_SIZE*LAB_SIZE, lab_data->start, lab_data->dest, lab_data);
    free(lab_data);
    return 0;
}