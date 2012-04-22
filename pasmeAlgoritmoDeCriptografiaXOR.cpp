#include <QtGui/QApplication>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <QMessageBox>
#include "pasmeAlgoritmosDeCriptografia.h"
#include "estadodaencriptacao.h"

using namespace std;

/*
 Encripta usando algoritmo XOR
*/
void encripta_XOR(std::vector<char>& key, const char* fin, const char* fout, const pasmeConfig* pc,QWidget * p){
	FILE* Fin=fopen(fin,"rb");
	FILE* Fout=fopen(fout,"wb");

	estadoDaEncriptacao w;
	w.show();

	w.setStatus("Encriptando...");

	w.reset();
	w.setTotalSteps(key.size());

	int i, ia, l;

	i=ia=0;
	l=key.size();

	while(!feof(Fin)){
		if(i==0) w.reset();

		w.setProgress(i);
		char c;

		fread(&c,sizeof(char),1,Fin);
		c^=key[ia];
		fwrite(&c,sizeof(char),1,Fout);

		ia=(ia+1)%l;
		i=(i+1)%l;
	}

	w.reset();
	fclose(Fin);
	fclose(Fout);
}

/*
 Desencripta usando algoritmo XOR
*/
void desencripta_XOR(std::vector<char>& key, const char* fin, const char* fout, const pasmeConfig* pc,QWidget * p){
	FILE* Fin=fopen(fin,"rb");
	FILE* Fout=fopen(fout,"wb");

	estadoDaEncriptacao w;
	w.show();

	w.setStatus("Desencriptando...");

	w.reset();
	w.setTotalSteps(key.size());

	int i, ia, l;

	i=ia=0;
	l=key.size();

	while(!feof(Fin)){
		if(i==0) w.reset();

		w.setProgress(i);
		char c;

		fread(&c,sizeof(char),1,Fin);
		c^=key[ia];
		fwrite(&c,sizeof(char),1,Fout);

		ia=(ia+1)%l;
		i=(i+1)%l;
	}

	w.reset();
	fclose(Fin);
	fclose(Fout);

}

