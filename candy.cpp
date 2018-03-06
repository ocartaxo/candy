// <OTAVIO AUGUSTO CARTAXO ARAUJO>
// <UNIVERSSIDADE FEDERAL DA BAHIA>

/*
COMENTARIO: < O MEU TABULEIRO FOI CONSTRUIDO COM BORDAS, PORTANTO, AS PEÇAS COMEÇAM
			A SER INDEXIDAS PELA LINHA 1 COLUNA 1, E AS BORDAS ESTARÃO VIZÍVEIS.
			DURANTE OS TESTES, EU PAREI O PROGRAMA USANDO CTRL + C ENQUANTO O PROGRAMA
			ESTAVA LENDO OS DADOS DO MOVIMENTO, E ISSO FEZ COM QUE ELE ENTRASSE NA CONDIÇÃO
			DE VALIDAÇÃO DO MOVIMENTO(LINHA 526), EXIBINDO A MENSAGEM DE MOVIMENTO INVÁLIDO.
			NÃO SEI POR QUE ISSO OCORROEU, E ACREDITO QUE NÃO SEJA ERRO NO CÓDIGO.
			NO MAIS, O CÓDIGO ESTÁ FUNCIONANDO PERFEITAMENTE.>

*/

#include<iostream>
#include<iomanip>
using namespace std;

// Elementos do tabuleiro
#define BORDA -1
#define VAZIO 0

// Variaveis globais
int N;		// dimensão do tabuleiro
int D;		// número máximo de tipos de peças diferentes no tabuleiro
int S;		// Semente para geração de números pseudo-aleatorios

int** tabuleiro;
int linha;
int coluna;
int pontos;
int pontosTotal = 0;

// Classe que define o movimento
class Movimento{
	public:
		pair <int,int> origem;
		pair <int,int> destino;
};

// Variavel que armazena o movimento
Movimento mover;

//
// USE BACKTRACKING PARA CRIAR TABULEIROS
// SEM ESTRUTURAS ELIMINAVEIS
//

/*
----------------------------------------------------------------------------------------------------
||||||||||||||||||||||||||||||||||||||||||||| O CÓDIGO |||||||||||||||||||||||||||||||||||||||||||||
----------------------------------------------------------------------------------------------------
*/

// Aloca um tabuleiro um NxN
void AlocaTabuleiro(){

	// Aloca espaco na memoria para o tabuleiro
	tabuleiro = new int*[N+2];
	for(int i= 0; i <= N+1; i++){
		tabuleiro[i] = new int[N+2];
	}


	// Define a borda
	for(int i = 0; i <= N+1; i++){

		tabuleiro[0][i]		= BORDA;
		tabuleiro[i][0]		= BORDA;
		tabuleiro[N+1][i]	= BORDA;
		tabuleiro[i][N+1]	= BORDA;

	}


	// Zera todas as posições do tabuleiro
	for(int i = 1; i <= N; i++){
		for(int j = 1; j <= N; j++){
			tabuleiro[i][j] = VAZIO;
		}
	}
}


// Procura por células vazias
bool ExisteCelulaVazia(int& i, int& j){

	for(i = 1; i <= N; i++){
		for(j = 1; j <= N; j++){
			if(tabuleiro[i][j] == VAZIO)
				return true;
		}

	}

	return false;
}


bool ExistePecasIguaisAcima(int row, int col, int num){

	if(row > 2){
		if( (num == tabuleiro[row-1][col]) &&
			(num == tabuleiro[row-2][col]) )
			return true;
	}

	return false;
}

bool ExistePecasIguaisAcimaAbaixo(int row, int col, int num){

	if(row > 1 && row < N){
		if( (num == tabuleiro[row-1][col]) &&
		    (num == tabuleiro[row+1][col]) )
			return true;
	}

	return false;
}

bool ExistePecasIguaisAbaixo(int row, int col, int num){

	if(row <= N-2){
		if( (num == tabuleiro[row+1][col]) &&
			(num == tabuleiro[row+2][col]) )
			return true;
	}

	return false;
}


// Procura por cores iguais na mesma coluna
bool ExistePecasIguaisNaMesmaColuna(int row, int col, int num){


	if( ExistePecasIguaisAcima(row, col, num) 		||
		ExistePecasIguaisAcimaAbaixo(row, col, num) ||
		ExistePecasIguaisAbaixo(row, col, num))
		return true;


	return false;
}

// Procura por peças iguais a esquerda da peça atual.
bool ExistePecasIguaisEsquerda(int row, int col, int num){

	if(col > 2){
		if( (num == tabuleiro[row][col-1]) &&
			(num == tabuleiro[row][col-2]) )
			return true;
	}

	return false;
}

// Procura por peças iguais a esquerda e a direita da peça atual.
bool ExistePecasIguaisDireitaEsquerda(int row, int col, int num){

	if(col > 1 && col < N){
		if( (num == tabuleiro[row][col-1]) &&
			(num == tabuleiro[row][col+1]) )
			return true;
	}

	return false;

}

