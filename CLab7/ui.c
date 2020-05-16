#include "clab7.h"

#define SONGS_ON_THE_RECORD_UPPER_LIMIT 40

/* these are unnessesary if text input is like in the 4th lab (with a "condition"-txt-file) */
#define MAX_NUM_OF_LYR_LINES 120
#define MAX_NUM_OF_ARTICLE_LINES 360

int months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

date * set_date();

int get_int()
{
    int num = 0;

    char * input = get_string(stdin);
    if (length_of(input) >= 10)
        input[9] = '\0';

    int i = 0;
    for (; input[i] && input[i] >= '0' && input[i] <= '9'; i++)
        num = num * 10 + input[i] - '0';

    free(input);
    return num;
}

void sign_up();
void sign_in();

box * get_item_by_id(id tag);
id select_one(int among_users, int among_groups, int among_articles, int among_releases);
id * filtered(id * original, int * num_of_options, char * tag);

void add_money(id you);
void release_a_record(id you);
void publish_an_article(id you);
void buy_a_record(id you);
void buy_an_article(id you);

date * set_date();
song set_song();
void session(id you);

int is_a_leap_year(int year)
{
    if (year % 4 != 0 || (year % 100 == 0 && year % 400 != 0))
        return 0;

    return 1;
}

user * get_user_by_id(id some_id)
{
    box * whatever = get_item_by_id(some_id);
    user * output;

    if (whatever->g != NULL)
        output = whatever->g->image;
    else
        output = whatever->u;   

    free(whatever);

    return output;
}

group * get_group_by_id(id some_id)
{
    box * whatever = get_item_by_id(some_id);
    group * output = whatever->g;
    free(whatever);

    return output;
}

int is_name_unique(int namespace, char * name)
{
    int i = 0;

    if (namespace == 0)
    {
        for (; i < num_of_articles; i++)
            if (are_strs_same(articles[i]->title, name))
                return 0;
    }
    else if (namespace == 1)
    {
        for (; i < num_of_groups; i++)
            if (are_strs_same(groups[i]->image->name, name))
                return 0;
    }
    else if (namespace == 2)
    {
        for (; i < num_of_releases; i++)
            if (are_strs_same(releases[i]->name, name))
                return 0;
    }
    else
    {
        for (; i < num_of_users; i++)
            if (are_strs_same(users[i]->name, name))
                return 0;
    }
       
    return 1;
}

void display_song(song one)
{
    printf("Song ");
    out_str_wo_nl(one.name);
    printf(":\n");

    if (one.cover != 0)
        printf("Cover: %d\n", one.cover);

    printf("Music: %d\n", one.music);

    if (one.lyrics->num_of_lines != 0)
    {
        printf("Lyrics:\n");
        int i = 0;
        for (; i < one.lyrics->num_of_lines; i++)
            printf("\t%s", one.lyrics->lines[i]);
    }
    printf("\n\n");
}

void display_release(id release_id)
{

    #pragma region getting release by id

    box * whatever = get_item_by_id(release_id);

    if (whatever->r == NULL)
        return;
    
    release * one = whatever->r;

    free(whatever);

    #pragma endregion

    #pragma region output

    printf("%s ", (one->type == 0 ? "Composition" : one->type == 1 ? "Single" :
        one->type == 2 ? "LP" : one->type == 3 ? "EP" : "Mixtape"));

    out_str_wo_nl(one->name);
    printf(" by ");
    box * tmp = get_item_by_id(one->authors[0]);

    if (tmp->u != NULL)
        out_str_wo_nl(tmp->u->name);
    else
        out_str_wo_nl(tmp->g->image->name);

    if (one->num_of_authors > 1)
    {
        printf(": ");
        int i = 1;
        for (; i < one->num_of_authors; i++)
        {
            box * tmp = get_item_by_id(one->authors[i]);

            if (tmp->u != NULL)
                out_str_wo_nl(tmp->u->name);

            printf(", ");
            free(tmp);
        }

        printf("\b\b.");
    }    
    else
    {
        printf(".");
    }

    free(tmp);

    printf(":\nCover: %d\nSongs:\n\n", one->cover);

    printf("\n---------------------------------\n");
    int i = 0;
    for (; i < one->num_of_songs; i++)
    {
        display_song(one->songs[i]);
        printf("\n---------------------------------\n");
    }
    #pragma endregion

}

