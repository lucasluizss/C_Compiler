#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
#include "scan.h"

// variaveis globais
int linha;
int coluna, antColumn;
char look;
char token[256];
int ntoken;
Tk *TkList=NULL, *elemento=NULL;

// fun��es locais
FILE *abreArq(char *nome);
void nextChar(FILE *p);
void scan(FILE *P);
void skipWhite(FILE *p);
void newLine(FILE *p);
void getWord(FILE *p);
void getNum(FILE *p);
void getOp(FILE *p);
void skipComment(FILE *p);
void getOp(FILE *p);
int isOp(char c);
int isSpecial(char c);
void getNum(FILE *p);


/***********************************************
 * Nome: getTokens
 * desc: obt�m todos os tokens do arquivo nome
 * returno: ponteiro para a lista de tokens
 ***********************************************/
Tk *getTokens(char *nome)
{
    linha = 1;
    coluna = 0;
    ntoken = 0;

    FILE *p;
    char *str;
    p = abreArq(nome);
    nextChar(p);

    while(!feof(p))
    {
        scan(p);

        ntoken++;
        //printf("Token: %d \n", ntoken);
        str = (char*) malloc(sizeof(char)*strlen(token) + 1);
        strcpy(str, token);
        elemento = (Tk*) malloc(sizeof(Tk));
        elemento->nome = str;
        elemento->linha = linha;
        elemento->coluna = antColumn;
        elemento->id = ntoken;
        elemento->prox = NULL;
        insereTk(elemento);
        //printf("Token: %s \n", elemento->nome);
    }

    return TkList;
}

/*********************************
 * Nome: scan
 * desc:
 * returno:
 ********************************/
void scan(FILE *p)
{
    strcpy(token, "");

    if(look == ' ' || look == '\t'){
        skipWhite(p);
    }

    if(look == '\n' || look == 13){ // CR LF
        newLine(p);
    }

    if(isOp(look) || isSpecial(look)){
        antColumn = coluna;
        getOp(p);
    }
    else if((look > 64 && look < 91) || (look > 96 && look < 123)){
        antColumn = coluna;
        getWord(p);
    }
    else{
        antColumn = coluna;
        getOp(p);
    }
}

/*********************************
 * Nome: abreArq
 * desc:
 * returno:
 ********************************/
FILE *abreArq(char *nome)
{
    char *var;
    FILE *in;

    // aqui tem um exemplo do uso da fun��o strstr

    var = strstr(nome,".c");

    if(var == NULL) // O ARQUIVO N�O TEM EXTEN��O
    {
        printf("Arquivo : %s invalido!\n", nome);
        exit(1); // cada erro ser� tratado com uma sa�da diferente de 0.
    }

    in = fopen(nome,"r");

    if(in == NULL)
    {
        printf("Nao foi possivel abrir o arquivo %s \n",nome);
        exit(3);
    }

    return in;
}

/*********************************
 * Nome: insereTk
 * desc:
 * returno: void
 ********************************/
void insereTk(Tk *TkElemento)
{
    Tk *ptr;

    if(TkList == NULL){
        TkList = TkElemento;
    }

    else{
        for(ptr = TkList; ptr->prox != NULL; ptr = ptr->prox);
        ptr->prox = TkElemento;
    }

}

/*********************************
 * Nome: exibeTk
 * desc:
 * returno: void
 ********************************/
void exibeTk(Tk *TkList)
{
    int linhaAtual = 1;

    while(TkList != NULL){
        if(TkList->linha > linhaAtual){
            int diff = TkList->linha - linhaAtual  ;

            for(int i=0;i<diff;i++){
                printf("\n");
            }

            linhaAtual = TkList->linha;
        }

        printf("%s", TkList->nome);
        TkList = TkList->prox;
    }

    printf("\n\nLinhas: %d\n", linha);
}

/*********************************
 * Nome: removeTk
 * desc:
 * returno: void
 ********************************/
void liberaTk(Tk *TkList)
{
    Tk *T,*ptr;

}

/*********************************
 * Nome: buscaTk
 * desc:
 * returno: void
 ********************************/
void removeTk(Tk *TkList, int chave)
{

}

/*********************************
 * Nome: nextChar
 * desc:
 * returno:
 ********************************/
void nextChar(FILE *p)
{
    if(look != EOF) // EOF(End Of File)
    {
        look = getc(p);
        coluna++;
    }
}

/*********************************
 * Nome: removeSpace
 * desc:
 * returno:
 ********************************/
void skipWhite(FILE *p)
{
    while (look == ' ' || look == '\t'){
        nextChar(p);
    }
}

/*********************************
 * Nome: removeSpace
 * desc:
 * returno:
 ********************************/
void newLine(FILE *p)
{
    while(look == '\n' || look == 13){
        if(look == '\n'){
            linha++;
            coluna = 0;
        }

        nextChar(p);
    }
}

/*********************************
 * Nome: skipComment
 * desc:
 * returno:
 ********************************/
void skipComment(FILE *p)
{
    char ant = look;
    nextChar(p);

    if(ant == '/' && look == '/'){
      while(look != '\n'){
          nextChar(p);
      }

      linha++;
    }
}

/*********************************
 * Nome: getNum
 * desc:
 * returno:
 ********************************/
void getNum(FILE *p)
{
    int i;

}

/*********************************
 * Nome: getWord
 * desc:
 * returno:
 ********************************/
void getWord(FILE *p)
{
    int i = 0;
    char temp[255];

    while(isalnum(look) || look == '_'){ //leia_isso
        temp[i] = look;
        nextChar(p);
        i++;
    }

    token[i] = '\0';

    strcpy(token, temp);
}

/*********************************
 * Nome: getOp
 * desc:
 * returno:
 ********************************/
void getOp(FILE *p)
{
    int i;

    token[0] = look;
    token[1] = '\0';
    nextChar(p);
}

/*********************************
 * Nome: isOp
 * desc:
 * returno:
 ********************************/
int isOp(char c)
{
    return (strchr("#.+-*/<>:=!", c) != NULL); //Returns a pointer to the first occurrence of character in the C string str.
}

int isSpecial(char c)
{
    return (strchr("{}(),;[]\"", c) != NULL);
}
