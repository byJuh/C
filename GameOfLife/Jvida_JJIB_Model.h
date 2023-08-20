/*JVida_Model.h
Beatriz Lopes Rizzo, Julia Gachido Schmidt, Joao Pedro Figols Neco, Isabella Rubio Venancio*/

#define MAX 60
#define MIN 10
int dimensao; //dimensao da matriz
int qtdCel; //quantidade de celulas vivas 
char vida[MAX][MAX]; //Matriz principal

typedef struct cel //estrutura da lista
{
	int lin, col;		//linha e coluna
	struct cel *next;	//proximo da lista
}tipoCel;				

tipoCel *pvivo;		//primeira celula viva da lista
tipoCel *pmorto;
tipoCel *pgeracao;	
tipoCel *atualMorto; //valor do elemento atual da lista (morto)
tipoCel *anteriorMorto; //valor do elemento anterior da lista (morto)
tipoCel *atual;		//valor do elemento atual da lista (vivo)
tipoCel *anterior; //valor do elemento anterior da lista (vivo)	
tipoCel *auxMorto; //salva valor da funcao malloc (primeiro elemento da lista)
tipoCel *auxGeracao;
int totvivo, totmorto, totgeracao;		//total das celulas vivas e mortas em suas respectivas listas
int flag; //indica se eh para mostrar + no mapa
int coord1, coord2; //linha e coluna de cada celula
tipoCel LConfig[100];
int auxTotvivo;
int op, cont, contAux, qtdger;



