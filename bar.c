#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// labyrith
void listdir(char *name, char* fileName, int* flag){
    
    if(*flag) return;
    
    DIR *dir;
    struct dirent *entry;
    
    dir = opendir(name);
    while ((entry = readdir(dir)) != NULL){
        if(entry->d_type == DT_DIR){
            if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
            
            char path[1024];
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            listdir(path, fileName, flag);
            
        } else if(strcmp(entry->d_name, fileName) == 0){
            *flag = 1;
            char path[1024];
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            printf("%s\n", path);
        }
    }
    closedir(dir);
    return;
}

int main(){
    
    int* flag = (int*)malloc(sizeof(int));
    *flag=0;
    char* fileName = "main.c";
    listdir(".", fileName, flag);
    return 0;
}
