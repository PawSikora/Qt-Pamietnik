#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QWheelEvent>
#include "edytuj.h"
#include "program.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Program;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, Program *app = nullptr);
    ~MainWindow();


    void wyswietlWpisy();

signals:
    void zapisz_wspomnienie(QDateTime data, QString wpis, QColor kolor, QFont format, QString obraz);


public slots:
    void odbierz_wspomnienie(QDateTime data, QString wpis, QColor kolor, QFont format, QString obraz);


private slots:
    void on_dodawanieWpisow_clicked();

    void on_poprzednie_clicked();

    void on_nastepne_clicked();

    void on_usunWpis_clicked();

    void on_zapiszKopie_clicked();

    void on_wczytajKopie_clicked();

    void on_cofnijZmiany_clicked();

private:
    Ui::MainWindow *ui = nullptr;
    Edytuj *m_okienko;
    Program *mainApp = nullptr;

    void keyPressEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

};
#endif // MAINWINDOW_H
