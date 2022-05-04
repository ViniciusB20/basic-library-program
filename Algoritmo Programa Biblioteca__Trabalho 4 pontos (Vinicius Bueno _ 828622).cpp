/* Trabalho - até 4 pontos - entregar até 20/06/2018

Nome : Vinicius De Carvalho Bueno // CODIGO : 828622 // Engenharia Computação 2°ETAPA

Elaborar um programa que contemple :

 1 - Abertura do programa com validação de usuario e senha -> OK
 2 - cadastro , alteração , listagem , e consulta de livros .
 3 - armazenar dos livros : 
 codigo (gerar automaticamente) , titulo , autores , isbn , editora , ano de publicação. -> OK
 4 - as consultas podem ocorrer por codigo , titulo do livro ou periodo de publicação (ano inicial - ano final)
 5 - listagem deve ser gerada em ordem alfabetica de titulo
 6 - gerenciar as funções por meio de um menu -> OK 
 7 - utilizar funções  -> OK 
 8 - armazenar o registro dos livros em modo binario -> OK */
 
 // Bibliotecas
 #include <iostream>
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <conio.h>
 #include <ctype.h>
 // Vetor que auxilia na ordenação
 #define MAX 300
 
 // Estruturas
 struct usuario {
	
	char nome[50];
	char senha[15];
	int perfil ;
 	
 };
 
typedef struct usuario user;
user users ;

struct livros {
	
	char titulo[30] ;
	char autores[30] ;
	char editora[30];
	int anopublicacao;
	int isbn ;
	int codigo ;
	int perfil ;
	
};

typedef struct livros livro; 
livro livros;

 
struct consulta {
	
	char titulo[30] ;
	char autores[30] ;
	char editora[30];
	int anopublicacao;
	int isbn ;
	int codigo ;
	int perfil ;
	
};

typedef struct consulta consultas; 
consultas consul;

consultas aux[MAX];
 
int tamanho , b ;

 
// Ponteiro
FILE *arquivo;


// Esquema pra dar certo
void login () ;
void cad_usuario (int chamada) ;
void cad_livros (int chamada) ;
void mostrar_livros(int chamada);
void pesquisar (consultas aux[]);
void alterar (consultas aux[]) ;
void ordenar_listar(consultas aux[]);
void printzinho (consultas aux[]);
int sequencia () ;

// Função Menu 
 void menu (int perfil) {
 	
 	int escolha ;
 	
 	system ("cls");
	printf ("\t***** MENU DE OPCOES *****");
	printf ("\n\t1 - Cadastrar novo Livro");
	printf ("\n\t2 - Cadastrar novo Usuario");
	printf ("\n\t3 - Alterar Cadastro Do Livro");
	printf ("\n\t4 - Consultar Um Livro Expecifico");
	printf ("\n\t5 - Mostrar Todos os Livros");
	printf ("\n\t6 - Mostrar Todos os Livros ordem alfabetica de titulo");
	printf ("\n\t0 - Sair Programa\n\t=>");
	scanf ("%i", &escolha);
 	
 	switch (escolha) {
 		
 		case 0 :{
 			printf ("\nPrograma foi fechado ...");
 			exit (0);
 			system ("\npause");
			break;
		 }
		 
		case 1 :{
			cad_livros(1);
			tamanho++ ;
			menu (perfil);
			break;
		} 
		
		case 2 :{
			cad_usuario(1);
			menu (perfil);
			break;
		}
		
		case 3 :{
			alterar(aux);
			menu (perfil);
			break;
		}
		
		case 4 :{
			pesquisar(aux);
			menu (perfil);
			break;
		}
		
		case 5 :{ 
			mostrar_livros(1);
			menu (perfil);
			break;
		}
		
		case 6 :{
			ordenar_listar(aux);
			menu(perfil);
			break;
		}
		
		default :{
			printf ("\nComando Invalido...");
			menu (perfil);
			break;
		}
 		
	 }
 	
 }
 
 // Função Cadastrar Usuario
