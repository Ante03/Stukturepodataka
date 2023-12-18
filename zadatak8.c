#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


struct _node;
typedef struct _node* Position;
typedef struct _node {
    int value;
    Position left;
    Position right;
} Node;

Position insert_Node(Position root, int value);
Position pronadi(Position root, int x);
Position Create_node(int value);
int postorder(Position root);
int preorder(Position root);
int inorder(Position root);

int main() {

    //Node head = { .value = 0, .left = NULL, .right = NULL };

    Position root = NULL;
    root = insert_Node(root, 5);


    while (1) {
        printf("1 - Stvori novu\n");
        printf("2 - Pronadi\n");
        printf("3 - Izbrisi\n");
        printf("4 - Ispisi preorder\n");
        printf("5 - Ispisi inorder\n");
        printf("6 - Ispisi postorder\n");
        printf("7 - Ispisi level order\n");
        printf("8 - Izadi\n");

        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int value = 0;
            printf("Unesite vrijednost:\n");
            scanf("%d", &value);
            insert_Node(root, value);
        }
        else if (choice == 2) {
            int value = 0;
            Position x = NULL;
            printf("Unesite vrijednost:\n");
            scanf("%d", &value);
            x = pronadi(root, value);
            if (x != NULL) {
                printf("\nPronaden je %d\n", value);
            }
            else
                printf("\nNije pronaden %d\n", value);
        }
        else if (choice == 3) {
            int value = 0;
            printf("Unesite vrijednost koju zelite izbrisati:");
            scanf("%d", &value);
            delete(root, value);
        }
        else if (choice == 4) {
            printf("\n");
            preorder(root);
            printf("\n");
        }
        else if (choice == 5) {
            printf("\n");
            inorder(root);
            printf("\n");
        }
        else if (choice == 6) {
            printf("\n");
            postorder(root);
            printf("\n");
        }
        else if (choice == 7) {

        }
        else if (choice == 8) {
            return 0;
        }
        else
            printf("UNIJELI STE KRIVU VRIJEDNOST!!");
    }


    return 0;
}

Position Create_node(int value) {
    Position newNode = NULL;

    newNode = (Position)malloc(sizeof(Node));
    if (!newNode) {
        printf("Nije se uspila napravit newNode");
        return NULL;
    }
    newNode->value = value;
    newNode->right = NULL;
    newNode->left = NULL;

    return newNode;
}

Position insert_Node(Position root, int value) {
    if (root == NULL) {
        return Create_node(value);
    }
    if (root->value > value) {
        root->left = insert_Node(root->left, value);
    }
    if (root->value <= value) {
        root->right = insert_Node(root->right, value);
    }

    return root;
}

Position pronadi(Position root, int x) {
    
    if (root == NULL || root->value == x) {
        return root;
    }

    if (x < root->value) {
        return pronadi(root->left, x);
    }

    return pronadi(root->right, x);
}

int inorder(Position root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->value);
        inorder(root->right);
    }
    return EXIT_SUCCESS;
}

int preorder(Position root) {
    if (root) {
        printf("%d ", root->value);
        preorder(root->left);
        preorder(root->right);
    }
    return EXIT_SUCCESS;
}

int postorder(Position root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->value);
    }
    return EXIT_SUCCESS;
}

Position delete(Position root, int value) {
    if (root == NULL)
        return root;

    if (value > root->value) {
        root->right=delete(root->right, value);
    }
    else if (value < root->value) {
        delete(root->left, value);
    }
    else {
        //zadnji clan
        if (root->left == NULL && root->right == NULL) {
            Position temp = root;
            free (temp);
            return NULL;
        }

        //jedan clan
        else if (root->left == NULL) {
            Position temp = root;
            Position tmp = root->right;
            free(temp);
            return tmp;
        }

        else if (root->right == NULL) {
            Position temp = root;
            Position tmp = root->left;
            free(temp);
            return tmp;
        }

        //dva clana
         Position temp = root->right;
         while (temp->left != NULL) {
             temp = temp->left;
         }
         root->value = temp->value;
         root->right = delete(root->right, temp->value);
    }
    return root;
}
