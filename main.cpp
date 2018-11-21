#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<list>
#include"scan.h"
using namespace std;

//extern Tk *getTokens(char *nome);
Tk* tokens;
list<simbolos*> listSimbolos;
list<Tk*> pReservadas;
list<Tk*> listId;
Tk* listTokens;
int contId;

char reservedWords[][10] = {
    "auto",
    "break",
    "case",
    "char",
    "const",
    "continue",
    "default",
    "do",
    "double",
    "else",
    "enum",
    "extern",
    "float",
    "for",
    "goto",
    "if",
    "int",
    "long",
    "register",
    "return",
    "short",
    "signed",
    "sizeof",
    "static",
    "struct",
    "switch",
    "typeof",
    "union",
    "unsigned",
    "void",
    "volatile",
    "while"
};

//list<simbolos*>listSimbolos;
void analiseLexica();
void loadId();
void loadPr();

int buscaId(char* nome);
int buscaSimbolo(char* nome);
Tk* lexaId(Tk* ptr);
void addListSimbolo(Tk* sb, int id);
void exibListSimbolo();

/*********************************
 * Nome: Lucas / Rhuan
 * desc:
 * returno:
 ********************************/
int main(int argc, char * argv[]) {

    char arq[50];
    char* var;
    if (argc != 2) {
        printf("digite o nome do arquivo:");
        scanf("%s", arq);
    } else {
        strcpy(arq, argv[1]);
    }

    listTokens = getTokens(arq);
    exibeTk(listTokens);
    loadId();
    loadPr();
    analiseLexica();
    liberaTk(listTokens);

    return 0;
}

void carregaRW() {
    char words[][10] = {
        "auto",
        "break",
        "case",
        "char",
        "const",
        "continue",
        "default",
        "do",
        "double",
        "else",
        "enum",
        "extern",
        "float",
        "for",
        "goto",
        "if",
        "int",
        "long",
        "register",
        "return",
        "short",
        "signed",
        "sizeof",
        "static",
        "struct",
        "switch",
        "typeof",
        "union",
        "unsigned",
        "void",
        "volatile",
        "while"
    };
}

void analiseLexica() {
    Tk * ptr;
    int aux = 0, lx;

    for (ptr = listTokens; ptr != NULL; ptr = ptr->prox) {

        printf("Nome: %s\n", ptr->nome);

        if (ptr->linha != aux) {
            aux = ptr->linha;
        }
        
        // teste se � um id
        if (buscaId(ptr->nome)) {
            printf("entrou....%s\n", ptr->nome);
            ptr = lexaId(ptr->prox);
        }
        // testa par saber se � um if

        // testa para saber se � um for

        // testa para saber se � uma express�o de atribui��o
        //printf("%s ", ptr->nome);
    }    
}

Tk * lexaId(Tk * ptr) {
    
    for (;;) {
        if (buscaSimbolo(ptr->nome)) {
            printf("Erro... linha: %d \nA variavel: %s ja foi declarada \n", ptr->linha, ptr->nome);
            exit(1);
        }

        if (!isalpha(ptr->nome[0])) {
            printf("Erro... linha: %d \nA variavel: %s esperado um identificador \n", ptr->linha, ptr->nome);
            exit(1);
        }

        addListSimbolo(ptr, 1);
        ptr = ptr->prox;

        if (ptr->nome[0] == ';') {
            ptr = ptr->prox;
            exibListSimbolo();
            return ptr;
        } else if (ptr->nome[0] == ',') {
            ptr = ptr->prox;
        } else {
            printf("Erro linha: %d, caractere: %s invalido. Esperado uma , ou ; \n", ptr->linha, ptr->nome);
            exit(1);
        }
    }

}

int buscaSimbolo(char *nome) {
    list<simbolos*> ::iterator it;

    for (it = listSimbolos.begin(); it != listSimbolos.end(); it++) {
        if (strcmp(nome, (*it)->nome) == 0) {
            return 1;
        }
    }

    return 0;
}

void exibListSimbolo() {
    list<simbolos*> ::iterator it;
    char tip[][15] = {
        "Ponteiro",
        "Id",
        "Constante",
        "Vetor",
        "Opr",
        "Preservada"
    };

    for (it = listSimbolos.begin(); it != listSimbolos.end(); it++) {
        printf("[ %s, %s , %d ]\n", (*it)->nome, tip[(*it)->id], (*it)->n);
    }

    printf("\n");
}

void loadId() {

    char nome[][10] = {
        "int",
        "char",
        "float",
        "double",
        "struct"
    };

    Tk * l;
    
    for (int i = 0; i < 6; i++) {
        l = (Tk * ) malloc(sizeof(Tk));
        l->nome = (char * ) malloc(sizeof(char) * strlen(nome[5]));
        strcpy(l->nome, nome[i]);
        l->id = contId;
        contId++;
        listId.push_back(l);
    }
}

int buscaId(char *nome) {
    list<Tk*> ::iterator it;
    int i = 1;

    for (it = listId.begin(); it != listId.end(); it++, i++) {
        if (strcmp(nome, ( * it)->nome) == 0) {
            return i;
        }
    }

    return 0;
}

void loadPr() {
    char nome[][10] = {
        "if",
        "for",
        "do",
        "switch",
        "while",
        "long"
    };

    Tk* l;
    
    for (int i = 0; i < 6; i++) {
        l = (Tk *) malloc(sizeof(Tk));
        l->nome = (char *) malloc(sizeof(char) * strlen(nome[5]));
        strcpy(l->nome, nome[i]);
        l->id = contId;
        contId++;
    }
}

void addListSimbolo(Tk *sb, int id) {
    static int scont = 0;
    scont++;
    //list <Tk*> listSimbolos;
    simbolos * ss = new simbolos();
    ss->n = scont;
    ss->id = id;
    ss->nome = sb-> nome;
    ss->linha = sb-> linha;
    listSimbolos.push_back(ss);
}