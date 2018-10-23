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
int buscaId(char* nome);
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
    loadId();
    loadPr();
    analiseLexica();
    listId.clear();

    system("pause");
    return 0;
}

void analiseLexica(){
    printf("========> Analise lexica em andamento...\n\n");
    Tk* ptr;
    int aux = 0, lx;

    for(ptr = listId.front(); ptr != NULL; ptr = ptr->prox){
        if(ptr->linha != aux){
            aux = ptr->linha;
        }

        lx = buscaId(ptr->nome);

        if(lx){
            printf("Entrou");
            exit(1);
        }        
    }
}

int buscaId(char* nome){
    printf("========> Buscando Id's...\n\n");
    list <Tk*>::iterator it;
    int i = 0;

    for(it = listId.begin(); it != listId.end(); it++, i++){
        if(strcmp(nome, (*it)->nome) == 0)
            return i;
    }

    return 0;
}

void loadId(){
    printf("========> Procurando por tokens reservados...\n\n");

    char nome[][10] = {"int", "char", "float", "double", "short", "long", "struct"};
    Tk* l;
    
    for(int i = 0; i < 7; i++){
        l = (Tk*) malloc(sizeof(Tk));
        l->nome = (char*)malloc(sizeof(char)*strlen(nome[0]));
        printf("========> %s <========\n\n", l->nome);
        strcpy(l->nome, nome[i]);
        contId++;
        listId.push_front(l);
        //pReservadas
    }
}

void loadPr(){
    printf("========> Procurando por palavras reservadas...\n\n");

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