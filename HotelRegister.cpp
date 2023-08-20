/* Beatriz Lopes Rizzo, Isabella Rubio Venancio e Julia Gachido Schmidt
EXP_Hotel */

#include<stdio.h>
//prototipo das funcoes
void fReserva (struct sthot H[20][14]);
int fMapa (int andar, int apto, struct sthot H[20][14]);
void fCheckIn (struct sthot H[20][14]);
void fCheckOut (struct sthot H[20][14]);
void fCancelarReserva (struct sthot H[20][14]);
void fTaxaOcupacaoReserva (int andar, int apto, struct sthot H[20][14]);
void fHospede (struct sthot H[20][14]);
void fclear();

struct sthot	//estrutura de informacoes do hospede
{
	char cpf[13];
	char nome[40];
	char cel[12];
	char end[40];
	char email[40];
	char status;
};

main()
{ 
	int op, i, j;
	struct sthot Hotel[20][14];

	for(i = 19; i >= 0; i--)
		{
		for(j = 0; j <= 13; j++)
			Hotel[i][j].status = '.';
		}
				
	do
	{	
		printf("\n");
		printf("  =======================MENU========================\n");
		printf("  |                                                 |\n");
		printf("  | (1) - Check-in de hospede                       |\n");
		printf("  | (2) - Check-out de hospede                      |\n");
		printf("  | (3) - Reservar apartamento                      |\n");
		printf("  | (4) - Cancelar reserva                          |\n");                     
		printf("  | (5) - Mapa de ocupacao e reservas do hotel      |\n");
		printf("  | (6) - Informacoes do hospede                    |\n");
		printf("  | (7) - Taxa de ocupacao e reservas do hotel      |\n");
		printf("  | (8) - Sair do menu                              |\n");
		printf("  |                                                 |\n");
		printf("  ==============Grand Budapest Hotel=================\n");
		printf("\nEscolha a opcao desejada (1 a 8):  ");
		scanf("%d", &op);
			
		if(op<1 || op>8)
		{
			printf("\nOpcao invalida, selecione outra\n\n");
			continue;
		}
		
		if(op==8)
			break;
			
		switch(op)
		{
			case 1:
				{
					fCheckIn(Hotel);
					break;
				}
			case 2:
				{
					fCheckOut(Hotel);
					break;
				}
			case 3:
				{
					fReserva(Hotel);
					break;
				}
			case 4:
				{
					fCancelarReserva(Hotel);
					break;
				}
			case 5:
				{
					fMapa (i, j, Hotel);
					break;
				}
			case 6: //informacoes do hospede
				{
					fHospede(Hotel);
					break;
				}
			case 7: 
				{
					fTaxaOcupacaoReserva (i, j, Hotel);
					break;
				}
				
			case 8: //sai do programa
				{
					break;
				}				
		}
			
	} while(op!=8);
		
	
}
//funcao que mostra mapa
int fMapa (int andar, int apto, struct sthot H[20][14])
{
	
	int i, j; // i = andar  j = apartamento
	
	printf("\n");
	printf("Apto ->\t");
	printf("\t");
		
	for(j = 1; j <=14; j++) //cria apartamentos, de 1 a 14
		{
		printf("%2d ", j);
		}
	printf("\n\n");
	
	for(i = 19; i >= 0; i--) //cria andares de 20 a 1
		{
		printf("Andar %2d\t", i+1);
		
		for(j = 0; j <=13; j++) 
			printf(" %c ", H[i][j].status);
		printf("\n");
		}	
}
//funcao que faz reserva do hospede, mostrando R no mapa
void fReserva (struct sthot H[20][14]) 
{
	int i, j;
	
	printf("\nDigite o andar e o apartamento que deseja reservar (entre espaco):  ");
	scanf("%d %d", &i, &j);
	
	if (j>14 || j<1 || i>20 || i< 1)
		printf("Apartamento/andar invalido\n\n");
		
	else
	{
		if (H[i-1][j-1].status != '.')
		{
			if (H[i-1][j-1].status == 'R')
				printf("\nApartamento ja reservado\n\n");
			if (H[i-1][j-1].status == 'O')
				printf("\nApartamento ocupado\n\n");
		}
		else
		{
			printf("\nReserva efetuada\n\n");
			H[i-1][j-1].status = 'R';
		}
	}
	
		
}
//funcao que faz check-in do hospede, mostrando O no mapa
void fCheckIn (struct sthot H[20][14])
{
	int i, j;
	
	do
	{
	printf("\nDigite o andar e o apartamento que deseja fazer Check-in (entre espaco):  ");
	scanf("%d %d", &i, &j);
	
	if (j>14 || j<1 || i>20 || i< 1)
		{
		printf("Apartamento/andar invalido\n\n");
		continue;
		}
		
	else
		{
			if (H[i-1][j-1].status == 'O')
				printf("\nApartamento ocupado\n\n");
			else
			{
				fclear();
				printf("\nNome: ");
				gets(H[i][j].nome);		//recebe o que vai ser digitado, colocando o /0 no final (string)
	
				printf("\nCPF: ");
				gets(H[i][j].cpf);		//inclui /n no final da digitacao

				printf("\nCelular: ");
				gets(H[i][j].cel);

				printf("\ne-mail: ");
				gets(H[i][j].email);

				printf("\nEndereco: ");
				gets(H[i][j].end);
				
				printf("\nCheck-in efetuado\n");
				H[i-1][j-1].status = 'O';
					
				
				break;
			}
		}
	} 
	while (j<14 && j>1 && i<20 && i> 1);
}
//funcao que faz check-out do hospede, retirando O anteriormente colocado e deixando o apto livre
void fCheckOut (struct sthot H[20][14])
{
	int i, j;
	
	printf("\nDigite o andar e o apartamento que deseja fazer Check-out(entre espaco):  ");
	scanf("%d %d", &i, &j);
	
	if (j>14 || j<1 || i>20 || i< 1)
		printf("Apartamento/andar invalido\n\n");
	else
	{
		if (H[i-1][j-1].status == 'O')
		{
			H[i-1][j-1].status = '.';
			printf("\nCheck-out efetuado\n\n");
		}
		else
		{
			if(H[i-1][j-1].status == 'R')
				printf("\nApartamento reservado, impossibilidade de fazer Check-Out\n\n");
			if(H[i-1][j-1].status == '.')
				printf("\nApartamento livre, impossibilidade de fazer Check-Out\n\n");
		}	
			
	}
	
}
//funcao que cancela reserva e retira R do apartamento, deixando-o livre no mapa(.)
void fCancelarReserva (struct sthot H[20][14])
{
	
		int i, j;
	
	printf("\nDigite o andar e o apartamento que deseja cancelar sua reserva(entre espaco):  ");
	scanf("%d %d", &i, &j);

	if (j>14 || j<1 || i>20 || i< 1)
		printf("Apartamento/andar invalido\n\n");
	else
	{
		if (H[i-1][j-1].status == 'R')
		{
			printf("\nCancelamento de reserva efetuado\n\n");
			H[i-1][j-1].status = '.';
		}
		else
		{
			if(H[i-1][j-1].status == 'O')
				printf("\nApartamento ocupado, impossibilidade de cancelar reserva\n\n");
			if(H[i-1][j-1].status == '.')
				printf("\nApartamento livre, impossibilidade de cancelar reserva\n\n");
		}
			
	}

}
//calcula taxa de ocupacao e reserva do hotel, levando em consideracao o numero total de apartamentos
void fTaxaOcupacaoReserva(int andar, int apto, struct sthot H[20][14])
{
	int contR, contO, i, j;
	float taxO, taxR;
	
	contR=0;
	contO=0;

	for(i = 19; i >= 0; i--)
		{
		for(j = 0; j <= 13; j++)
			{
			if (H[i][j].status == 'R')
				contR = contR + 1;
			if(H[i][j].status == 'O')
				contO = contO + 1;
		 	}	
		}
	
	taxO = (contO * 100.0)/(20*14);
	taxR = (contR * 100.0)/(20*14);
	
	printf("Taxa de ocupacao: %5.2f%%\n", taxO);
	printf("Taxa de reservas: %5.2f%%\n\n", taxR);
	                         
}
//para limpeza do buffer do teclado
void fclear()
{
	char carac;
	while((carac = fgetc(stdin)) != EOF && carac != '\n'){}
}
//funcao que mostra as informacoes do hospede, as quais foram inseridas no check-in
void fHospede (struct sthot H[20][14])
{
	int i, j;
	
	printf("\nDigite o andar e o apartamento que deseja ver a informacao do hospede(entre espaco):  ");
	scanf("%d %d", &i, &j);
	
	if (j>14 || j<1 || i>20 || i< 1)
		printf("Apartamento/andar invalido\n\n");
		
	else
	{
		if (H[i-1][j-1].status != 'O')
			printf("\nApartamento vazio\n\n");
		else
		{
			printf("\n---------------Informacoes do Hospede------------------");
			printf("\nNome: %s\t\t", H[i][j].nome);	
			printf("\nCPF: %s", H[i][j].cpf);
			printf("\nCelular: %s", H[i][j].cel);
			printf("\nE-mail: %s", H[i][j].email);
			printf("\nEndereco: %s", H[i][j].end);
			printf("\n-------------------------------------------------------\n\n");
		}
	}
	
}

