#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct _Element;
typedef struct _Element* Position;
typedef struct _Element {
	int coefficient;
	int exponent;
	Position next;
} Element;

Position NEWELEMENT(int coefficient, int exponent);
int read_file(Position headpoly1, Position headpoly2);
int InsertSorted(Position head, int coefficient, int exponent);
void ispis(Position head);
int add(Position head, Position head1, Position head2);
int multiply(Position head, Position head1, Position head2);

int main() {

	Element headpoly1 = { .coefficient = 0, .exponent = 0, .next = NULL };
	Element headpoly2 = { .coefficient = 0, .exponent = 0, .next = NULL };
	Element headpolyadd = { .coefficient = 0, .exponent = 0, .next = NULL };
	Element headpolymultiply = { .coefficient = 0, .exponent = 0, .next = NULL };
	char* fileName = "polynoms.txt";

	read_file(&headpoly1, &headpoly2);
	ispis(&headpoly1);
	ispis(&headpoly2);
	add(&headpolyadd, &headpoly1, &headpoly2);
	ispis(&headpolyadd);
	multiply(&headpolymultiply, &headpoly1, &headpoly2);
	ispis(&headpolymultiply);

	return 0;
}

void ispis(Position head) {
	if (head->next == NULL) {
		printf("Lista je prazna ili nema elemenata za ispis.\n");
		return;
	}

	head = head->next;

	while (head != NULL) {
		printf("%dx^%d ", head->coefficient, head->exponent);
		head = head->next;
	}
	printf("\n");
}

Position NEWELEMENT(int coefficient, int exponent) {
	Position new = NULL;
	new = (Position)malloc(sizeof(Element));

	if (!new) {
		printf("Nije uspilo napravit new!");
		return NULL;
	}

	new->coefficient = coefficient;
	new->exponent = exponent;
	new->next = NULL;

	return new;
}

int read_file(Position headpoly1, Position headpoly2) {

	FILE* filepointer;
	int coefficient = 0, exponent = 0;
	char temp = 0;

	filepointer = fopen("polynoms.txt", "r");
	if (!filepointer) {
		printf("MISTAKE!");
		return EXIT_FAILURE;
	}

	while (fscanf(filepointer, " %dx^%d%c", &coefficient, &exponent, &temp) == 3) {

		InsertSorted(headpoly1, coefficient, exponent);

		if (temp == '\n' || temp=='EOF') {
			break;
		}
	}

	while (fscanf(filepointer, "%dx^%d", &coefficient, &exponent) == 2) {

		InsertSorted(headpoly2, coefficient, exponent);
		fscanf(filepointer, "%c", &temp);

		if (temp == '\n' || temp=='EOF') {
			break;
		}
	}
	fclose(filepointer);
	return 0;
}

int InsertSorted(Position head, int coefficient, int exponent) {
	Position previous = NULL;
	Position current = NULL;
	Position newel;

	newel = NEWELEMENT(coefficient, exponent);

	current = head;
	if (head->next == NULL) {
		newel->next = head->next;
		head->next = newel;
		return 0;
	}

	current = head;
	while (current->next != NULL) {
		current = current->next;
	}
	while (head->next != NULL) {
		head = head->next;
		if (head->exponent == newel->exponent) {
			head->coefficient = head->coefficient + newel->coefficient;
			return 0;
		}
	}

	if (current->exponent == newel->exponent) {
		current->coefficient = current->coefficient + newel->coefficient;
		return 0;
	}

	newel->next = current->next;
	current->next = newel;

	return 0;
}

int add(Position head,Position head1, Position head2) {

	head1 = head1->next;
	while (head1 != NULL) {
		InsertSorted(head, head1->coefficient, head1->exponent);
		head1 = head1->next;
	}
	head2 = head2->next;
	while (head2 != NULL) {
		InsertSorted(head, head2->coefficient, head2->exponent);
		head2 = head2->next;
	}

	return 0;
}

int multiply(Position head, Position head1, Position head2) {

	Position current = NULL;
	head1 = head1->next;
	head2 = head2->next;
	current=head2;

	while (head1 != NULL) {
		while (head2 != NULL) {
			InsertSorted(head, head1->coefficient * head2->coefficient, head1->exponent + head2->exponent);
			head2 = head2->next;
		}
		head2 = current;
		head1 = head1->next;
	}

	return 0;
}