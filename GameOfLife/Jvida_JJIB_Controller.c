/*Jvida_JJIB_Controller.h
Beatriz Lopes Rizzo, Julia Gachido Schmidt, Joao Pedro Figols Neco, Isabella Rubio Venancio*/

#include "JVida_JJIB_Model.h"
#include "JVida_JJIB_View.h"
#include <stdlib.h>
#include <stdio.h>

//funcao que gera a matriz do mundo
void geraMatriz()
{
	int i, j;
	for (i = 0; i < MAX; i++)
	{
		for (j = 0; j < MAX; j++)
		{
			vida[i][j] = '.';
		}
	}
}

//funcao que contem a logica do menu principal
void inicializaMenu()
{
	flag = 0;
	
	do
	{
		op = menuPrincipal();
		
		switch (op)
		{
			case 1:  //apresentar o mundo
			{
				geraVida();
				break;	
			}
			case 2:	 //limpar o mundo
			{
				geraMatriz();
				geraVida();
				limpaListaMorto();
				limpaListaVivo();	
				break;
			}
			case 3:  //criar celulas vivas
			{
				geraVida();
				coordCelula();
				break;	
			}
			case 4: //apresenta lista
			{
				mostraListVivo();
				mostraListMorto();
				break;
			}
			case 5:	//apresenta/remove celulas mortas
			{
				geraVida();
				break;
			}
			case 6: 
			{
				iniciaProcesso();
				break;	
			}
			case 7: //grava geracao inicial
			{
				gravaCelulas();
				mensagem(2);
				break;	
			}
			case 8: //recupera geracao inicial
			{
				recuperaCelulas();
				carregaMortosVizinhos();
				mensagem(3);
				break;	
			}
		}
	}
	while (op != 9);
}

//funcao que adiciova vivo
void carregaVivo(int ii, int jj)
{
	tipoCel *aux = malloc(sizeof(tipoCel));
	if (aux == NULL)
	{
		mensagem(1);
	}
	
	aux->lin = ii;
	aux->col = jj;

	if (totvivo == 0)
	{
		pvivo = aux;
		pvivo->next = NULL;
	}
	else
	{
		aux->next = pvivo;
		pvivo = aux;
	}
	totvivo++;	
}

//funcao que remove elementos da lista
void removeVivo(int ii, int jj)
{
	atual = pvivo;
	anterior = NULL;

	if (totvivo > 0)
	{	
		if (pvivo->lin == ii && pvivo->col == jj) //remove primeiro da lista (ultima celula inserida)
		{	
			pvivo = pvivo->next;
			free(atual);
		}
		else
		{
			while (atual->lin != ii || atual->col != jj) 
			{
				anterior = atual;
				atual = atual->next;
			}
			//elemento a ser removido sempre estara na lista
			anterior->next = atual->next;
			free(atual);	
		}			
	}
	totvivo--;
}

//permite a adicao de mortos na lista
void carregaMortosVizinhos()
{	
	int i, j;
	
	//limpa lista dos mortos (apenas se houver algo na lista)
	limpaListaMorto();
	
	//retira '+' da matriz 
	for (i = 0; i < dimensao; i++)
	{
		for (j = 0; j < dimensao; j++)
		{
			if (vida[i][j] == '+')
			{
				vida[i][j] = '.';
			}
		}
	}
	
	//percorre lista das celulas vivas para achar suas mortas vizinhas
	atual = pvivo;
	
	if (totvivo > 0)
	{
		if(atual->next == NULL) //so tem uma unica celula viva
		{
			descobreCoord(atual->lin, atual->col);
		}
		else
		{
			while (atual != NULL)
			{
				descobreCoord(atual->lin, atual->col);
				atual = atual->next;
			}
		}
	}
}	

//descobre as 8 coordenadas mortas de cada celula vizinha
void descobreCoord(int lin, int col)
{
	int k, j, morto;
	for (k = lin - 1; k <= lin + 1; k++) //linhas
	{
		for (j = col - 1; j <= col + 1; j++) //colunas
		{
			if(vida[k][j] != 'O' && k < dimensao && j < dimensao && k >= 0 && j >= 0 && totmorto == 0) //primeira celula adicionada
			{
				carrega1Morto(k, j);
			}
			else
			{
				morto = verifica1Morto(k, j);
				if (vida[k][j] != 'O' && k < dimensao && j < dimensao && k >= 0 && j >= 0 && morto != 1)
        		{
            		carrega1Morto(k, j);
        		}
			}
		}	
	}
}

//verifica se a celula ja esta na lista dos mortos
int verifica1Morto(int ii, int jj)
{
	atualMorto = pmorto;
		
	if (totmorto > 0)
	{
		while (atualMorto->next != NULL && (atualMorto->lin != ii || atualMorto->col != jj))
		{
			anteriorMorto = atualMorto;
			atualMorto = atualMorto->next;
		}
		if (atualMorto->lin == ii && atualMorto->col == jj)
		{
			return 1; //a celula ja existe na lista de mortos	
		}
		else
		{
			return 0;
		}
	}
}

//adiciona uma celula morta na lista 
void carrega1Morto (int ii, int jj)
{
	//cria lista de mortos
	auxMorto = malloc(sizeof(tipoCel));
	if (auxMorto == NULL)
	{
		mensagem(1);
	}
	
	auxMorto->lin = ii;
	auxMorto->col = jj;
	
	if (totmorto == 0)
	{
		pmorto = auxMorto;
		pmorto->next = NULL;
	}
	else
	{
		auxMorto->next = pmorto;
		pmorto = auxMorto;
		
	}
	vida[pmorto->lin][pmorto->col] = '+';
	totmorto++;
}