// Procura por peças iguais a direta da peça atual.
bool ExistePecasIguaisDireita(int row, int col, int num){

	if(col <= N-2){
		if( (num == tabuleiro[row][col+1]) &&
			(num == tabuleiro[row][col+2]) )
			return true;
	}

	return false;
}


// Procura por pecas iguais na mesma linha.
bool ExistePecasIguaisNaMesmaLinha(int row, int col, int num){

	if( ExistePecasIguaisEsquerda(row, col, num)		||
		ExistePecasIguaisDireitaEsquerda(row, col, num) ||
		ExistePecasIguaisDireita(row, col, num))
		return true;


	return false;
}

// Procura por uma estrutura pontuável
bool ExisteEstruturaPontuavel(int row, int col, int num){


	if(ExistePecasIguaisNaMesmaLinha(row, col, num) ||
		ExistePecasIguaisNaMesmaColuna(row, col, num))
		return true;

	return false;
}


// Gera um tabuleiro N x N sem estruturas pontuáveis
// utilizando backtracking
bool ConstroiTabuleiro(){

	int i, j;

	if(!ExisteCelulaVazia(i, j)){
		return true;
	}

	tabuleiro[i][j] = rand()%D+1;

	if(!ExisteEstruturaPontuavel(i, j, tabuleiro[i][j])){
		if(ConstroiTabuleiro())
			return true;
	}

	for(int num = 1; num <= D; num++){

		tabuleiro[i][j] = num;

		if(!ExisteEstruturaPontuavel(i, j, num)){
			if(ConstroiTabuleiro())
				return true;
		}

	}


	tabuleiro[i][j] = VAZIO;

	// Aciona o backtracking
	return false;
}

// Imprime o tabuleiro com as bordas
void ImprimeTabuleiro(){
	for(int i= 0; i <= N+1; i++){
		for(int j= 0; j <= N+1; j++){
			cout<<setw(3)<<tabuleiro[i][j];
		}
		cout<<endl;
	}
}

// Libera o espaço da memória
void ApagaTabuleiro(){
	for(int i= 0; i <= N+1; i++){
		delete [] tabuleiro[i];
	}
	delete [] tabuleiro;
}

// Verifica se existe existe uma estrutura pontuavel acima, entre e abaixo
// da peca movida, e as marca como vazio.
void MarcaPecasIguaisNaMesmaColuna(int row, int col, int num){

	if(ExistePecasIguaisAcima(row, col, num)){
		for(int i = row; i >= 1; i--){

			if(tabuleiro[i][col] == num)
				tabuleiro[i][col] = VAZIO;
			else if(tabuleiro[i][col] == VAZIO)
				continue;
			else
				break;

		}

	}

	if(ExistePecasIguaisAcimaAbaixo(row, col, num)){

		for(int i = row; i >= 1; i--){

			if(tabuleiro[i][col] == num)
				tabuleiro[i][col] = VAZIO;
			else if(tabuleiro[i][col] == VAZIO)
				continue;
			else
				break;

		}

		for(int i = row; i <= N; i++){

			if(tabuleiro[i][col] == num)
				tabuleiro[i][col] = VAZIO;
			else if(tabuleiro[i][col] == VAZIO)
				continue;
			else
				break;
		}

	}

	if(ExistePecasIguaisAbaixo(row, col, num)){

		for(int i = row; i <= N; i++){

			if(tabuleiro[i][col] == num)
				tabuleiro[i][col] = VAZIO;
			else if(tabuleiro[i][col] == VAZIO)
				continue;
			else
				break;
		}

	}

}


// Verifica se existe estrutura(s) pontuavel(eis) a direita, entre e esquerda
// da peca movida, e as marca como vazio.
void MarcaPecasIguaisNaMesmaLinha(int row, int col, int num){

	if(ExistePecasIguaisDireita(row, col, num)){

		for(int j = col; j <= N; j++){

			if(tabuleiro[row][j] == num)
				tabuleiro[row][j] = VAZIO;
			else if(tabuleiro[row][j] == VAZIO)
				continue;
			else
				break;

		}
	}


	if(ExistePecasIguaisDireitaEsquerda(row, col, num)){

		for(int j = col; j <= N; j++){

			if(tabuleiro[row][j] == num)
				tabuleiro[row][j] = VAZIO;
			else if(tabuleiro[row][j] == VAZIO)
				continue;
			else
				break;

		}

		for(int j = col; j >= 1; j--){

			if(tabuleiro[row][j] == num)
				tabuleiro[row][j] = VAZIO;
			else if(tabuleiro[row][j] == VAZIO)
				continue;
			else
				break;
		}

	}


	if(ExistePecasIguaisEsquerda(row, col, num)){

		for(int j = col; j >= 1; j--){

			if(tabuleiro[row][j] == num)
				tabuleiro[row][j] = VAZIO;
			else if(tabuleiro[row][j] == VAZIO)
				continue;
			else
				break;
		}

	}
}

