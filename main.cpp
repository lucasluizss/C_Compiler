#include<iostream>
#include<list>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"scan.h"

using namespace std;
//extern Tk *getTokens(char *nome);
Tk* tokens;
list <Tk*> simbolos;
list <Tk*> pReservadas;
list <Tk*> listId;
int contId;

void analiseLexica();
void loadId();
void loadPr();
/*********************************
 * Nome: main
 * desc:
 * returno:
 ********************************/
int main(int argc, char *argv[])
{
    //simbolos.push

    contId = 0;
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
    analiseLexica();
    listId.clear();

    return 0;
}

void analiseLexica(){
    Tk* list;
    // list<Tk*>::iterator it;

    // for(it = simbolos.front(); it != NULL; it++){

    // }

    for(list = tokens; list != NULL; list=list->prox){

    }
}

void loadId(){
    char nome[][10] = {"int", "char", "float", "double", "short", "long"}
    Tk* l;
    
    for(int = 0; i < 6; i++){
        l = (Tk*) malloc(sizeof(Tk));
        l->nome = (char*)malloc(sizeof(char)*strlen(nome[0]));
        strcpy(l->nome, nome[i]);
        contId++;
        listId.push_front(l);
        //pReservadas
    }
}

void loadPr(){
    char nome[][10] = {"do", "for", "while", "switch", "else", "if"}
    Tk* l;
    
    for(int = 0; i < 6; i++){
        l = (Tk*) malloc(sizeof(Tk));
        l->nome = (char*)malloc(sizeof(char)*strlen(nome[0]));
        strcpy(l->nome, nome[i]);
        contId++;
        //pReservadas
    }
}