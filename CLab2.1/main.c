#include "clab2.h"

const int months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int main()
{   
    file_name = "projects.txt";

    get_data_from_file();

    main_menu();

    write_data_to_file();

    free(projects);

    return 0;
}