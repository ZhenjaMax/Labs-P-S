#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define UNIT_SIZE 512
#define START_DIRECTORY "./labyrinth"
#define BAD_END "Deadlock"
#define GOOD_END "Minotaur"
#define RESULT_FILE "./result.txt"

typedef struct Filetree{
	char* name;
	char* path;
	char* tailname;
}Filetree;

Filetree* createLink(char* name, char* path, char* tailname){
	Filetree* link = malloc(sizeof(Filetree));
	char* linkname = malloc(UNIT_SIZE*sizeof(char));
	link->name = strcpy(linkname, name);
	char* linkpath = malloc(UNIT_SIZE*sizeof(char));
	link->path = strcpy(linkpath, path);
	char* linktailname = malloc(UNIT_SIZE*sizeof(char));
	link->tailname = strcpy(linktailname, tailname);
	return link;
}

void createLinkList(const char *name, int* count, Filetree*** list){
    DIR *dir;
    struct dirent *element;
    if (!(dir = opendir(name))) return;
    while ((element = readdir(dir)) != NULL){
		char path[UNIT_SIZE];
        snprintf(path, sizeof(path), "%s/%s", name, element->d_name);
        if ((element->d_type == DT_DIR)&&(strcmp(element->d_name, "."))&&(strcmp(element->d_name, ".."))) createLinkList(path, count, list); else {
            FILE *fp = fopen(path, "r");
			char tailname[UNIT_SIZE];
			while(fgets(tailname, UNIT_SIZE, fp)!=NULL){
				strtok(tailname, "\n");
				(*count)++;
				*list = realloc(*list, (*count)*sizeof(Filetree*));
				if(strcmp(tailname, BAD_END)==0) (*list)[(*count)-1] = createLink(element->d_name, path, BAD_END);
				else if(strcmp(tailname, GOOD_END)==0) (*list)[(*count)-1] = createLink(element->d_name, path, GOOD_END);
				else (*list)[(*count)-1] = createLink(element->d_name, path, tailname+9);
			}
			fclose(fp);
        }
    }
    closedir(dir);
	return;
}

char** getPathList(int count, Filetree** list, int* pathListLength){
	int i=0;
	char** pathList = malloc((*pathListLength)*sizeof(char*));
	char* tempname = GOOD_END;
	while(1){
		for(i=0; i<count; i++) if(strcmp((list[i])->tailname, tempname)==0) break;
		if(i==count) return pathList; else {
			(*pathListLength)++;
			pathList = realloc(pathList, (*pathListLength)*sizeof(char*));
			pathList[(*pathListLength)-1] = list[i]->path;
			tempname = list[i]->name;
		}
	}
}

void importPathList(char** pathList, int* pathListLength){
	FILE* fp = fopen(RESULT_FILE, "w");
	for(int i=(*pathListLength)-1; i>=0; i--){
		fputs(pathList[i], fp);
		putc('\n', fp);
	}
	fclose(fp);
	return;
}

void removeLinkList(int count, Filetree** list){
	for(int i=0; i<count; i++){
		free(list[i]->name);
		free(list[i]->path);
		free(list[i]->tailname);
		free(list[i]);
	}
	free(list);
	return;
}

int main(){
	int count = 0;
	Filetree** list = malloc(sizeof(Filetree*)*count);
    createLinkList(START_DIRECTORY, &count, &list);
	int pathListLength = 0;
	char** pathList = getPathList(count, list, &pathListLength);
	importPathList(pathList, &pathListLength);
	removeLinkList(count, list);
    return 0;
}
