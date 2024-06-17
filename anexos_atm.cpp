#include <stdio.h>
#include <stdlib.h>
#include<locale.h>
#include<string.h>
#define MAX_USERS 3
#define MAX_MOVIMENTOS 100



typedef struct {
    char tipo[20]; // Type of movement: "Transferência" or other types
    double valor; // Amount of money moved
    char data[20]; // Date of the movement
    char detalhe[50]; // Additional details about the movement
} Movimentos;

typedef struct // modelo de struct para cada utilizador
{
    char  id[10];
    char  name[50]; //nome do user
    int   pin; // pin do user
    char  iban[22]; //iban do user
    char  swift[11]; // swift do user
    double dosh;//balanço da conta
	Movimentos movimento[MAX_MOVIMENTOS];
	int num_movimentos; 
} Users;







int ler_db(const char *nomeArquivo, Users user[], int max_users) {
    FILE *file = fopen(nomeArquivo, "r"); // Abre o arquivo para leitura
    if (file == NULL) {
        printf("Erro ao abrir o ficheiro de utilizadores.\n");
        return 1;
    }

    int read = 0;
    int registo = 0;

    do {
        read = fscanf(file,
                      "%11[^,],%49[^,],%i,%23[^,],%11[^,],%lf\n",
                      user[registo].id,
                      user[registo].name, 
                      &user[registo].pin,
                      user[registo].iban,
                      user[registo].swift, 
                      &user[registo].dosh);
        if (read == 6) {
            registo++;
        }

        if (read != 6 && !feof(file)) {
            printf("Formato do ficheiro incorreto.\n");
            fclose(file);
            return 1;
        }

        if (ferror(file)) {
            printf("Erro ao ler o ficheiro.\n");
            fclose(file);
            return 1;
        }

        if (registo >= max_users) {
            printf("Número máximo de utilizadores atingido.\n");
            break;
        }

    } while (!feof(file));

    fclose(file);

    printf("\n%d registos lidos.\n\n", registo);
    
    system("pause");

    return 0;
}


void get_users(const Users user[], int num_users) {
	for (int i = 0 ;i < num_users; i++){		
		printf("Utilizador %d:\n", i + 1);
        printf("ID: %s\n", user[i].id);
        printf("Nome: %s\n", user[i].name);
        printf("PIN: %d\n", user[i].pin);
        printf("IBAN: %s\n", user[i].iban);
        printf("SWIFT: %s\n", user[i].swift);
        printf("Dosh: %.2lf\n\n", user[i].dosh);
		printf("Movimentos registados: %d\n\n", user[i].num_movimentos);		
	}
	
		system("pause");
}	
	

//função do banner do atm

void print_banner(){

system("cls");
printf("\n\n"); 	
printf("\t  /$$$$$$  /$$$$$$$$ /$$      /$$ \n");
printf("\t /$$__  $$|__  $$__/| $$$    /$$$ \n");
printf("\t| $$  \\ $$   | $$   | $$$$  /$$$$ \n");
printf("\t| $$$$$$$$   | $$   | $$ $$/$$ $$ \n");
printf("\t| $$__  $$   | $$   | $$  $$$| $$ \n");
printf("\t| $$  | $$   | $$   | $$\\  $ | $$ \n");
printf("\t| $$  | $$   | $$   | $$ \\/  | $$ \n");
printf("\t|__/  |__/   |__/   |__/     |__/ \n\n\n");
}



void print_header(){
	printf("\n|- - - - - - - - - - - - - - - - - - - - - - -|\n");
	}


int login_user(const Users user [],int num_users, char *id_input, int pin_input ){
			
		int i; 
		for (i = 0; i < num_users; i++) {
		       if (strcmp(user[i].id, id_input) == 0 && user[i].pin == pin_input) {
		          // utilizador encontrado
		        printf("\n\nUtilizador %s autenticado.\n", user[i].name);
		          return i;
				 }        
		        	    	          
		} 
		if( i == num_users){
		
		printf("\n\nID ou PIN incorreto.\n\n");
	    return -1; // Indicate that the user was not found
		}
	}
	


void registar_movimento(char mov){	
	
	
}

void dados_conta(const Users user){
	
	system("cls");
		
	printf("\n---Verificação de Dados da conta---\n\n ");
	
	printf("Nome: %s\n", user.name);       
    printf("IBAN: %s\n", user.iban);
    printf("SWIFT: %s\n", user.swift);
    printf("Balanço: %.2lf$\n\n", user.dosh);
        
    system("pause");
}



void transferencia_bancaria( Users *user, Users user_alvo[], int num_users){
	
	char iban_alvo[45];
	double valor_transferir;
	
	system("cls");		
	printf("\n---Transferência Bancaria---\n\n ");
	
	printf("Por favor insira o iban da conta que irá receber a transferência:");	
	scanf(" %s",iban_alvo);
	printf("Valor a transferir: ");
	scanf("%lf",&valor_transferir);	
	
	if(user->dosh < valor_transferir) {
		printf("Montante superior ao seu saldo");	
		return;	
		}	
	
	for (int i = 0; i < num_users; i++) {
	       if (strcmp(user_alvo[i].iban, iban_alvo) == 0 ) {
	          // utilizador encontrado
	       	user->dosh -= valor_transferir;
			user_alvo[i].dosh += valor_transferir;
			printf("\n\nTransferência realizada com sucesso para %s.\n", user_alvo[i].name);
			
			return;     	       
		        	    	          
		} 
		 if(i==num_users){		 		
		printf("\n\n Iban inválido .\n\n");
	      }
		}
	}
	
