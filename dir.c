#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

void ls(char * path) {
    printf("==== listing %s ====\n", path);
    DIR * dir = opendir(path);
    struct dirent *info;
    info = readdir(dir);
    while (info) {
        char * name = info->d_name;
        if (info->d_type == DT_DIR) {
            printf("dir: %s\n", name);
        } else if (info->d_type == DT_REG) {
            printf("reg: %s\n", name);
        } else {
            printf("oth: %s\n", name);
        }
        info = readdir(dir);
    }
    closedir(dir);
}

off_t total_size(char * path) {
    DIR * dir = opendir(path);
    off_t size = 0;
    struct dirent *info;
    info = readdir(dir);
    while (info) {
        if (info->d_type == DT_REG) {
            char filepath[256];
            strcpy(filepath, path);
            strcat(filepath, "/");
            strcat(filepath, info->d_name);
            struct stat sb;
            stat(filepath, &sb);
            size += sb.st_size;
        }
        info = readdir(dir);
    }
    closedir(dir);
    return size;
}

int main() {
    printf("***** SCANNING \"TEST\" DIRECTORY ***** \n");
    ls("test");
    printf("total size of test: %lu\n", total_size("test"));
    printf("***** SCANNING CURRENT DIRECTORY: *****\n");
    ls(".");
    printf("total size of curr dir: %lu\n", total_size("."));
}
