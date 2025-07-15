#include<stdio.h>
#include<stdlib.h>
typedef struct Term{
	int exp;
	int coeff;
	struct Term *next;
}Term;

typedef struct{
	Term* head;
}Polynomial;


Term* createTerm(int exp, int coeff){
	Term* t = (Term*)malloc(sizeof(Term));
	 t->exp  = exp;
	 t->coeff  = coeff;
	 t->next  = NULL;
	return t;
}
void insertEnd(Polynomial* p,Term* t){

	// printf("%p",p->head);
	if (!p->head){
		p->head = t;
		return;
	}
	Term* lastEle = p->head;
	while(lastEle->next != NULL){

		lastEle = lastEle->next;
	}
	lastEle->next = t;
	
}

// void insertSorted(Polynomial* p,Term* t){
// 	if (p->head == NULL ||t->exp > p->head->exp){
// 		t->next = p->head;
// 		p->head = t;
// 		return;
// 	}
// 	Term* lastEle = p->head;
// 	while(lastEle->next && lastEle->next->exp>=t->exp){
// 		printf("hai\n");
// 		if(t->exp == lastEle->exp){
// 			lastEle->coeff = lastEle->coeff+ t->coeff;
// 			free(t);
// 			return;
// 		}
// 		lastEle = lastEle->next;
// 	}
// 	t->next = lastEle->next;
// 	lastEle->next = t;
// }

void insertSorted(Polynomial* p, Term* t) {
    // Empty list or new term’s exp > head’s exp → insert at head
    if (p->head == NULL || t->exp > p->head->exp) {
        t->next = p->head;
        p->head = t;
        return;
    }

    Term* current = p->head;
    Term* prev = NULL;

    while (current != NULL && current->exp >= t->exp) {
        if (current->exp == t->exp) {
            // Exponents match — combine coefficients
            current->coeff += t->coeff;
            free(t); // don’t leak memory
            return;
        }
        prev = current;
        current = current->next;
    }

    // Insert new term in sorted position
    t->next = current;
    prev->next = t;
}

Polynomial* createPolynomial(int size){
	Polynomial *p = (Polynomial*)malloc(sizeof(Polynomial));
	p->head = NULL;
	int i;
	Term* lastEle = p->head;
	for(i = 0;i<size;i++){
		int exp,coeff;
		printf("Enter exponent of element %d: ",i+1);
		scanf("%d",&exp);
		printf("Enter coeffeicent of element %d: ",i+1);
		scanf("%d",&coeff);
		Term* t = createTerm(exp, coeff);
		insertSorted(p,t);
	}
	return p;
}

void displayPolynomial(Polynomial* poly){
	Term *element = poly->head;
	int firstEle = 0;
	while (1){
		if( firstEle == 1){
			printf(" + ");
		}
		printf("%dx^%d",element->coeff,element->exp);
		if (!element->next){
			break;
		}
		element = element->next;
		if (firstEle == 0){
			firstEle = 1;
		}
	}
	printf(" = 0\n");
}


int main(){
	int p1_size,p2_size;
	printf("We are going to create 2 polynomials, then get sum and product of them\n");
	printf("Enter number of terms in polynomial 1:\t");
	scanf("%d",&p1_size);
	Polynomial* p1 = createPolynomial(p1_size);

	displayPolynomial(p1);
	free(p1);
	return 0;
}
