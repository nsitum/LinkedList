#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Person;
typedef struct Person person;
typedef person* Position;

struct Person {
    char first_name[16];
    char last_name[32];
    int birth_year;

    Position next;
};

person enter_data();
int choose_action(Position p, Position p2);
int insert_begenning(char ime[16], char prezime[32], int god_rod, Position head);
int insert_end(char ime[16], char prezime[32], int god_rod, Position p);
void print_list(Position p);
void find_osoba_by_prezime(Position p, char prezime[32]);
void delete_osoba_by_prezime(Position p, char prezime[32]);

Position find_element_before(Position p, char prezime[32]);
int insert_before(char ime[16], char prezime[32], int god_rod, Position p, char prezime2[32]);
int insert_after(char ime[16], char prezime[32], int god_rod, Position p, char prezime2[32]);
int write_to_file(Position p);
int read_file(Position p);
int get_count(Position p);
int sort_by_prezime(Position p);

void free_memory(Position pozicija);
void free_memory(Position lista1, Position lista2);

int main() {
    struct Person head;
    head.next = NULL;

    choose_action(&head);

    return 0;
}

person enter_data() {
    person student;

    printf("Unesi ime:\n");
    scanf("%s", student.first_name);

    printf("Unesi prezime:\n");
    scanf("%s", student.last_name);

    printf("Unesi godinu rodenja:\n");
    scanf("%d", &student.birth_year);

    return student;
}

int choose_action(Position p) {
    int counter, action, success, running = 1;

    person student;
    char last_name[32];

    while (running == 1) {
        printf("\nChoose action (0-10):\n");
        printf("1 - Dinamicki dodaj novi element na pocetak liste:\n");
        printf("2 - Ispisi listu:\n");
        printf("3 - Dinamicki dodaj novi element na kraj liste:\n");
        printf("4 - Pronadi element u listi (po prezimenu):\n");
        printf("5 - Obrisi element iz liste (po prezimenu):\n");
        printf("6 - Dodaj element prije odredenog prezimena:\n");
        printf("7 - Dodaj element nakon odredenog prezimena:\n");
        printf("8 - Upisi u datoteku:\n");
        printf("9 - Ispisi iz datoteke:\n");
        printf("10 - Sortiraj listu abecedno po prezimenu:\n");
        printf("0 - Zaustavi program):\n");
        printf("--------------------------------------------------\n");
        printf("Unesi broj: ");
        scanf("%d", &action);

        switch (action) {
        case 1:
            student = enter_data();
            success = insert_begenning(student.first_name, student.last_name, student.birth_year, p);

            if (success == -1) {
                printf("Zaustavljanje programa zbog neuspjesne alokacije memorije\n");
                free_memory(p);
                return 0;
            }
            break;
        case 2:
            print_list(p);
            break;
        case 3:
            student = enter_data();

            success = insert_end(student.first_name, student.last_name, student.birth_year, p);

            if (success == -1) {
                printf("Zaustavljanje programa zbog neuspjesne alokacije memorije\n");
                free_memory(p);
                return 0;
            }
            break;
        case 4:
            printf("Unesi prezime:\n");
            scanf("%s", last_name);
            find_osoba_by_prezime(p, last_name);
            break;
        case 5:
            printf("Unesi prezime:\n");
            scanf("%s", last_name);
            delete_osoba_by_prezime(p, last_name);
            break;
        case 6:
            printf("Unesi prezime prije kojeg zelis unijeti novi element:\n");
            scanf("%s", last_name);

            student = enter_data();
            success = insert_before(student.first_name, student.last_name, student.birth_year, p, last_name);

            if (success == -1) {
                printf("Zaustavljanje programa zbog neuspjesne alokacije memorije\n");
                free_memory(p);
                return 0;
            }
            break;
        case 7:
            printf("Unesi prezime nakon kojeg zelis unijeti novi element:\n");
            scanf("%s", last_name);

            student = enter_data();
            success = insert_after(student.first_name, student.last_name, student.birth_year, p, last_name);

            if (success == -1) {
                printf("Zaustavljanje programa zbog neuspjesne alokacije memorije\n");
                free_memory(p);
                return 0;
            }
            break;
        case 8:
            success = write_to_file(p);

            if (success == -2) {
                printf("Zaustavljanje programa zbog neuspjesnog otvaranja datoteke\n");
                free_memory(p);
                return 0;
            }
            break;
        case 9:
            success = read_file(p);

            if (success == -2) {
                printf("Zaustavljanje programa zbog neuspjesnog otvaranja datoteke\n");
                free_memory(p);
                return 0;
            }
            break;
        case 10:
            counter = get_count(p);
            for (int x = 0; x < counter; x++) {
                success = sort_by_prezime(p);
                if (success == -1) {
                    printf("Zaustavljanje programa zbog neuspjesne alokacije memorije\n");
                    free_memory(p);
                    return 0;
                }
            }
            break;
        case 0:
            printf("Stopping program...\n");
            free_memory(p);
            running = 0;
            break;
        default:
            break;
        }
    }

    return 0;
}

