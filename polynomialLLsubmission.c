#include<stdio.h>
#include<stdlib.h>

typedef struct Term {
	int exp;
	int coeff;
	struct Term* next;
} Term;

typedef struct {
	Term* head;
} Polynomial;

Term* createTerm(int exp, int coeff) {
	Term* t = (Term*)malloc(sizeof(Term));
	t->exp = exp;
	t->coeff = coeff;
	t->next = NULL;
	return t;
}

void insertSorted(Polynomial* p, Term* t) {

	if(p->head == NULL ||t->exp > p->head->exp) {
		t->next = p->head;
		p->head = t;
		return;
	}
	Term* current = p->head;
	Term* prev = NULL;

	while (current!= NULL && current->exp >= t->exp ) {
		if(current->exp == t->exp) {
			current->coeff += t->coeff;
			free(t);
			return;
		}
		prev = current;
		current = current->next;
	}
	t->next = current;
	prev->next = t;
}

Polynomial* createPolynomial() {
	Polynomial* p = (Polynomial*)malloc(sizeof(Polynomial));
	p->head = NULL;
	return p;
}

Polynomial* generatePolynomial(int size) {
	Polynomial *p = createPolynomial();
	int i;
	Term* lastEle = p->head;
	for(i = 1; i<=size; i++) {
		int exp,coeff;
		printf("Enter exponent of term %d: ",i);
		scanf("%d",&exp);
		printf("Enter coefficent of term %d: ",i);
		scanf("%d",&coeff);
		Term* t = createTerm(exp,coeff);
		insertSorted(p,t);
	}
	return p;
}

void addPolynomial(Polynomial *sum,Polynomial *p){
    Term *current = p->head;
    while(current){
        int exp = current->exp;
        int coeff = current->coeff;
        Term *new_term = createTerm(exp,coeff);
        insertSorted(sum,new_term);
        current=current->next;
    }
}

Polynomial* sumOfPolynomial(Polynomial *p1,Polynomial *p2){
    Polynomial *sum = createPolynomial();
    addPolynomial(sum,p1);
    addPolynomial(sum,p2);
    return sum;
}

Polynomial *productOfPolynomial(Polynomial *p1,Polynomial *p2){
    Polynomial *product = createPolynomial();
    Term *outerTerm = p1->head;
    while(outerTerm){
        int outerExp = outerTerm->exp;
        int outerCoeff = outerTerm->coeff;
        printf("%dx^%d",outerTerm->coeff,outerTerm->exp);
        Term *innerTerm = p2->head;
        while(innerTerm){
            int innerExp = outerExp+innerTerm->exp;
            int innerCoeff = outerCoeff*innerTerm->coeff;
            Term *new_term = createTerm(innerExp,innerCoeff);
            insertSorted(product,new_term);
            innerTerm = innerTerm->next;
        }
        outerTerm = outerTerm->next;
    }
    return product;
}

void displayPolynomial(Polynomial* p){
    Term *current = p->head;
    while(current){
        printf("%dx^%d",current->coeff,current->exp);
        current = current->next;
        if(current){
            printf(" + ");
        }
    }
    printf("= 0\n");
}

void freePolynomial(Polynomial* p){
    Term* current = p->head;
    while(current){
        Term *next =current->next;
        free(current);
        current = next;
    }
    free(p);
}

int main() {
	int p1_size,p2_size;
	printf("We are going to create 2 polynomials, then get sum and product of them\n");
	printf("Enter number of terms in polynomial 1: ");
	scanf("%d",&p1_size);
	Polynomial *p1 = generatePolynomial(p1_size);
	printf("Enter number of terms in polynomial 2: ");
	scanf("%d",&p2_size);
	Polynomial *p2 = generatePolynomial(p2_size);
    
    printf("1: ");
    displayPolynomial(p1);
    printf("2: ");
    displayPolynomial(p2);
    printf("Sum: ");
	Polynomial *sum = sumOfPolynomial(p1,p2);
    displayPolynomial(sum);
    printf("Product: ");
	Polynomial *product = productOfPolynomial(p1,p2);
    displayPolynomial(product);
    
    freePolynomial(p1);
    freePolynomial(p2);
    freePolynomial(sum);
    freePolynomial(product);
    return 0;
}