void display_article(id article_id)
{

    #pragma region getting release by id

    box * whatever = get_item_by_id(article_id);

    if (whatever->a == NULL)
        return;
    
    article * one = whatever->a;

    free(whatever);

    #pragma endregion

    #pragma region output

    printf("Article ");
    out_str_wo_nl(one->title);

    printf(" by ");
    box * tmp = get_item_by_id(one->authors[0]);

    if (tmp->u != NULL)
        out_str_wo_nl(tmp->u->name);
    else 
        out_str_wo_nl(tmp->g->image->name);

    if (one->num_of_authors > 1)
    {
        printf(": ");
        int i = 1;
        for (; i < one->num_of_authors; i++)
        {
            box * tmp = get_item_by_id(one->authors[i]);

            if (tmp->u != NULL)
                out_str_wo_nl(tmp->u->name);

            printf(", ");
            free(tmp);
        }

        printf("\b\b.");
    }    
    else
    {
        printf(".");
    }

    free(tmp);

    printf(":\n\n");

    int i = 0;
    for (; i < one->text->num_of_lines; i++)
        printf("\t%s", one->text->lines[i]);

    #pragma endregion

}

void main_menu()
{
    while (1)
    {
        char chinput = 0;
        do
        {
            system("cls");

            printf("Tap:\t\tTo:\n\n");
            printf(" 1\t\t Sign up\n");
            printf(" 2\t\t Sign in\n");
            printf(" 0\t\t Exit app.\n");

            chinput = getch();

        } while (chinput != '0' && chinput != '1' && chinput != '2');
    
        if (chinput == '0')
            break;

        if (chinput == '1')
        {
            sign_up();
        }
        else 
        {
            sign_in();
        }
    }

}

void sign_up()
{
    system("cls");

    #pragma region user or group

    char user_or_group;
    do
    {
        printf("Are you a (u)ser/artist or a (g)roup/band? \n");
        user_or_group = getch();
    } while (user_or_group != 'u' && user_or_group != 'g');

    #pragma endregion

    #pragma region option to add members if group

    int num_of_members = 0;
    id * members = NULL;

    if (user_or_group == 'g')
    {
        char when;
        do
        {
            printf("\nWould you like to add members (r)ight away or would you prefer to do it (l)ater? \n");
            when = getch();
        } while (when != 'r' && when != 'l');
        
        if (when == 'r')
        {
            int chinput;
            do 
            {
                id new_member = select_one(1, 0, 0, 0);

                if (new_member == -1)
                {
                    printf("No one was selected. ");
                }
                else if (is_among(members, num_of_members, new_member))
                {
                    printf("This user is already in the group. ");
                }
                else
                {
                    members = (id*)realloc(members, sizeof(id) * (num_of_members + 1));

                    if (members == NULL)
                        report_merror();

                    members[num_of_members++] = new_member;
                    printf("This user has been added to the group. ");
                }

                printf("Press n if it\'s enough: ");
                chinput = getch();
            } while (chinput != 'n');
        }
    }

    #pragma endregion

    #pragma region getting name and checking if it is unique

    char * name;

    printf("\nEnter ");
    if (user_or_group == 'u') 
        printf("your name: ");
    else
        printf("the name of the group: ");
    
    name = get_string(stdin);

    while (!is_name_unique(3, name))
    {
        free(name);
        printf("\nThere\' already a user with this name. Try again: ");
        name = get_string(stdin);
    }

    #pragma endregion

    #pragma region add user or group to the list and start session

    if (user_or_group == 'u')
    {
        user * new_one = new_user(name);

        users = (user**)realloc(users, sizeof(user*) * (num_of_users + 1));

        if (users == NULL)
            report_merror();

        users[num_of_users++] = new_one;

        session(new_one->user_id);
    }    
    else
    {
        group * new_one = new_group(name, num_of_members, members);

        groups = (group**)realloc(groups, sizeof(group*) * (num_of_groups + 1));

        if (groups == NULL)
            report_merror();

        groups[num_of_groups++] = new_one;

        session(new_one->image->user_id);
    }

    #pragma endregion

}

