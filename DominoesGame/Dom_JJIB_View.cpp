/*Nomes: Beatriz Lopes Rizzo, Julia Gachido Schmidt, Joao Pedro Figols Neco e Isabella Rubio Venancio
Dom_JJIB_View.cpp*/

#include "Dom_JJIB_View.h"


//funcao que apresenta menu
int menuGeral()
{
	int res;
	int auxM;
	do
	{
		auxM = 0;
		printf("\n");
    	printf("************** Domino ***************");
    	printf("\n1. Iniciar Jogo (2 jogadores)\n");
    	printf("2. Iniciar Jogo (contra o computador)\n");
    	printf("3. Continuar Jogo\n");
    	printf("4. Regras do Jogo\n");
    	printf("5. Salvar o Jogo\n");
    	printf("6. Recuperar Jogo\n");
    	printf("7. Sair do Jogo\n");
    	printf("*************************************");
    	printf("\nQual opcao voce deseja usar? ");
    	scanf("%d", &res);
		flush_in();
    	
    	if (res <= 0 || res > 7)
    	{
    		printf("\n");
        	printf("Opcao invalida, escolha outra\n");
		}
   	 	else
   		{
   			printf("Opcao selecionada: %d\n\n", res);
			auxM = 1;
		}
	}
	while (auxM != 1);
	
	return res;	
}	

//funcao que apresenta a peca de cada jogador distribuida
void apresentaPecas()
{
    int i;
	int n = 1;
	naux = 0;
	
	printf("Jogador %c Pecas:", jogador);
    for (i = 0; i < 28; i++)
    {
        if (peca[i].status == jogador)
        {
            printf("%d.[%d|%d]\t      ", n, peca[i].lado1, peca[i].lado2);
            n++;
        }
    }
    naux = n-1;
    printf("\n");
}

//funcao que apresenta as pecas e a mesa
void apresentaMesa()
{
	printf("==============\n");
	printf("MESA: ");
	for (int i = 0; i < qtdMesa; i++)
	{
		printf("[%d|%d]", mesa[i].lado1, mesa[i].lado2);
		mesaE = mesa[0].lado1;
		mesaD = mesa[i].lado2;
	}
	printf("\n");
	printf("==============\n\n");
		
}

//funcao que apresenta o menu do jogador (sub-menu)
int menuJogador()
{
	int esc; 
	int auxJ;
	
	do
	{
		auxJ = 0;
		printf("\n*********Menu Jogador**********");
    	printf("\n1 - Jogar (Possiveis: %d ou %d)\n", mesaE, mesaD);
    	printf("2 - Comprar\n");
    	printf("3 - Passar\n");
    	printf("4 - Sair(interromper o jogo)\n");
    	printf("*******************************\n");
   		printf("Selecione uma opcao:  ");
    	scanf("%d", &esc);
    	flush_in();
    	printf("\n");

		if (esc > 4 || esc < 1)
    	{
       		printf("Opcao invalida, escolha outra\n\n"); 
    		apresentaMesa();
    		apresentaPecas();
    	}
    	else
    	{
      		printf("Opcao: %d\n\n", esc);
      		auxJ = 1;
		}
	}
	while (auxJ != 1);
    
    return esc;
    	
}

//funcao que pergunta ao jogador qual peca ele deseja escolher
int escolherPeca()
{
	int op;
	int auxP;
		
	do
	{
		auxP = 1;
		printf("Escolha a peca para jogar (0 para desistir):  ");
		scanf("%d", &op);
		flush_in();
		printf("\n");
		
		if ((op < 0 || op > naux) && (naux != 0)) 
		{
			printf("Essa peca nao existe, escolha outra!!\n\n");
			auxP = 0;
		}
	}
	while (auxP == 0);
	
	return op;
}

//funcao que permite ao usuario escolher qual lado da mesa deseja jogar (direito ou esquerdo)
char escolhaLadoMesa()
{
	char lado;
	int auxM;
	
	do
	{
		auxM = 0;
		printf("Escolha do lado da mesa: Esquerda/Direita (E/D) ");
		scanf("%c", &lado);
		flush_in();
		
		
		if ((lado == 'E') || (lado == 'e') || (lado == 'D') || (lado == 'd'))
		{
			auxM = 1;
			return lado;	
		}
	
		else
		{
			printf("Digite um lado valido\n\n");
		}
	}
	while (auxM != 1);	
}

