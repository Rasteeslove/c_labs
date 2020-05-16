#include "clab7.h"

#define DEF_LINE_LEN 16
#define DEF_LINE_NUM 4


char * get_string(FILE * file_or_con);
void write_string_to_file(char * str, FILE * file);

text * get_text(FILE * file_or_con, int (*condition_for_reading)(), int max_line_num);
void move_text_to_file(FILE * file, text * text);

void get_data_from_file();
void write_data_to_file();

user * get_user_from_file(FILE * file);
void write_user_to_file(user * one, FILE * file);

group * get_group_from_file(FILE * file);
void write_group_to_file(group * one, FILE * file);

release * get_release_from_file(FILE * file);
void write_release_to_file(release * one, FILE * file);

article * get_article_from_file(FILE * file);
void write_article_to_file(article * one, FILE * file);

int * get_int_arr(FILE * file, int size);
void write_int_arr_to_file(FILE * file, int * arr, int size);

money get_money(FILE * file);
void write_money_to_file(FILE * file, money one);

date * get_date(FILE * file);
void write_date_to_file(FILE * file, date * one);

song get_song(FILE * file);
void write_song_to_file(FILE * file, song one);

int yes_function();

/* gets any allocatable line from file or stdin */
char * get_string(FILE * file_or_con)
{
    char * str;
    int chinput;
    size_t len = 0;
    size_t capacity = DEF_LINE_LEN;

    str = (char*)malloc(sizeof(char) * capacity);
    
    if (str == NULL)
        report_merror();

    while ((chinput = fgetc(file_or_con)) != EOF && chinput != '\n')
    {
        str[len++] = chinput;
        if (len == capacity)
        {
            str = (char*)realloc(str, sizeof(char) * (capacity *= 2));
            if (str == NULL)
                report_merror();
        }
    }

    str[len++] = '\n';

    if (len == capacity)
    {
        str = (char*)realloc(str, sizeof(char) * (capacity += 1));
        if (str == NULL)
            report_merror();

        str[len++] = '\0';
        return str;
    }

    str[len++] = '\0';

    return (char*)realloc(str, sizeof(char) * len);
}

void write_string_to_file(char * str, FILE * file)
{
    if (fputs(str, file) == EOF)
        report_werror();
}

/* gets any allocatable text from file or stdin.
   stops reading:
   1) if max_line_num == 0 and condition for reading returns 1 on call
   2) if max_line_num > 0 then after reading max_line_num lines */
