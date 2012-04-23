#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

#include "pasmeConfig.h"

namespace Ui {
	class MainWindow;
}

enum TIPO_ALGORITMO_CRIPTOGRAFIA{
	PASME,
	XOR
};


class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);

	void setPC(int argc, char** argv){
		pc.argc=argc;
		pc.argv=argv;
	}

	~MainWindow();

private slots:
	void chamarOcultarInformacao();
	void chamarRevelarInformacao();
	void capturarNomeArquivoComMensagemASerOcultada();
	void capturarNomeArquivoOndeEsconderMensagem();
	void capturarNomeArquivoComMensagemOculta();
	void isXORclicked();
	void isPASMEclicked();
	void capturarNomeArquivoAlvo();
	void capturarNomeArquivoChave();
	void useArquivoChaveClicked();
	void chamarEncriptador();
	void chamarDesencriptador();
	void chamarAjuda();
	void chamarSobre();
    void chamarOcultarInformacaoImagem();
    void chamarRevelarInformacaoImagem();
    void capturarNomeArquivoOcultarMensagemImagem();
    void capturarNomeArquivoOcultarArquivoAlvo();
    void capturarNomeArquivoRevelarMensagemImagem();
    void capturarNomeArquivoRevelarArquivoDestino();

private:
	Ui::MainWindow *ui;

	pasmeConfig pc;

	bool usarArquivoChave;//usar arquivo chave

    QString nomeArquivoOcultarMensagemImagem;
    QString nomeArquivoOcultarArquivoAlvo;
    QString nomeArquivoRevelarMensagemImagem;
    QString nomeArquivoRevelarArquivoDestino;
	QString nomeArquivoMensagemASerOcultada;
	QString nomeArquivoOndeEsconderMensagem;
	QString nomeArquivoComMensagemASerRecuperada;
	QString nomeArquivoAlvo;
	QString nomeArquivoChave;

	TIPO_ALGORITMO_CRIPTOGRAFIA tipoAlgoritmoCriptografia;
};

#endif // MAINWINDOW_H
