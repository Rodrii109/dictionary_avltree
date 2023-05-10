/*
Coisas pra fazer: 
----------------
	- criar as listas encadeadas das palavras
	- criar as funções de inserção e remoção das listas encadeadas
	- criar a função de impressão das listas encadeadas

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodeLinkedList{
	char word[100];
	struct nodeLinkedList *next;
};

struct nodeAVL{
	char info;
	int height;
	int bf;
	struct nodeAVL *left;
	struct nodeAVL *right;
	struct nodeLinkedList *LinkedListRoot;
};

int height(struct nodeAVL *node){
	if(node == NULL)
		return 0;
	else
		return node->height;
}

int getBalanceFactor(struct nodeAVL *node){
	if(node == NULL)
		return 0;
	else
		return height(node->left) - height(node->right);
}

int getMax(int a, int b){
	return (a > b) ? a : b;
}

struct nodeAVL *RR(struct nodeAVL *node){
	struct nodeAVL *x = node->left;
	struct nodeAVL *T2 = x->right;

	x->right = node;
	node->left = T2;
	
	node->height = getMax(height(node->left), height(node->right)) + 1;
	x->height = getMax(height(x->left), height(x->right)) + 1;

	node->bf = getBalanceFactor(node);
	x->bf = getBalanceFactor(x);
	
	return x;
}

struct nodeAVL *LL(struct nodeAVL *node){
	struct nodeAVL *y = node->right;
	struct nodeAVL *T2 = y->left;

	y->left = node;
	node->right = T2;

	node->height = getMax(height(node->left), height(node->right)) + 1;
	y->height = getMax(height(y->left), height(y->right)) + 1;

	node->bf = getBalanceFactor(node);
	y->bf = getBalanceFactor(y);

	return y;
}

struct nodeLinkedList *newNodeLinkedList(char word[100]){
	struct nodeLinkedList *node = (struct nodeLinkedList *)malloc(sizeof(struct nodeAVL));

	strcpy(node->word,word);
	node->next = NULL;

	return node;
}

struct nodeAVL *newNode(char info, char word[100]){
	struct nodeAVL *node = (struct nodeAVL *)malloc(sizeof(struct nodeAVL));

	node->info = info;
	node->left = NULL;
	node->right = NULL;
	node->LinkedListRoot = newNodeLinkedList(word);
	node->height = 1;
	node->bf = 0;

	return (node);
}

struct nodeAVL *insertNode(struct nodeAVL *root, char info, char word[100]){
	if(root == NULL)
		return newNode(info,word);
	
	if(root->info > info)
		root->left = insertNode(root->left, info, word);
	else if(root->info < info)
		root->right = insertNode(root->right, info, word);
	else
		return root;

	root->height = 1 + getMax(height(root->left), height(root->right));
	root->bf = getBalanceFactor(root);

	if(root->bf == 2){
		if(root->right->bf == -1)
			root->left = LL(root->left);
		return RR(root);
	}else if(root->bf == -2){
		if(root->left->bf == 1)
			root->right = RR(root->right);
		return LL(root);
	}

	return root;
}

struct nodeAVL *getPredecessor(struct nodeAVL *node){
	struct nodeAVL *current = node;

	while(current->right != NULL)
		current = current->right;

	return current;
}

struct nodeAVL *deleteNode(struct nodeAVL *root, char info){
	if(root == NULL)
		return root;

	if(root->info > info)
		root->left = deleteNode(root->left,info);
	else if(root->info < info)
		root->right = deleteNode(root->right,info);

	else{
		if((root->left == NULL) || (root->right == NULL)){
      	struct nodeAVL *temp = root->left ? root->left : root->right;
	      	if(temp == NULL){
	      		temp = root;
	      		root = NULL;
	      	}else
	      		*root = *temp;
      	free(temp);
  	  	}else{
	  	    struct nodeAVL *temp = getPredecessor(root->left);
	  	    root->info = temp->info;
  	    	root->right = deleteNode(root->right, temp->info);
  	  	}
  	}

  	if(root == NULL)
  		return root;

  	root->height = 1 + getMax(height(root->left), height(root->right));
	root->bf = getBalanceFactor(root);

	if(root->bf == 2){
		if(root->right->bf == -1)
			root->left = LL(root->left);
		return RR(root);
	}else if(root->bf == -2){
		if(root->left->bf == 1)
			root->right = RR(root->right);
		return LL(root);
	}

	return root;
}

struct nodeAVL *searchNodeAVL(struct nodeAVL *root){

}

void insertNodeLinkedList(struct nodeAVL *rootAVL, char word[100]){

}	

void deleteNodeLinkedList(struct nodeLinkedList *root, char word[100]){

}

void scanWords(struct nodeAVL *root){
	char word[100];
	int n = -1;
	
	while(strncmp(word,"0", 1) != 0){
		fgets(word,100,stdin);
		
		if(word[0] == '0')
			break;

		struct nodeAVL *aux = searchNodeAVL(root);
		if(aux == NULL){
			root = insertNode(root, word[0], word);
		}else{
			//procurar na lista o lugar onde armazenar a palavra
			/*if(a palavra for encontrada na lista){
				não faz nada
			}else{
				adiciona a palavra na lista
				n++;
			}*/
		}
	}

	if(n == 0)
		printf("Nenhum dado foi carregado.\n");
	else{
		printf("Todos os dados foram carregados com sucesso!!\n");
		printf("Total de %d palavras adicionadas no dicionario\n",n);
  	}
}

void printInOrder(struct nodeAVL *root){
	if(root != NULL){
		printInOrder(root->left);
		printf("%c height: %d balance factor: %d\n", root->info,root->height,root->bf);
		printInOrder(root->right);
	}
}

void printMenu(){
	printf("\n");
	printf("*** MENU DE OPÇÕES: ENTRE COM A OPÇÃO DESEJADA ***\n");
	printf("\n");
	printf("1. Busca\n");
	printf("2. Inserção\n");
	printf("3. Remoção\n");
	printf("4. Impressão de um no\n");
	printf("5. Impressão da arvore\n");
	printf("6. Encerrar\n");
	printf("\n");
}


int main(){
	int option;

	struct nodeAVL *root = (struct nodeAVL *)malloc(sizeof(struct nodeAVL));
	while(1){
		printMenu();
		scanf("%d", &option);

		switch(option){
			case 1:
				break;
			case 2:
				scanWords(root);
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				printf("Programa encerrado!!\n");
				return 0;
				break;
			default:
				printf("Essa opcao nao existe! tente de novo com numeros entre 1-6\n");
		}
	}
	return 0;
}
