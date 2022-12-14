/*
Name: DINESH MOOD
BlazerId: dmood
Project #: Homework_2
To compile: gcc -o dmood_hw2 dmood_hw2.c
To run: ./dmood_hw2 <options> <filepath>
 -S: List all files with size, permissions and last access time.
 -s: List all files with file size less than or equal to the value specified.
 -f: List all files with specified conditions in documentation
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int MaxDepth = -1, MaxLength = -1, Attr = 0;
char *Substr = "";
char *PATH = ".";

int search(char *path, int curDepth)
{
    DIR *dir;
    struct dirent *dirEntry;
    struct stat fileStat;

    dir = opendir(path);
    while (dirEntry = readdir(dir))
    {
        if (strcmp(dirEntry->d_name, ".") != 0 && strcmp(dirEntry->d_name, "..") != 0)
            lstat(dirEntry->d_name, &fileStat);
        else
            continue;

        char *newPath = malloc(strlen(path) + strlen(dirEntry->d_name) + 2);
        strncpy(newPath, path, strlen(path) + 1);
        strcat(newPath, "/");
        strncat(newPath, dirEntry->d_name, strlen(dirEntry->d_name) + 1);

        if (MaxDepth == -1 || curDepth <= MaxDepth)
        {
            if (dirEntry->d_type == DT_DIR)
            {
                for (int i = 0; i < curDepth; i++)
                    printf("\t");

                printf("%s\t", dirEntry->d_name);
                if (Attr == 1)
                    printf("\t0\t");
                else if (S_ISLNK(fileStat.st_mode))
                {
                    char buf[1024];
                    int len = readlink(path, buf, sizeof(buf) - 1);
                    buf[len] = '\0';
                    char *name = strstr(buf, "/");
                    if (name == NULL)
                        name = path;
                    else
                        name++;
                    printf("(%s)\t", name);
                }

                if (Attr)
                {
                    printf("\t0\t");
                    printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
                    printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
                    printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
                    printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
                    printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
                    printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
                    printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
                    printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
                    printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
                    printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
                    printf("\t%s", ctime(&fileStat.st_atime));
                }
                printf("\n");
                search(newPath, curDepth + 1);
            }
            else if (strstr(dirEntry->d_name, Substr) && (MaxLength == -1 || fileStat.st_size <= MaxLength))
            {
                for (int i = 0; i < curDepth; i++)
                    printf("\t");

                printf("%s\t", dirEntry->d_name);

                if (S_ISLNK(fileStat.st_mode))
                {
                    char buf[1024];
                    int len = readlink(path, buf, sizeof(buf) - 1);
                    buf[len] = '\0';
                    char *name = strstr(buf, "/");
                    if (name == NULL)
                        name = path;
                    else
                        name++;
                    printf("(%s)\t", name);
                }

                if (Attr)
                {
                    printf("\t%ld\t", fileStat.st_size);
                    printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
                    printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
                    printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
                    printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
                    printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
                    printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
                    printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
                    printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
                    printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
                    printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
                    printf("\t%s", ctime(&fileStat.st_atime));
                }
                printf("\n");
            }
        }
    }
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        if (strncmp(argv[i], "-s", 2) == 0)
        {
            MaxLength = atoi(argv[i + 1]);
            i++;
        }
        else if (strncmp(argv[i], "-f", 2) == 0)
        {
            Substr = argv[i + 1];
            MaxDepth = atoi(argv[i + 2]);
            i += 2;
        }
        else if (strncmp(argv[i], "-S", 2) == 0)
        {
            Attr = 1;
        }
        else
        {
            PATH = argv[i];
        }
    }

    search(PATH, 0);
}

