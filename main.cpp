#include <iostream>
#include<stdio.h>
#include<string.h>
#include"scan.h"

using namespace std;
//extern Tk *getTokens(char *nome);

/*********************************
 * Nome: main
 * desc:
 * returno:
 ********************************/
int main(int argc, char *argv[])
{
    Tk *Lista;
    char nome[50];// = "arquivo.c";

    if(argc==2){
        strcpy(nome, argv[1]);
    }
    else{
        printf("Digite o nome do arquivo: ");
        scanf("%s", nome);
    }

    Lista = getTokens(nome);
    exibeTk(Lista);

    return 0;
}
