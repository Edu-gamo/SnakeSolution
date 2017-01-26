#pragma once
#include <rapidxml_utils.hpp>
#include <rapidxml_iterators.hpp>
#include <rapidxml_print.hpp>
#include <rapidxml.hpp>
#include <iostream>  
#include <fstream>
#include <string>

using namespace std;

namespace IOManager {
	void openingConfiguration(string difficulty) {
		rapidxml::file<> xmlFile("myXML.xml");
		rapidxml::xml_document<> doc;
		doc.parse<0>(xmlFile.data());

		std::cout << "Nombre de la raiz: " << doc.first_node()->name() << "\n";
	}

	void introducirRanking(string nombre, int score) {
		char tab = '\t', linea = ';';
		ofstream fsalida("ranking.dat", ios::out | ios::app | ios::binary);

		fsalida.write(reinterpret_cast<char *>(&nombre), nombre.size());
		fsalida.write(reinterpret_cast<char *>(&tab), sizeof(tab));
		fsalida.write(reinterpret_cast<char *>(&score), sizeof(score));
		fsalida.write(reinterpret_cast<char *>(&linea), sizeof(linea));
		fsalida.close();
	}

	/*vector<pair<string, double>>*/ void leerRanking() {
		ifstream fentrada("ranking.dat", ios::in | ios::binary);
		vector<pair<string, double>> ranking;
		char msn[256];
		int i = 0;
		
		if (fentrada.is_open()) {
			while (!fentrada.eof()) {
				fentrada.read(reinterpret_cast<char *>(&msn), sizeof(msn));
			}

			while (msn[i] != '\0') {
				cout << msn[i];
				i++;
			}
		} else {
			cout << "No hay ninguna puntuacion" << endl;
		}

		//return ranking;
	}
}