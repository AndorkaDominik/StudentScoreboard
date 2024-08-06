#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "debugmalloc.h"
#include "strukturak.h"
#include "fajl_kezeles.h"
#include "ranglista.h"
#include "potlas.h"

// A hallhatók pontszámának kiszámítása
Hallgato* pontszamokSzamolasa(Hallgato *head) {
    Hallgato *current = head;
    while (current != NULL) {
        current->dbKisZh = current->dbNagyZh = current->pontszamKisZh = current->pontszamNagyZh = current->pontszam = current->potolni = 0;

        //Legjobb kiszárthelyi eredmények
        int i = 0;
        while (i < 6) {
            if (i == 0 || current->kisZH[i-1] >= current->kisZH[i]) { /* jó sorrend? */
                i++;                /* elõre */
            } else {
                double tmp = current->kisZH[i];  /* csere */
                current->kisZH[i] = current->kisZH[i-1];
                current->kisZH[i-1] = tmp;
                i--;                /* vissza */
            }
        }
        // Kis zárthelyi pontszámok és darabok kiszámolása
        for (int j = 0; j < 6; j++) {
            if (current->kisZH[j] > 0 && current->dbKisZh != 4) {
                current->pontszamKisZh += current->kisZH[j];
                current->dbKisZh++;
            }
        }

        // Nagy zárthelyi pontszámok és darabok kiszámolása
        for (int j = 0; j < 2; j++) {
            if (current->nagyZH[j] > 0) {
                current->pontszamNagyZh += current->nagyZH[j];
                current->dbNagyZh++;
            }
        }

        current->pontszam = current->pontszamKisZh + current->pontszamNagyZh + current->nagyHF;
        current = current->next;
    }
    return head;
}