int insert_begenning(char ime[16], char prezime[32], int god_rod, Position head) {
    person* new_position = malloc(sizeof(person));

    if (new_position == NULL) {
        return -1;
    }

    strcpy(new_position->first_name, ime);
    strcpy(new_position->last_name, prezime);
    new_position->birth_year = god_rod;

    new_position->next = head->next;
    head->next = new_position;

    return 0;
}



int insert_end(char ime[16], char prezime[32], int god_rod, Position p) {
    person* new_position = malloc(sizeof(person));

    if (new_position == NULL) {
        return -1;
    }

    strcpy(new_position->first_name, ime);
    strcpy(new_position->last_name, prezime);
    new_position->birth_year = god_rod;

    while (p->next != NULL) {
        p = p->next;
    }

    new_position->next = p->next;
    p->next = new_position;

    return 0;
}

void print_list(Position p) {
    p = p->next;

    if (p == NULL) {
        printf("Lista je prazna\n");
    }

    while (p != NULL) {
        printf("%s %s %d\n", p->first_name, p->last_name, p->birth_year);
        p = p->next;
    }
}

void find_osoba_by_prezime(Position p, char prezime[32]) {
    p = p->next;
    while (p != NULL) {

        if (strcmp(p->last_name, prezime) == 0) {
            printf("\nFound person:\n%s %s %d\n\n", p->first_name, p->last_name, p->birth_year);
        }
        p = p->next;
    }
}

void delete_osoba_by_prezime(Position p, char prezime[32]) {
    while (p->next != NULL) {

        if (strcmp(p->next->last_name, prezime) == 0) {
            Position target = p->next;
            p->next = target->next;
            free(target);
            break;
        }
        p = p->next;
    }
}

Position find_element_before(Position p, char prezime[32]) {
    while (p->next != NULL) {

        if (strcmp(p->next->last_name, prezime) == 0) {
            return p;
        }
        p = p->next;
    }

    return NULL;
}

int insert_before(char ime[16], char prezime[32], int god_rod, Position p, char prezime2[32]) {
    person* new_position = malloc(sizeof(person));

    if (new_position == NULL) {
        return -1;
    }

    strcpy(new_position->first_name, ime);
    strcpy(new_position->last_name, prezime);
    new_position->birth_year = god_rod;

    p = find_element_before(p, prezime2);

    new_position->next = p->next;
    p->next = new_position;

    return 0;
}

int insert_after(char ime[16], char prezime[32], int god_rod, Position p, char prezime2[32]) {
    person* new_position = malloc(sizeof(person));

    if (new_position == NULL) {
        return -1;
    }

    strcpy(new_position->first_name, ime);
    strcpy(new_position->last_name, prezime);
    new_position->birth_year = god_rod;

    p = find_element_before(p, prezime2);

    new_position->next = p->next->next;
    p->next->next = new_position;
}

int write_to_file(Position p) {
    FILE* fp = NULL;

    fp = fopen("list.txt", "w");

    if (fp == NULL) {
        printf("Datoteka nije otvorena\n");
        return -2;
    }

    p = p->next;

    if (p == NULL) {
        printf("Lista je prazna\n");
        return;
    }

    while (p != NULL) {
        printf("%s %s %d\n", p->first_name, p->last_name, p->birth_year);
        fprintf(fp, "%s %s %d\n", p->first_name, p->last_name, p->birth_year);
        p = p->next;
    }

    fclose(fp);

    return 0;
}

int read_file(Position p) {
    FILE* fp = NULL;
    int success = 0;

    fp = fopen("list.txt", "r");

    if (fp == NULL) {
        printf("Datoteka nije otvorena\n");
        return -2;
    }

    char ime[16];
    char prezime[32];
    int god_rod;

    while (!feof(fp)) {
        fscanf(fp, "%s %s %d\n", ime, prezime, &god_rod);
        success = insert_end(ime, prezime, god_rod, p);

        if (success == -1) {
            return -1;
        }
    }

    return 0;
}

int get_count(Position p) {
    int counter = 0;
    while (p->next != NULL) {
        counter++;
        p = p->next;
    }
    printf("%d", counter);
    return counter;
}

int sort_by_prezime(Position p) {
    Position temp, temp2;
    temp = p;
    temp2 = p;

    int counter = 0, success = 0;

    while (temp->next != NULL) {
        counter++;
        temp = temp->next;
    }

    temp = p;

    int i, j, x, y;

    for (i = 0; i < counter - 1; i++) {

        temp = p;
        for (x = 0; x < i; x++) {
            temp = temp->next;
        }

        for (j = i + 1; j < counter; j++) {
            temp2 = p;
            for (y = 0; y < j;y++) {
                temp2 = temp2->next;
            }

            if (strcmp(temp->next->last_name, temp2->next->last_name) > 0) {
                success = insert_end(temp2->first_name, temp2->last_name, temp2->birth_year, p);

                if (success == -1) {
                    return -1;
                }

                delete_osoba_by_prezime(p, temp2->last_name);
            }
        }
    }

    return 0;
}

void free_memory(Position list) {
    while (list->next != NULL) {
        Position target = list->next;
        list->next = target->next;
        free(target);
    }
}