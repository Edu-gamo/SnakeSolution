#pragma once
#include <rapidxml_utils.hpp>
#include <rapidxml_iterators.hpp>
#include <rapidxml_print.hpp>
#include <rapidxml.hpp>
#include <iostream>  
#include <fstream>
#include <string>
#include <sstream>

#define archivoRanking "ranking.dat"
#define archivoConfiguacion "myXML.xml"

using namespace std;

namespace IOManager {
	int consultarXML(string difficulty, string datoABuscar) {
		int datoARetornar= 0;
		string str1;

		rapidxml::xml_document<> doc;
		std::ifstream xmlFile(archivoConfiguacion);
		std::stringstream buffer;
		buffer << xmlFile.rdbuf();
		xmlFile.close();
		std::string content(buffer.str());
		doc.parse<0>(&content[0]);

		rapidxml::xml_node<> *pRoot = doc.first_node();
		for (rapidxml::xml_node<> *pNode = pRoot->first_node("difficulty"); pNode; pNode = pNode->next_sibling()) {
			rapidxml::xml_attribute<> *pAttr = pNode->first_attribute();
			if (pAttr->value() == difficulty) {
				for (rapidxml::xml_node<> *pNodeI = pNode->first_node(); pNodeI; pNodeI = pNodeI->next_sibling()) {
					str1 = pNodeI->name();
					if (!str1.compare(datoABuscar)) {
						datoARetornar = atoi(pNodeI->value());
					}
				}
			}
		}
		return datoARetornar;
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