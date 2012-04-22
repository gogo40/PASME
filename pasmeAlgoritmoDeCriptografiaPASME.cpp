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
 Encripta usando algoritmo PASME
*/
void encripta_PASME(std::vector<char>& key, const char* fin, const char* fout, const pasmeConfig* pc,QWidget * p){
	estadoDaEncriptacao w;
	w.show();

	w.setStatus("Encriptando...");

	w.reset();
	w.setTotalSteps(13);

	FILE* Fout=fopen(fout,"wb");

	vector<char> fc(pc->tamChave);

	for(int i=0;i<pc->tamChave;i++) fc[i]=rand()%255;

	w.setProgress(1);

	gmp_randclass r1 (gmp_randinit_mt);
	r1.seed(7*time(NULL)+11);

	w.setProgress(2);

	gmp_randclass r2 (gmp_randinit_mt);
	r2.seed(13*time(NULL)*mpz_class(time(NULL))+37);

	w.setProgress(3);

	gmp_randclass r3 (gmp_randinit_mt);
	r3.seed(59*time(NULL)*mpz_class(time(NULL))*mpz_class(time(NULL))+19);

	w.setProgress(4);

	gmp_randclass r4 (gmp_randinit_mt);
	r4.seed(73*time(NULL)*mpz_class(time(NULL))*mpz_class(time(NULL))*mpz_class(time(NULL))+31);

	w.setProgress(5);

	gmp_randclass r5 (gmp_randinit_mt);
	r5.seed(91*time(NULL)*mpz_class(time(NULL))*mpz_class(time(NULL))*mpz_class(time(NULL))*mpz_class(time(NULL))+7);

	w.setProgress(6);

	gmp_randclass r6 (gmp_randinit_mt);
	r6.seed(73*time(NULL)*mpz_class(time(NULL))*mpz_class(time(NULL))*mpz_class(time(NULL))*mpz_class(time(NULL))*mpz_class(time(NULL))+31);

	gmp_randclass r7(gmp_randinit_mt);
	r7.seed(171*time(NULL)*mpz_class(time(NULL))*mpz_class(time(NULL))*mpz_class(time(NULL))*mpz_class(time(NULL))*mpz_class(time(NULL))*mpz_class(time(NULL))+33);

	w.setProgress(7);
	mpz_class P;
	mpz_class K1(r1.get_z_bits(pc->C));//lixo a ser adicionado a W
	mpz_class K2(r2.get_z_bits(pc->D));//valor do lixo a
	mpz_class K3(r3.get_z_bits(pc->A));//tamanho dos caracteres
	mpz_class K4(r4.get_z_bits(pc->B));//resto da divisao
	mpz_class K5(r5.get_z_bits(pc->B));//incremento da mensagem
	mpz_class a;
	
	mpz_class W(0);
	int len = key.size();

	mpz_t mpz_aux;
	mpz_init(mpz_aux);

	w.setProgress(8);
	mpz_nextprime (mpz_aux, K5.get_mpz_t() );
	K5 = mpz_class(mpz_aux);

	
	K3+=K5+1024;

	w.setProgress(9);
	mpz_nextprime (mpz_aux, K4.get_mpz_t() );
	K4 = mpz_class(mpz_aux);

	w.setProgress(10);
	mpz_nextprime (mpz_aux, K1.get_mpz_t() );
	K1 = mpz_class(mpz_aux);

	/*Algoritmo para "colocar lixo" na W*/
	w.setProgress(11);
	mpz_nextprime (mpz_aux, K3.get_mpz_t() );
	K3 = mpz_class(mpz_aux);

	mpz_class b(K3);

	w.setProgress(12);
	mpz_nextprime (mpz_aux, K2.get_mpz_t() );

	w.setStatus("Gerando chave publica...");

	w.reset();
	w.setTotalSteps(len);
	for(int i=0;i<len;i++)
	{
		w.setProgress(i);
		a = mpz_class(mpz_aux);
		W+=( int(key[i]) +a) *b  ;
		b*=K3;
		mpz_nextprime (mpz_aux, a.get_mpz_t() );

	}

	W+=K1;

	/**********************************/

	int v;

	string X_(""),Y_("");


	X_=K1.get_str(10);

	v=X_.size();
	fwrite(&v,sizeof(int),1,Fout);
	for(int i=0;i<X_.size();i++) fwrite(&X_[i],sizeof(char),1,Fout);

	X_=K2.get_str(10);

	v=X_.size();
	fwrite(&v,sizeof(int),1,Fout);
	for(int i=0;i<X_.size();i++) fwrite(&X_[i],sizeof(char),1,Fout);

	X_=K3.get_str(10);

	v=X_.size();
	fwrite(&v,sizeof(int),1,Fout);
	for(int i=0;i<X_.size();i++) fwrite(&X_[i],sizeof(char),1,Fout);


	X_=K4.get_str(10);

	v=X_.size();
	fwrite(&v,sizeof(int),1,Fout);
	for(int i=0;i<X_.size();i++) fwrite(&X_[i],sizeof(char),1,Fout);


	X_=K5.get_str(10);

	v=X_.size();
	fwrite(&v,sizeof(int),1,Fout);
	for(int i=0;i<X_.size();i++) fwrite(&X_[i],sizeof(char),1,Fout);


	mpz_class X(0);

	len = fc.size();
	b= 1;

	w.setStatus("Encriptando a palavra-chave...");

	w.reset();
	w.setTotalSteps(len);

	X_="";
	for(int i=0;i<len;i++){
		w.setProgress(i);
		X+=( int(fc[i]) + K5)*b  ;
		b*=K3;
	}

	X_=X.get_str(10);

	mpz_class Q(r7.get_z_bits (X_.size()));
	Q+=X;
	mpz_nextprime (mpz_aux, Q.get_mpz_t() );
	Q = mpz_class(mpz_aux);

	Y_=Q.get_str(10);


	v=X_.size();
	fwrite(&v,sizeof(int),1,Fout);

	int py=0;
	for(int i=0;i<X_.size();i++){
		int w=X_[i]^Y_[py];
		fwrite(&w,sizeof(char),1,Fout);
		py=(py+1)%Y_.size();
	}


	P = W*Q + K4;

	Y_=P.get_str(10);

	v=Y_.size();
	fwrite(&v,sizeof(int),1,Fout);
	for(int i=0;i<Y_.size();i++) fwrite(&Y_[i],sizeof(char),1,Fout);


	w.setStatus("Feito!!!");
	w.reset();
	/********************************/
	FILE* Fin=fopen(fin,"rb");
	int ia;
	ia=0;
	while(!feof(Fin)){
		char c;
		fread(&c,sizeof(char),1,Fin);
		c^=fc[ia];
		fwrite(&c,sizeof(char),1,Fout);
		ia=(ia+1)%pc->tamChave;
	}
	fclose(Fin);
	fclose(Fout);
	
	mpz_clear(mpz_aux);

	QMessageBox::information( p, QString("Aviso!"),
	QString("Mensagem encriptada!!!") );
}

