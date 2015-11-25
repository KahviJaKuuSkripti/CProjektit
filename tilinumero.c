#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <malloc.h>

typedef struct tili {
    int saldo;
    int tilinumero;
    char* tili_nimi;
} tili;

int tili_lisaa_rahaa(tili* t, int maara) {
    t->saldo += maara;

    return 0;
}

int tili_ota_rahaa(tili* t, int maara) {
    if (maara > t->saldo) {
        printf("Tilin rahat eivät riitä!\n");
        return 1; // Tilin rahat eivät riitä
    }

    t->saldo -= maara;

    return 0;
}

int avaa_tili(tili* t, int tilinumero) {
    t->tilinumero = tilinumero;
    int tili_tiedot_koko = sizeof(char) * (int)log10(tilinumero * 10.0) + strlen("tilit/.txt") + 1;
    t->tili_nimi = malloc(tili_tiedot_koko);
    snprintf(t->tili_nimi, tili_tiedot_koko, "tilit/%d.txt", tilinumero);

    FILE* tili_tiedot = fopen(t->tili_nimi, "r");

    if (tili_tiedot == NULL) {
        printf("Tiliä ei ole olemassa, luodaan se...\n");
        tili_tiedot = fopen(t->tili_nimi, "w");
        fprintf(tili_tiedot, "0");
        t->saldo = 0;
    }
    else {
        fscanf(tili_tiedot, "%d", &(t->saldo));
    }
    printf("Tilin saldo on: %d\n", t->saldo);

    fclose(tili_tiedot);
    return 0;
}

int sulje_tili(tili* t) {
    FILE* tili_tiedot = fopen(t->tili_nimi, "w");
    fprintf(tili_tiedot, "%d", t->saldo);
    fclose(tili_tiedot);
    free(t->tili_nimi);
    return 0;
}

int pyyda_toiminto(tili* t) {
    while (1) {
        printf("Anna toiminto. Kirjoita \"h\" saadaksesi ohjeita.\n");
        char toiminto;
        scanf("%c", &toiminto);

        int maara = 0;
        switch (toiminto) {
            case 'h':;
                printf("'n' = näytä tilinumero, 's' = näytä saldo, 't' = talleta, 'o' = ota, 'p' = poistu, 'h' = ohje\n");
                break;
            case 'n':;
                printf("Tilinumero: %d\n", t->tilinumero);
                break;
            case 't':;
                while (getchar() != '\n'); // Poista jäljelle jäänyt syöte
                printf("Anna määrä: ");
                scanf("%d", &maara);
                tili_lisaa_rahaa(t, maara);
                break;
            case 'o':;
                while (getchar() != '\n'); // Poista jäljelle jäänyt syöte
                printf("Anna määrä: ");
                scanf("%d", &maara);
                tili_ota_rahaa(t, maara);
                break;
            case 's':;
                printf("Tilin saldo on: %d\n", t->saldo);
                break;
            case 'p':;
                printf("Poistutaan.\n");
                return 0;
            default:
                printf("Toiminto ei kelpaa.\n");
        }
        while (getchar() != '\n'); // Poista jäljelle jäänyt syöte
    }
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Anna tilinumero");
        return 1;
    }

    tili t;

    int tilinumero = atol(argv[1]);

    int avaa_tili_tulos = avaa_tili(&t, tilinumero);
    if (avaa_tili_tulos != 0) {
        return avaa_tili_tulos;
    }

    pyyda_toiminto(&t);
    sulje_tili(&t);

    return 0;
}