void sign_in()
{
    system("cls");

    id you = select_one(1, 1, 0, 0);

    if (you != -1)
        session(you);
}

id select_one(int among_users, int among_groups, int among_articles, int among_releases)
{

    #pragma region parameters errors handling

    if (among_users == 0 && among_groups == 0 && among_articles == 0 && among_releases == 0)
        return -1;

    #pragma endregion

    #pragma region setting up all options array

    int num_of_options = (among_users ? num_of_users : 0) + (among_groups ? num_of_groups : 0) +
        (among_articles ? num_of_articles : 0) + (among_releases ? num_of_releases : 0);

    id * options = (id*)malloc(sizeof(id) * num_of_options);

    int i = 0, j;
    if (among_users)
        for (j = 0; j < num_of_users; i++, j++)
            options[i] = users[j]->user_id;

    if (among_groups)
        for (j = 0; j < num_of_groups; i++, j++)
            options[i] = groups[j]->image->user_id;

    if (among_articles)
        for (j = 0; j < num_of_articles; i++, j++)
            options[i] = articles[j]->article_id;

    if (among_releases)
        for (j = 0; j < num_of_releases; i++, j++)
            options[i] = releases[j]->release_id;

    #pragma endregion

    #pragma region selecting

    char * tag = NULL;
    int num_of_available = num_of_options;
    id * available = filtered(options, &num_of_options, tag);

    while (1)
    {
        printf("\nEnter:\t\tTo select\n\n 0\t\t Nothing\n");

        for (i = 0; i < num_of_available; i++)
        {
            box * tmp = get_item_by_id(available[i]);

            int index = tmp->a != NULL ? 0 : tmp->g != NULL ? 1 :
                tmp->r != NULL ? 2 : tmp->u->name != NULL ? 3 : -1;

            printf(" %d\t\t %s: ", i + 1, index == 0 ? "article" : index == 1 ? "group" : 
                index == 2 ? "release" : index == 3 ? "user" : NULL);

            out_str_wo_nl(tmp->a != NULL ? tmp->a->title : 
                    tmp->g != NULL ? tmp->g->image->name : tmp->r != NULL ? tmp->r->name : 
                        tmp->u->name != NULL ? tmp->u->name : NULL);

            printf("\n");

            free(tmp);
        }

        printf("\nEnter tag or press enter to select: ");
        free(tag);
        tag = get_string(stdin);

        if (length_of(tag) == 2)
        {
            printf("\nEnter the number of the option: ");

            int chinput, option = 0;
            while ((chinput = fgetc(stdin)) >= '0' && chinput <= '9')
                option = option * 10 + chinput - '0';

            if (option == 0)
                return -1;

            if (option <= num_of_available)
                return available[option - 1];
        } 
        else
        {
            tag[length_of(tag) - 2] = '\0';

            free(available);

            num_of_available = num_of_options;
            available = filtered(options, &num_of_available, tag);
        }
    }

    #pragma endregion

}

