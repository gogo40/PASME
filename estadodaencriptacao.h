#ifndef ESTADODAENCRIPTACAO_H
#define ESTADODAENCRIPTACAO_H

#include <QDialog>
#include <QProgressBar>
#include <QString>

namespace Ui {
	class estadoDaEncriptacao;
}

class estadoDaEncriptacao : public QDialog
{
	Q_OBJECT

public:
	explicit estadoDaEncriptacao(QWidget *parent = 0);
	~estadoDaEncriptacao();
	void reset();
	void setTotalSteps(int v);
	void setProgress(int v);
	void setStatus(const QString& s);
private:
	Ui::estadoDaEncriptacao *ui;
};

#endif // ESTADODAENCRIPTACAO_H
