#include "clab7.h"

int main()
{
    file_name = "devs_db.txt";   /* where to read from and write to */

    get_data_from_file();

    main_menu();  

    write_data_to_file();

    #pragma region clearing heap

    int i;

    for (i = 0; i < num_of_articles; i++)
        delete_article(articles[i]);
    free(articles);

    for (i = 0; i < num_of_groups; i++)
        delete_group(groups[i]);
    free(groups);

    for (i = 0; i < num_of_releases; i++)
        delete_release(releases[i]);
    free(releases);

    for (i = 0; i < num_of_users; i++)
        delete_user(users[i]);
    free(users);

    #pragma endregion

}