#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define START_DIRECTORY "./labyrinth"
#define START_FILE "file.txt"
#define BAD_END "Deadlock"
#define GOOD_END "Minotaur"
#define RESULT_FILE "result.txt"

typedef struct Filetree{
	char* name;
	char* path;
	char* tailname;
	struct filetree* head;
	struct filetree* tail;
}Filetree;

Filetree* createListLink(char* name, char* path, char* tailname){
	Filetree* link = (Filetree*)malloc(sizeof(Filetree));
	
	char* linkname = (char*)malloc(512*sizeof(char));
	strcpy(linkname, name);
	link->name = linkname;
	
	char* linkpath = (char*)malloc(512*sizeof(char));
	strcpy(linkpath, path);
	link->path = linkpath;
	
	if(tailname == NULL){link->tailname = NULL;} else {
		char* linktailname = (char*)malloc(512*sizeof(char));
		strcpy(linktailname, tailname+9); //@include txt.txt (9+...)
		link->tailname = linktailname;
	}
	
	link->head = NULL;
	link->tail = NULL;
	return link;
}

void writelistFiletree(int* count, Filetree** list, char* path){
	DIR* d = opendir(path);
	struct dirent* element;
	while ((element = readdir(d)) != NULL){
		if(strcmp(element->d_name, ".") == 0 || strcmp(element->d_name, "..") == 0) continue;
		char farPath[512];
        snprintf(farPath, 512, "%s/%s", path, element->d_name);
		if(element->d_type == DT_DIR){
			writelistFiletree(count, list, farPath);
		} else {
			FILE *fp = fopen(path, "r");
			char tailname[512];
			while(!feof(fp)){
				fgets(tailname, 512, fp);
				if(strcmp(tailname, BAD_END)) continue;
				(*count)++;
				list = (Filetree**)realloc(list, (*count)*sizeof(Filetree*));
				if(strcmp(tailname, GOOD_END)){
					list[(*count)-1] = createListLink(element->d_name, farPath, NULL);
				} else {
					list[(*count)-1] = createListLink(element->d_name, farPath, tailname);
				}
			}
			fclose(fp);
		}
	}
	closedir(d);
	return;
}

int main(){
	
	int count = 0;
	Filetree** list = malloc(sizeof(Filetree*)*count);
	char startPath[512];
	strcpy(startPath, START_DIRECTORY);
	writelistFiletree(&count, list, startPath);
	
	for(int i=0; i<count; i++) printf("%s -> %s\n", (list[i])->name, (list[i])->tailname);
	
	return 0;
}
