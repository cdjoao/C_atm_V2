#include <stdio.h>
#include <stdlib.h>
#include<locale.h>
#include<string.h>
#include "anexos_atm.cpp"
#define MAX_USERS 3
#define MAX_MOVIMENTOS 100

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	
	
		setlocale(LC_ALL, "Portuguese");//teclado PT
		
		// *****************************Leitura do ficheiro que contem as informações dos utilizadores***************************	
	

    Users user[MAX_USERS];
    int resultado = ler_db("users.txt", user, MAX_USERS);
    if (resultado != 0) {
        return 1;
    }
    
    //*************verificar as structs inseridas. Apenas está aqui para teste. Em funcionamento normal esta secção deve estar em comentário.****

    char verificar_users;
    printf("Deseja verificar os utilizadores (y)? ");
    scanf(" %c", &verificar_users);

    if (verificar_users == 'y') {
        get_users(user,MAX_USERS); // Chama a função para imprimir os utilizadores
    }
//*****************************Fim de inserção de dados***********************************

//****************************Inicio do ATM******************************

	char user_input[10];
	int pin_input;
	int str_id;//id da struct do user
	char movimentos [20][20];




	
	int sucesso_login=0;
	for( int tentativa = 0 ; tentativa < 3 ;tentativa++){
		
		print_banner();

	print_header();	
		
		printf("\n\nPor favor insira o seu ID e o seu Pin de acesso à conta.\n");
		
		printf("\n%dº de 3 tentativas.\n",tentativa+1);
		
		
		
		printf("\n\n ID do utilizador:"); 	
		scanf("%9s",user_input);
		printf("\n Pin do utilizador:");
		scanf("%d",&pin_input);
	
		
		str_id = login_user(user,MAX_USERS,user_input,pin_input);
		
		if (str_id !=-1) {
			sucesso_login=1;
			break;			
		}
	}
	
	if (sucesso_login==0){
		printf("Limite de tentativas atingido");
		return 1;		
	}		

	char op ; // apenas é necessario um Char, poupa-se memoria
		
	op = 'Y'; // iniciar loop infinito
		
	while (op == 'Y'| op == 'y') {  //loop infinito	
	print_banner();
	print_header();	
	
	int operacao;
		
	printf("Bem vindo %s, por favor indique qual a operação que deseja realizar:\n\n", user[str_id].name);
	
	
	printf("1-Verificar dados de conta\n");
	printf("2-Transfrências bancarias\n");
	printf("3-Pagamentos\n");
	printf("4-Levantamentos\n");
	printf("5-Listar movimentos\n");
	printf("6-Alterar codigo de acesso\n");
	printf("0-Sair do programa\n");
	
	
	printf("\nInsira operação que quer realizar:", user[str_id].name);
	scanf(" %d",&operacao);
	
	
	switch (operacao){
			
			case 1:
				dados_conta(user[str_id]);
				break;
				
			case 2:
				transferencia_bancaria(&user[str_id],user,MAX_USERS);
				
				break;
				
			case 3:
				pagamentos(&user[str_id]);
				//
				break;
				
			case 4:
				levantamentos(&user[str_id]);
				//
				break;
				
			case 5:
				alterar_pin(&user[str_id]);
				break;
			case 6:
				
				alterar_pin(&user[str_id]);
				//
				break;	
				
			case 0:
				 printf("Sair do programa...");
				 return 0;
				//
				break;	
				
			default:
				printf("Não inseriu nenhuma operação válida.");
				break;			
		}
	
		printf("\n\n Deseja fazer mais alguma operação?\n");
		printf("\t Y- Continuar a fazer operações.\n");
		printf("\t Qualquer letra para sair do programa.\n");
		
		scanf (" %c", &op);	//substitur op no final para depois confirmar o status de saida do loop	
										
								
				
					
		}
	
	
	
	
	
	

		
		
		
		
	return 0;
}