void cad_usuario (int chamada) {
	
	// Abrir o arquivo para gravação
	arquivo=fopen("usuario.txt","ab");
	
	printf ("\nInforme o nome do usuario :\n");
	fflush(stdin);
	gets(users.nome);
	printf ("\nInforme a senha do usuario :\n");
	fflush(stdin);
	gets (users.senha);
	
	if (chamada==0){
		users.perfil=1;
	}
	else {
		users.perfil=1;
	}
	
	// Gravar no arquivo
	fwrite(&users,sizeof(users),1,arquivo);
	
	// Fechar o arquivo
	fclose(arquivo);
	
}

// Cadastrar Livros
void cad_livros (int chamada) {
	
	// Abrir arquivo para gravação
	arquivo=fopen("bancolivros.txt","ab");
	
	printf ("\nInforme o titulo do livro :");
	fflush (stdin);
	gets (livros.titulo);
	printf ("\nInforme o ano de publicacao :");
	scanf ("%i", &livros.anopublicacao);
	printf ("\nInforme o nome dos autores : ");
	fflush (stdin);
	gets (livros.autores);
	printf ("\nInforme o nome da editora :");
	fflush (stdin);
	gets (livros.editora);
	printf ("\nInforme o isbn do livro :");
	scanf ("%i", &livros.isbn);
	
	// Adicionar Codigo sequencial
	livros.codigo = sequencia () ;
	
	if (chamada==0){
		livros.perfil=1;
	}
	
	// Gravar no Arquivo
	fwrite(&livros,sizeof(livros),1,arquivo) ;
	
	// Fechar o arquivo
	fclose(arquivo);
	
}

// Mostrar Livros rm ordem de codigo
void mostrar_livros (int chamada) {
	
	// Abrir o arquivo para leitura 
	if ((arquivo=fopen("bancolivros.txt","r"))==NULL)
	{
		printf ("\nErro na abertura do arquivo...");
	}
	while(fread(&livros,sizeof(livros),1,arquivo))
	{
		printf ("\n\tTitulo : %s", livros.titulo);
		printf ("\n\tAutor : %s ", livros.autores);
		printf ("\n\tAno Publicacao : %i", livros.anopublicacao);
		printf ("\n\tEditora : %s", livros.editora);
		printf ("\n\tISBN : %i ", livros.isbn);
		printf ("\n\tCodigo Livro : %i \n", livros.codigo);
	}
	
	printf ("\n\n");
	system ("\npause");
	
	// Fechar Arquivo
	fclose(arquivo);
}

// Mostrar Livros em ordem de Titulo
void ordenar_listar (consultas aux[]){
	
	// Local
	int i , k , l;
	consultas a;
	
	// Abrir o arquivo para leitura 
	if ((arquivo=fopen("bancolivros.txt","r"))==NULL)
	{
		printf ("\nErro na abertura do arquivo...");
	}
	
	// Transferencia para vetor
	b = 0 ;
	while(fread(&livros,sizeof(livros),1,arquivo))
	{
		
		strcpy(aux[b].titulo,livros.titulo) ;
		strcpy(aux[b].autores,livros.autores) ;
		strcpy(aux[b].editora,livros.editora) ;
		aux[b].anopublicacao = livros.anopublicacao ;
		aux[b].isbn = livros.isbn ;
		aux[b].codigo = livros.codigo ;
		
		b++ ;
	}
	
	// Ordenação
	for (k=0 ; k<b ; k++){
		for(l=k+1 ; l<b ; l++){
			if(strcmp(aux[k].titulo,aux[l].titulo)>0)
			{
				// Codigo
				a.codigo = aux[k].codigo;
				aux[k].codigo = aux[l].codigo;
				aux[l].codigo = a.codigo;
				
				// Titulo
				strcpy(a.titulo,aux[k].titulo);
				strcpy(aux[k].titulo,aux[l].titulo);
				strcpy(aux[l].titulo,a.titulo);
				
				// Ano Publicação 
				a.anopublicacao = aux[k].anopublicacao ;
				aux[k].anopublicacao = aux[l].anopublicacao ;
				aux[l].anopublicacao = a.anopublicacao ;
				
				// Autores
				strcpy(a.autores,aux[k].autores);
				strcpy(aux[k].autores,aux[l].autores);
				strcpy(aux[l].autores,a.autores);
				
				// ISBN
				a.isbn = aux[k].isbn;
				aux[k].isbn = aux[l].isbn;
				aux[l].isbn = a.isbn;
				
				// Editora
				strcpy(a.editora,aux[k].editora);
				strcpy(aux[k].editora,aux[l].editora);
				strcpy(aux[l].editora,a.editora);
				
			}
		}
	}
	
	printzinho(aux) ;
	
	// Fechar Arquivo
	fclose(arquivo);

}

