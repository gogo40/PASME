#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pasmeGerenciadorOcultacao.h"

#include <vector>
#include <cstdio>
#include <cstdlib>

#include <QString>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QtCore>

using namespace std;

/**
Oculta o arquivo 'mens' no arquivo 'alvo'
*/
void oculta(const char* mens, const char* alvo, QWidget * p){

	QMessageBox::information(p,"Aviso!","Comprimindo mensagem...");

	QString tmp(mens); tmp+=".tmp";
	gzFile tmpF = gzopen(tmp.toAscii(),"wb9f");

	if(!tmpF){
		QMessageBox::information(p,"Aviso!","Falha ao abrir arquivo:"+tmp);
		return;
	}

	//Realizando compressão da mensagem
	FILE* fin=fopen(mens,"rb");

	if(!fin){
		QMessageBox::information(p,"Aviso!","Falha ao abrir arquivo:"+QString(mens));
		return;
	}


	while(!feof(fin)){
		char c;
		fread(&c,sizeof(char),1,fin);
		gzwrite(tmpF,&c,sizeof(char));
	}

	gzclose(tmpF);
	fclose(fin);

	//Realizando ocultação da mensagem
	QMessageBox::information(p,"Aviso!","Ocultando mensagem...");

	fin=fopen(tmp.toAscii(),"rb");
	if(!fin){
		QMessageBox::information(p,"Aviso!","Falha ao abrir arquivo:"+tmp);
		return;
	}

	FILE* fout=fopen(alvo,"ab");

	if(!fout){
		QMessageBox::information(p,"Aviso!","Falha ao abrir arquivo:"+QString(alvo));
		return;
	}

	int l=0;

	l=0;
	while(!feof(fin)){
		char c;
		fread(&c,sizeof(char),1,fin);
		fwrite(&c,sizeof(char),1,fout);
		l++;
	}
	fwrite(&l,sizeof(int),1,fout);

	fclose(fin);
	fclose(fout);

	QMessageBox::information(p,"Aviso!","Mensagem ocultada!");

}

/**
 Revela a mensagem oculta no arquivo 'fonte' e grava no arquivo 'dest'
*/
void revela(const char* fonte, const char* dest, QWidget * p){

	QMessageBox::information(p,"Aviso!","Recuperando mensagem...");

	FILE* fin=fopen(fonte,"rb");
	if(!fin){
		QMessageBox::information(p,"Aviso!",QString("Falha ao abrir arquivo:")+fonte);
		return;
	}

	QString tmp(fonte); tmp+=".tmp";
	FILE* tmpF=fopen(tmp.toAscii(),"wb");
	if(!tmpF){
		QMessageBox::information(p,"Aviso!",QString("Falha ao abrir arquivo:")+tmp);
		return;
	}

	int l=0, i=0;

	//Recupera tamanho do arquivo ocultado e posiciona iterador de arquivo
	fseek(fin,-sizeof(int),SEEK_END);
	fread(&l,sizeof(int),1,fin);

	fseek(fin,-l*sizeof(char)-sizeof(int),SEEK_END);

	//Recupera mensagem comprimida
	QMessageBox::information(p,"Aviso!","Recuperando mensagem comprimida...");

	i=0;
	while(i<l){
		char c;
		fread(&c,sizeof(char),1,fin);
		fwrite(&c,sizeof(char),1,tmpF);
		i++;
	}

	fclose(fin);
	fclose(tmpF);

	//Grava mensagem no arquivo destino
	QMessageBox::information(p,"Aviso!","Gravando mensagem recuperada...");

	gzFile gtmpF=gzopen(tmp.toAscii(),"rb9f");
	if(!gtmpF){
		QMessageBox::information(p,"Aviso!",QString("Falha ao abrir arquivo:")+tmp);
		return;
	}

	FILE* fout=fopen(dest,"wb");
	if(!fout){
		QMessageBox::information(p,"Aviso!",QString("Falha ao abrir arquivo:")+dest);
		return;
	}

	while(!gzeof(gtmpF)){
		char c;
		gzread(gtmpF,&c,sizeof(char));
		fwrite(&c,sizeof(char),1,fout);
	}
	fclose(fout);
	gzclose(gtmpF);

	QMessageBox::information(p,"Aviso!","Recuperação de mensagem concluida!");

}