// Segéd függvények a rangsorhoz
int compare(const void *a, const void *b) {
    // Csökkenõ sorrend: visszatérési érték negatív, ha a < b
    // és pozitív, ha a > b, 0, ha a == b
    return (*(Hallgato *)b).pontszam - (*(Hallgato *)a).pontszam;
}
int compareN(const void *a, const void *b) {
    // Csökkenõ sorrend: visszatérési érték negatív, ha a < b
    // és pozitív, ha a > b, 0, ha a == b
    return (*(Hallgato *)b).pontszamNagyZh - (*(Hallgato *)a).pontszamNagyZh;
}
int compareK(const void *a, const void *b) {
    // Csökkenõ sorrend: visszatérési érték negatív, ha a < b
    // és pozitív, ha a > b, 0, ha a == b
    return (*(Hallgato *)b).pontszamKisZh - (*(Hallgato *)a).pontszamKisZh;
}
int compareHF(const void *a, const void *b) {
    // Csökkenõ sorrend: visszatérési érték negatív, ha a < b
    // és pozitív, ha a > b, 0, ha a == b
    return (*(Hallgato *)b).nagyHF - (*(Hallgato *)a).nagyHF;
}
// Láncolt lista dinamikus tömbbe másolása pontszám alapján
void listaTombbe(Hallgato* head, int* tombMeret, Hallgato** tomb) {
    // Láncolt lista elemeinek száma
    int meret = 0;
    Hallgato* current = head;
    while (current != NULL) {
        meret++;
        current = current->next;
    }

    // Dinamikus tömböt allokálása
    *tomb = (Hallgato*)malloc(meret * sizeof(Hallgato));
    if (*tomb == NULL) {
        fprintf(stderr, "Hiba a memoriafoglalas soran.\n");
        exit(EXIT_FAILURE);
    }

    // Elemek átmásolása a láncolt listából a dinamikus tömbbe
    current = head;
    for (int i = 0; i < meret; i++) {
        strcpy((*tomb)[i].nev, current->nev);
        (*tomb)[i].pontszam = current->pontszam;
        current = current->next;
    }

    // Tömb méretének beállítása
    *tombMeret = meret;
}
// Láncolt lista dinamikus tömbbe másolása Nagy Zh pontszám alapján
void listaTombbeN(Hallgato* head, int* tombMeret, Hallgato** tomb) {
    // Láncolt lista elemeinek száma
    int meret = 0;
    Hallgato* current = head;
    while (current != NULL) {
        meret++;
        current = current->next;
    }

    // Dinamikus tömböt allokálása
    *tomb = (Hallgato*)malloc(meret * sizeof(Hallgato));
    if (*tomb == NULL) {
        fprintf(stderr, "Hiba a memoriafoglalas soran.\n");
        exit(EXIT_FAILURE);
    }

    // Elemek átmásolása a láncolt listából a dinamikus tömbbe
    current = head;
    for (int i = 0; i < meret; i++) {
        strcpy((*tomb)[i].nev, current->nev);
        (*tomb)[i].pontszamNagyZh = current->pontszamNagyZh;
        current = current->next;
    }

    // Tömb méretének beállítása
    *tombMeret = meret;
}
// Láncolt lista dinamikus tömbbe másolása Kis Zh pontszám alapján
void listaTombbeK(Hallgato* head, int* tombMeret, Hallgato** tomb) {
    // Láncolt lista elemeinek száma
    int meret = 0;
    Hallgato* current = head;
    while (current != NULL) {
        meret++;
        current = current->next;
    }

    // Dinamikus tömböt allokálása
    *tomb = (Hallgato*)malloc(meret * sizeof(Hallgato));
    if (*tomb == NULL) {
        fprintf(stderr, "Hiba a memoriafoglalas soran.\n");
        exit(EXIT_FAILURE);
    }

    // Elemek átmásolása a láncolt listából a dinamikus tömbbe
    current = head;
    for (int i = 0; i < meret; i++) {
        strcpy((*tomb)[i].nev, current->nev);
        (*tomb)[i].pontszamKisZh = current->pontszamKisZh;
        current = current->next;
    }

    // Tömb méretének beállítása
    *tombMeret = meret;
}
// Láncolt lista dinamikus tömbbe másolása Nagy HF pontszám alapján
void listaTombbeHF(Hallgato* head, int* tombMeret, Hallgato** tomb) {
    // Láncolt lista elemeinek száma
    int meret = 0;
    Hallgato* current = head;
    while (current != NULL) {
        meret++;
        current = current->next;
    }

    // Dinamikus tömböt allokálása
    *tomb = (Hallgato*)malloc(meret * sizeof(Hallgato));
    if (*tomb == NULL) {
        fprintf(stderr, "Hiba a memoriafoglalas soran.\n");
        exit(EXIT_FAILURE);
    }

    // Elemek átmásolása a láncolt listából a dinamikus tömbbe
    current = head;
    for (int i = 0; i < meret; i++) {
        strcpy((*tomb)[i].nev, current->nev);
        (*tomb)[i].nagyHF = current->nagyHF;
        current = current->next;
    }

    // Tömb méretének beállítása
    *tombMeret = meret;
}
// Rangsorok kiírása
void kiirTomb(Hallgato* tomb, int meret) {
    printf("\nA hallgatok rangsora osszpontszam alapjan: \n");
    for (int i = 0; i < meret; i++) {
        printf("%d. hely %s, Pontszam: %d\n", i+1, tomb[i].nev, tomb[i].pontszam);
    }
}
void kiirTombN(Hallgato* tomb, int meret) {
    printf("\nA hallgatok rangsora Nagy Zh pontok alapjan: \n");
    for (int i = 0; i < meret; i++) {
        printf("%d. hely %s, Pontszam: %d\n", i+1, tomb[i].nev, tomb[i].pontszamNagyZh);
    }
}
void kiirTombK(Hallgato* tomb, int meret) {
    printf("\nA hallgatok rangsora Kis Zh pontok alapjan: \n");

    for (int i = 0; i < meret; i++) {
        printf("%d. hely %s, Pontszam: %d\n", i+1, tomb[i].nev, tomb[i].pontszamKisZh);
    }
}
void kiirTombHF(Hallgato* tomb, int meret) {
    printf("\nA hallgatok rangsora Nagy Házi Feladat pontok alapjan: \n");

    for (int i = 0; i < meret; i++) {
        printf("%d. hely %s, Pontszam: %d\n", i+1, tomb[i].nev, tomb[i].nagyHF);
    }
}
