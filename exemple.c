#include<stdio.h>
#include<string.h>

typedef struct tk{
    char *name;
    int linha;
    struct tk *prox;
}Tk;

Tk *tkList;

int main(int argc, char * argv[]){
    printf("Olá mundo!");

    FILE *a;
    Tk *item;
    char str[50];

    if(argc == 2){
        strcpy(str, argc[1]);
    }
    else{
        printf("Enter with the file name: ");
        scanf("%s", str);
    }

    a = openFile(str);

    //region File working
    while(!feof(a)){
        //char look;
        //look = fgetc(a);
        //printf("%c", look);

        scan(a);
        item = (Tk*) malloc(sizeof(Tk));
        item -> prox = NULL;
        item -> linha = 0;
        item -> name = (char*) malloc (sizeof()*strlen(token));
        strcpy(item->name, token);
        insereList(item);
    }

    return tkList;

    //endregion

    return 0;
}

FILE *openFile(char *name){
    FILE *p;

    p = fopen(name, "r");

    if(p = null){
        printf("Error to load file!");
        exit(1);
    }

    return p;
}