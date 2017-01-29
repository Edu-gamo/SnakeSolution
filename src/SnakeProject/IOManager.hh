#pragma once
#include <rapidxml_utils.hpp>
#include <rapidxml_iterators.hpp>
#include <rapidxml_print.hpp>
#include <rapidxml.hpp>
#include <iostream>  
#include <fstream>
#include <string>

#define archivoRanking "ranking.dat"
#define archivoConfiguacion "configuracion.dat"

using namespace std;

namespace IOManager {
	void openingConfiguration(string difficulty) {
		rapidxml::file<> xmlFile(archivoConfiguacion);
		rapidxml::xml_document<> doc;
		doc.parse<0>(xmlFile.data());
		std::cout << "Nombre de la raiz: " << doc.first_node()->name() << "\n";
	}

	void introducirRanking(string nombre, int score) {
		char final = ';';
		int scorein = score;

		ofstream fsalida("ranking.dat", ios::out | ios::app | ios::binary);

		fsalida.write((nombre.c_str()), nombre.size());
		fsalida.write(reinterpret_cast<char *>(&final), sizeof(final));
		fsalida.write(reinterpret_cast<char *>(&scorein), sizeof(scorein));

		fsalida.close();
	}
	
	vector<pair<string, int>> leerRanking() {
		vector<pair<string, int>> ranking;

		bool cond = false;
		string pruebachar;
		int pruebaint;

		ifstream fentrada(archivoRanking, ios::in | ios::binary);

		if (fentrada.is_open()) {
			while (!fentrada.eof()) {
				if (!cond) {
					getline(fentrada, pruebachar, ';');
					cond = true;
				} else {
					fentrada.read(reinterpret_cast<char *>(&pruebaint), sizeof(pruebaint));
					ranking.push_back(make_pair(pruebachar, pruebaint));
					cond = false;
				}	
			}
		}
		else {
			cout << "No hay ninguna puntuacion" << endl;
		}
		fentrada.close();

		return ranking;
	}
}