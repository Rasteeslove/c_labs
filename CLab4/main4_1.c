#include "clab4.h"

int writable_via_file();

int main()
{
    /* ввод: */

    FILE * conf = fopen("conf.txt", "w");  /* чтобы остановить ввод текста, в этот файл введите ненулевой инт, например 1 (я не хотел заканчивать ввод текста парой нажатий enter: так конец ввода не зависит от ввода) */
    fclose(conf);  

    printf("Enter your text (write \"1\" to \"conf.txt\" and press enter to stop reading):\n");

    char * text = read_text((char*)&"text.txt"[0], writable_via_file);

    /* первое задание редактирует содержимое файла, так что не запускайте его перед вторым */

    printf("\n\nHere is the text:\n\n");
    write_text(text);
    
    /* task two : */
    printf("\n\nHere are the words of the text beginning and ending with the same letter:\n\n");
    out_same_lets(text);

    /* task one : */
    printf("\n\nHere is the text with only first entries of every letter left:\n\n");
    leave_first_letters(text);
    write_text(text);

    return 0;
}

int writable_via_file()
{
    FILE * conf = fopen("conf.txt", "r"); 
    int trig = 0;
    fscanf(conf, "%d", &trig);
    fclose(conf);
    return !trig;
}