box * get_item_by_id(id tag)
{
    box * output = new_box();

    int i;
    for (i = 0; i < num_of_users; i++)
        if (users[i]->user_id == tag)
        {
            output->u = users[i];
            return output;
        }

    for (i = 0; i < num_of_groups; i++)
        if (groups[i]->image->user_id == tag)
        {
            output->g = groups[i];
            return output;
        }

    for (i = 0; i < num_of_articles; i++)
        if (articles[i]->article_id == tag)
        {
            output->a = articles[i];
            return output;
        }

    for (i = 0; i < num_of_releases; i++)
        if (releases[i]->release_id == tag)
        {
            output->r = releases[i];
            return output;
        }

    return output;
}

id * filtered(id * original, int * num_of_options, char * tag)
{
    id * output;
    size_t size = 0;
    size_t capacity = DEF_STRUCT_CAP;

    output = (id*)malloc(sizeof(id) * capacity);

    if (output == NULL)
        report_merror();

    int i = 0;
    for (; i < *num_of_options; i++)
    {
        box * check = get_item_by_id(original[i]);

        if (substr(tag, (check->u != NULL ? check->u->name : check->g != NULL ? check->g->image->name :
            check->a != NULL ? check->a->title : check->r != NULL ? check->r->name : NULL)) != -1)
        {
            output[size++] = original[i];
        }

        free(check);

        if (size == capacity)
        {
            output = (id*)realloc(output, sizeof(id) * (capacity *= 2));
            if (output == NULL)
                report_merror();
        }
    }

    output = (id*)realloc(output, sizeof(id) * size);
    *num_of_options = size;

    if (output == NULL && *num_of_options != 0)
        report_merror();

    return output;
}

void session(id you)
{

    #pragma region getting user/group by id

    user * user_you = get_user_by_id(you);
    group * group_you = get_group_by_id(you);

    if (user_you == NULL)
        return;

    #pragma endregion

    #pragma region session

    int chinput;
    do 
    {
        system("cls");

        #pragma region main info output

        /* user's */
        out_str_wo_nl(user_you->name);
        printf("\n\tfull account: %d$,\n\trevenue: %d$.\n\n",
            user_you->full_account, user_you->revenue);
        
        /* group's if it is a group */
        if (group_you != NULL)
        {
            printf("\tMembers: ");

            if (group_you->num_of_members == 0)
                printf("none.\n\n");
            else
            {
                int i = 0;
                for (; i < group_you->num_of_members; i++)
                {
                    user * member = get_user_by_id(group_you->members[i]);
                    if (member != NULL)
                    {
                        out_str_wo_nl(member->name);
                        printf(", ");
                    }
                }
                printf("\b\b.\n\n");
            }
        }
        
        #pragma endregion

        #pragma region options output

        printf("Tap:\t\tTo:\n" 
            " 1\t\t add money\n" 
            " 2\t\t release a record\n" 
            " 3\t\t publish an article\n" 
            " 4\t\t buy a record\n" 
            " 5\t\t buy an article\n" 
            " 6\t\t see my records\n" 
            " 7\t\t see my articles\n");

        if (group_you != NULL)
        {
            printf(" 8\t\t add a member\n" 
                " 9\t\t remove a member\n");
        }

        printf(" 0\t\t sign out\n");

        #pragma endregion

        chinput = getch();

        #pragma region input processing

        if (chinput == '1') /* add money */
        {
            system("cls");
            printf("Enter the amount: ");
            add_money(you);
        }
        else if (chinput == '2') /* release a record */
        {
            release_a_record(you);
        }
        else if (chinput == '3') /* publish an article */
        {
            publish_an_article(you);
        }
        else if (chinput == '4') /* buy a record */
        {
            buy_a_record(you);
        }
        else if (chinput == '5') /* buy an article */
        {
            buy_an_article(you);
        }
        else if (chinput == '6') /* see my records */
        {
            int i = 0;
            for (; i < user_you->num_of_purchased_releases; i++)
            {
                display_release(user_you->purchased_releases[i]);
                printf("\n**************************************\n");
            }

            printf("\nPress any key to return to your account...");
            getch();
        }
        else if (chinput == '7') /* see my articles */
        {
            int i = 0;
            for (; i < user_you->num_of_purchased_articles; i++)
            {
                display_article(user_you->purchased_articles[i]);
                printf("\n**************************************\n");
            }

            printf("\nPress any key to return to your account...");
            getch();
        }
        else if (chinput == '8' && group_you != NULL) /* add a member */
        {
            id new_member = select_one(1, 0, 0, 0);

            if (is_among(group_you->members, group_you->num_of_members, new_member))
            {
                printf("This user is already in the group. Press any key to return to the account...");
                getch();
                continue;
            }

            group_you->members = (id*)realloc(group_you->members, sizeof(id) * group_you->num_of_members + 1);

            if (group_you->members == NULL)
                report_merror();

            group_you->members[group_you->num_of_members++] = new_member;

            printf("This user has been added to the group. Press any key to return to the account...");
            getch();

        }
        else if (chinput == '9' && group_you != NULL) /* remove a member */
        {
            if (group_you->num_of_members == 0)
            {
                printf("There's no one to remove. Press any key to return to your account...");
                getch();
                continue;
            }

            printf("Whom would you like to remove?\nEnter:\t\tTo remove:\n\n");
            printf(" 0\t\t No one\n");
            int i = 0;
            for (; i < group_you->num_of_members; i++)
            {
                printf(" %d\t\t ", i + 1);
                
                user * cur_member = get_user_by_id(group_you->members[i]);

                if (cur_member != NULL)
                    out_str_wo_nl(cur_member->name);
                    
                printf("\n");
            }

            int choice;
            do
            {
                choice = get_int();
            } while(choice < 0 || choice > group_you->num_of_members);

            if (choice == 0)
                continue;

            if (group_you->num_of_members == 1)
            {
                free(group_you->members);
                group_you->members = NULL;
                group_you->num_of_members = 0;
            }

            for (; choice < group_you->num_of_members - 1; choice++)
                group_you->members[choice - 1] = group_you->members[choice];

            group_you->members = (id*)realloc(group_you->members, --group_you->num_of_members * sizeof(id));

            if (group_you->members == NULL)
                report_merror();

            printf("This user has been removed from the group. Press any key to return to your account...");
            getch();

        }

        #pragma endregion

    } while (chinput != '0');

    #pragma endregion
    
}

