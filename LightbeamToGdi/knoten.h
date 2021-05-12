#ifndef KNOTEN_H
#define KNOTEN_H

enum KnotenFarbe {WEISS,GRAU,SCHWARZ};
#define NIL -1
#define UNENDLICH INT_MAX

class Knoten
{
public:
    KnotenFarbe farbe;  // Farbmarkierung für Breitensuche
    int d;              // Distanz zum Startknoten bei der Breitensuche
    int vorgaenger;
    Knoten(){d=UNENDLICH; vorgaenger=NIL; farbe=WEISS; }
    std::string Name;
    // first Party
};

#endif // KNOTEN_H
