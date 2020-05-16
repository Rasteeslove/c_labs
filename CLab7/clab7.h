
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define DEF_STRUCT_CAP 4
#define MAX_INT 2147483647
#define cover_art int
#define mp3 int
#define id int
#define money int


typedef enum release_type
{

    Composition,
    Single,
    LP,
    EP,
    Mixtape,


} release_type;

typedef struct text text;
typedef struct date date;
typedef struct user user;
typedef struct group group;
typedef struct song song;
typedef struct release release;
typedef struct article article;

typedef struct box box;

typedef struct text 
{

    int num_of_lines;
    char ** lines;
    
} text;

typedef struct date
{

    int day, month, year;

} date;

typedef struct user
{

    id user_id;
    char * name;

    int num_of_releases;
    id * releases;
    int num_of_articles;
    id * articles;
    int num_of_purchased_releases;
    id * purchased_releases; 
    int num_of_purchased_articles;
    id * purchased_articles;

    money revenue;/**/
    money full_account;

} user;

typedef struct group
{

    int num_of_members;
    id * members;

    user * image;

} group;

typedef struct song
{
    char * name;

    cover_art cover;

    mp3 music;
    text * lyrics;

} song;

typedef struct release
{

    id release_id;
    release_type type;
    date * dropped;
    char * name;

    int num_of_authors;
    id * authors;

    cover_art cover;

    int num_of_songs; 
    song * songs;

    /* some separator-ints could be added for A-side, B-side, albums of double / triple album
    or just generally sections of the record with the names assigned to them */

    money price;

} release;

typedef struct article
{

    id article_id;
    date * published;
    char * title;

    int num_of_authors;
    id * authors;

    text * text;

    /* tags (ids) to users and groups could be added */

    money price;

} article;

typedef struct box
{
    user * u;
    group * g;
    release * r;
    article * a;
} box;

char * file_name;

size_t num_of_users;
size_t num_of_groups;
size_t num_of_releases;
size_t num_of_articles;

user ** users;
group ** groups;
release ** releases;
article ** articles;

void get_data_from_file();
void write_data_to_file();

int get_int();
char * get_string(FILE * file_or_con);
text * get_text(FILE * file_or_con, int (*condition_for_reading)(), int max_line_num);

void report_merror();
void report_uerror();
void report_werror();

user * new_user(char * name);
group * new_group(char * name, int num_of_members, id * members);
release * new_release();
article * new_article();

void delete_user(user * one);
void delete_group(group * one);
void delete_release(release * one);
void delete_article(article * one);

box * new_box();

int yes_function();
int length_of(char * str);
int substr(char * sub, char * str);
int are_strs_same(char * first, char * second);
int is_among(int * items, int num_of_items, int item);
void out_str_wo_nl(char * str);

void main_menu();