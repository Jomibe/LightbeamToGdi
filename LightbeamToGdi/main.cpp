#include <iostream>
#include <fstream>
#include "Graph.h"
#include "knoten.h"

#define DEBUG_LASTHOSTNAME 0
#define DEBUG_GOTFPARTY 0
#define DEBUG_THIRDPARTIES 0
#define DEBUG_OUTPUT 0

/********************************
 * Jonas B, Marcus N  *
 * 11.05.2021                   *
 * GdI II, Miniprojekt-1        *
 ********************************/

using namespace std;

int main() {
	string lastHostname;
	string firstParty;
	string thirdParty;
	string line;
	size_t ende;

	int currentKnoten = 1;
	int KnotenLastFirst = 0;
    bool checkThirdPartyExists = 0;
    int KnotenExistingThirdParty = 0;
    Graph *g1 = new Graph();

    if(DEBUG_OUTPUT) {cout << "DEBUG : Starte mit dem Einlesen ... ";};

    //---------------------------------------------------------------------------------------------------------
    ifstream jsonimport ("lightbeamData.json"); if (jsonimport.is_open()) {
    	if(DEBUG_OUTPUT) {cout << "fertig" << endl;};
        while ( getline (jsonimport,line) ) { // Gesamten Inhalt der Datei einlesen
        	if(line.find("hostname\": \"")!= string::npos) {
        		lastHostname = line;
        		if(DEBUG_LASTHOSTNAME) {cout << "DEBUG : Found last hostname " << lastHostname.substr(17, lastHostname.size()-19) << endl;};
        	}

            if(line == "    \"firstParty\": true,") { // First Parties suchen ("firstParty": true)
            	if(DEBUG_GOTFPARTY) {cout << "DEBUG : Got first party ";};
                // First Parties identifizieren (hostname)
                firstParty = lastHostname.substr(17, lastHostname.size()-19); // letzte zwei Zeichen abschneiden, 17+2

                checkThirdPartyExists = false;
                for (int i = 1; i < currentKnoten; i++) { // gibt es bereits einen Knoten mit dem Namen der ThirdParty?
                    if(g1->V[i].Name == firstParty) {
                        checkThirdPartyExists = true;
                        KnotenLastFirst = i;
                    }
                }

                if(!checkThirdPartyExists) { // Pruefen ob Knoten mit Namen von ThirdParty bereits existiert
                    g1->V[currentKnoten].Name =firstParty;
                    KnotenLastFirst = currentKnoten;
                    currentKnoten++;
                }





                if(DEBUG_GOTFPARTY) {cout << firstParty << endl;};
            }
            //----------------------------------------------------------------------------------------------------------------------------------
            // Kanten von First Parties zu Third Parties ausgeben ("thirdParties": [)
            if(line == "    \"thirdParties\": [") { // Third Parties der letzten gefundenen First Party ausgeben
            	getline (jsonimport,line);
            	if(DEBUG_THIRDPARTIES) {cout << "DEBUG : Third Parties from " << firstParty << " are:" << endl;};
            	while(line != "    ]") {
                    thirdParty = line.substr(7); // Anfang wegkuerzen
                    ende = thirdParty.find("\""); // Ende finden, letzte ThirdParty endet mit " statt ",
                    thirdParty = thirdParty.substr(0, ende);
                    getline (jsonimport,line); // naechste Zeile
                    if(DEBUG_THIRDPARTIES) {cout << "DEBUG :  \\-> " << thirdParty << endl;};

                        // existiert die ThirdParty bereits bei einer anderen FirstParty?
                        // Prüfung, ob ThirdParty bereits existiert: falls ja, verwende den Knoten für die Kante; falls nein erstelle einen neuen
                    checkThirdPartyExists = false;
                        for (int i = 1; i < currentKnoten; i++) { // gibt es bereits einen Knoten mit dem Namen der ThirdParty?
                        	if(g1->V[i].Name == thirdParty) {
                        		checkThirdPartyExists = true;
                        		KnotenExistingThirdParty = i;
                        	}
                        }

                        if(checkThirdPartyExists) { // Pruefen ob Knoten mit Namen von ThirdParty bereits existiert
                            // falls dieser bereits existiert, erstelle Kante zu vorhandenem Knoten
                        	g1->insert_Edge(KnotenLastFirst, KnotenExistingThirdParty);
                        }
                        else {
                            // Falls dieser noch nicht existiert, erstelle neuen Knoten und Kante dazu
                            // Knoten erstellen
                        	g1->V[currentKnoten].Name = thirdParty;


                            // Kante erstellen
                        	g1->insert_Edge(KnotenLastFirst, currentKnoten);

                        	currentKnoten++;
                        }

                    }
                    //cout << endl;
                }

            }
            jsonimport.close();
        }


        else cout << "Unable to open file";

        g1->knotenzahl=currentKnoten-1;
        //g1.Graph_Debug(g1);
        //g1->ausgabe_gdi_format();

        std::ofstream outfile;
		outfile.open("ausgabe.gdi", std::ofstream::out | std::ofstream::trunc); // Datei wird vor dem Schreiben geleert
        if (outfile.is_open()) {
        	if(DEBUG_OUTPUT) {cout << "DEBUG : Schreibe erste Zeile in ausgabe.gdi ... ";};
        	string write ("G ");
        	write +=  std::to_string(g1->knotenzahl)+ "\n";
        	outfile << write;
        	if(DEBUG_OUTPUT) {cout << "fertig" << endl;};
        		for(int i=1; i<= g1->knotenzahl;i++){
        			if(g1->V[i].Name != ""){
        				if(DEBUG_OUTPUT) {cout << "DEBUG : Beginne Ausgabe des Knotens " << i << " in ausgabe.gdi ... ";};
        				outfile << "V " << i << " " << g1->V[i].Name << endl;
        				if(DEBUG_OUTPUT) {cout << "fertig" << endl;};
        					for(int j=1; j<=g1->knotenzahl; j++){
        						if(g1->Adj[i][j]==1){
        							if(DEBUG_OUTPUT) {cout << "DEBUG : Beginne Ausgabe der untergeordneten Knoten " << i << "-" << j << " in ausgabe.gdi ... ";};
        							write="E "+std::to_string(i)+" ";
        							write+=std::to_string(j)+" 1\n";
        							outfile << write;
        							if(DEBUG_OUTPUT) {cout << "fertig" << endl;};
        						}
        					}
        				}
        			}
        			outfile.close();
        		}

        		else cout << "Unable to open file";
        		return 0;
        	}
