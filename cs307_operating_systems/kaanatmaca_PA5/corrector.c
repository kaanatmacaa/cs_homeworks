#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <dirent.h>

struct list
{
    char *gender;
    char *name;
    char *surname;
    struct list *next;
};

struct list *head = NULL;
struct list *node = NULL;
struct list *temp = NULL;
char word[20];
int count = 1;

void listdir(const char *name, int indent)
{
    DIR *dir;
    struct dirent *entry;
    char *fileDatabase = "./database.txt";

    if (!(dir = opendir(name)))
        return;

    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type == DT_DIR) // gcc a.c --std=c99 -Wall
        {
            char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            printf("%*s[%s]\n", indent, "", entry->d_name);
            listdir(path, indent + 2);
        }
        else
        {
            printf("%*s- %s\n", indent, "", entry->d_name);
            char *filename = entry->d_name;
            const size_t len = strlen(entry->d_name);
            char newname[1024];
            snprintf(newname, sizeof(newname), "%s/%s", name, entry->d_name);
            if (strcmp(newname, fileDatabase) == 0)
            { // if ./database.txt do nothing since we already opened it in main
            }
            else
            {
                // TODO: dname .txt mi diye bak
                if (!(len > 4 && entry->d_name[len - 4] == '.' && entry->d_name[len - 3] == 't' && entry->d_name[len - 2] == 'x' && entry->d_name[len - 1] == 't'))
                {
                    printf("Can not open %s since it is not txt file\n", entry->d_name);
                }
                else
                {
                    FILE *ftext = fopen(newname, "r+");
                    if (!ftext)
                        printf("Can not open %s \n", entry->d_name);
                    else
                    {
                        printf("Can open %s \n", entry->d_name);
                        while (!feof(ftext))
                        {
                            fscanf(ftext, "%s", word);
                            temp = head;
                            for (int i = 0; i < count; i += 3)
                            {
                                if (temp == NULL)
                                    break;
                                struct list *check = (struct list *)malloc(sizeof(struct list));
                                check->name = strdup(word);               // char * name = strdup(word)
                                if (strcmp(check->name, temp->name) == 0) // if same strings
                                {
                                    printf("%s ", word);
                                    printf("%ld \n", ftell(ftext));
                                    check->gender = temp->gender;
                                    check->surname = temp->surname;
                                    char *realGen;
                                    if (strcmp(check->gender, "m") == 0)
                                        realGen = "Mr.";
                                    else
                                        realGen = "Ms.";
                                    int offset1 = strlen(check->name) + 4;
                                    fseek(ftext, -offset1, SEEK_CUR);
                                    fputs(realGen, ftext);
                                    printf("%ld ", ftell(ftext));
                                    fseek(ftext, offset1 - 3, SEEK_CUR);
                                    printf("%ld ", ftell(ftext));
                                    fseek(ftext, 1, SEEK_CUR);
                                    printf("%ld \n", ftell(ftext));
                                    fputs(check->surname, ftext);
                                    fseek(ftext, -(strlen(check->surname) + 1), SEEK_CUR);
                                }
                                free(check);
                                temp = temp->next;
                            }
                        }
                    }
                }
            }
        }
    }
    closedir(dir);
}

int main(int argc, char *argv[])
{
    FILE *fdata = fopen("database.txt", "r");
    if (!fdata)
        printf("Can not open database file \n");
    else
    {
        head = (struct list *)malloc(sizeof(struct list));
        while (!feof(fdata))
        {
            fscanf(fdata, "%s", word);
            if (count <= 3)
            {
                if (count % 3 == 1) // 1
                    head->gender = strdup(word);
                else if (count % 3 == 2) // 2
                    head->name = strdup(word);
                else
                    head->surname = strdup(word);
            }
            else if (count % 3 == 1) // 4
            {
                if (node != NULL)
                    temp = node;
                node = (struct list *)malloc(sizeof(struct list));
                if (count == 4)
                    head->next = node;
                else
                    temp->next = node;

                node->gender = strdup(word);
            }
            else if (count % 3 == 2) // 5
            {
                node->name = strdup(word);
            }
            else if (count % 3 == 0) // 6
            {
                node->surname = strdup(word);
            }
            count++;
        }
    }
    listdir(".", 0);
    return 0;
}