void add_money(id you)
{

    #pragma region getting you by id

    user * user_you = get_user_by_id(you);
    if (user_you == NULL)
        return;

    #pragma endregion

    int sum = get_int();

    #pragma region checking account for int overflow

    if (sum < 0 || MAX_INT - user_you->full_account < sum)
    {
        printf("\nCan\'t add so much money. Press any key to return to your account...");
        getch();
        return;
    }

    #pragma endregion
   
    #pragma region adding money

    user_you->full_account += sum;
    
    printf("\n%d$ have been added to your account. Press any key to return to it...", sum);
    getch();
    return;

    #pragma endregion

}

void release_a_record(id you)
{
    system("cls");

    #pragma region getting you by id

    user * user_you = get_user_by_id(you);
    group * group_you = get_group_by_id(you);
    if (user_you == NULL)
        return;

    #pragma endregion

    release * new_one = new_release();

    #pragma region setting type

    printf("Is the record...\n"
           "Composition(1)\tSingle(2)\tLP(3)\tEP(4)\tMixtape(5)? ");

    do
    {
        new_one->type = getch() - '1';
    } while (new_one->type < 0 || new_one->type > 4);

    #pragma endregion

    #pragma region setting name

    printf("\nEnter the name of the release: ");

    char * tmp = get_string(stdin);

    if (length_of(tmp) == 2)
    {
        free(tmp);
        tmp = "Untitled\n";
    }

    new_one->name = tmp;

    #pragma endregion

    #pragma region setting cover

    printf("\nSet the cover(just enter int): ");

    new_one->cover = get_int();

    #pragma endregion

    #pragma region setting user-you / group + members as author(s) and adding the release to yours

    {

    new_one->num_of_authors = 1 + (group_you != NULL ? group_you->num_of_members : 0); 
    new_one->authors = (id*)malloc(sizeof(id) * new_one->num_of_authors);
    new_one->authors[0] = you;

    int i = 1;
    for (; i < new_one->num_of_authors; i++)
        new_one->authors[i] = group_you->members[i - 1];
    
    user_you->purchased_releases = (id*)realloc(user_you->purchased_releases, 
        user_you->num_of_purchased_releases + 1);
    if (user_you->purchased_releases == NULL)
        report_merror();

    user_you->purchased_releases[user_you->num_of_purchased_releases++] = 
        new_one->release_id;
     
    }

    #pragma endregion

    #pragma region setting date

    do
    {
        printf("\nEnter the date of the release: ");
        new_one->dropped = set_date();
    } while (new_one->dropped == NULL);

    #pragma endregion

    #pragma region seting songs

    {

    /* setting num of songs */
    do 
    {
        printf("\nEnter the number of songs on the record: ");
        new_one->num_of_songs = get_int();         
    } while (new_one->num_of_songs <= 0 || new_one->num_of_songs > SONGS_ON_THE_RECORD_UPPER_LIMIT);
    new_one->songs = (song*)malloc(sizeof(song) * new_one->num_of_songs);

    /* setting songs */
    int i = 0;
    for (; i < new_one->num_of_songs; i++)
    {
        printf("\nSet the song #%d:\n", i + 1);
        new_one->songs[i] = set_song();
    } 
    
    }

    #pragma endregion

    #pragma region setting price

    do 
    {
        printf("\nEnter the price of the record: ");
        new_one->price = get_int();     
    } while (new_one->price <= 0);

    #pragma endregion

    #pragma region releasing

    /* adding new release to yours as an id */
    user_you->releases = (id*)realloc(user_you->releases, sizeof(id) * (user_you->num_of_releases + 1));   
    if (user_you->releases == NULL)
        report_merror();
    user_you->releases[user_you->num_of_releases++] = new_one->release_id; 

    /* adding new release to all of them */
    releases = (release**)realloc(releases, sizeof(release*) * (num_of_releases + 1));
    if (releases == NULL)
        report_merror();
    releases[num_of_releases++] = new_one;

    #pragma endregion

}

