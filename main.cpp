#include <stdio.h>
#include <string.h>
#include <iostream>


// Definieren aller global benötigten Variablen
char spielfeld[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
int spieler = -1;
int spielStatus = -1;
char spielerSymbol = '0';

// Definieren aller benötigten Methoden
void spielfeldAusgeben();

int spielStatusPruefen();

void spielerEingabe();

void spielerWechseln();

bool spielSpeichern();

bool spielLaden();

void spielStart();

// Main Methode
int main() {

    char eingabe;

    do {
        printf("\n");
        printf("Tic Tac Toe Hauptmenu\n");
        printf("1 - Neues Spiel erstellen\n");
        printf("2 - Gepeichertes Spiel Laden\n");
        printf("3 - Programm beenden\n");
        printf("\n");

        printf("Bitte eine Zahl zwischen 1 und 3 eingeben: ");
        fflush(stdin);
        scanf("%c", &eingabe);

        switch (eingabe) {
            case '1':
                printf("\n");
                printf("Neues Spiel wird erstellt...\n");
                for (int i = 0; i < sizeof(spielfeld); i++) {
                    spielfeld[i] = i + 1 + '0';
                }
                spielStart();
                break;
            case '2':
                printf("\n");
                printf("Ladevorgang wird gestartet...\n");
                if (spielLaden()) {
                    printf("\n");
                    printf("Spiel wurde erfolgreich geladen!\n");
                    spielStart();
                } else {
                    printf("\n");
                    printf("Laden fehlgeschlagen!\n");
                }
                break;
            case '3':
                printf("\n");
                printf("Programm wird beendet...\n");
                exit(0);
            default:
                printf("\n");
                printf("Ungueltige Eingabe!\n");
                break;
        }

    } while (eingabe != 3);


    return 0;
}

void spielStart() {

    spielStatus = 0;
    spieler = 1;

    // TODO: Abfrage Bot oder Multiplayer
    // TODO: Implemantation Bot

    do {
        spielfeldAusgeben();
        spielerEingabe();
        spielStatus = spielStatusPruefen();
    } while (spielStatus == 0);

    if (spielStatus != 3) {
        spielfeldAusgeben();
    }


    if (spielStatus == 1) {
        printf("\n");
        printf("Spieler %d (%c) hat gewonnen!\n", spieler, spielerSymbol);
    } else if (spielStatus == 2) {
        printf("\n");
        printf("Spiel wurde unentschieden beendet!\n");
    }

}


// Ausgeben des Spielfeldes auf der Konsole
void spielfeldAusgeben() {

    printf("\n");
    printf(" %c | %c | %c\n", spielfeld[0], spielfeld[1], spielfeld[2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c\n", spielfeld[3], spielfeld[4], spielfeld[5]);
    printf("---|---|---\n");
    printf(" %c | %c | %c\n", spielfeld[6], spielfeld[7], spielfeld[8]);


}

// Spielstatus überprüfen
// 0 -> Spiel noch nicht beendet
// 1 -> Spiel wurde gewonnen
// 2 -> Spiel wurde unentschieden beendet
// 3 -> Spiel wurde beendet/gespeichert
int spielStatusPruefen() {

    if (
        // Horizontal
            spielfeld[0] == spielfeld[1] && spielfeld[1] == spielfeld[2] ||
            spielfeld[3] == spielfeld[4] && spielfeld[4] == spielfeld[5] ||
            spielfeld[6] == spielfeld[7] && spielfeld[7] == spielfeld[8] ||
            // Vertikal
            spielfeld[0] == spielfeld[3] && spielfeld[3] == spielfeld[6] ||
            spielfeld[1] == spielfeld[4] && spielfeld[4] == spielfeld[7] ||
            spielfeld[2] == spielfeld[5] && spielfeld[5] == spielfeld[8] ||
            // Diagonal
            spielfeld[0] == spielfeld[4] && spielfeld[4] == spielfeld[8] ||
            spielfeld[2] == spielfeld[4] && spielfeld[4] == spielfeld[6]) {
        return 1;
    } else if (spielfeld[0] != '1' && spielfeld[1] != '2' && spielfeld[2] != '3' &&
               spielfeld[3] != '4' && spielfeld[4] != '5' && spielfeld[5] != '6' &&
               spielfeld[6] != '7' && spielfeld[7] != '8' && spielfeld[8] != '9') {
        return 2;
    } else if (spielStatus == 3) {
        return 3;
    } else {
        return 0;
    }
}

void spielerEingabe() {

    char eingabe;

    if (spieler == 1) {
        spielerSymbol = 'X';
    } else if (spieler == 2) {
        spielerSymbol = 'O';
    }

    printf("\n");
    printf("Spieler %d (%c) ist am Zug!\n", spieler, spielerSymbol);
    printf("Bitte waehle ein freies Spielfeld aus\n");
    printf("oder 's' um das Spiel zu speichern\n");
    printf("oder 'q' um das Spiel zu beenden\n");
    printf("Deine Eingabe: ");
    fflush(stdin);
    scanf("%c", &eingabe);

    if (eingabe == '1' && spielfeld[0] == '1') {
        spielfeld[0] = spielerSymbol;
    } else if (eingabe == '2' && spielfeld[1] == '2') {
        spielfeld[1] = spielerSymbol;
    } else if (eingabe == '3' && spielfeld[2] == '3') {
        spielfeld[2] = spielerSymbol;
    } else if (eingabe == '4' && spielfeld[3] == '4') {
        spielfeld[3] = spielerSymbol;
    } else if (eingabe == '5' && spielfeld[4] == '5') {
        spielfeld[4] = spielerSymbol;
    } else if (eingabe == '6' && spielfeld[5] == '6') {
        spielfeld[5] = spielerSymbol;
    } else if (eingabe == '7' && spielfeld[6] == '7') {
        spielfeld[6] = spielerSymbol;
    } else if (eingabe == '8' && spielfeld[7] == '8') {
        spielfeld[7] = spielerSymbol;
    } else if (eingabe == '9' && spielfeld[8] == '9') {
        spielfeld[8] = spielerSymbol;
    } else if (eingabe == 's' || eingabe == 'S') {
        if (spielSpeichern()) {
            printf("\n");
            printf("Spiel wurde erfolgreich gespeichert!\n");
            spielStatus = 3;
        } else {
            printf("\n");
            printf("Fehler beim Speichern des Spiels, setzte Spiel fort...\n");
        }
    } else if (eingabe == 'q' || eingabe == 'Q') {
        spielStatus = 3;
        printf("\n");
        printf("Spiel wurde beendet.\n");
    } else {
        printf("\n");
        printf("Ungueltige Eingabe!\n");
        spielerWechseln();
    }

    spielerWechseln();
}

void spielerWechseln() {
    if (spieler == 1) {
        spieler = 2;
    } else if (spieler == 2) {
        spieler = 1;
    }
}

bool spielSpeichern() {

    FILE *datei;

    char spielName[100];

    printf("\n");
    printf("Name unter dem das Spiel gespeichert werden soll: ");
    fflush(stdin);
    scanf("%s", spielName);

    datei = fopen(strcat(spielName, ".txt"), "w");

    if (datei != NULL) {
        fprintf(datei, "%s", spielfeld);
        fclose(datei);
        return true;
    } else {
        fclose(datei);
        return false;
    }

}

bool spielLaden() {

    FILE *datei;

    char spielName[100];
    char zeichen;
    int i = 0;

    printf("\n");
    printf("Name des gespeicherten Spiels: ");
    fflush(stdin);
    scanf("%s", spielName);

    datei = fopen(strcat(spielName, ".txt"), "r");

    if (datei != NULL) {
        // TODO: Richter Spieler Anfangen
        do {
            zeichen = fgetc(datei);
            spielfeld[i] = zeichen;
            i++;
        } while (zeichen != EOF);
        fclose(datei);
        return true;
    } else {
        fclose(datei);
        return false;
    }
}