// Printf de teste
void printzinho (consultas aux[]) {
	
	int i ;
	
	printf ("\n **** Lista Dos Livros Em Ordem Alfabetica ****\n");
	// Exibir Ordenado
	for (i=0 ; i<b ; i++){
		
		printf ("\n\tTitulo : %s ", aux[i].titulo);
		printf ("\n\tAutor : %s ", aux[i].autores) ;
		printf ("\n\tEditora : %s ", aux[i].editora);
		printf ("\n\tAno Publicacao : %i ",aux[i].anopublicacao);
		printf ("\n\tCodigo ISBN : %i ",aux[i].isbn);
		printf ("\n\tCodigo na biblioteca : %i \n",aux[i].codigo);	
		
	}
	
	printf ("\n\n");
	system ("\npause");
	
}

// Função Alterar
void alterar (consultas aux[]) {
	
	int pp , flag , flagg , posicao=0 , achou=0 ;
	consultas p;
	pp = 0 ;
	flagg = 0 ;
	flag = 0 ;
	
	// Abrir o arquivo para leitura 
	if ((arquivo=fopen("bancolivros.txt","r"))==NULL)
	{
		printf ("\nErro na abertura do arquivo...");
	}
						
	printf ("\nLivros Cadastrados No Banco De Dados :\n");
	
	while(fread(&livros,sizeof(livros),1,arquivo))
	{
		printf ("\nTitulo : %s", livros.titulo);
		printf ("\nCodigo Livro : %i \n", livros.codigo);
	}
	
	// Fechar Arquivo
	fclose(arquivo);
	
	fseek(arquivo, posicao, SEEK_SET);
	// Abrir o arquivo para leitura 
	arquivo=fopen("bancolivros.txt","r+ab");
	
	
	printf ("\nDigite o codigo do livro que deseja alterar :\n=>");
	scanf ("%i", &p.codigo);
	
	while(fread(&livros,sizeof(livros),1,arquivo))
	{
			if(p.codigo==livros.codigo){
					
				flag = 1 ;	
					
				printf ("\nLivro Selecionado : %s", livros.titulo);
				printf ("\nAutores : %s ", livros.autores);
				printf ("\nAno Publicacao : %i", livros.anopublicacao);
				printf ("\nEditora : %s", livros.editora);
				printf ("\nISBN : %i ", livros.isbn);
				printf ("\nCodigo Livro : %i \n", livros.codigo);
			
				printf ("\nDigite a opcao que deseja alterar :\n=>");
				printf ("\n 1 - Titulo ");
				printf ("\n 2 - Autores ");
				printf ("\n 3 - Ano Publicacao ");
				printf ("\n 4 - Editora ");
				printf ("\n 5 - ISBN ");
				printf ("\n 6 - Codigo\n=>");
				scanf  ("%i", &pp);		
					
				switch (pp){
							case 1 :{
					
								printf ("\nDigite o novo titulo:");
								fflush (stdin);
								gets (livros.titulo);
								
								
								fseek(arquivo, posicao, SEEK_SET);
                    			achou = fwrite(&livros,sizeof(livros),1,arquivo) == sizeof(livros);

								break;
							}
							
							case 2 :{
								printf ("\nDigite os novos autores:");
								fflush (stdin);
								gets (livros.autores);
								
								fseek(arquivo, posicao, SEEK_SET);
                    			achou= fwrite(&livros,sizeof(livros),1,arquivo) == sizeof(livros);
								
								break;
							}
							
							case 3 :{
								printf ("\nDigite o novo ano de publicacao:");
								scanf ("%i", &livros.anopublicacao);
								
								fseek(arquivo, posicao, SEEK_SET);
                    			achou= fwrite(&livros,sizeof(livros),1,arquivo) == sizeof(livros);
								
								break;
							}
							
							case 4 :{
								printf ("\nDigite o nova editora do livro:");
								fflush (stdin);
								gets (livros.editora);
								
								fseek(arquivo, posicao, SEEK_SET);
                    			achou= fwrite(&livros,sizeof(livros),1,arquivo) == sizeof(livros);
								
								break;
							}
							
							case 5 :{
								printf ("\nDigite o novo ISBN :");
								scanf ("%i", &livros.isbn);
								
								fseek(arquivo, posicao, SEEK_SET);
                    			achou = fwrite(&livros,sizeof(livros),1,arquivo) == sizeof(livros);
								
								break;
							}
							
							case 6 :{
								printf ("\nDigite o novo Codigo :");
								scanf ("%i", &livros.codigo);
								
								fseek(arquivo, posicao, SEEK_SET);
                    			achou = fwrite(&livros,sizeof(livros),1,arquivo) == sizeof(livros);
								
								break;
							}
							
							default :{
								printf ("\nOpcao Invalida...");	
								break;
							}
					};
				}
				posicao = posicao + sizeof(livros);
				fseek(arquivo, posicao, SEEK_SET);
			};
			
			if (flag==0) {
				printf ("\nNao tem nenhum livro com esse codigo para alteracao...");
			}

	printf ("\n");
	system ("\npause");
	
	// Fechar Arquivo
	fclose(arquivo);
}
 
