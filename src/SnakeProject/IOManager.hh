#pragma once
#include <rapidxml_utils.hpp>
#include <rapidxml_iterators.hpp>
#include <rapidxml_print.hpp>
#include <rapidxml.hpp>
#include <iostream>  
#include <fstream>
#include <string>
#include <sstream>

#define archivoConfiguacion "myXML.xml"

using namespace std;

namespace IOManager {

	//Funcion para consultar el archivo xml donde guardamos las configuraciones
	static int consultarXML(string difficulty, string datoABuscar) {
		int datoARetornar= 0;
		string str1;


		rapidxml::xml_document<> doc;
		std::ifstream xmlFile(archivoConfiguacion);
		std::stringstream buffer;
		buffer << xmlFile.rdbuf(); //copiamos datos al buffer
		xmlFile.close(); // cerramos el ifstream
		std::string content(buffer.str()); //convertimos en string el contenido del buffer
		doc.parse<0>(&content[0]); //parseamos la info

		//recorremos la info parseada con estructura xml
		rapidxml::xml_node<> *pRoot = doc.first_node(); //primer nodo con funcion de ROOT en el xml (difficulties)
		for (rapidxml::xml_node<> *pNode = pRoot->first_node("difficulty"); pNode; pNode = pNode->next_sibling()) { //recorremos los elementos (difficulty)
			rapidxml::xml_attribute<> *pAttr = pNode->first_attribute(); // seleccionamos el primer atributo que es la id
			if (pAttr->value() == difficulty) { // comparamos si la id coincide con la que tenemos que usar
				for (rapidxml::xml_node<> *pNodeI = pNode->first_node(); pNodeI; pNodeI = pNodeI->next_sibling()) { 
					str1 = pNodeI->name();
					if (!str1.compare(datoABuscar)) {
						datoARetornar = atoi(pNodeI->value()); //guardamos y convertimos en integer el valor del elemento encontrado
					}
				}
			}
		}
		return datoARetornar;
	}

	//funcion para introducir una score en el archivo del ranking
	static void introducirRanking(std::vector<std::pair<std::string, int>> rankingActual, string difficulty) {
		char final = ';';

		ofstream fsalida("ranking" + difficulty + ".dat", ios::out | ios::binary);

		for (auto it = rankingActual.begin(); it != rankingActual.end(); ++it) { //iterator que recorre el vector de pair
			fsalida.write((it->first.c_str()), it->first.size());
			fsalida.write(reinterpret_cast<char *>(&final), sizeof(final));
			fsalida.write(reinterpret_cast<char *>(&it->second), sizeof(it->second));
		}

		fsalida.close();
	}
	
	//funcion para leer y devolver en un vector de pair el archivo donde estan guardados los ranking
	static vector<pair<string, int>> leerRanking(string difficulty) {
		vector<pair<string, int>> ranking;

		bool cond = false;
		string pruebachar;
		int pruebaint;

		ifstream fentrada("ranking" + difficulty + ".dat", ios::in | ios::binary);

		if (fentrada.is_open()) { 
			while (!fentrada.eof()) { //bucle hasta end of file
				if (!cond) { //condicion para alternar datos a la hora de almacenarlos
					getline(fentrada, pruebachar, ';');
					cond = true;
				} else {
					fentrada.read(reinterpret_cast<char *>(&pruebaint), sizeof(pruebaint));
					ranking.push_back(make_pair(pruebachar, pruebaint)); // los inserta al final del vector
					cond = false;
				}	
			}
		}
		fentrada.close();

		return ranking;
	}
}