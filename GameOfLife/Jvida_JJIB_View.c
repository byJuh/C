/*Jvida_JJIB_View.c
Beatriz Lopes Rizzo, Julia Gachido Schmidt, Joao Pedro Figols Neco, Isabella Rubio Venancio*/

#include "JVida_JJIB_View.h"
#include "JVida_JJIB_Model.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

//permite ao usuario escolher a dimensao do mundo
int tamanho()
{
	int tam;
	do
	{
		printf("\nSelecione a dimensao da matriz (de 10 a 60): ");
		scanf("%d", &dimensao);
		tam = 0;
		flush_in(); 
		
		if (dimensao > MAX || dimensao < MIN)
		{
			printf("Dimensao invalida\n");
			tam = 1;
		}
	}
	while(tam != 0);
	
	return dimensao;
}

//imprime na tela o mundo (e as celulas)
void geraVida()
{
	int i, j, teste;
	if (flag == 0 && op == 5)
	{
		flag = 1;
	}
	else
	{
		flag = 0;
	}

	qtdCel = 0;
	
	printf("\n");
	printf("\t");
	for(j = 0; j < dimensao; j++)		//cabecalho
	{
		printf("%02d  ", j);
	}
	printf("\n\n");
	
	for(i = 0; i < dimensao; i++)
	{
		printf("%02d\t", i);	
		for(j = 0; j < dimensao; j++)
		{
			if (vida[i][j] == '+' && flag == 0)
			{
				char ponto = '.';
				printf("%c   ", ponto);
				
			}
			else
			{
				printf("%c   ", vida[i][j]);
			}
				
		}
			printf("\n");
	}
	
	for(i = 0; i < dimensao; i++)
	{	
		for(j = 0; j < dimensao; j++)
		{
			if (vida[i][j] == 'O')
			{
				qtdCel++;
			}
		}
	}
	
	printf("\ngeracao %d:  %d celulas vivas\n", cont, qtdCel);

	
	
}

//interface com o usuario do menu
int menuPrincipal()
{
	int op, menu;
	
	do
	{
		printf("\n");
		printf("****************JOGO DA VIDA****************\n");
		printf("|1. Apresenta o mundo                      |\n");
		printf("|2. Limpa o mundo (remove as celulas vivas)|\n");
		printf("|3. Insere/remove celulas vivas            |\n");
		printf("|4. Apresenta a lista                      |\n");
		printf("|5. Apresenta/esconde celulas mortas       |\n");
		printf("|6. Inicia processo                        |\n");
		printf("|7. Gravar geracao inicial                 |\n");
		printf("|8. Recuperar geracao inicial              |\n");
		printf("|9. Sair                                   |\n");
		printf("********************************************");
		printf("\nSelecione a opcao: ");
		scanf("%d", &op);
		menu = 0;
		flush_in();
		
		if (op < 1 || op > 9)
		{
			printf("Opcao invalida, escolha outra!!\n");
			menu = 1;
		}
	}
	while(menu != 0);
	
	return op;
}

//permite ao usuario escolher coordenada para inserir celula
void coordCelula()
{
	int  i, j, auxC, auxR;
	char carac, removeCel;
	auxR = 0;
	auxC = 0;
	
	do
	{
		//inicializando com valores fora da faixa
		coord1 = -3;
		coord2 = -3;
		printf("\nEscolha as coordenadas para inserir a celula (entre virgulas e -1,-1 para desistir): ");
		scanf("%d%c%d", &coord1, &carac, &coord2);
		flush_in();
		
		if (((coord1 >= 0 && coord1 < dimensao) && (coord2 >= 0 && coord2 < dimensao) && (carac == ',')) || (coord1 == -1 && coord2 == -1))
		{
			auxC = 1;
			
			if (coord1 == -1 && coord2 == -1)
			{
				auxC = 0;
			}
			else if (vida[coord1][coord2] == 'O')
			{
				do
				{
					printf("\nJa ha uma celula nesse local. Deseja exclui-la (S: SIM/N: NAO)? ");
					scanf("%c", &removeCel);
					flush_in();
			
					if (removeCel == 's' || removeCel == 'S') 
					{
						vida[coord1][coord2] = '.';
						removeVivo(coord1, coord2);
						geraVida();
						auxR = 0;
					}
					else if (removeCel == 'n' || removeCel == 'N')
					{
						auxR = 0;
					}
					else
					{
						printf("\nOpcao invalida\n");
						auxR = 1;
					}
				}
				while(auxR != 0);
			}
			else
			{
				vida[coord1][coord2] = 'O';
				carregaVivo(coord1, coord2);
				geraVida();	
			}
		}
		else 
		{
			printf("\nCoordenada invalida, insira outra\n");
			auxC = 1;
		}
	}
	while (auxC != 0);
	carregaMortosVizinhos();
}

