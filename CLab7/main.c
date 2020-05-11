#include "clab7.h"

int main()
{
    file_name = "devs_db.txt";   /* where to read from and write to */

    get_data_from_file();

    main_menu();  

    write_data_to_file();
}