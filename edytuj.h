#ifndef EDYTUJ_H
#define EDYTUJ_H

#include <QDialog>
#include <QFileDialog>
#include "program.h"

namespace Ui { class Edytuj;}

class Program;

class Edytuj : public QDialog
{
    Q_OBJECT

public:
    explicit Edytuj(QWidget *parent = nullptr);
    ~Edytuj();

signals:
    void wyslij_wspomnienie(QDateTime data, QString wpis, QColor kolor, QFont format, QString obraz);


private slots:
    void on_formatTekstu_currentIndexChanged(int index);

    void on_kolorTekstu_currentIndexChanged(int index);

    void on_dodajObraz_clicked();

    void on_usunObraz_clicked();

    void on_buttonBox_accepted();

private:
    Ui::Edytuj *ui;
    QString obraz;

};

#endif // EDYTUJ_H