void publish_an_article(id you)
{
    system("cls");

    #pragma region getting you by id

    user * user_you = get_user_by_id(you);
    group * group_you = get_group_by_id(you);
    if (user_you == NULL)
        return;

    #pragma endregion

    article * new_one = new_article();

    #pragma region setting the title

    printf("\nEnter the title of the article: ");

    char * tmp = get_string(stdin);

    if (length_of(tmp) == 2)
    {
        free(tmp);
        tmp = "Untitled\n";
    }

    new_one->title = tmp;

    #pragma endregion   

    #pragma region setting date

    do
    {
        printf("\nEnter the date of the publishing: ");
        new_one->published = set_date();
    } while (new_one->published == NULL);

    #pragma endregion

    #pragma region setting text the easy way

    /* setting num of lines */
    int lines_num;
    do 
    {
        printf("Enter the number of lines in the article: ");
        lines_num = get_int();
    } while (lines_num < 0 || lines_num > MAX_NUM_OF_ARTICLE_LINES);

    /* writing text */
    if (lines_num == 0)
    {
        new_one->text->num_of_lines = 0;
        new_one->text->lines = NULL;
    }
    else
    {
        printf("\nEnter text: ");
        new_one->text = get_text(stdin, yes_function, lines_num);
    }

    #pragma endregion

    #pragma region setting the author(s) the same way as with the release

    new_one->num_of_authors = 1 + (group_you != NULL ? group_you->num_of_members : 0); 
    new_one->authors = (id*)malloc(sizeof(id) * new_one->num_of_authors);
    new_one->authors[0] = you;

    int i = 1;
    for (; i < new_one->num_of_authors; i++)
        new_one->authors[i] = group_you->members[i - 1];

    if (user_you != NULL)
    {
        user_you->purchased_articles = (id*)realloc(user_you->purchased_articles, 
            user_you->num_of_purchased_articles + 1);

        if (user_you->purchased_articles == NULL)
            report_merror();

        user_you->purchased_articles[user_you->num_of_purchased_articles++] = 
            new_one->article_id;
    }    

    #pragma endregion

    #pragma region setting price

    do 
    {
        printf("\nEnter the price of the article: ");
        new_one->price = get_int();
            
    } while (new_one->price <= 0);

    #pragma endregion  

    #pragma region publishing

    /* adding to yours as an id */
    user_you->articles = (id*)realloc(user_you->articles, sizeof(id) * (user_you->num_of_articles + 1));  
    if (user_you->articles == NULL)
        report_merror();
    user_you->articles[user_you->num_of_articles++] = new_one->article_id; 

    /* ading to all */
    articles = (article**)realloc(articles, sizeof(article*) * (num_of_articles + 1));
    if (articles == NULL)
        report_merror();
    articles[num_of_articles++] = new_one;

    #pragma endregion

}

