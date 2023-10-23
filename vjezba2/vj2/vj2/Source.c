#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE (50)
#define MAX_LINE (1024)
#define FILE_ERROR_OPEN (-1)

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

Position creating_n_p();
int add_to_list(Position head);
int print_list(Position head);
int add_to_end(Position head);

int main()
{
	int no_persons, i;
	Person* Persons;
	Person Head = { .next = NULL, .name = {0},
				.surname = {0}, .birthYear = 0 };

	printf("How many persons do you want to have?");
	scanf("%d", &no_persons);

	for (i = 0; i < no_persons; i++) {
		add_to_list(&Head);
	}

	add_to_list(&Head);
	print_list(&Head);
	add_to_end(&Head);
	print_list(&Head);

	return 0;
}

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

int add_to_list(Position head) {

	Position newPerson = NULL;
	newPerson = creating_n_p();

	newPerson->next = head->next;
	head->next = newPerson;

	return 0;
}

int print_list(Position head) {

	if (!head) {
		printf("Empty list!");
	}
	head = head->next;
	for (; head != NULL; head = head->next) {
		printf("%s		%s		%d\n", head->name, head->surname, head->birthYear);
	}

	return EXIT_SUCCESS;
}

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