void pagamentos(Users *user){
	double valor_transferir;
	int pagamento_menu, num_tlm, entidade, referencia;
	
	system("cls");		
	printf("\n---Pagamentos---\n\n ");
	
	printf("Por favor selecione o tipo de pagamento que quer realizar\n\n");
	printf("1-Carregamento de telemovel\n");
	printf("2-Pagamento por referência\n\n");
	printf("3-Retornar ao menu principal\n\n");
	printf("Operação: ");
	scanf("%d", &pagamento_menu);
	
	
	switch (pagamento_menu){
		
		case 1://carregamento tlm
			printf("\n---Carregamento telemovel---\n\n ");
			
			printf("Por favor insira o nº de telemovel para efectuar o carregamento e o montante a carregar:\n ");
			printf("Numero telemovel:\n ");
			scanf("%d",&num_tlm);
			printf("\nMontante a transferir:");
			scanf("%lf",&valor_transferir);
			
			if(user->dosh < valor_transferir) {
				printf("Montante superior ao seu saldo");	
				return;	
			}
			
			user->dosh -= valor_transferir;	
			printf("Carregamento de %lf a %d effectuado com sucesso",valor_transferir,num_tlm);
			system("pause");			
						
			break;
			
		case 2:// pagamento referencia
		printf("\n---Pagamento por refência---\n\n ");		
			
			printf("Por favor insira a entidade, a referência e o montante:\n ");
			printf("Entidade:\n ");
			scanf("%d",&entidade);
			printf("\nReferência:");
			scanf("%d",&referencia);
			printf("\nMontante:");
			scanf("%lf",&valor_transferir);
			
			if(user->dosh < valor_transferir) {
				printf("Montante superior ao seu saldo");	
				return;	
			}
			
			user->dosh -= valor_transferir;	
			printf("Pagamento de  %lf $ effectuado com sucesso",valor_transferir);
			system("pause");			
		
			break;
			
		case 3:
			break;
		
		default:
			printf("Operador inválido....Retornar ao menu principal\n");
			system("pause")	;		
			break;	
					
	}
		
}
	
	
void levantamentos(Users *user)	{
	system("cls");	
	printf("\n---Levantamento---\n\n ");
		
	int escolha_levantamento;
	double valor_especifico;
	
	printf("Por favor selecione a quantia que quer levantar:\n");
	
	printf("1-10$    4-100$\n");
	printf("2-20$    5-200$\n");	
	printf("3-50$    6-Outro valor \n\n");
	printf("0-Menu anterior \n");
	
	
	scanf("%d",&escolha_levantamento);
	system("cls");
	printf("\n---Levantamento---\n\n ");	
	
	switch(escolha_levantamento){
		
		case 1:
			if(user->dosh < 10) {
				printf("Montante superior ao seu saldo");	
				return;	
			}
			user->dosh -= 10;	
			printf("Levantamento de 10$ effectuado com sucesso\n");
			break;
		case 2:
			if(user->dosh < 20) {
				printf("Montante superior ao seu saldo");	
				return;	
			}
			user->dosh -= 20;	
			printf("Levantamento de 20$ effectuado com sucesso\n");
			break;
		case 3:
			if(user->dosh < 50) {
				printf("Montante superior ao seu saldo");	
				return;	
			}
			user->dosh -= 50;	
			printf("Levantamento de 50$ effectuado com sucesso\n");
			break;
		case 4:
			if(user->dosh < 100) {
				printf("Montante superior ao seu saldo");	
				return;	
			}
			user->dosh -= 100;	
			printf("Levantamento de 100$ effectuado com sucesso\n");
			break;
		case 5:
			if(user->dosh < 200) {
				printf("Montante superior ao seu saldo");	
				return;	
			}
			user->dosh -= 200;	
			printf("Levantamento de 200$ effectuado com sucesso\n");
			break;
		case 6:
			printf("Indique o montante que deseja levantar. Este atm distribui notas e moedas.\n");
			printf("Quantia:");
			scanf("%lf",&valor_especifico);
			if(user->dosh < valor_especifico) {
				printf("Montante superior ao seu saldo");	
				return;	
			}
			user->dosh -= valor_especifico;	
			printf("Levantamento de %lf effectuado com sucesso\n",valor_especifico);
			break;
		case 0:
			break;
		default:
			printf("Digitou um caracter inválido. Retornar ao menu aterior...\n");
			break;	
	}
	
}


void alterar_pin(Users *user){
	
	system("cls");	
	printf("\n---Alteração de pin---\n\n ");
	
	int pin_check;
	int pin_novo;
	
	printf("Insira o seu pin atual:");
	scanf("%d",&pin_check);
	
	if (user->pin==pin_check){
			printf("Insira o novo pin (4 digitos):");
			scanf("%d",&pin_novo);
			user->pin = pin_novo;
			
			printf("\nPin alterado com sucesso\n");
	
	} else {
		printf("\nPin incorreto. Retornar ao menu anterior...\n");
	}
		
}

listar_movimentos(){
	
	
}
	
	
	       
    
        
 

	  	
		