// Função Consultar
void pesquisar (consultas aux[]) {
	
	int escolha , q , v , flag , kk ;
	consultas b;
	v = tamanho ;
	
	// Abrir o arquivo para leitura 
	if ((arquivo=fopen("bancolivros.txt","r"))==NULL)
	{
		printf ("\nErro na abertura do arquivo...");
	}
	
	printf ("\n\tDeseja pesquisar por :");
	printf ("\n\t 1 - Titulo De Livro ");
	printf ("\n\t 2 - Codigo De Livro");
	printf ("\n\t 3 - Ano de publicacao\n=>");
	scanf ("%i", &escolha);
	
	switch (escolha){
		
		case 1 :{
			flag=0 ;
			printf ("\n Digite o titulo do livro que procura :\n=>");
			fflush(stdin);
			gets(b.titulo);
		
			while(fread(&livros,sizeof(livros),1,arquivo))
			{
					if(strcmp(b.titulo,livros.titulo)==0){
						printf ("\nRESULTADO DA PESQUISA para %s :\n", b.titulo);
						printf ("\nTitulo : %s", livros.titulo);
						printf ("\nAutor : %s ", livros.autores);
						printf ("\nAno Publicacao : %i", livros.anopublicacao);
						printf ("\nEditora : %s", livros.editora);
						printf ("\nISBN : %i ", livros.isbn);
						printf ("\nCodigo Livro : %i \n", livros.codigo);
						
						flag = 1 ;
					}		
			};
			
			if (flag==0) {
				printf ("\nRESULTADO DA PESQUISA para %s :\n nada encontrado com esse titulo...\n", b.titulo);
			}
			
			printf ("\n\n");
			break;
		}
		
		case 2 :{
			flag=0 ;
			printf ("\n Digite o codigo do livro que procura :\n=>");
			scanf ("%i", &b.codigo);
			
			while(fread(&livros,sizeof(livros),1,arquivo))
			{
					if(b.codigo==livros.codigo){
						printf ("\nRESULTADO DA PESQUISA para codigo %i:\n", b.codigo);
						printf ("\nTitulo : %s", livros.titulo);
						printf ("\nAutor : %s ", livros.autores);
						printf ("\nAno Publicacao : %i", livros.anopublicacao);
						printf ("\nEditora : %s", livros.editora);
						printf ("\nISBN : %i ", livros.isbn);
						printf ("\nCodigo Livro : %i \n", livros.codigo);
						
						flag = 1 ;
					}		
			};
			
			if (flag==0) {
				printf ("\nRESULTADO DA PESQUISA para codigo %i :\n nada encontrado com esse codigo...\n", b.codigo);
			}
			
			printf ("\n\n");
			
			
			break;
		}
	
		case 3 :{
			flag=0 ;
			kk=0 ;
			printf ("\n Digite o periodo do ano de publicacao do livro que procura deseja procurar :\n");
			printf ("\nDE => ");
			scanf ("%i", &b.anopublicacao);
			printf ("\nATE => ");
			scanf ("%i", &b.isbn);
			
			while(fread(&livros,sizeof(livros),1,arquivo))
			{
					if(livros.anopublicacao>=b.anopublicacao && livros.anopublicacao<=b.isbn){
						if(kk == 0){
							printf ("\nRESULTADO DA PESQUISA para livros postados entre %i / %i :\n", b.anopublicacao , b.isbn);
							kk++ ;
						}
						printf ("\nTitulo : %s", livros.titulo);
						printf ("\nAutor : %s ", livros.autores);
						printf ("\nAno Publicacao : %i", livros.anopublicacao);
						printf ("\nEditora : %s", livros.editora);
						printf ("\nISBN : %i ", livros.isbn);
						printf ("\nCodigo Livro : %i \n", livros.codigo);
						
						flag = 1 ;
					}		
			};
			
			if (flag==0) {
				printf ("\nRESULTADO DA PESQUISA para livros publicados entre %i / %i :\n nada encontrado com esse codigo...\n", b.anopublicacao , b.isbn );
			}
			
			printf ("\n\n");
			
		
			break;
		}
		
		default :{
			printf ("\nOpcao Invalida...");
			break;
		}
		
	};
	
	// Fechar Arquivo
	fclose(arquivo);
	
	system ("\npause\n");
}
 