void buy_a_record(id you)
{

    #pragma region getting you by id

    box * whatever = get_item_by_id(you);

    user * user_you = NULL;

    if (whatever->u != NULL)
        user_you = whatever->u;
    else if (whatever->g != NULL)
        user_you = whatever->g->image;
    else
        return;

    free(whatever);

    #pragma endregion

    #pragma region selecting a record

    id record_id = select_one(0, 0, 0, 1);

    if (record_id == -1)
        return;

    whatever = get_item_by_id(record_id);

    release * selected;
    if ((selected = whatever->r) == NULL)
    {
        free(whatever);
        return;
    }
    free(whatever);

    #pragma endregion

    #pragma region checking if it is already yours

    if (is_among(user_you->purchased_releases, user_you->num_of_purchased_releases,
        selected->release_id))
        {
            printf("It\'s already yours. Press any key to return to your account...");
            getch();
            return;
        }

    #pragma endregion

    #pragma region confirmation

    printf("\n%sDo you want to buy it for %d$? (y / n) ", selected->name, selected->price);

    int chinput;

    do
    {
        chinput = getch();
    } while (chinput != 'y' && chinput != 'n');
    
    #pragma endregion

    #pragma region checking affordableness and money transfer

    if (chinput == 'y')
    {
        if (user_you->full_account < selected->price)
        {
            printf("\nYou don\'t have enough money. Press any key to return to your account...");
            getch();
            return;
        }
        else
        {
            user_you->full_account -= selected->price;

            box * author = get_item_by_id(selected->authors[0]);

            user * user_author = NULL;

            if (author->u != NULL)
                user_author = author->u;
            else if (author->g != NULL)
                user_author = author->g->image;
            else
                return;

            free(author);

            if (selected->price <= MAX_INT - user_author->revenue)
                user_author->revenue += selected->price;
            if (selected->price <= MAX_INT - user_author->full_account)  
                user_author->full_account += selected->price;

            user_you->purchased_releases = (id*)realloc(user_you->purchased_releases,
                sizeof(id) * (user_you->num_of_purchased_releases + 1));

            user_you->purchased_releases[user_you->num_of_purchased_releases++] = record_id;

            printf("\nYou have bought it. Press any key to return to your account...");
            getch();
            return;
        }
    }  

    #pragma endregion

}