//funcao com switch de mensagens
void mensagem (int msg)
{
    switch (msg)
    {
        case 1: //Indicacao de primeiro lance
            {
            	printf("O primeiro lance foi do jogador %c\n\n", jogador);
            	break;
            }
        case 2: //Indicacao de que peca nao encaixa na mesa
            {
            	printf("Erro: peca incompativel. Escolha outra!!\n\n");
        		apresentaMesa();
            	apresentaPecas();
            	break;
            }
        case 3: //Indicacao de que nao existem mais pecas no monte para comprar
            {
            	printf("Nao ha mais pecas para serem compradas!!\n\n");
            	break;
            }
        case 4: //O jogador em questao nao pode passar, apenas comprar
            {
            	printf("Voce nao pode passar a vez. Ainda ha pecas para comprar!!\n\n");
            	break;    
            }
        case 5: //Venceu com louvor
            {
            	printf("Parabens Jogador 1!! Voce venceu com louvor!!\n\n");
            	break;
            }
        case 6: //Venceu com louvor
            {
            	printf("Parabens Jogador 2!! Voce venceu com louvor!!\n\n");
            	break;
            }
        case 7: //Venceu na comparacao
            {
            	printf("Parabens Jogador 1!! Voce venceu!!\n\n");
            	break;
            }
        case 8: //Venceu na comparacao
            {
            	printf("Parabens Jogador 2!! Voce venceu!!\n\n");
            	break;
            }
        case 9: //O jogador nao pode passar a vez
            {
            	printf("Voce nao pode passar a vez, ainda ha pecas jogaveis!!!\n\n");
            	break;
            }
		case 11:
			{
				printf("O arquivo dominoPeca nao pode ser aberto para gravacao\n");
				break;
			}
		case 12:
			{
				printf("O arquivo dominoMesa nao pode ser aberto para gravacao\n");
				break;
			}
		case 13:
			{
				printf("Erro na gravacao do arquivo dominoPeca\n");
				break;
			}
		case 14:
			{
				printf("Erro na gravacao do arquivo dominoMesa\n");
				break;
			}
		case 15:
			{
				printf("O arquivo dominoVariaveis nao pode ser aberto para gravacao\n");
				break;
			}
		case 16:
			{
				printf("Erro na gravacao do arquivo dominoVariaveis\n");
				break;
			}
		case 17:
			{
				printf("O arquivo dominoPeca nao pode ser aberto para leitura\n");
				break;
			}
		case 18:
			{
				printf("O arquivo dominoMesa nao pode ser aberto para leitura\n");
				break;
			}
		case 19:
			{
				printf("O arquivo dominoVariaveis nao pode ser aberto para leitura\n");
				break;
			}
		case 20:
			{
				printf("Erro na leitura do arquivo dominoPeca\n");
				break;
			}
		case 21:
			{
				printf("Erro na leitura do arquivo dominoMesa\n");
				break;
			}
		case 22:
			{
				printf("Erro na leitura do arquivo dominoVariaveis\n");
				break;
			}
		case 23:
			{
				printf("Seu jogo foi salvo!!!\n");
				break;
			}
		case 24:
			{
				printf("Seu jogo foi recuperado!!!\n");
				break;
			}
	}
}

void flush_in()
{
    
	int ch;
    do 
	{
	    ch = fgetc(stdin);
    } 
	while (ch != EOF && ch != '\n');
    
}

void regrasJogo()
{
	printf("**********************************************************REGRAS DO JOGO******************************************************\n");
	printf("*   1. Escolha se querer jogar contra o computador ou contra outro jogador                                                   *\n");
	printf("*   2. Cada jogador recebe 7 pecas                                                                                           *\n");
	printf("*   3. Quem tiver a maior peca inicia o jogo                                                                                 *\n");
	printf("*   4. Caso jogue a sua ultima peca, compre ate que nao haja mais                                                            *\n");
	printf("*   5. Vence quem jogar a sua ultima peca ou se a mesa fechar, com o bolo vazio, vence quem tiver menos pecas ou soma menor  *\n");
	printf("******************************************************************************************************************************\n");
	
}
