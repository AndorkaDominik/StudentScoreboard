#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "debugmalloc.h"
#include "strukturak.h"
#include "fajl_kezeles.h"
#include "ranglista.h"
#include "potlas.h"


int main() {
    // láncolt lista első pointere
    Hallgato *hallgatok = NULL;
    // adatok beolvasása a fájlból
    adatokBeolvasasa(&hallgatok);
    // hallgatók pontszámának kiszámítása és láncolt listába írása
    hallgatok = pontszamokSzamolasa(hallgatok);
    // hallgatók pótlás kötelességének ellenőrzése és láncolt listába írása
    hallgatok = potlasEllenorzes(hallgatok);
    //Globális változók
    int mainChoice, subChoice;
    int tombMeret;
    Hallgato* tomb;
    // menü megjelenítése
    do {
        // Főmenü kiírása
        printf("-------------------------------------\n");
        printf("Fomenu:\n");
        printf("1. Kiirja a hallgatok adatait       1\n");
        printf("2. Potzh kotelezettek [Fajlba]      2\n");
        printf("3. PotNHF kotelezettek [Fajlba]     3\n");
        printf("4. Rangsor [Kepernyore]             4\n");
        printf("5. Kilepes                          5\n");
        printf("-------------------------------------\n\n");
        printf("Kerem irja be az opcio sorszamat: ");
        scanf("%d", &mainChoice);



        switch(mainChoice) {
            case 1:
                kiirLista(hallgatok);
                break;
            case 2:
                zhPotlasKiiras(hallgatok);
                printf("A pot zarthelyire kotelezettek listaja letrejott/megvaltozott.\n\n");
                break;
            case 3:
                hfPotlasKiiras(hallgatok);
                printf("A pot nagy hazifeladatra kotelezettek listaja letrejott/megvaltozott.\n\n");
                break;
            case 4:
                // Almenü
                do {
                    // Almenü kiírása
                    printf("-------------------------------------\n\n");
                    printf("\nMi alapjan rangsoroljon a program:\n");
                    printf("1. Nagy ZH pontok                  1\n");
                    printf("2. Kis ZH pontok                   2\n");
                    printf("3. Nagy HF pontok                  3\n");
                    printf("4. Osszpontszam                    4\n");
                    printf("5. Vissza a fomenuhoz              5\n");
                    printf("-------------------------------------\n\n");
                    printf("Kerem irja be az opcio sorszamat: ");

                    scanf("%d", &subChoice);

                    switch(subChoice) {
                        case 1:
                            listaTombbeN(hallgatok, &tombMeret, &tomb);
                            qsort(tomb, tombMeret, sizeof(Hallgato), compareN);
                            kiirTombN(tomb, tombMeret);
                            free(tomb);
                            break;
                        case 2:
                            listaTombbeK(hallgatok, &tombMeret, &tomb);
                            qsort(tomb, tombMeret, sizeof(Hallgato), compareK);
                            kiirTombK(tomb, tombMeret);
                            free(tomb);
                            break;
                        case 3:
                            listaTombbeHF(hallgatok, &tombMeret, &tomb);
                            qsort(tomb, tombMeret, sizeof(Hallgato), compareHF);
                            kiirTombHF(tomb, tombMeret);
                            free(tomb);
                            break;
                        case 4:
                            listaTombbe(hallgatok, &tombMeret, &tomb);
                            qsort(tomb, tombMeret, sizeof(Hallgato), compare);
                            kiirTomb(tomb, tombMeret);
                            free(tomb);
                            break;
                        case 5:
                            printf("Vissza a fomenube.\n");
                            break;
                        default:
                            printf("Ervenytelen opcio, kerlek valassz ujra.\n");
                    }
                } while(subChoice != 5);  // Amíg nem választja a visszatérést a főmenühöz
                break;

            case 5:
                printf("Kilepes.\n");
                break;

            default:
                printf("Ervenytelen opcio, kerlek valassz ujra.\n");
        }

    } while(mainChoice != 5);  // Amíg nem választja a kilépést



    // adatokFelszabadítása függvény meghívása
    adatokFelszabaditasa(hallgatok);

    return 0;
}
