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
    Tk* Lista;
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
    Tk* ptr;
    int aux = 0;
    for(ptr = listId.front(); ptr != NULL; ptr = ptr->prox){
        //ptr->nome;
        
    }
}

int buscaId(char* nome){
    list <Tk*>::iterator it;

    for(it = listId.begin(); it != listId.end(); it++){
        if(strcmp(nome, (*it)->nome) == 0)
            return 1;
    }

    return 0;
}

void loadId(){
    char nome[][10] = {"int", "char", "float", "double", "short", "long"};
    Tk* l;
    
    for(int i = 0; i < 6; i++){
        l = (Tk*) malloc(sizeof(Tk));
        l->nome = (char*)malloc(sizeof(char)*strlen(nome[0]));
        printf("%s", nome[i]);
        strcpy(l->nome, nome[i]);
        contId++;
        listId.push_front(l);
        //pReservadas
    }
}

void loadPr(){
    char nome[][10] = {"do", "for", "while", "switch", "else", "if"};
    Tk* l;
    
    for(int i = 0; i < 6; i++){
        l = (Tk*) malloc(sizeof(Tk));
        l->nome = (char*)malloc(sizeof(char)*strlen(nome[0]));
        strcpy(l->nome, nome[i]);
        contId++;
        //pReservadas
    }
}