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


Polynomial* createPolynomial(){
	Polynomial *p = (Polynomial*)malloc(sizeof(Polynomial));
	p->head = NULL;
	return p;
}
Polynomial* generatePolynomial(int size){
	Polynomial *p = createPolynomial();
	int i;
	Term* lastEle = p->head;
	for(i = 0;i<size;i++){
		int exp,coeff;
		printf("Enter exponent of element %d: ",i+1);
		scanf("%d",&exp);
		printf("Enter coefficient of element %d: ",i+1);
		scanf("%d",&coeff);
		Term* t = createTerm(exp, coeff);
		insertSorted(p,t);
	}
	return p;
}
Polynomial* sumOfPolynomial(Polynomial *p1,Polynomial *p2){
	Polynomial *sum = createPolynomial();
	Term *p1_elements = p1->head;
	while(p1_elements){
		int exp=p1_elements->exp;
		int coeff=p1_elements->coeff;
		Term *new_term = createTerm(exp,coeff);
		insertSorted(sum,new_term);
		p1_elements = p1_elements->next;
	}
	Term *p2_elements =  p2->head;
	while(p2_elements){
		int exp=p2_elements->exp;
		int coeff=p2_elements->coeff;
		Term *new_term = createTerm(exp,coeff);
		insertSorted(sum,new_term);
		p2_elements = p2_elements->next;
	}
	return sum;
}

Polynomial* productOfPolynomial(Polynomial *p1,Polynomial *p2){
	Polynomial *product = createPolynomial();
	Term *p1_elements = p1->head;
	while(p1_elements){
		int outerExp=p1_elements->exp;
		int outerCoeff=p1_elements->coeff;
		Term *p2_elements =  p2->head;
		while(p2_elements){
		int exp = outerExp + p2_elements->exp;
		int coeff = outerCoeff * p2_elements->coeff;	
			Term *new_term = createTerm(exp,coeff);
			insertSorted(product,new_term);
			p2_elements = p2_elements->next;
		}
		p1_elements = p1_elements->next;
	}
	return 	product;
	}
void displayPolynomial(Polynomial* poly){
	Term *element = poly->head;
	int firstEle = 0;
	while (element){
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

void freePolynomial(Polynomial* p) {
    Term* current = p->head;
    while (current) {
        Term* next = current->next;
        free(current);
        current = next;
    }
    free(p);
}

int main(){
	int p1_size,p2_size;
	printf("We are going to create 2 polynomials, then get sum and product of them\n");
	printf("Enter number of terms in polynomial 1:\t");
	scanf("%d",&p1_size);
	Polynomial* p1 = generatePolynomial(p1_size);
	printf("Enter number of terms in polynomial 2:\t");
	scanf("%d",&p2_size);
	Polynomial* p2 = generatePolynomial(p2_size);
	Polynomial* sum = sumOfPolynomial(p1,p2);
	Polynomial* product = productOfPolynomial(p1,p2);

	printf("p1: ");
	displayPolynomial(p1);
	printf("p2: ");
	displayPolynomial(p2);
	printf("sum: ");
	displayPolynomial(sum);
	printf("product: ");
	displayPolynomial(product);
	
	freePolynomial(p1);
  freePolynomial(p2);
  freePolynomial(sum);
  freePolynomial(product);

	return 0;
	
}