// Marca a(s) estrutura(s) pontuavel(eis)  como vazio.
void ExecutaMovimento(int row, int col, int num){

	MarcaPecasIguaisNaMesmaLinha(row, col, num);
	MarcaPecasIguaisNaMesmaColuna(row, col, num);

}


// Realiza o  movimento da peça.
void MovePeca(){

	int linhaOrigem = mover.origem.first;
	int colunaOrigem = mover.origem.second;

	int linhaDestino = mover.destino.first;
	int colunaDestino = mover.destino.second;

	int pecaOrigem = tabuleiro[linhaOrigem][colunaOrigem];
	int pecaDestino = tabuleiro[linhaDestino][colunaDestino];

	if(ExisteEstruturaPontuavel(linhaDestino, colunaDestino, pecaOrigem)){

		tabuleiro[linhaOrigem][colunaOrigem] = pecaDestino;
		tabuleiro[linhaDestino][colunaDestino] = pecaOrigem;


		ExecutaMovimento(linhaDestino, colunaDestino, pecaOrigem);

		if(ExisteEstruturaPontuavel(linhaOrigem, colunaOrigem, pecaDestino)){
			ExecutaMovimento(linhaOrigem, colunaOrigem, pecaDestino);
		}

	}

}

// Calcula a quantidade de peças vazias no
// tabuleiro e retorna esse número para ser adicionado
// a pontuação total.
int CalculaPontuacao(){

	int qtdPecasMarcadas = 0;

	for(int row = 1; row <= N; row++){
		for(int col = 1; col <= N; col++){

			if(tabuleiro[row][col] == VAZIO)
				qtdPecasMarcadas++;

		}
	}

	return qtdPecasMarcadas;
}

// Usa a função ConstroiTabuleiro() para evitar de
// criar estruturas pontuáveis
void ReConstroiTabuleiro(){
	ConstroiTabuleiro();
}

// Verifica se o movimento é válido
bool MovimentoEhValido(){

	int linhaOrigem = mover.origem.first;
	int colunaOrigem = mover.origem.second;

	int linhaDestino = mover.destino.first;
	int colunaDestino = mover.destino.second;

	if( (abs(linhaDestino - linhaOrigem) == 1 )||
		(abs(colunaDestino - colunaOrigem) == 1) ){


		if( (abs(linhaDestino - linhaOrigem) == 1) &&
			(abs(colunaDestino - colunaOrigem) == 1))
			return false;

		else if(tabuleiro[linhaDestino][colunaDestino] == BORDA ||
				tabuleiro[linhaOrigem][colunaOrigem]   == BORDA)
			return false;

		else
			return true;

	}

	return false;

}

// Procura movimentos válidos.
bool ExisteMovimento(){

	for(int i = 1; i <= N; i++){
		for(int j = 1; j <= N; j++){

			if( ExisteEstruturaPontuavel(i+1, j, tabuleiro[i][j]) ||
				ExisteEstruturaPontuavel(i-1, j, tabuleiro[i][j]) ||
				ExisteEstruturaPontuavel(i, j+1, tabuleiro[i][j]) ||
				ExisteEstruturaPontuavel(i, j-1, tabuleiro[i][j]))
				return true;
		}
	}

	return false;
}


// Roda o programa
int main(int argc, char* argv[]){

	//Leitura da dimensao do tabuleiro
	cout<<"Dimensao do tabuleiro: "<<endl;
	cin>>N;

	cout<<"Numero maximo de pecas diferentes: "<<endl;
	cin>>D;

	cout<<"Informe a semente pseudoaleatoria: "<<endl;
	cin>>S;

	// Alimentando o gerador de numero pseudoaleatorios
	srand(S);
	AlocaTabuleiro();

	ConstroiTabuleiro();
	ImprimeTabuleiro();

	do{

		cout<<"Linha origem: ";
		cin>>linha;
		cout<<"Coluna origem: ";
		cin>>coluna;
		mover.origem = make_pair (linha,coluna);

		cout<<"Linha destino: ";
		cin>>linha;
		cout<<"Coluna destino: ";
		cin>>coluna;
		mover.destino = make_pair (linha,coluna);

		if(!MovimentoEhValido()){
			cout << "O seu movimento eh invalido.";
			cout << "Por favor, faca outro movimento." << endl;
			continue;
		}

		MovePeca();
		pontos = CalculaPontuacao();
		cout<<"Pontos Obtidos: "<< pontos <<endl;
		pontosTotal += pontos;

		ImprimeTabuleiro();
		ReConstroiTabuleiro();

		cout<<"\nTabuleiro atual: "<<endl;
		ImprimeTabuleiro();

	}while(ExisteMovimento());

	cout << "Fim de jogo." << endl;
	cout << "Pontuacao Total: " << pontosTotal << endl;


	return 0;
}
