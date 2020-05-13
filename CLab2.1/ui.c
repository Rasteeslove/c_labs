#include "clab2.h"

#define RATE 0.09
#define OTHER_EXPENCES_TO_WAGES 2.5
#define AV_MON_DAYS 30.0
#define AV_WAGE 400.0
#define WORKING_HOURS 8

const char * days_of_the_week[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", 
    "Saturday", "Sunday"};

void out_str_wo_nl(char * str);
void set_date(date * one);
int length_of(char * str);
int get_int();
void add_project();
project * select_project();
void analyze_project(project * one);
void about();
void main_menu();

void out_str_wo_nl(char * str)
{
    if (str == NULL)
        return;

    int i = 0;
    for (; str[i] && str[i] != '\n'; i++)
        printf("%c", str[i]);
}

void set_date(date * one)
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

    if (y <= 2000 || y > 2100 || m <= 0 || m > 12 || d <= 0 ||
        (d > months[m - 1] && !(m == 2 && d == 29 && is_a_leap_year(y))))
        return;

    one->day = d;
    one->month = m;
    one->year = y;
}

int length_of(char * str)
{
    if (str == NULL)
    {
        return 0;
    }

    int i = 0;
    for (; str[i]; i++) {}

    return i + 1;
}

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

void add_project()
{
    system("cls");

    printf("New project:\n\n");

    #pragma region name

    printf("Enter the name of the project: ");
    char * name = get_string(stdin);

    #pragma endregion

    #pragma region dates

    date start = new_date();
    do
    {
        printf("Enter the start date: ");
        set_date(&start);
    } while (start.day == 0);
    
    date finish = new_date();
    do
    {
        printf("Enter the finish date: ");
        set_date(&finish);
    } while (finish.day == 0 || start.year > finish.year ||
        (start.year == finish.year && start.month > finish.month) ||
        (start.year == finish.year && start.month == finish.month && 
        start.day > finish.day));

    project tmp = new_project(NULL, start, finish, 0);

    while (duration_in_work_days_of(tmp) == 0)
    {
        printf("Seems like the project doesn\'t include any work days. Reenter it:\n");

        start = new_date();
        do
        {
            printf("Enter the start date: ");
            set_date(&start);
        } while (start.day == 0);
    
        finish = new_date();
        do
        {
            printf("Enter the finish date: ");
            set_date(&finish);
        } while (finish.day == 0 || start.year > finish.year ||
            (start.year == finish.year && start.month > finish.month) ||
            (start.year == finish.year && start.month == finish.month && 
            start.day > finish.day));

        tmp = new_project(NULL, start, finish, 0);
    }

    #pragma endregion

    #pragma region devs

    int num_of_devs;
    do
    {
        printf("Enter the number of developers: ");
        num_of_devs = get_int();
    } while (num_of_devs <= 0);

    #pragma endregion

    #pragma region confirm

    int choice;
    do
    {
        printf("Add project? (y / n)\n");
        choice = getch();
    } while (choice != 'y' && choice != 'n');

    if (choice == 'n')
        return;

    #pragma endregion

    #pragma region adding to projects

    projects = (project*)realloc(projects, sizeof(project) * (number_of_projects + 1));

    if (projects == NULL)
        report_error("memory error");

    projects[number_of_projects++] = new_project(name, start, finish, num_of_devs);

    #pragma endregion

}

project * select_project()
{
    system("cls");
    printf("Enter:\t\tTo select:\n\n");

    int i = 0;
    for (; i < number_of_projects; i++)
        printf(" %d\t\t %s", i + 1, projects[i].name);

    printf(" 0\t\t[nothing: cancel selecting]\n\n");

    int choice;
    do 
    {
        printf("Input: ");
        choice = get_int();
    } while (choice < 0 || choice > number_of_projects);

    if (choice == 0)
        return NULL;
    else
        return &projects[choice - 1];
}

void analyze_project(project * one)
{
    unsigned int duration = duration_in_work_days_of(*one);
    unsigned int labour_cost = duration * one->number_of_developers;

    double sum_of_wages = labour_cost / AV_MON_DAYS * AV_WAGE;
    double other_expences = sum_of_wages * OTHER_EXPENCES_TO_WAGES;
    double total_cost = sum_of_wages + other_expences;
    double profit = total_cost * RATE;
    int to_be_considered;

    if (profit > 1000)
        to_be_considered = 1;
    else
        to_be_considered = 0;

    system("cls");

    printf("Analyzing project ");
    out_str_wo_nl(one->name);
    printf(" developed by %d developer(s) "
           "starting %s %d/%d/%d and ending %s %d/%d/%d lasting %u work days including holidays:\n\n"
           "\tThe amount of labour to complete the project is %u man-days or %u man-hours,\n"
           "\tthe sum of wages for the developers is roughly %.2f$ + %.2f for other expences, \n"
           "\tmaking up the project\'s total cost of %.2f$.\n\n"
           "\tWith the rate of return of 9%% the project\'s gonna generate the profit of %.2f$.\n\n",
           one->number_of_developers,
           days_of_the_week[day_of_the_week(one->start_date)], one->start_date.month, 
            one->start_date.day, one->start_date.year,
           days_of_the_week[day_of_the_week(one->finish_date)], one->finish_date.month, 
            one->finish_date.day, one->finish_date.year,
           duration,
           labour_cost , labour_cost * WORKING_HOURS,
           sum_of_wages, other_expences, total_cost, profit);

    printf("\tThe profit is %s1000$, therefore the project is %sto be considered.\n\n",
           to_be_considered ? ">" : "<", to_be_considered ? "" : "not ");

    printf("Press any key to return to the menu...");
    getch();
}

void about()
{
    system("cls");

    printf("About the app:\n"
           "\tversion: first and final\n"
           "\tdeveloped by Rastsislau Kayko\n"
           "Press any key to return to the main menu...");

    getch();
}

void main_menu()
{
    int chinput;

    do 
    {
        system("cls");

        printf("Tap:\t\tTo:\n\n"
               " 1\t\t add project\n"
               " 2\t\t analyze project\n"
               " 3\t\t about the app\n"
               " 0\t\t exit app");

        chinput = getch();

        if (chinput == '1')
        {
            add_project();
        }
        else if (chinput == '2')
        {
            project * to_analyze = select_project();
            if (to_analyze != NULL)
                analyze_project(to_analyze);
        }
        else if (chinput == '3')
        {
            about();
        }

    } while (chinput != '0');
}
