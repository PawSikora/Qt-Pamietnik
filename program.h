#ifndef PROGRAM_H
#define PROGRAM_H

#include <QObject>
#include <QTextEdit>
#include <QLabel>
#include <QFile>
#include "pamietnik.h"

class MainWindow;

class Program : public QObject
{
    Q_OBJECT

public:
    explicit Program(QObject *parent = nullptr);
    void setGUI(MainWindow *ui = nullptr) {GUI = ui;}


    //Metody warstwy uslug
    void wyswietl(QTextEdit *poprzedni, QTextEdit *aktualny, QTextEdit *nastepny, QLabel *obraz_wyswietlany);
    void zapiszWpisy();
    void wczytajWpisy();
    void usunWpis();
    void doTylu();
    void doPrzodu();
    void zapisz(QString nazwaPliku);
    void wczytaj(QString nazwaPliku);

    void zapiszPoZamknieciu();
    void wczytajPoOtwarciu();

    void ustawienieWyswietlacza(QTextEdit *wyswietlacz, QVector<Pamietnik>::iterator iter);
    void resetWyswietlacza(QTextEdit *wyswietlacz);


public slots:
    void zapisz_wspomnienie(QDateTime data, QString wpis, QColor kolor, QFont format, QString obraz);


private:
    MainWindow *GUI = nullptr;
    QTextEdit *poprzedniWpis;
    QTextEdit *aktualnyWpis;
    QTextEdit *nastepnyWpis;
    QLabel *obraz;


    QVector<Pamietnik> zbior_wpisow;
    QVector<Pamietnik>::iterator iter_przewijania = zbior_wpisow.end()-1;
    QString domyslny_plik = "domyslny_Plik.txt";
};

#endif // PROGRAM_H
