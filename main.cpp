#include "lab.hpp"
#include "solver.hpp"
int main()
{
    system("CLS");
    result lab_data = create_paths();
    std::cout << "szukam...\n";
#ifndef SHOW_ARR
    add_path_anim(&lab_data->lab_str, solve(LAB_SIZE*LAB_SIZE, lab_data->start, lab_data->dest, lab_data));
#else
    solve(LAB_SIZE*LAB_SIZE, lab_data->start, lab_data->dest, lab_data);
#endif
    free(lab_data);
    return 0;
}