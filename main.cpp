#include <stdio.h>
#include <string.h>
#include <iostream>


// Definieren aller global benötigten Variablen
char spielfeld[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
int spieler = 1;

// Definieren aller benötigten Methoden
void spielfeldAusgeben();
int spielStatusPruefen();
void spielerZug();
void spielerWechseln();
void spielSpeichern();
void spielLaden();

// Main Methode
int main() {

    int spielStatus;

    do {
        spielfeldAusgeben();
        spielerZug();
        spielStatus = spielStatusPruefen();
    } while (spielStatus == 0);

    return 0;
}

// Ausgeben des Spielfeldes auf der Konsole
void spielfeldAusgeben() {

    printf("\nTic-Tac-Toe\n");

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
    } else {
        return 0;
    }
}

void spielerZug() {

    char eingabe;
    char spielerSymbol;


    if (spieler == 1) {
        spielerSymbol = 'X';
    } else if (spieler == 2) {
        spielerSymbol = 'O';
    }

    printf("Spieler %d, waehle ein Feld: ", spieler);
    fflush(stdin);
    scanf("%c", &eingabe);
    printf("\n");

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
        spielSpeichern();
    } else {
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

void spielSpeichern() {

    FILE *datei;

    char spielName[100];

    printf("Name unter dem das Spiel gespeichert werden soll: ");
    scanf("%s", spielName);

    datei = fopen(strcat(spielName, ".txt"), "w");

    if(datei != NULL) {
        fprintf(datei, "%s", spielfeld);
    } else {
        printf("Fehler beim Speichern!\n");
    }
    fclose(datei);
}

void spielLaden() {

        FILE *datei;

        char spielName[100];
        char zeichen;
        int i = 0;

        printf("Name des gespeicherten Spiels: ");
        scanf("%s", spielName);

        datei = fopen(strcat(spielName, ".txt"), "r");

        if(datei != NULL) {
            do {
                zeichen = fgetc(datei);
                spielfeld[i] = zeichen;
                i++;
            } while (zeichen != EOF);
        } else {
            printf("Fehler beim Laden!\n");
        }
        fclose(datei);
}