text * get_text(FILE * file_or_con, int (*condition_for_reading)(), int max_line_num) 
{      
    char ** lines;
    char * line;
    size_t line_num = 0;
    size_t capacity = DEF_LINE_NUM;

    lines = (char**)malloc(sizeof(char*) * capacity);

    if (lines == NULL)
    {
        printf("\nMemory error\n");
        exit(EXIT_FAILURE);
    }

    while (condition_for_reading() && (max_line_num == 0 || line_num < max_line_num))
    {
        lines[line_num++] = get_string(file_or_con);
        if (line_num == capacity)
        {
            lines = (char**)realloc(lines, sizeof(char*) * (capacity *= 2));
            if (lines == NULL)
            {
                printf("\nMemory error\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    lines = (char**)realloc(lines, sizeof(char*) * line_num);

    text * output = (text*)malloc(sizeof(text));

    output->num_of_lines = line_num;
    output->lines = lines;

    return output;
}

/* if both params !=null : writes num of lines and lines to file */
void move_text_to_file(FILE * file, text * text)
{

    #pragma region parameters error handling

    if (file == NULL || text == NULL)
        return;

    #pragma endregion

    #pragma region writing number of lines to file

    if (fprintf(file, "%d ", text->num_of_lines) == EOF)
        report_werror();

    #pragma endregion

    #pragma region writing lines to file

    int i = 0;
    for (; i < text->num_of_lines; i++)   
        if (fputs(text->lines[i], file) == EOF) 
            report_werror();

    #pragma endregion

}

void get_data_from_file()
{
    FILE * db = fopen(file_name, "rb");

    #pragma region checking if the file exists (it may not if it is the first run)

    if (db == NULL)
    {
        num_of_articles = num_of_groups = num_of_releases = num_of_users = 0;

        articles = NULL;
        groups = NULL;
        releases = NULL;
        users = NULL;

        return;
    }

    #pragma endregion

    #pragma region getting numbers of the four main structs

    if (fscanf(db, "%d %d %d %d ", &num_of_articles, &num_of_groups, &num_of_releases, &num_of_users) == EOF)
        report_uerror();

    #pragma endregion

    int i, capacity;

    #pragma region getting articles

    capacity = DEF_STRUCT_CAP;
    articles = (article**)malloc(sizeof(article*) * capacity);

    if (articles == NULL)
        report_merror();

    for (i = 0; i < num_of_articles;)
    {
        articles[i++] = get_article_from_file(db);  

        if (i == capacity)
        {
            articles = (article**)realloc(articles, sizeof(article*) * (capacity *= 2));
            if (articles == NULL)  
                report_merror(); 
        }
    } 

    #pragma endregion

    #pragma region getting groups

    capacity = DEF_STRUCT_CAP;
    groups = (group**)malloc(sizeof(group*) * capacity);

    if (groups == NULL)
        report_merror();

    for (i = 0; i < num_of_groups;)
    {
        groups[i++] = get_group_from_file(db);  

        if (i == capacity)
        {
            groups = (group**)realloc(groups, sizeof(group*) * (capacity *= 2));
            if (groups == NULL)  
                report_merror(); 
        }
    }

    #pragma endregion

    #pragma region getting releases

    capacity = DEF_STRUCT_CAP;
    releases = (release**)malloc(sizeof(release*) * capacity);

    if (releases == NULL)
        report_merror();

    for (i = 0; i < num_of_releases;)
    {
        releases[i++] = get_release_from_file(db);  

        if (i == capacity)
        {
            releases = (release**)realloc(releases, sizeof(release*) * (capacity *= 2));
            if (releases == NULL)  
                report_merror(); 
        }
    }

    #pragma endregion

    #pragma region getting users

    capacity = DEF_STRUCT_CAP;
    users = (user**)malloc(sizeof(user*) * capacity);

    if (users == NULL)
        report_merror();

    for (i = 0; i < num_of_users;)
    {
        users[i++] = get_user_from_file(db);  

        if (i == capacity)
        {
            users = (user**)realloc(users, sizeof(user*) * (capacity *= 2));
            if (users == NULL)  
                report_merror(); 
        }
    }

    #pragma endregion

    fclose(db);
}

void write_data_to_file()
{
    FILE * db = fopen(file_name, "wb");

    #pragma region checking if the file was created

    if (db == NULL)
    {
        report_werror();
    }

    #pragma endregion

    #pragma region writing numbers of the four main structs

    if (fprintf(db, "%d %d %d %d ", num_of_articles, num_of_groups, num_of_releases, num_of_users) == EOF)
        report_werror();

    #pragma endregion

    int i;

    #pragma region writing articles

    for (i = 0; i < num_of_articles; i++)
        write_article_to_file(articles[i], db);

    #pragma endregion

    #pragma region writing groups

    for (i = 0; i < num_of_groups; i++)
        write_group_to_file(groups[i], db);

    #pragma endregion

    #pragma region writing releases

    for (i = 0; i < num_of_releases; i++)
        write_release_to_file(releases[i], db);

    #pragma endregion

    #pragma region writing users

    for (i = 0; i < num_of_users; i++)
        write_user_to_file(users[i], db);

    #pragma endregion

    fclose(db);
}

user * get_user_from_file(FILE * file)
{
    user * new_one = (user*)malloc(sizeof(user));

    if (fscanf(file, "%d ", &new_one->user_id) == EOF)
        report_uerror();

    new_one->name = get_string(file);

    if (fscanf(file, "%d ", &new_one->num_of_releases) == EOF)
        report_uerror();

    new_one->releases = get_int_arr(file, new_one->num_of_releases);

    if (fscanf(file, "%d ", &new_one->num_of_articles) == EOF)
        report_uerror();

    new_one->articles = get_int_arr(file, new_one->num_of_articles);

    if (fscanf(file, "%d ", &new_one->num_of_purchased_releases) == EOF)
        report_uerror();

    new_one->purchased_releases = get_int_arr(file, new_one->num_of_purchased_releases);

    if (fscanf(file, "%d ", &new_one->num_of_purchased_articles) == EOF)
        report_uerror();

    new_one->purchased_articles = get_int_arr(file, new_one->num_of_purchased_articles);

    if (fscanf(file, "%d %d ", &new_one->revenue, &new_one->full_account) == EOF)
        report_uerror();

    return new_one;
}

void write_user_to_file(user * one, FILE * file)
{
    if (fprintf(file, "%d ", one->user_id) == EOF)
        report_werror();

    write_string_to_file(one->name, file);

    if (fprintf(file, "%d ", one->num_of_releases) == EOF)
        report_werror();

    write_int_arr_to_file(file, one->releases, one->num_of_releases);

    if (fprintf(file, "%d ", one->num_of_articles) == EOF)
        report_werror();

    write_int_arr_to_file(file, one->articles, one->num_of_articles);

    if (fprintf(file, "%d ", one->num_of_purchased_releases) == EOF)
        report_werror();

    write_int_arr_to_file(file, one->purchased_releases, one->num_of_purchased_releases);

    if (fprintf(file, "%d ", one->num_of_purchased_articles) == EOF)
        report_werror();

    write_int_arr_to_file(file, one->purchased_articles, one->num_of_purchased_articles);

    if (fprintf(file, "%d %d ", one->revenue, one->full_account) == EOF)
        report_werror();
}

group * get_group_from_file(FILE * file)
{
    group * new_one = (group*)malloc(sizeof(group));

    new_one->image = get_user_from_file(file);
    
    if (fscanf(file, "%d ", &new_one->num_of_members) == EOF)
        report_uerror();

    new_one->members = get_int_arr(file, new_one->num_of_members);

    return new_one;
}

void write_group_to_file(group * one, FILE * file)
{
    write_user_to_file(one->image, file);

    if (fprintf(file, "%d ", one->num_of_members) == EOF)
        report_werror();

    write_int_arr_to_file(file, one->members, one->num_of_members);
}

release * get_release_from_file(FILE * file)
{
    release * new_one = (release*)malloc(sizeof(release));

    if (fscanf(file, "%d %d ", &new_one->release_id, &new_one->type) == EOF)
        report_uerror();

    new_one->dropped = get_date(file);

    new_one->name = get_string(file);

    if (fscanf(file, "%d ", &new_one->num_of_authors) == EOF)
        report_uerror();

    new_one->authors = get_int_arr(file, new_one->num_of_authors);

    if (fscanf(file, "%d %d ", &new_one->cover, &new_one->num_of_songs) == EOF)
        report_uerror();

    new_one->songs = (song*)malloc(sizeof(song) * new_one->num_of_songs);
    int i;
    for (i = 0; i < new_one->num_of_songs; i++)
        new_one->songs[i] = get_song(file);

    if (fscanf(file, "%d ", &new_one->price) == EOF)
        report_uerror();

    return new_one;
}

void write_release_to_file(release * one, FILE * file)
{
    if (fprintf(file, "%d %d ", one->release_id, one->type) == EOF)
        report_werror();

    write_date_to_file(file, one->dropped);

    write_string_to_file(one->name, file);

    if (fprintf(file, "%d ", one->num_of_authors) == EOF)
        report_werror();

    write_int_arr_to_file(file, one->authors, one->num_of_authors);

    if (fprintf(file, "%d %d ", one->cover, one->num_of_songs) == EOF)
        report_werror();

    int i;
    for (i = 0; i < one->num_of_songs; i++)
        write_song_to_file(file, one->songs[i]);

    if (fprintf(file, "%d ", one->price) == EOF)
        report_werror();
}

article * get_article_from_file(FILE * file)
{
    article * new_one = (article*)malloc(sizeof(article));

    if (fscanf(file, "%d ", &new_one->article_id) == EOF)
        report_uerror();

    new_one->published = get_date(file);

    new_one->title = get_string(file); 

    if (fscanf(file, "%d ", &new_one->num_of_authors) == EOF)
        report_uerror();

    new_one->authors = get_int_arr(file, new_one->num_of_authors);

    int tmp;
    if (fscanf(file, "%d ", &tmp) == EOF)
        report_uerror();

    if (tmp != 0)
        new_one->text = get_text(file, yes_function, tmp);

    if (fscanf(file, "%d ", &new_one->price) == EOF)
        report_uerror();

    return new_one;
}

void write_article_to_file(article * one, FILE * file)
{
    if (fprintf(file, "%d ", one->article_id) == EOF)
        report_werror();

    write_date_to_file(file, one->published);

    write_string_to_file(one->title, file);

    if (fprintf(file, "%d ", one->num_of_authors) == EOF)
        report_werror();

    write_int_arr_to_file(file, one->authors, one->num_of_authors);

    move_text_to_file(file, one->text);

    write_money_to_file(file, one->price);
}

int * get_int_arr(FILE * file, int size)
{
    int * output = (int*)malloc(sizeof(int) * size);

    int i;
    for (i = 0; i < size; i++)
        if (fscanf(file, "%d ", &output[i]) == EOF)
            report_uerror();

    return output;
}

void write_int_arr_to_file(FILE * file, int * arr, int size)
{
    int i;
    for (i = 0; i < size; i++)
        if (fprintf(file, "%d ", arr[i]) == EOF)
            report_werror();
}

void write_money_to_file(FILE * file, money one)
{
    if (fprintf(file, "%d ", one) == EOF)
        report_werror();
}

date * get_date(FILE * file)
{
    date * new_date = (date*)malloc(sizeof(date));

    if (fscanf(file, "%d %d %d ", &new_date->month, &new_date->day, &new_date->year) == EOF)
        report_uerror();

    return new_date;
}

void write_date_to_file(FILE * file, date * one)
{
    if (fprintf(file, "%d %d %d ", one->month, one->day, one->year) == EOF)
        report_werror();
}

song get_song(FILE * file)
{
    song new_one;

    new_one.name = get_string(file);

    int tmp;
    if (fscanf(file, "%d %d %d ", &new_one.cover, &new_one.music, &tmp) == EOF)
        report_uerror();

    if (tmp != 0)
        new_one.lyrics = get_text(file, yes_function, tmp);
    else
    {
        new_one.lyrics = (text*)malloc(sizeof(text));

        new_one.lyrics->lines = NULL;
        new_one.lyrics->num_of_lines = 0;
    }

    return new_one;
}

void write_song_to_file(FILE * file, song one)
{
    write_string_to_file(one.name, file);

    if (fprintf(file, "%d %d ", one.cover, one.music) == EOF)
        report_werror();

    move_text_to_file(file, one.lyrics);
}

int yes_function()
{
    return 1;
}


