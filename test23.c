#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Filetree{
	char* name;
	char* path;
	char* tailname;
	struct filetree* head;
	struct filetree* tail;
}Filetree;

Filetree* createListLink(char* name, char* path, char* tailname){
	
	Filetree* link = (Filetree*)malloc(sizeof(Filetree));
	
	char* linkname = (char*)malloc(1024*sizeof(char));
	strcpy(linkname, name);
	link->name = linkname;
	
	char* linkpath = (char*)malloc(1024*sizeof(char));
	strcpy(linkpath, path);
	link->path = linkpath;
	
	if(tailname == NULL) link->tailname = NULL; else {
		char* linktailname = (char*)malloc(1024*sizeof(char));
		strcpy(linktailname, tailname+9); //@include txt.txt (9+...)
		link->tailname = linktailname;
	}
	
	link->head = NULL;
	link->tail = NULL;
	return link;
}

void listdir(const char *name, int* count, Filetree** list){
    DIR *dir;
    struct dirent *element;

    if (!(dir = opendir(name)))
        return;

    while ((element = readdir(dir)) != NULL) {
        if (element->d_type == DT_DIR) {
            if (strcmp(element->d_name, ".") == 0 || strcmp(element->d_name, "..") == 0) continue;
			char path[1024];
            snprintf(path, sizeof(path), "%s/%s", name, element->d_name);
            listdir(path, count, list);
        } else {
		    char path[1024];
            snprintf(path, sizeof(path), "%s/%s", name, element->d_name);
            FILE *fp = fopen(path, "r");
			char tailname[1024];
			while(fgets(tailname, 1024, fp)!=NULL) printf("%s", tailname);
			fclose(fp);
        }
    }
    closedir(dir);
}

int main(){
	int count = 0;
	Filetree** list = malloc(sizeof(Filetree*)*count);
	
    listdir("./labyrinth", &count, list);
    return 0;
}
