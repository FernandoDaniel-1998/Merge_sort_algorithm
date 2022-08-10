#include <stdio.h>
#include <stdlib.h>

typedef struct lista { // Definindo e criando a estrutura da lista
  int info;
  struct lista* prox;
}TLista;

typedef TLista *PLista; // Criando um ponteiro para a estrutura acima

PLista insere(PLista lista, int num);
void imprime (PLista l);
void libera (PLista l);
void encontra_ini_e_meio(PLista lista, PLista* inicio, PLista* meio);
PLista ord_sublistas(PLista i, PLista ii);
void merge_sort(PLista* lista);

int main(void) {

  int valor,tamanho;
  PLista lista = NULL;

  scanf("%d",&tamanho);

  for(int i=0; i<tamanho; i++){ // Apenas lendo o conteudo dos nos
  scanf("%d",&valor);
  lista = insere(lista, valor);
  }

  merge_sort(&lista); // Dividindo e ordenando as sublistas

  imprime(lista); // Apenas imprimira os elementos da lista ja ordenados

  libera(lista); // Liberara a memoria alocada pela lista

  return 0;
}

PLista insere(PLista lista, int num){ // Essa funcao insere elementos em listas encadeadas
  PLista novo = (PLista) malloc(sizeof(TLista)); // Alocando cada elemento (no) dinamicamente
  novo -> info = num;
  novo -> prox = lista;

  return novo;
}

void imprime (PLista l){ // Funcao apenas para imprimir as informacoes da lista
  PLista pp;
  for (pp = l; pp != NULL; pp = pp->prox){
    printf("%d ", pp->info);
  }
  printf("\n");
}

void libera (PLista l){ // Funcao que liberara os elementos da lista
  
  PLista p = l, t;
  while (p != NULL){
    t = p->prox; // A variavel "t" guarda referencia para o proximo elemento
    free(p); // Libera o no alocado dinamicamente
    p = t; // Faz p apontar para o proximo 
  }
  
}

void encontra_ini_e_meio(PLista lista, PLista* inicio, PLista* meio){ // Esta funcao eh responsavel por pegar qual eh o elemento que esta no meio da lista
  PLista aux1,aux2;
  
  aux2 = lista;
  aux1 = lista->prox;
 
  while (aux1 != NULL) { // Neste laco usei o principio da lebre e da tartaruga para encontrar o meio da minha lista; ha medida que um ponteiro percorre 1 elemento, o outro percorre o dobro e, com isso quando o ponteiro  mais rapido atingir o final da lista, o mais lento estara na metade do caminho(noh que esta no meio da lista)
    
    aux1 = aux1->prox;
    
    if (aux1 != NULL) {
      aux2 = aux2->prox;
      aux1 = aux1->prox;
    }
  }

  *inicio = lista; // Nestas listas eu armazeno o inicio da lista em um ponteiro que é parametro da mesma e faco a mesma coisa para o meio da lista
  *meio = aux2->prox;
  aux2->prox = NULL;
  
}

PLista ord_sublistas(PLista i, PLista ii){
  
  PLista result = NULL;
 
  if (i == NULL) // Essas condicoes eh quando apenas sobram os ultimos elementos da cada subslista; caso sobre elementos, diretamente sao empregados na lista original
    return (ii);
  else if (ii == NULL)
    return (i);
 
  if (i->info <= ii->info) { // Aqui eh que entra a recursao para inserir os elementos na lista ja ordenada. Nesta etapa se o elemento da sublista a esquerda for menor, ele entrara na minha lista ja ordenada e depois sera atualizado na ultima linha deste "if"
    result = i;
    result->prox = ord_sublistas(i->prox, ii);
  }
  else { // Neste "else" acontece o que esta acima, contudo apenas quando o elemento da sublista a direita eh maior, em seguida sendo atualizado tambem
    result = ii;
    result->prox = ord_sublistas(i, ii->prox);
  }
  
  return (result); // Ao final de todas comparacoes, o que sera retornado eh a lista ja ordenada
}

void merge_sort(PLista* lista){
  
  PLista cabeca = *lista;
  PLista i, ii; // Esses sao ponteiros para auxiliar na "quebra" da lista

  if ((cabeca == NULL) || (cabeca->prox == NULL)) { // Condicao de parada para a recursao desta funcao
    return;
  }

  encontra_ini_e_meio(cabeca, &i, &ii); // Como ja dito, essa funcao encontrara o meio e o inicio da lista

  merge_sort(&i); // Nesta etapa a sublista "i" sera "quebrada" para apenas 1 noh
  merge_sort(&ii); // Analogo acima, mas com a sublista "ii"


  *lista = ord_sublistas(i,ii); // Nesta etapa a lista sera ordenada usando a recursao nas substrings
  
}