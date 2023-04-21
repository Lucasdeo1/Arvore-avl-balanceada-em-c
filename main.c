#include <stdio.h>
#include <stdlib.h>
//Lucas deodato Avl
typedef struct arvore {
    int inf;
    int altura;
    struct arvore* esq;
    struct arvore* dir;
} arvore;

arvore* cria(int v);
arvore* encontrarmin(arvore* a);
int altura(arvore* a);
int fb(arvore* a);
arvore* rotadir(arvore* a);
arvore* rotaesq(arvore* a);
arvore* insere(arvore* a, int v);
arvore* remover(arvore* a, int v);
void preordem(arvore* a);
void emordem(arvore*a);	
void posordem(arvore*a);

int main() {
	arvore* a;
	int v;
	a = cria(15);
	a = insere(a, 6);
	a = insere(a, 12);
	a = insere(a, 9);
	a = insere(a, 14);
	a = insere(a, 13);
	a = insere(a, 25);
	a = insere(a, 18);
	a = insere(a, 20);
	a = insere(a, 23);
	a = insere(a, 5);
	a = insere(a, 3);
	a = insere(a, 1);
	a = insere(a, 38);
	a = insere(a, 45);
	a = insere(a, 50);
	a = insere(a, 48);
	a = insere(a, 46);
	a = insere(a, 60);
	printf("arvore AVL apos insercao:\n");
	printf("preordem:\n");
	preordem(a);
	printf("\n----------------------------------\n");
	printf("emordem:\n");
	emordem(a);
	printf("\n----------------------------------\n");
	printf("posordem:\n");
	posordem(a);
	printf("\n----------------------------------\n");
	
	a = remover(a, 23);
	a = remover(a, 3);
	a = remover(a, 48);
	a = remover(a, 15);
	a = remover(a, 13);
	printf("arvore AVL apos remocao:\n");
	printf("preordem:\n");
	preordem(a);
	printf("\n----------------------------------\n");
	printf("emordem:\n");
	emordem(a);
	printf("\n----------------------------------\n");
	printf("posordem:\n");
	posordem(a);
	printf("\n----------------------------------\n");
	
	free(a);
	return 0;
}

arvore* cria(int v) {
    arvore* a = (arvore*) malloc(sizeof(arvore));
    a->inf = v;
    a->altura = 1;
    a->esq = NULL;
    a->dir = NULL;
    return a;
}

arvore* encontrarmin(arvore* a) {
    if (a == NULL) {
        return NULL;
    } else if (a->esq == NULL) {
        return a;
    } else {
        return encontrarmin(a->esq);
    }
}


int altura(arvore* a) {
    if (a == NULL) {
        return 0;
    }
    return a->altura;
}


int fb(arvore* a) {
    if (a == NULL) {
        return 0;
    }
    return altura(a->esq) - altura(a->dir);
}


arvore* rotadir(arvore* a) {
    arvore* aux = a->esq;
    a->esq = aux->dir;
    aux->dir = a;
    a->altura = 1 + (altura(a->esq) > altura(a->dir) ? altura(a->esq) : altura(a->dir));
    aux->altura = 1 + (altura(aux->esq) > altura(aux->dir) ? altura(aux->esq) : altura(aux->dir));
    return aux;
}


arvore* rotaesq(arvore* a) {
    arvore* aux = a->dir;
    a->dir = aux->esq;
    aux->esq = a;
    a->altura = 1 + (altura(a->esq) > altura(a->dir) ? altura(a->esq) : altura(a->dir));
    aux->altura = 1 + (altura(aux->esq) > altura(aux->dir) ? altura(aux->esq) : altura(aux->dir));
    return aux;
}


arvore* insere(arvore* a, int v) {
    if (a == NULL) {
        return cria(v);
    }
    if (v < a->inf) {
        a->esq = insere(a->esq, v);
    } else {
        a->dir = insere(a->dir, v);
    }
    a->altura = 1 + (altura(a->esq) > altura(a->dir) ? altura(a->esq) : altura(a->dir));
    int balance = fb(a);
    if (balance > 1 && v < a->esq->inf) {
        return rotadir(a);
    }
    if (balance < -1 && v > a->dir->inf) {
        return rotaesq(a);
    }
    if (balance > 1 && v > a->esq->inf) {
        a->esq = rotaesq(a->esq);
        return rotadir(a);
    }
    if (balance < -1 && v < a->dir->inf) {
		a->dir = rotadir(a->dir);
		return rotaesq(a);
	}
	return a;
}
	

arvore* remover(arvore* a, int v) {
	if (a == NULL) {
		return NULL;
	}
	if (v < a->inf) {
		a->esq = remover(a->esq, v);
	} else if (v > a->inf) {
		a->dir = remover(a->dir, v);
	} else {
		if (a->esq == NULL && a->dir == NULL) {
		free(a);
		return NULL;
		} 
		else if (a->esq == NULL || a->dir == NULL) {
			arvore* temp = a->esq ? a->esq : a->dir;
			free(a);
			return temp;
		} else {
			arvore* temp = encontrarmin(a->dir);
			a->inf = temp->inf;
			a->dir = remover(a->dir, temp->inf);
		}
	}
	if (a == NULL) {
		return NULL;
	}
	a->altura = 1 + (altura(a->esq) > altura(a->dir) ? altura(a->esq) : altura(a->dir));
	int balance = fb(a);
	if (balance > 1 && fb(a->esq) >= 0) {
		return rotadir(a);
	}
	if (balance > 1 && fb(a->esq) < 0) {
		a->esq = rotaesq(a->esq);
		return rotadir(a);
	}
	if (balance < -1 && fb(a->dir) <= 0) {
		return rotaesq(a);
	}
	if (balance < -1 && fb(a->dir) > 0) {
		a->dir = rotadir(a->dir);
		return rotaesq(a);
	}
	return a;
}	

void preordem(arvore* a) {
	if (a == NULL) {
		return ;
	}
	printf("%d ", a->inf);
	preordem(a->esq);
	preordem(a->dir);
}

void emordem(arvore*a){
	if (a == NULL) {
		return ;
	}
	emordem(a->esq);
	printf("%d ", a->inf);
	emordem(a->dir);
}
	
void posordem(arvore*a){
	if (a == NULL) {
		return ;
	}
	posordem(a->esq);
	posordem(a->dir);
	printf("%d ", a->inf);	
}

