#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "debugmalloc.h"
#include "strukturak.h"
#include "fajl_kezeles.h"
#include "ranglista.h"
#include "potlas.h"

// A hallhat�k pontsz�m�nak kisz�m�t�sa
Hallgato* pontszamokSzamolasa(Hallgato *head) {
    Hallgato *current = head;
    while (current != NULL) {
        current->dbKisZh = current->dbNagyZh = current->pontszamKisZh = current->pontszamNagyZh = current->pontszam = current->potolni = 0;

        //Legjobb kisz�rthelyi eredm�nyek
        int i = 0;
        while (i < 6) {
            if (i == 0 || current->kisZH[i-1] >= current->kisZH[i]) { /* j� sorrend? */
                i++;                /* el�re */
            } else {
                double tmp = current->kisZH[i];  /* csere */
                current->kisZH[i] = current->kisZH[i-1];
                current->kisZH[i-1] = tmp;
                i--;                /* vissza */
            }
        }
        // Kis z�rthelyi pontsz�mok �s darabok kisz�mol�sa
        for (int j = 0; j < 6; j++) {
            if (current->kisZH[j] > 0 && current->dbKisZh != 4) {
                current->pontszamKisZh += current->kisZH[j];
                current->dbKisZh++;
            }
        }

        // Nagy z�rthelyi pontsz�mok �s darabok kisz�mol�sa
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

// Seg�d f�ggv�nyek a rangsorhoz
int compare(const void *a, const void *b) {
    // Cs�kken� sorrend: visszat�r�si �rt�k negat�v, ha a < b
    // �s pozit�v, ha a > b, 0, ha a == b
    return (*(Hallgato *)b).pontszam - (*(Hallgato *)a).pontszam;
}
int compareN(const void *a, const void *b) {
    // Cs�kken� sorrend: visszat�r�si �rt�k negat�v, ha a < b
    // �s pozit�v, ha a > b, 0, ha a == b
    return (*(Hallgato *)b).pontszamNagyZh - (*(Hallgato *)a).pontszamNagyZh;
}
int compareK(const void *a, const void *b) {
    // Cs�kken� sorrend: visszat�r�si �rt�k negat�v, ha a < b
    // �s pozit�v, ha a > b, 0, ha a == b
    return (*(Hallgato *)b).pontszamKisZh - (*(Hallgato *)a).pontszamKisZh;
}
int compareHF(const void *a, const void *b) {
    // Cs�kken� sorrend: visszat�r�si �rt�k negat�v, ha a < b
    // �s pozit�v, ha a > b, 0, ha a == b
    return (*(Hallgato *)b).nagyHF - (*(Hallgato *)a).nagyHF;
}
// L�ncolt lista dinamikus t�mbbe m�sol�sa pontsz�m alapj�n
void listaTombbe(Hallgato* head, int* tombMeret, Hallgato** tomb) {
    // L�ncolt lista elemeinek sz�ma
    int meret = 0;
    Hallgato* current = head;
    while (current != NULL) {
        meret++;
        current = current->next;
    }

    // Dinamikus t�mb�t allok�l�sa
    *tomb = (Hallgato*)malloc(meret * sizeof(Hallgato));
    if (*tomb == NULL) {
        fprintf(stderr, "Hiba a memoriafoglalas soran.\n");
        exit(EXIT_FAILURE);
    }

    // Elemek �tm�sol�sa a l�ncolt list�b�l a dinamikus t�mbbe
    current = head;
    for (int i = 0; i < meret; i++) {
        strcpy((*tomb)[i].nev, current->nev);
        (*tomb)[i].pontszam = current->pontszam;
        current = current->next;
    }

    // T�mb m�ret�nek be�ll�t�sa
    *tombMeret = meret;
}
// L�ncolt lista dinamikus t�mbbe m�sol�sa Nagy Zh pontsz�m alapj�n
void listaTombbeN(Hallgato* head, int* tombMeret, Hallgato** tomb) {
    // L�ncolt lista elemeinek sz�ma
    int meret = 0;
    Hallgato* current = head;
    while (current != NULL) {
        meret++;
        current = current->next;
    }

    // Dinamikus t�mb�t allok�l�sa
    *tomb = (Hallgato*)malloc(meret * sizeof(Hallgato));
    if (*tomb == NULL) {
        fprintf(stderr, "Hiba a memoriafoglalas soran.\n");
        exit(EXIT_FAILURE);
    }

    // Elemek �tm�sol�sa a l�ncolt list�b�l a dinamikus t�mbbe
    current = head;
    for (int i = 0; i < meret; i++) {
        strcpy((*tomb)[i].nev, current->nev);
        (*tomb)[i].pontszamNagyZh = current->pontszamNagyZh;
        current = current->next;
    }

    // T�mb m�ret�nek be�ll�t�sa
    *tombMeret = meret;
}
// L�ncolt lista dinamikus t�mbbe m�sol�sa Kis Zh pontsz�m alapj�n
void listaTombbeK(Hallgato* head, int* tombMeret, Hallgato** tomb) {
    // L�ncolt lista elemeinek sz�ma
    int meret = 0;
    Hallgato* current = head;
    while (current != NULL) {
        meret++;
        current = current->next;
    }

    // Dinamikus t�mb�t allok�l�sa
    *tomb = (Hallgato*)malloc(meret * sizeof(Hallgato));
    if (*tomb == NULL) {
        fprintf(stderr, "Hiba a memoriafoglalas soran.\n");
        exit(EXIT_FAILURE);
    }

    // Elemek �tm�sol�sa a l�ncolt list�b�l a dinamikus t�mbbe
    current = head;
    for (int i = 0; i < meret; i++) {
        strcpy((*tomb)[i].nev, current->nev);
        (*tomb)[i].pontszamKisZh = current->pontszamKisZh;
        current = current->next;
    }

    // T�mb m�ret�nek be�ll�t�sa
    *tombMeret = meret;
}
// L�ncolt lista dinamikus t�mbbe m�sol�sa Nagy HF pontsz�m alapj�n
void listaTombbeHF(Hallgato* head, int* tombMeret, Hallgato** tomb) {
    // L�ncolt lista elemeinek sz�ma
    int meret = 0;
    Hallgato* current = head;
    while (current != NULL) {
        meret++;
        current = current->next;
    }

    // Dinamikus t�mb�t allok�l�sa
    *tomb = (Hallgato*)malloc(meret * sizeof(Hallgato));
    if (*tomb == NULL) {
        fprintf(stderr, "Hiba a memoriafoglalas soran.\n");
        exit(EXIT_FAILURE);
    }

    // Elemek �tm�sol�sa a l�ncolt list�b�l a dinamikus t�mbbe
    current = head;
    for (int i = 0; i < meret; i++) {
        strcpy((*tomb)[i].nev, current->nev);
        (*tomb)[i].nagyHF = current->nagyHF;
        current = current->next;
    }

    // T�mb m�ret�nek be�ll�t�sa
    *tombMeret = meret;
}
// Rangsorok ki�r�sa
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
    printf("\nA hallgatok rangsora Nagy H�zi Feladat pontok alapjan: \n");

    for (int i = 0; i < meret; i++) {
        printf("%d. hely %s, Pontszam: %d\n", i+1, tomb[i].nev, tomb[i].nagyHF);
    }
}