void buy_an_article(id you)
{

    #pragma region getting user by id

    box * whatever = get_item_by_id(you);

    user * user_you = NULL;

    if (whatever->u != NULL)
        user_you = whatever->u;
    else if (whatever->g != NULL)
        user_you = whatever->g->image;
    else
        return;

    free(whatever);

    #pragma endregion

    #pragma region selecting article

    id article_id = select_one(0, 0, 1, 0);

    if (article_id == -1)
        return;

    whatever = get_item_by_id(article_id);

    article * selected;
    if ((selected = whatever->a) == NULL)
    {
        free(whatever);
        return;
    }
    free(whatever);

    #pragma endregion

    #pragma region checking if it is already yours

    if (is_among(user_you->purchased_articles, user_you->num_of_purchased_articles,
        selected->article_id))
        {
            printf("It\'s already yours. Press any key to return to your account...");
            getch();
            return;
        }

    #pragma endregion

    #pragma region confirmation

    printf("\nDo you want to buy ");
    out_str_wo_nl(selected->title);
    printf(" for %d$? (y / n)", selected->price);

    int chinput;
    do
    {
        chinput = getch();
    } while (chinput != 'y' && chinput != 'n');

    #pragma endregion
    
    #pragma region checking affordableness

    if (chinput == 'y')
    {
        if (user_you->full_account < selected->price)
        {
            printf("\nYou don\'t have enough money. Press any key to return to your account...");
            getch();
            return;
        }
        else
        {
            user_you->full_account -= selected->price;

            box * author = get_item_by_id(you);

            user * user_author = NULL;

            if (author->u != NULL)
                user_author = author->u;
            else if (author->g != NULL)
                user_author = author->g->image;
            else
                return;

            free(author);

            user_author->revenue += selected->price;
            user_author->full_account += selected->price;

            user_you->purchased_articles = (id*)realloc(user_you->purchased_articles,
                sizeof(id) * (user_you->num_of_purchased_articles + 1));

            user_you->purchased_articles[user_you->num_of_purchased_articles++] = article_id;

            printf("\nYou have bought it. Press any key to return to your account...");
            getch();
            return;
        }
    }  

    #pragma endregion

}

date * set_date()
{
    char * str = get_string(stdin);

    int i = 0, m = 0, d = 0, y = 0;
    for (; str[i] && str[i] != '\n' && str[i] != '/'; i++)
        m = m * 10 + str[i] - '0';
    for (i++ ; str[i] && str[i] != '\n' && str[i] != '/'; i++)
        d = d * 10 + str[i] - '0';
    for (i++ ; str[i] && str[i] != '\n' && str[i] != '/'; i++)
        y = y * 10 + str[i] - '0';

    free(str);

    if (y <= 1900 || y > 2100 || m <= 0 || m > 12 || d <= 0 ||
        (d > months[m - 1] && !(m == 2 && d == 29 && is_a_leap_year(y))))
        return NULL;

    date * new_date = (date*)malloc(sizeof(date));

    new_date->day = d;
    new_date->month = m;
    new_date->year = y;

    return new_date;
}

song set_song()
{
    song new_one;

    #pragma region setting name, cover & music

    printf("Set name of the song: ");

    new_one.name = get_string(stdin);
    if (length_of(new_one.name) == 2)
    {
        free(new_one.name);
        new_one.name = "untitled\n";
    }

    printf("\nSet cover of the song(0 for none): ");

    new_one.cover = get_int();

    printf("\nSet *music* (just enter int): ");

    new_one.music = get_int();

    #pragma endregion

    #pragma region setting lyrics the easy way

    int lines_num;
    do 
    {
        printf("\nEnter the number of lines in lyrics: ");
        lines_num = get_int();

    } while (lines_num < 0 || lines_num > MAX_NUM_OF_LYR_LINES);

    if (lines_num == 0)
    {
        new_one.lyrics = (text*)malloc(sizeof(text));
        new_one.lyrics->num_of_lines = 0;
        new_one.lyrics->lines = NULL;
    }
    else
    {
        printf("\nEnter lyrics: ");
        new_one.lyrics = get_text(stdin, yes_function, lines_num);
    }

    #pragma endregion

    return new_one;
}
