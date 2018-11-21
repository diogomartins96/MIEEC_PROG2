#define TAMANHO_MAX_ROBOT 10000
#define TAMANHO_MAX_MOVIMENTOS 65535
#define TAMANHO_MAX_CELULAS 65536

typedef unsigned long hash_func(const char *, int);

typedef struct mov
{
	char flag[3];
	struct mov* proximo;
} movimento;

typedef struct
{
	char nome[17];
	int index;
} robo_tabela_dispersao;

typedef struct elem
{
	robo_tabela_dispersao* robo;
	struct elem* proximo;
} elemento_tabela_dispersao;

struct tab_dispersao
{
	hash_func *hfunc;
	elemento_tabela_dispersao **elementos;
	int tamanho;
	int tamanho_de_robots;
};

typedef struct tab_dispersao *tabela_dispersao;

typedef struct
{
	char nome[17];
	char * direcoes;
	int numero_movimentos;
} robo_vetor;

tabela_dispersao tabela_cria(int tamanho, hash_func *hfunc);

void tabela_apaga(tabela_dispersao td);

int tabela_adiciona(tabela_dispersao td, const char * nome, int index_robo);

int tabela_valor(tabela_dispersao td, const char *nome);

unsigned long hash_krm(const char* chave, int tamanho);

void funcao_ler(FILE* ficheiro, robo_vetor* vetor, int* numero_robos);

void tamanho_labirinto(robo_vetor* vetor, int numero_robos, int* x_minimo, int* x_maximo, int* y_minimo, int* y_maximo, int* L, int* H);
