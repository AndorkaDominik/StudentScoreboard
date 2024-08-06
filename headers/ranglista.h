#ifndef RANGLISTA_H_INCLUDED
#define RANGLISTA_H_INCLUDED

// ranglista
Hallgato* pontszamokSzamolasa(Hallgato *head);
int compare(const void *a, const void *b);
int compareK(const void *a, const void *b);
int compareN(const void *a, const void *b);
int compareHF(const void *a, const void *b);
void listaTombbe(Hallgato* head, int* tombMeret, Hallgato** tomb);
void listaTombbeN(Hallgato* head, int* tombMeret, Hallgato** tomb);
void listaTombbeK(Hallgato* head, int* tombMeret, Hallgato** tomb);
void listaTombbeHF(Hallgato* head, int* tombMeret, Hallgato** tomb);
void kiirTomb(Hallgato* tomb, int meret);
void kiirTombN(Hallgato* tomb, int meret);
void kiirTombK(Hallgato* tomb, int meret);
void kiirTombHF(Hallgato* tomb, int meret);

#endif // RANGLISTA_H_INCLUDED