/*
 Desencripta usando algoritmo PASME
*/
void desencripta_PASME(std::vector<char>& key, const char* fin, const char* fout, const pasmeConfig* pc,QWidget * p){
	estadoDaEncriptacao w;
	w.show();


	FILE* Fin=fopen(fin,"rb");

	mpz_class P;
	mpz_class K1;//lixo a ser adicionado a W
	mpz_class K2;//valor do lixo a
	mpz_class K3;//tamanho dos caracteres
	mpz_class K4;//resto da divisao
	mpz_class K5;//incremento da mensagem
	mpz_class Q;
	string X_;
	mpz_class X(0);

	int l;
	char c;
	string in;


	try{
		fread(&l,sizeof(int),1,Fin);
		in.clear();
		for(int i=0;i<l;i++){
			fread(&c,sizeof(char),1,Fin);
			in+=c;
		}
		K1=mpz_class(in.c_str());
	}catch(...){
		return;
	}

	try{
		fread(&l,sizeof(int),1,Fin);
		in.clear();
		for(int i=0;i<l;i++){
			fread(&c,sizeof(char),1,Fin);
			in+=c;
		}
		K2=mpz_class(in.c_str());
	}catch(...){
		return;
	}

	try{
		fread(&l,sizeof(int),1,Fin);
		in.clear();
		for(int i=0;i<l;i++){
			fread(&c,sizeof(char),1,Fin);
			in+=c;
		}
		K3=mpz_class(in.c_str());
	}catch(...){
		return;
	}

	try{
		fread(&l,sizeof(int),1,Fin);
		in.clear();
		for(int i=0;i<l;i++){
			fread(&c,sizeof(char),1,Fin);
			in+=c;
		}
		K4=mpz_class(in.c_str());
	}catch(...){
		return;
	}

	try{
		fread(&l,sizeof(int),1,Fin);
		in.clear();
		for(int i=0;i<l;i++){
			fread(&c,sizeof(char),1,Fin);
			in+=c;
		}
		K5=mpz_class(in.c_str());
	}catch(...){
		return;
	}

	try{
		fread(&l,sizeof(int),1,Fin);
		in.clear();
		for(int i=0;i<l;i++){
			fread(&c,sizeof(char),1,Fin);
			in+=c;
		}
		X_=in;
	}catch(...){
		return;
	}

	try{
		fread(&l,sizeof(int),1,Fin);
		in.clear();
		for(int i=0;i<l;i++){
			fread(&c,sizeof(char),1,Fin);
			in+=c;
		}
		P=mpz_class(in.c_str());
	}catch(...){
		return;
	}

	FILE* Fout=fopen(fout,"wb");

	mpz_class a;

	mpz_class W(0);
	int len = key.size(), i;

	mpz_t mpz_aux;
	mpz_init(mpz_aux);

	/*Algoritmo para  verificar a W*/

	mpz_class b(K3);

	mpz_nextprime (mpz_aux, K2.get_mpz_t() );


	w.reset();
	w.setTotalSteps(len);

	for(i=0;i<len;i++)
	{
		/*1*/w.setProgress(i);
		a = mpz_class(mpz_aux);
		W+=( int(key[i]) +a) *b  ;
		b*=K3;
		mpz_nextprime (mpz_aux, a.get_mpz_t() );

	}

	W+=K1;

	mpz_clear(mpz_aux);
	/**********************************/

	if( (P%W) == K4){
		/*Recuperando mensagem*/
		Q=(P-K4)/W;

		string Y_;

		Y_=Q.get_str(10);
		int py=0;
		for(int i=0;i<X_.size();i++){
			X_[i]^=Y_[py];
			py=(py+1)%Y_.size();
		}
		X=mpz_class(X_);

		bool flag(true);
		mpz_class ui;

		w.setStatus("Desencriptando...");
		i=0;
		w.setTotalSteps(100);

		X_="";
		while(flag)
		{
			if(i==0) w.reset();
			/*1*/w.setProgress(i);

			a = X%K3;
			X-=a;
			X/=K3;

			ui = a - K5;
			X_+=(char)(ui.get_d());

			if(X<=0)
				flag = false;
			i=(i+1)%100;

		}

		w.reset();

		int ia=0;
		while(!feof(Fin)){
			char c;
			fread(&c,sizeof(char),1,Fin);
			c^=X_[ia];
			fwrite(&c,sizeof(char),1,Fout);
			ia=(ia+1)%X_.size();
		}
		/**********************************/
		QMessageBox::information( p, QString("Aviso!"),
		QString("Mensagem revelada!!!") );
	}
	else{
		QMessageBox::information( p, QString("Aviso!"),
		QString("ACESSO NEGADO!!!") );
	}

	fclose(Fout);
	fclose(Fin);

}
