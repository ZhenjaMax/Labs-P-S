#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct MusicalComposition{
    char* name;
    char* author;
    int year;
    struct MusicalComposition* p_prev;
    struct MusicalComposition* p_next;
} MusicalComposition;

MusicalComposition* createMusicalComposition(char* name, char* autor,int year);
MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n);
void push(MusicalComposition* head, MusicalComposition* element);
void removeEl(MusicalComposition* head, char* name_for_remove);
int count(MusicalComposition* head);
void print_names(MusicalComposition* head);

int main(){
    int length;
    scanf("%d\n", &length);  

    char** names = (char**)malloc(sizeof(char*)*length);
    char** authors = (char**)malloc(sizeof(char*)*length);
    int* years = (int*)malloc(sizeof(int)*length);

    for (int i=0;i<length;i++)
    {
        char name[80];
        char author[80];

        fgets(name, 80, stdin);
        fgets(author, 80, stdin);
        fscanf(stdin, "%d\n", &years[i]);

        (*strstr(name,"\n"))=0;
        (*strstr(author,"\n"))=0;

        names[i] = (char*)malloc(sizeof(char*) * (strlen(name)+1));
        authors[i] = (char*)malloc(sizeof(char*) * (strlen(author)+1));

        strcpy(names[i], name);
        strcpy(authors[i], author);

    }
    MusicalComposition* head = createMusicalCompositionList(names, authors, years, length);
    char name_for_push[80];
    char author_for_push[80];
    int year_for_push;

    char name_for_remove[80];

    fgets(name_for_push, 80, stdin);
    fgets(author_for_push, 80, stdin);
    fscanf(stdin, "%d\n", &year_for_push);
    (*strstr(name_for_push,"\n"))=0;
    (*strstr(author_for_push,"\n"))=0;

    MusicalComposition* element_for_push = createMusicalComposition(name_for_push, author_for_push, year_for_push);

    fgets(name_for_remove, 80, stdin);
    (*strstr(name_for_remove,"\n"))=0;

    printf("%s %s %d\n", head->name, head->author, head->year);
    int k = count(head);

    printf("%d\n", k);
    push(head, element_for_push);

    k = count(head);
    printf("%d\n", k);

    removeEl(head, name_for_remove); 
    print_names(head);

    k = count(head);
    printf("%d\n", k);

    for (int i=0;i<length;i++){
        free(names[i]);
        free(authors[i]);
    }
    free(names);
    free(authors);
    free(years);

    return 0;
}

MusicalComposition* createMusicalComposition(char* name, char* author, int year){
    MusicalComposition* Composition = malloc(sizeof(MusicalComposition));
    Composition->name = name;
    Composition->author = author;
    Composition->year = year;
    Composition->p_prev = NULL;
    Composition->p_next = NULL;
    return Composition;
}

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){
    MusicalComposition* curr = NULL;
    MusicalComposition* prev = NULL;
    MusicalComposition* head = NULL;
    for(int i=0; i<n; i++){
        curr = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        if(i==0){
            head = curr;
            prev = curr;
            continue;
        }
        prev->p_next=curr;
        curr->p_prev=prev;
        prev=curr;
    }
    return head;
}

void push(MusicalComposition* head, MusicalComposition* element){
    MusicalComposition* curr = head;
    while(curr->p_next) curr = curr->p_next;
    curr->p_next=element;
    element->p_prev=curr;
    return;
}

void removeEl(MusicalComposition* head, char* name_for_remove){
    MusicalComposition* curr = head;
	while(strcmp(curr->name, name_for_remove)) curr = curr->p_next;
	(curr->p_next)->p_prev = curr->p_prev;
	(curr->p_prev)->p_next = curr->p_next;
	free(curr);
	return;
}

int count(MusicalComposition* head){
	int n=1;
	MusicalComposition* curr = head;
	while(curr->p_next){
		curr=curr->p_next;
		n++;
	}
	return n;
}

void print_names(MusicalComposition* head){
	MusicalComposition* curr = head;
	while(curr){
		printf("%s\n", curr->name);
		curr = curr->p_next;
	}
	return;
}