// Função sequencia dos codigos
int sequencia () {
	
	//Locais
	int numero ;
	
	//Ponteiro para o arquivo
	FILE *pontseq ;
	
	//Verificar se é a primeira vez
	if ((pontseq=fopen("sequencia.txt","r"))==NULL) {
		
		//  Abrir gravação
		pontseq=fopen("sequencia.txt","w");
		fprintf (pontseq,"%i",1) ;
		fclose (pontseq);
		
		return 1 ;
	}
	
	// Depois da primeira
	while ((fscanf(pontseq,"%i", &numero))!=EOF)
		numero++ ;
	
	fclose(pontseq);
	
	//Abrir o arquivo para manutação
	pontseq=fopen("sequencia.txt","w");
	fprintf (pontseq,"%i" ,numero);
	fclose (pontseq);
	return numero ;

	return 0 ;	
} 
 

// Função para Login
void login () {
	char auxnome[50] , auxsenha[15] ;
	int flag=0 ;
	
	// abrir arquivo para leitura ou gravação
	if ((arquivo=fopen("usuario.txt","r"))==NULL){
		printf ("Primeiro acesso , cadastrar agora\n");
		cad_usuario(0);
	}else{
		printf ("\n**** FAZER LOGIN ****");
		printf ("\nInforme o nome usuario : ");
		fflush (stdin);
		gets (auxnome);
		printf ("\nInforme a senha :");
		fflush (stdin);
		gets (auxsenha);
		while (fread(&users,sizeof(users),1,arquivo)==1)
		{
			if ((strcmp(users.nome,auxnome)==0) && (strcmp(users.senha,auxsenha)==0)){
				printf("\nUsuario foi autenticado...\n");
				printf ("\n\n");
				menu(users.perfil);
				flag=1 ; 
			}
		}
		if (flag==0){
			printf ("\nUsuario nao encontrado no sistema\n");
			system ("\npause");	
		}
	}
}

 // Função Principal 
 main () {
 	
 	login () ;
 	
 } 
 
