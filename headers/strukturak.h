#ifndef STRUKTURAK_H_INCLUDED
#define STRUKTURAK_H_INCLUDED

// Csoport struktúra
typedef struct {
    struct Csoport *next;
    char* csoportvez;
    char* csoportkod;
} Csoport;

// Hallgató struktúra
typedef struct Hallgato {
    struct Hallgato *next;
    char nev[30];
    char neptun[7];
    char gyakorlatCsoport[4];
    char eloadasCsoport[4];
    int hianyzasok[14];
    int kisZH[6];
    int nagyZH[2];
    int nagyHF;
    int dbKisZh;
    int pontszamKisZh;
    int dbNagyZh;
    int pontszamNagyZh;
    int pontszam;
    int potolni;
} Hallgato;


#endif // STRUKTURAK_H_INCLUDED