//funcao que apresenta a lista das celulas vivas
void mostraListVivo()
{
	atual = pvivo;
	
	printf("\n%d celulas vivas: ", totvivo);
	
	if (totvivo > 0)
	{
		while (atual->next != NULL)
		{
			printf("%d,%d  ", atual->lin, atual->col);
			atual = atual->next;
		}
		printf("%d,%d  ", atual->lin, atual->col); //imprime a primeira celula que foi criada (ultima da lista)
	}
	printf("\n");
	
}

//apresenta a lista das celulas mortas
void mostraListMorto()
{
	atualMorto = auxMorto;
	
	printf("\n%d celulas mortas: ", totmorto);
	
	if (totmorto> 0)
	{
		while (atualMorto->next != NULL)
		{
			printf("%d,%d  ", atualMorto->lin, atualMorto->col);
			atualMorto = atualMorto->next;
		}
		printf("%d,%d  ", atualMorto->lin, atualMorto->col); //imprime a primeira celula que foi criada (ultima da lista)
	}
	printf("\n");
}

//colocar mensagem de coordenada ja utilizada
void flush_in()
{
	int ch;
	
    do 
	{
	    ch = fgetc(stdin);
    } 
	while (ch != EOF && ch != '\n');
}

//funcao de mensagens 
void mensagem(int msg)
{
	switch(msg)
	{
		case 1:
		{
			printf("Sem espaco na memoria para inclusao de celula viva\n");
			break;
		}	
		case 2:
		{
			printf("\nJogo salvo\n");
			break;
		}
		case 3:
		{
			printf("\nJogo recuperado\n");
			break;
		}	
		case 4:
		{
			printf("O arquivo CONFIG_INIC nao pode ser aberto.\n");
			break;
		}	
		case 5:
		{
			printf("\nErro na gravacao do arquivo CONFIG_INIC.\n");
			break;
		}
		case 6:
		{
			printf("\nErro na leitura do arquivo CONFIG_INIC\n");
			break;
		}
	}	
	
}

void iniciaProcesso()
{
    int qtdger, velocidade, morte1, morte2;
    int temp;
    char confirma;
    cont = 0;
    contAux = 0;
    
    do
    {
    	printf("\nQuantidade de geracoes:  ");
    	scanf("%d", &qtdger);
    	flush_in();
    
    	if (qtdger > 0)
    	{
    		morte1 = 0;
    		
    		do 
    		{
    			printf("\nVelocidade de simulacao em segundos (0 = passo-a-passo):  ");
				scanf("%d", &velocidade);
				flush_in();
				temp = velocidade;
   		
				if (temp >= 0)
				{
					morte2 = 0;
					
					printf("\nConfirme o inicio do processo (s, <n>):  ");
    				scanf("%s", &confirma);
    		
    				if (confirma == 'S' || confirma == 's')
    				{
    					cont++;
    					proxGeracao();
						carregaListas();
						geraVida();
							
    					if (temp != 0)
    					{
    						while (cont != qtdger)
							{
								Sleep(1000 * temp);
								cont++;
								proxGeracao();
								carregaListas();								
								geraVida();		
							}
							
						}
						else
						{
							while (cont != qtdger)
							{
								if (prossegue() == 1)
								{
									cont++;
									proxGeracao();
									carregaListas();
									geraVida();
								}	
							}

						}
    					
					}
				}
				else
				{
					printf ("\nVelocidade invalida. Digite outra!!\n");
					morte2 = 1;
				}
			}
			while(morte2 != 0);
    		
		}
		else
		{
			printf("\nQuantidade invalida. Digite outra!!\n");
			morte1 = 1;
		}

	} 
	while(morte1 != 0);
	
	
}

int prossegue()
{
	char resp;
    flush_in();
   
    printf("Prosseguir? (<s>, n): ");
    resp = getchar();
    
    if (resp == 'n' || resp == 'N')
    {
    	return 0;
	}
	else
	{
		return 1;
	}
    
}


