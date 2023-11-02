#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE (50)
#define MAX_LINE (1024)
#define EMPTY_LIST (-1)
#define NO_PERSON_FOUND_INT (-2)

//structure for person(name, surname and birth year)
struct _Person;
typedef struct _Person* Position;
typedef struct _Person
{
	char name[MAX_SIZE];
	char surname[MAX_LINE];
	int birthYear;
	Position next;
} Person;

//inicilizacija funkcija
Position creating_n_p();
int add_to_list(Position head);
int print_list(Position head);
int add_to_end(Position head);
int find_person(Position Head);
int menu(Position Head);
int delete_person(Position Head);
Position find_p_b(Position Head);

int main()
{
	int no_persons, i;
	int menureturn = 1;
	Person* Persons;
	Person Head = { .next = NULL, .name = {0},
				.surname = {0}, .birthYear = 0 };

	do {
		menu(&Head);
		menureturn = menu(&Head);
	} while (!menureturn);

	return 0;
}

//function for creating person
Position creating_n_p() {
	Position newPerson = NULL;

	newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson)
		printf("Error");

	printf("Name: ");
	scanf("%s", newPerson->name);
	printf("Surname: ");
	scanf("%s", newPerson->surname);
	printf("Birth year:");
	scanf("%d", &newPerson->birthYear);

	return newPerson;

}

//function to adding person at the first place of the list
int add_to_list(Position head) {

	Position newPerson = NULL;
	newPerson = creating_n_p();

	newPerson->next = head->next;
	head->next = newPerson;

	return 0;
}

//function for printing list
int print_list(Position head) {

	if (!head->next) {
		printf("prazna lista");
		return EXIT_FAILURE;
	}
	head = head->next;
	for (; head != NULL; head = head->next) {
		printf("%s		%s		%d\n", head->name, head->surname, head->birthYear);
	}

	return EXIT_SUCCESS;
}

//function for adding person at the end
int add_to_end(Position head) {

	Position newPerson = NULL;
	newPerson = creating_n_p();

	while (head->next != NULL) {
		head = head->next;
	}

	newPerson->next = NULL;
	head->next = newPerson;

	return 0;
}

//menu - here we let user to choose which function he wants to use
int menu(Position Head) {

	char selection = NULL;

	printf("Choose which function do you want to use: ");
	printf("\nPress 'a' for adding new person:");
	printf("\nPress 'e' for adding new person at the end of the list:");
	printf("\nPress 'p' for printing list:");
	printf("\nPress 'f' for finding person:");
	printf("\nPress 'd' for deleting person:");
	printf("\nPress 'x' for exit: \n");

	scanf(" %c", &selection);

	switch (selection) {
		case 'a':
			add_to_list(&Head);
			break;

		case  'e':
			add_to_end(&Head);
			break;

		case 'p':
			print_list(&Head);
			break;

		case 'f':
			find_person(&Head);
			break;

		case 'd':
			delete_person(&Head);
			break;

		case 'x':
			return 1;
			break;
	}

	return 0;
}

//function for finding person by surname
int find_person(Position Head) {
	
	if (!Head->next) {
		printf("prazna lista");
		return EXIT_FAILURE;
	}
	char surname[50] = { 0 };
	printf("\nUnesite prezime osobe koju zelite pronaci: \n");
	scanf(" %s", surname);

	while (Head != NULL) {
		if (strcmp(Head->surname, surname)==0) {
			printf("\nTa osoba je: %s %s %d.\n", Head->name, Head->surname, Head->birthYear);
			Head = Head->next;
		}
		else {
			Head = Head->next;
		}
	}

	return 0;
}

//function for deleting person
int delete_person(Position Head) {

	Position sadasnja;;
	Position prosla;
	if (!Head->next) {
		printf("prazna lista");
		return EXIT_FAILURE;
	}

	prosla=find_p_b(Head);
	if (!prosla)
		return EXIT_FAILURE;
	sadasnja=prosla->next;
	prosla->next = sadasnja->next;
	free(sadasnja);

	return 0;
}

//function for finding person 
//before the person that we need
Position find_p_b(Position Head) {

	int god = 0;
	Position trenutna=NULL, prethodna = NULL;

	if (!Head->next) {
		printf("prazna lista");
		return NULL;
	}

	printf("Unesite godiste osobe koju zelite pronaci?");
	scanf("%d", &god);

	trenutna = Head->next;
	prethodna = Head;

	while (trenutna) {
		if (god==trenutna->birthYear){
			return prethodna;
		}
		prethodna = trenutna;
		trenutna = trenutna->next;
	}
	printf("trazena osoba ne postoji!!!");
	return NULL;
}