#include<iostream>
#include<stdio.h> 
#include<stdlib.h>
#include<string.h> 
#include<list> 
#include "scan.h"
using namespace std;

//extern Tk*getTokens(char*nome);
Tk* tokens;
list<simbolos*> listSimbolos;
list<char*> pReservadas;
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
void ShowError(int linha, char* msg);
int buscaId(char* nome);
int buscaSimbolo(char* nome);
Tk* lexaId(Tk* ptr);
void addListSimbolo(Tk* sb, int id);
void exibListSimbolo();
int buscaPalReser(char* nome);

/*********************************
* Nome: main
* desc:
* returno:
********************************/
int main(int argc, char* argv[]) {
  char arq[50];
  char* var;

  if (argc != 2) {
    printf("Digite o nome do arquivo: ");
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
  int i;
  char* str;
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
  //list<Tk*> pReservadas;
  //pReservadas
  for (i = 0; i<32; i++) {
    str = (char* ) malloc(sizeof(char)* strlen(words[i]));
    strcpy(str, words[i]);
    pReservadas.push_back(str);
  }
}

void analiseLexica() {
  Tk* ptr;
  int aux = 0, lx;

  for (ptr = listTokens; ptr != NULL; ptr = ptr -> prox) {
    
    if (ptr -> linha != aux) {      
      aux = ptr -> linha;
    }

    lx = buscaId(ptr -> nome);

    if (lx) {
      printf("Entrou %s\n", ptr -> nome);
      ptr = lexaId(ptr -> prox);
    } else if (buscaPalReser(ptr -> nome)) {      
      if (!strcmp(ptr -> nome, "if") || !strcmp(ptr -> nome, "for") || !strcmp(ptr -> nome, "while")){
        if (strcmp(ptr -> prox -> nome, "(")) {
          ShowError(aux, "Caracter \"(\" esperado!");
        }
      }
      else if (!strcmp(ptr -> nome, "else")) {
        if (strcmp(ptr -> prox -> nome, "{")) {
          ShowError(aux, "Caracter \"{\" esperado!");
        }
      }

      aux++;
    }
  }
}

Tk* lexaCase(Tk* ptr) {

}

void ShowError(int linha, char* msg){
  printf("Erro linha %d: %s", linha, msg);
  exit(1);
}

Tk* lexaId(Tk* ptr) {
  int ehAtribuicao = 0;

  for (;;) {
    if (buscaSimbolo(ptr -> nome)) {
      printf("Erro linha %d: A variavel: \"%s\" ja foi declarada! \n", ptr -> linha, ptr -> nome);
      exit(1);
    }

    if (!isalpha(ptr -> nome[0])) {
      printf("Erro linha %d: A variavel: \"%s\" esperado um identificador! \n", ptr -> linha, ptr -> nome);
      exit(1);
    }

    addListSimbolo(ptr, 1);
    ptr = ptr -> prox;

    if (ptr -> nome[0] == ';') {
      exibListSimbolo();
      return ptr;
    } else if (ptr -> nome[0] == ',') {
      // if (ehAtribuicao) {
      //   ShowError(ptr -> linha, "Caracter \",\" invalido. Esperado operador ou \";\"");
      // }
      ptr = ptr -> prox;
    } else {
      printf("Erro linha: %d, caractere: %s invalido. Esperado uma , ou ; \n", ptr -> linha, ptr -> nome);
      exit(1);
    }

    // if (ptr -> nome[0] == '=') {
    //   ehAtribuicao = 1;
    //   ptr = ptr -> prox;
    // }
  }
}

int buscaSimbolo(char* nome) {
  list<simbolos*> ::iterator it;

  for (it = listSimbolos.begin(); it != listSimbolos.end(); it++) {
    if (strcmp(nome, (* it) -> nome) == 0) {
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
    printf("[ %s, %s , %d ]\n", (* it) -> nome, tip[(* it) -> id], (* it) -> n);
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

  Tk* l;
  //Palavras reservadas
  for (int i = 0; i<6; i++) {
    l = (Tk* ) malloc(sizeof(Tk));
    l -> nome = (char* ) malloc(sizeof(char)* strlen(nome[5]));
    strcpy(l -> nome, nome[i]);
    l -> id = contId;
    contId++;
    listId.push_back(l);
    //pReservadas
  }
}

int buscaId(char* nome) {
  //list<Tk*> listId;
  list<Tk*> ::iterator it;
  int i = 1;

  for (it = listId.begin(); it != listId.end(); it++, i++) {
    if (strcmp(nome, (* it) -> nome) == 0) {
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
  //Palavras reservadas
  for (int i = 0; i<6; i++) {
    l = (Tk* ) malloc(sizeof(Tk));
    l -> nome = (char* ) malloc(sizeof(char)* strlen(nome[5]));
    strcpy(l -> nome, nome[i]);
    l -> id = contId;
    contId++;
    pReservadas.push_back(l -> nome);
  }
}

void addListSimbolo(Tk* sb, int id) {
  static int scont = 0;
  scont++;
  //list<Tk*> listSimbolos;
  simbolos* ss = new simbolos();
  ss -> n = scont;
  ss -> id = id;
  ss -> nome = sb -> nome;
  ss -> linha = sb -> linha;
  listSimbolos.push_back(ss);
}

int buscaPalReser(char* nome) {
  //list<Tk*> listId;
  list<char*> ::iterator it;
  int i = 1;

  for (it = pReservadas.begin(); it != pReservadas.end(); it++, i++) {
    if (strcmp(nome,* it) == 0) {
      return i;
    }
  }

  return 0;
}
