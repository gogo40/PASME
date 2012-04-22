#ifndef AJUDA_H
#define AJUDA_H

#include <QDialog>

namespace Ui {
    class ajuda;
}

class ajuda : public QDialog
{
    Q_OBJECT

public:
    explicit ajuda(QWidget *parent = 0);
    ~ajuda();

private:
    Ui::ajuda *ui;
};

#endif // AJUDA_H
