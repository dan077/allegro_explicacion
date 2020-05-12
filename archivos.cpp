#include <vector>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

class Pregunta {

public:
	string pregunta;
	string opcion1, opcion2;
	int correcta;
	int id;

	Pregunta(string pregunta, string opcion1, string opcion2, int correcta,int id) {
		this->pregunta = pregunta;
		this->opcion1 = opcion1;
		this->opcion2 = opcion2;
		this->correcta = correcta;
		this->id = id;
	}
};

int split(std::string texto, std::vector<std::string>& vector, char delimit) {
	std::string palabra = "";

	for (int i = 0; i <= texto.length(); i++) {
		if (texto[i] == delimit || texto[i] == '\0') {
			vector.push_back(palabra);
			palabra = "";
		}
		else {
			palabra += texto[i];
		}
	}

	return vector.size();
}


void lectura(string nombre, char delimit) {
	ifstream archivo(nombre, ios::in);
	if (archivo.fail()) {
		cout << "Error, al abrir el archivo" << endl;
	}
	else {
		vector<string> resultado;
		string linea;

		while (!archivo.eof()) 
		{
			getline(archivo, linea);
			if (split(linea, resultado, delimit) == 5) {
				Pregunta* obj = new Pregunta(resultado[0], resultado[1], resultado[2], stoi(resultado[3]), stoi(resultado[4]));
				cout << obj->pregunta << endl;
			}
			resultado.clear();
		}
		archivo.close();
	}
}

void escritura(string nombre, Pregunta *obj, char delimit,int id,bool ignoraSalto = false) {
	ofstream archivo(nombre, ios::out | ios::app);
	string salto = ignoraSalto ? "" : "\n";
	archivo << salto << obj->pregunta << delimit << obj->opcion1 << delimit << obj->opcion2 << delimit << obj->correcta << delimit << id;
	archivo.close();
}



void borrar(string nombre, int id,char delimit) {
	ifstream archivo(nombre, ios::in);
	if (archivo.fail()) {
		cout << "Error, al abrir el archivo" << endl;
	}
	else {
		bool primerDato = true;
		vector<string> resultado;
		string linea;
		while (!archivo.eof())
		{
			getline(archivo, linea);
			if (split(linea, resultado, delimit) == 5) {
				if (stoi(resultado[4]) == id) {

				}
				else {
					Pregunta* obj = new Pregunta(resultado[0], resultado[1], resultado[2], stoi(resultado[3]), stoi(resultado[4]));
					escritura("auxx.txt", obj, delimit, stoi(resultado[4]),primerDato);
					primerDato = false;
				}
				

			}
			resultado.clear();
		}
		archivo.close();
		remove(nombre.c_str());
		rename("auxx.txt", (nombre).c_str());
		
	}
	
}


int main() {
	string nombre = "preguntas.txt";
	char delimit = '|';


	//Pregunta* obj = new Pregunta("Pregunta x4", "opcion1", "opcion2", 1,6);
	//escritura(nombre, obj, delimit,6);
	borrar(nombre, 4, delimit);
	lectura(nombre, delimit);

	system("Pause");
	return 0;
}