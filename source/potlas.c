#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "debugmalloc.h"
#include "strukturak.h"
#include "fajl_kezeles.h"
#include "ranglista.h"
#include "potlas.h"


// A hallgató zh és hf pótlás kötelezettségének ellenõrzése
Hallgato* potlasEllenorzes(Hallgato *head){
    Hallgato *current = head;
    while (current != NULL) {
        current->potolni = 0;
        if(current->dbKisZh < 4 || current->pontszamKisZh < 20){
            current->potolni = 1;
        }
        if(current->pontszamNagyZh < 40 || current->nagyZH[0] == 0 || current->nagyZH[1]==0 || (current->nagyZH[0] == 0 && current->nagyZH[1] < 20 )){
            current->potolni = 1;
        }
        if(current->nagyHF == 0){
            current->potolni+=2;
        }
        current = current->next;
    }

    return head;
}

// A hallgató zh pótlásának kiírása
void zhPotlasKiiras(Hallgato *head){
    Hallgato *current = head;
    FILE *f =fopen("zhPot.txt", "w");
    if (f == NULL) {
        perror("Nem lehet megnyitni a fájlt!");
        return; /* vagy más módon "menekülünk" */
    }

    fprintf(f, "Hallgatok akiknek zh-t kell potolni:\n\n");

    while(current !=0){
        int i=1;
        if(current->potolni == 1 || current->potolni == 3){
            fprintf(f, "%s %s\n", current->nev, current->neptun);
        }
        current = current->next;
    }
    fclose(f);
}

// A hallgató hf pótlásának kiírása
void hfPotlasKiiras(Hallgato *head){
    Hallgato *current = head;
    FILE *f =fopen("hfPot.txt", "w");
    if (f == NULL) {
        perror("Nem lehet megnyitni a fájlt!");
        return; /* vagy más módon "menekülünk" */
    }

    fprintf(f, "Hallgatok akiknek nhf-t kell potolni:\n\n");

    while(current !=0){
        int i=1;
        if(current->potolni == 2 || current->potolni == 3){
            fprintf(f, "%s %s\n", current->nev, current->neptun);
        }
        current = current->next;
    }
    fclose(f);
}