//limpa a lista dos vivos
void limpaListaVivo()
{
	while(totvivo != 0)
	{
		atual = pvivo;
		pvivo = pvivo->next;
		free(atual);
		totvivo--;
	}
}

//limpa a lista dos mortos
void limpaListaMorto()
{
	while (totmorto != 0 )
	{
		atualMorto = pmorto;
		pmorto = pmorto->next;
		free(atualMorto);
		totmorto--;
	}
}
void limpaListaGeracao()
{
	tipoCel *aux;
	while (totgeracao != 0)
	{
		aux = pgeracao;
		pgeracao = pgeracao->next;
		free(aux);
		totgeracao--;
	}
}
//funcao que grava as celulas
void gravaCelulas()
{
	FILE*fp;
	int auxTotvivo;
	int i = 0;

	tipoCel *aux;
	aux = pvivo;
	auxTotvivo = totvivo;
	
	fp = fopen("CONFIG_INIC", "w");
	if((fp = fopen("CONFIG_INIC", "w")) == NULL)
	{
        mensagem(4);
        return;
    }
        
    while(auxTotvivo != 0)
    {
		LConfig[i] = *aux;
		if(fwrite(&LConfig[i],sizeof(tipoCel),1,fp)!=1)
        {
            mensagem(5);
            break;
        }
		aux = aux->next;
		i++;
		auxTotvivo--;
	}
	
	LConfig[i].next = NULL;
	fclose(fp);
}

//recupera as celulas
void recuperaCelulas()
{
	int i = 0;
	geraMatriz();
	limpaListaVivo();
	limpaListaMorto();

	FILE *fp;

	fp = fopen("CONFIG_INIC", "r");
	
	if((fp = fopen("CONFIG_INIC", "r")) == NULL)
    {
        mensagem(4);
        return;
    }
    
	do
    {
		if(fread(&LConfig[i],sizeof(tipoCel),1,fp)!=1)
        {
            mensagem(6);
            break;
        }
	   
	   coord1 = LConfig[i].lin;
	   coord2 = LConfig[i].col;
	   vida[coord1][coord2] = 'O';	
	   carregaVivo(coord1, coord2);	   
	}
	while(LConfig[i].next != NULL);
	
	fclose(fp);
}

void proxGeracao()
{	
	int linhaMorto, colunaMorto, contGer, auxvivo;
	int auxMorto = totmorto;
	tipoCel *auxpmorto = pmorto;
	while(auxMorto != 0 )
	{
		contGer = 0;
		atualMorto = auxpmorto;
		atual = pvivo;
		linhaMorto = atualMorto->lin;
		colunaMorto = atualMorto->col;
		auxvivo = totvivo;

		while (auxvivo != 0)
		{
			if ((linhaMorto - 1 == atual->lin ||linhaMorto + 1 == atual->lin ||linhaMorto == atual->lin) && (colunaMorto == atual->col ||colunaMorto - 1 == atual->col ||colunaMorto + 1 == atual->col))
			{
				contGer++;
			}
			atual = atual->next;
			auxvivo--;
		}
		if (contGer == 3)
		{
			carregaGeracao(linhaMorto, colunaMorto);
			vida[linhaMorto][colunaMorto] = 'O';
		}
		auxpmorto = auxpmorto->next;
		auxMorto--;
	}
	
	auxvivo = totvivo;
	int auxvivoDentro = totvivo;
	atual = pvivo;
	while (auxvivoDentro != 0)
	{
		auxvivo = totvivo;
		contGer = 0;
			
		tipoCel *aux1 = pvivo;
		tipoCel *aux2 = aux1;
		while (aux2->next != NULL)
		{
			if ((aux1->lin - 1 == atual->lin || aux1->lin + 1 == atual->lin || aux1->lin == atual->lin) && ( aux1->col == atual->col || aux1->col - 1 == atual->col ||aux1->col + 1 == atual->col ) && (aux1->lin != atual->lin || aux1->col != atual->col))
			{
				contGer++;
			}
			aux2 = aux1;
			aux1 = aux1->next;
			auxvivo--;
		}
		if (contGer < 2)
		{
			vida[atual->lin][atual->col] = '.';
		}
		else if (contGer == 2 || contGer == 3)
		{
			carregaGeracao(atual->lin, atual->col);
		}
		else 
		{
			vida[atual->lin][atual->col] = '.';
		}
			
		atual = atual->next;
		auxvivoDentro--;
	}
		
}

//carrega celulas que nasceram na lista da proxima geracao
void carregaGeracao(int ii, int jj)
{
	//cria lista de celulas que nasceram
	tipoCel *auxGeracao = malloc(sizeof(tipoCel));
	if (auxGeracao == NULL)
	{
		mensagem(1);
	}
	
	auxGeracao->lin = ii;
	auxGeracao->col = jj;
	
	if (totgeracao == 0)
	{
		pgeracao = auxGeracao;
		pgeracao->next = NULL;
	}
	else
	{
		auxGeracao->next = pgeracao;
		pgeracao = auxGeracao;
		
	}
	if (vida[ii][jj] == '.')
	{
		vida[pgeracao->lin][pgeracao->col] = '+';
	}
	
	totgeracao++;
}

void carregaListas()
{
	int linha, coluna;
	limpaListaVivo();
	carregaMortosVizinhos();
	limpaListaMorto();

	if (totgeracao != 0)
	{
		tipoCel *aux1;
		aux1 = pgeracao;
		linha = aux1->lin;
		coluna = aux1->col;

		while (totgeracao != 0)
		{
			carregaVivo(aux1->lin, aux1->col);
			aux1 = aux1->next;
			totgeracao--;
		}
	}

	carregaMortosVizinhos();
	limpaListaGeracao();
			
}
