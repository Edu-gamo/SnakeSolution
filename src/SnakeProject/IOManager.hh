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
		const char* nombrein = nombre.c_str();
		int scorein = score;
		char separacion = ';';
		char* nombreout = {};
		ofstream fsalida("ranking.dat", ios::out | ios::app | ios::binary);

		fsalida.write(reinterpret_cast<char *>(&nombrein), sizeof(nombrein));
		fsalida.write(reinterpret_cast<char *>(&scorein), sizeof(scorein));

		fsalida.close();

		/*ifstream fentrada("ranking.dat", ios::in | ios::binary);

		fentrada.read(reinterpret_cast<char *>(&nombreout), sizeof(nombreout));

		fentrada.close();

		cout << nombreout << endl;*/
	}
	
	/*vector<pair<char*, int>>*/ void leerRanking() {
		vector<pair<char*, int>> ranking;
		bool cond = false;
		char* pruebachar;
		int pruebaint;

		ifstream fentrada("ranking.dat", ios::in | ios::binary);

		if (fentrada.is_open()) {
			while (!fentrada.eof()) {
				if (!cond) {
					fentrada.read(reinterpret_cast<char *>(&pruebachar), sizeof(pruebachar));
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

		for (auto it = ranking.begin(); it != ranking.end(); ++it) {
			auto v_temp = *it;
			std::cout << v_temp.second << endl;
		
		}

		//return ranking;
	}

	void introducirRanking2(string nombre, int score) {
		const char* nombrein = nombre.c_str();
		int scorein = score, scoreout;
		char* nombreout = {};

		ofstream fsalida("ranking.dat", ios::out | ios::binary);

		fsalida.write(reinterpret_cast<char *>(&nombrein), sizeof(nombrein));
		fsalida.write(reinterpret_cast<char *>(&scorein), sizeof(scorein));

		fsalida.close();

		ifstream fentrada("ranking.dat", ios::in | ios::binary);

		fentrada.read(reinterpret_cast<char *>(&nombreout), sizeof(nombreout));
		fentrada.read(reinterpret_cast<char *>(&scoreout), sizeof(scoreout));

		fentrada.close();

		cout << nombreout << ' ' << scoreout << endl;
	}
}