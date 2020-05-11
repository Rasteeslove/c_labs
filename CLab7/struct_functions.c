#include <time.h>
#include "clab7.h"

int id_exists(id one)
{
    int i = 0;
    for (; i < num_of_users; i++)
        if (users[i]->user_id == one)
            return 1;

    for (; i < num_of_groups; i++)
        if (groups[i]->image->user_id == one)
            return 1;

    for (; i < num_of_releases; i++)
        if (releases[i]->release_id == one)
            return 1;

    for (; i < num_of_articles; i++)
        if (articles[i]->article_id == one)
            return 1;

    return 0;
}

id get_new_id()
{
    id new_id;
    do {
        srand(time(NULL));
        new_id = rand();  
    } while (id_exists(new_id));

    return new_id;
}

user * new_user(char * name)
{
    user * new_user = (user*)malloc(sizeof(user));

    new_user->user_id = get_new_id();
    new_user->name = name;

    new_user->articles = NULL;
    new_user->releases = NULL;
    new_user->purchased_articles = NULL;
    new_user->purchased_releases = NULL;

    new_user->full_account = new_user->num_of_articles = new_user->num_of_purchased_articles = 
        new_user->num_of_purchased_releases = new_user->num_of_releases = new_user->revenue = 0;
     
    return new_user;
}

group * new_group(char * name, int num_of_members, id * members)
{
    group * new_group = (group*)malloc(sizeof(group));

    new_group->image = new_user(name);

    new_group->num_of_members = num_of_members;
    new_group->members = members;
     
    return new_group;
}

/*
group * new_group(char * name)
{
    group * new_group = (group*)malloc(sizeof(group));

    new_group->image = new_user(name);

    new_group->num_of_members = 0;
    new_group->members = NULL;
     
    return new_group;
}*/

release * new_release()
{
    release * new_one = (release*)malloc(sizeof(release));

    new_one->release_id = get_new_id();

    return new_one;
}

article * new_article()
{
    article * new_one = (article*)malloc(sizeof(article));

    new_one->article_id = get_new_id();

    return new_one;
}

box * new_box()
{
    box * new_one = (box*)malloc(sizeof(box));

    new_one->a = NULL;
    new_one->g = NULL;
    new_one->r = NULL;
    new_one->u = NULL;

    return new_one;
}

void delete_user(user * one)
{
    free(one->name);

    free(one->releases);
    free(one->articles);
    free(one->purchased_articles);
    free(one->purchased_releases);

    free(one);
}

void delete_group(group * one)
{
    delete_user(one->image);
    free(one->members);

    free(one);
}

void delete_text(text * one)
{
    int i = 0;
    for (; i < one->num_of_lines; i++)
        free(one->lines[i]);

    free(one->lines);
    free(one);
}

void delete_song_info(song one)
{
    free(one.name);
    delete_text(one.lyrics);
}

void delete_release(release * one)
{
    free(one->name);
    free(one->authors);
    free(one->dropped);
    
    int i = 0;
    for (; i < one->num_of_songs; i++)
        delete_song_info(one->songs[i]);

    free(one->songs);
}

void delete_article(article * one)
{
    free(one->authors);
    free(one->published);
    free(one->title);
    delete_text(one->text);

    free(one);
}