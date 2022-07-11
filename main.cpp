#include <iostream>

// Definieren aller global benötigten Variablen
char spielfeld[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
int spieler = 1;

// Definieren aller benötigten Methoden
void spielfeldAusgeben();
int spielStatusPruefen();
void spielerZug();
void spielerWechseln();

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

    char gewähltesFeld;
    char spielerSymbol;


    if (spieler == 1) {
        spielerSymbol = 'X';
    } else if (spieler == 2) {
        spielerSymbol = 'O';
    }

    printf("Spieler %d, waehle ein Feld: ", spieler);
    fflush(stdin);
    scanf("%c", &gewähltesFeld);
    printf("\n");

    if (gewähltesFeld == '1' && spielfeld[0] == '1') {
        spielfeld[0] = spielerSymbol;
    } else if (gewähltesFeld == '2' && spielfeld[1] == '2') {
        spielfeld[1] = spielerSymbol;
    } else if (gewähltesFeld == '3' && spielfeld[2] == '3') {
        spielfeld[2] = spielerSymbol;
    } else if (gewähltesFeld == '4' && spielfeld[3] == '4') {
        spielfeld[3] = spielerSymbol;
    } else if (gewähltesFeld == '5' && spielfeld[4] == '5') {
        spielfeld[4] = spielerSymbol;
    } else if (gewähltesFeld == '6' && spielfeld[5] == '6') {
        spielfeld[5] = spielerSymbol;
    } else if (gewähltesFeld == '7' && spielfeld[6] == '7') {
        spielfeld[6] = spielerSymbol;
    } else if (gewähltesFeld == '8' && spielfeld[7] == '8') {
        spielfeld[7] = spielerSymbol;
    } else if (gewähltesFeld == '9' && spielfeld[8] == '9') {
        spielfeld[8] = spielerSymbol;
    } else {
        printf("Ungueltiger Zug!\n");
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
