#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "debugmalloc.h"
#include "strukturak.h"
#include "fajl_kezeles.h"
#include "ranglista.h"
#include "potlas.h"

// A hallgatót hozzáadó függvény
Hallgato* hozzaadHallgato(Hallgato *head, Hallgato *uj) {
    if (head == NULL) {
        return uj;
    } else {
        Hallgato *current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = uj;
        return head;
    }
}

void adatokBeolvasasa(Hallgato **head) {
    FILE *file = fopen("mintafajl2.txt", "r");
    if (file == NULL) {
        perror("Hiba a fajl megnyitasakor");
        exit(EXIT_FAILURE);
    }

    char sor[256];
    while (fgets(sor, sizeof(sor), file) != NULL) {
        Hallgato *uj = (Hallgato*)malloc(sizeof(Hallgato));
        if (uj == NULL) {
            perror("Memóriafoglalási hiba");
            exit(EXIT_FAILURE);
        }
        uj->next = NULL;

        char *temp = strtok(sor, ";");
        strcpy(uj->nev, temp);

        temp = strtok(NULL, ";");
        strcpy(uj->neptun, temp);

        temp = strtok(NULL, ";");
        strcpy(uj->gyakorlatCsoport, temp);


        temp = strtok(NULL, ";");
        strcpy(uj->eloadasCsoport, temp);
        for (int i = 0; i < 14; i++) {
            temp = strtok(NULL, ";");
            uj->hianyzasok[i] = atoi(temp);
        }

        for (int i = 0; i < 6; i++) {
            temp = strtok(NULL, ";");
            uj->kisZH[i] = atoi(temp);
        }

        for (int i = 0; i < 2; i++) {
            temp = strtok(NULL, ";");
            uj->nagyZH[i] = atoi(temp);
        }
        temp = strtok(NULL, "\n");
        uj->nagyHF = atoi(temp);

        *head = hozzaadHallgato(*head, uj);
    }

    fclose(file);
}

void adatokFelszabaditasa(Hallgato *head) {
    while (head != NULL) {
        Hallgato *temp = head;
        head = head->next;
        free(temp);
    }
}

// A hallgatók kiírása
void kiirLista(Hallgato *head) {
    printf("\n------------------------------\n");
    printf("Hallgatok listaja:\n");
    Hallgato *current = head;
    while (current != NULL) {
        printf("%s %s %s %s", current->nev, current->neptun, current->gyakorlatCsoport, current->eloadasCsoport);

        printf("\t");
        for (int j = 0; j < 14; j++) {
            printf("%d ", current->hianyzasok[j]);
        }
        printf("\t");
        for (int j = 0; j < 6; j++) {
            printf("%d ", current->kisZH[j]);
        }
        printf("\t");
        for (int j = 0; j < 2; j++) {
            printf("%d ", current->nagyZH[j]);
        }
        printf("\t");
        printf("%d", current->nagyHF);
        printf("\t");
        printf("%d", current->dbKisZh);
        printf("\t");
        printf("%d", current->dbNagyZh);
        printf("\t");
        printf("%d", current->pontszamKisZh);
        printf("\t");
        printf("%d", current->pontszamNagyZh);
        printf("\t");
        printf("%d", current->pontszam);
        printf("\t");
        printf("%d", current->potolni);
        printf("\n");
        current = current->next;
    }
}
