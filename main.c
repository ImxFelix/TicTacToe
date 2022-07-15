/*****************************************************************************
* Projekt: Tic Tac Toe
* Dateiname: main.c
* Beschreibung: Tic Tac Toe mit Multiplayer/Singleplayer und Laden/Speichern
* Autoren: Dennis Pfender, Alex Nachname
* Matr.-Nr.: XXXXXX, XXXXXX
* Erstellt: 02.07.2022
*****************************************************************************/

// Einbinden der Bibliotheken
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

// Definieren der globalen Variablen
char spielfeld[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
int spieler = -1;
int spielStatus = -1;
int spielModus = -1;
char spielerSymbol = '0';
bool spielerZweiStartet = false;

// Initialisieren der Funktionen
void spielfeldAusgeben();

int spielStatusPruefen();

void spielerEingabe();

void spielerWechseln();

bool spielSpeichern();

bool spielLaden();

void spielStart();

void botZug();

/*
 * Main Methode, die das Hauptmenü beinhaltet
 */
int main() {

    char eingabe;

    // Hauptmenü, dass die Eingaben überprüft und die entsprechenden Funktionen aufruft
    do {
        // Ausgabe der Auswahlmöglichkeiten
        printf("\n");
        printf("Tic Tac Toe Hauptmenu\n");
        printf("1 - Neues Spiel erstellen\n");
        printf("2 - Gepeichertes Spiel Laden\n");
        printf("3 - Programm beenden\n");
        printf("\n");

        // Eingabe der Auswahlmöglichkeiten
        printf("Bitte eine Zahl zwischen 1 und 3 eingeben: ");
        fflush(stdin);
        scanf("%c", &eingabe);

        // Prüfen der Eingabe
        switch (eingabe) {
            case '1':
                printf("\n");
                printf("Neues Spiel wird erstellt...\n");
                // Spielfeld wird zurückgesetzt
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

/*
 * Das Spiel wird basierend auf den Eingaben im Hauptmenü gestartet
 */
void spielStart() {

    // Variablen auf Standardwert setzen
    spielStatus = 0;
    spielModus = -1;
    spieler = 1;

    // Abfrage des Spielmodus
    do {
        printf("\n");
        printf("Waehlen sie den Spielmodus\n");
        printf("1 - Spieler gegen Spieler\n");
        printf("2 - Spieler gegen Computer\n");
        printf("Ihre Eingabe: ");

        fflush(stdin);
        scanf("%d", &spielModus);

        // Prüfen, ob die Eingabe Gültig ist
        if (spielModus != 1 && spielModus != 2) {
            printf("\n");
            printf("Ungueltige Eingabe!\n");
        }
    } while (spielModus != 1 && spielModus != 2);

    // Basierend auf dem Spielmodus Spieler wechseln oder Computer-Zug durchführen, falls Spieler 2 Startet
    if (spielerZweiStartet == true) {
        if (spielModus == 1) {
            spielerWechseln();
        } else if (spielModus == 2) {
            botZug();
        }
        spielerZweiStartet = false;
    }

    // Spiel wird gestartet und solange durchgeführt, bis das Spiel beendet ist
    do {
        spielfeldAusgeben();
        spielerEingabe();
        spielStatus = spielStatusPruefen();

        // Basierend auf dem Spielmodus entweder den Spieler Wechseln oder den Computer-Zug durchführen
        if (spielStatus == 0) {
            if (spielModus == 1) {
                spielerWechseln();
            } else if (spielModus == 2) {
                botZug();
                // Prüfen ob der Computer gewonnen hat
                if (spielStatus = spielStatusPruefen() == 1) {
                    spielStatus = 4;
                }
            }
        }
    } while (spielStatus == 0);

    // Ausgabe des Spielstatus, ausgenommen das Spiel wurde gespeichert
    if (spielStatus != 3) {
        spielfeldAusgeben();
    }

    // Ausgabe der Spiel ergebnisse
    if (spielStatus == 1) {
        printf("\n");
        printf("Spieler %d (%c) hat gewonnen!\n", spieler, spielerSymbol);
    } else if (spielStatus == 2) {
        printf("\n");
        printf("Spiel wurde unentschieden beendet!\n");
    } else if (spielStatus == 4) {
        printf("\n");
        printf("Das Spiel wurde vom Computer gewonnen!\n");
    }
}

/*
 * Das Spielfeld wird ausgegeben
 */
void spielfeldAusgeben() {

    printf("\n");
    printf(" %c | %c | %c\n", spielfeld[0], spielfeld[1], spielfeld[2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c\n", spielfeld[3], spielfeld[4], spielfeld[5]);
    printf("---|---|---\n");
    printf(" %c | %c | %c\n", spielfeld[6], spielfeld[7], spielfeld[8]);
}

/*
 * Der Spielstatus wird geprüft
 * @return
 * 0 - Spiel noch nicht beendet
 * 1 - Spiel wurde gewonnen
 * 2 - Spiel wurde unentschieden beendet
 * 3 - Spiel wurde beendet/gespeichert
 * 4 - Spiel wurde von Computer gewonnen
 */
int spielStatusPruefen() {

    // Prüfen ob 3 Gleiche Symbole in einer Reihe/Spalte/Diagonale vorhanden sind
    // und ob das Spielfeld voll ist und somit ein Unentschieden ist
    if (
        // 3 Gleiche Symbole Horizontal
        spielfeld[0] == spielfeld[1] && spielfeld[1] == spielfeld[2] ||
        spielfeld[3] == spielfeld[4] && spielfeld[4] == spielfeld[5] ||
        spielfeld[6] == spielfeld[7] && spielfeld[7] == spielfeld[8] ||
        // 3 Gleiche Symbole Vertikal
        spielfeld[0] == spielfeld[3] && spielfeld[3] == spielfeld[6] ||
        spielfeld[1] == spielfeld[4] && spielfeld[4] == spielfeld[7] ||
        spielfeld[2] == spielfeld[5] && spielfeld[5] == spielfeld[8] ||
        // 3 Gleiche Symbole Diagonal
        spielfeld[0] == spielfeld[4] && spielfeld[4] == spielfeld[8] ||
        spielfeld[2] == spielfeld[4] && spielfeld[4] == spielfeld[6]) {
        return 1;
    } else if (
        spielfeld[0] != '1' && spielfeld[1] != '2' && spielfeld[2] != '3' &&
        spielfeld[3] != '4' && spielfeld[4] != '5' && spielfeld[5] != '6' &&
        spielfeld[6] != '7' && spielfeld[7] != '8' && spielfeld[8] != '9') {
        return 2;
    } else if (spielStatus == 3) {
        return 3;
    } else if (spielStatus == 4) {
        return 4;
    } else {
        return 0;
    }
}

/*
 * Die Spieleingabe eines Spielers wird geprüft und ausgeführt
 */
void spielerEingabe() {

    char eingabe;

    // Symbol wird basierend auf Spieler geändert
    if (spieler == 1) {
        spielerSymbol = 'X';
    } else if (spieler == 2) {
        spielerSymbol = 'O';
    }

    // Eingabe wird abgefragt
    printf("\n");
    printf("Spieler %d (%c) ist am Zug!\n", spieler, spielerSymbol);
    printf("Bitte waehle ein freies Spielfeld aus\n");
    printf("oder 's' um das Spiel zu speichern\n");
    printf("oder 'q' um das Spiel zu beenden\n");
    printf("Deine Eingabe: ");
    fflush(stdin);
    scanf("%c", &eingabe);

    // Eingabe wird geprüft
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
    }
}

/*
 * Methode, die einen automatischen Spielzug vom Computer ausführt
 */
void botZug() {

    bool feldGefunden = false;
    do {
        // Zufallszahl zwischen 1 und 9
        srand(time(NULL));
        int zufallsZahl = rand() % 9 + 1;

        // Prüft, ob die zufällig generierte Index im Spielfeld frei ist
        if (spielfeld[zufallsZahl] != 'X' && spielfeld[zufallsZahl] != 'O') {
            spielfeld[zufallsZahl] = 'O';
            feldGefunden = true;
        }
    } while (!feldGefunden);
}

/*
 * Der Spieler wird gewechselt
 */
void spielerWechseln() {
    if (spieler == 1) {
        spieler = 2;
    } else if (spieler == 2) {
        spieler = 1;
    }
}

/*
 * Das Spiel wird gespeichert
 * @return
 * true - Spiel konnte nicht gespeichert werden
 * false - Spiel wurde erfolgreich gespeichert
 */
bool spielSpeichern() {

    FILE *datei;

    char spielName[100];

    // Dateiname wird abgefragt
    printf("\n");
    printf("Name unter dem das Spiel gespeichert werden soll: ");
    fflush(stdin);
    scanf("%s", spielName);

    // Datei wird geöffnet
    datei = fopen(strcat(spielName, ".txt"), "w");

    // Datei wird geprüft
    if (datei != NULL) {
        fprintf(datei, "%s", spielfeld);
        fclose(datei);
        return true;
    } else {
        fclose(datei);
        return false;
    }
}

/*
 * Ein vorhandenes Spiel wird geladen
 * @return
 * true - Spiel wurde erfolgreich geladen
 * false - Spiel konnte nicht geladen werden
 */
bool spielLaden() {

    FILE *datei;

    char spielName[100];
    char zeichen;
    int i = 0;
    int anzahlZuegeX = 0;
    int anzahlZuegeO = 0;

    // Dateiname wird abgefragt
    printf("\n");
    printf("Name des gespeicherten Spiels: ");
    fflush(stdin);
    scanf("%s", spielName);

    // Datei wird geöffnet
    datei = fopen(strcat(spielName, ".txt"), "r");

    // Datei wird geprüft
    if (datei != NULL) {
        do {
            // Zeichen wird ausgelesen und in das Spielfeld geschrieben
            zeichen = fgetc(datei);
            spielfeld[i] = zeichen;

            // Prüft, ob das Zeichen ein X oder ein O ist und zählt die Anzahl der Züge
            if (zeichen == 'X') {
                anzahlZuegeX++;
            } else if (zeichen == 'O') {
                anzahlZuegeO++;
            }
            i++;
        } while (zeichen != EOF);

        // Prüft ob Spieler 2 am Zug ist
        if (anzahlZuegeO < anzahlZuegeX) {
            spielerZweiStartet = true;
        }

        fclose(datei);
        return true;
    } else {
        fclose(datei);
        return false;
    }
}