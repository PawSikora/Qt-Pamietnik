#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, Program *app)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      mainApp(app)
{
    app->setGUI(this);
    ui->setupUi(this);

    //Ustawienie wyswietlaczy
    ui->poprzedniWpis->setReadOnly(1);
    ui->aktualnyWpis->setReadOnly(1);
    ui->nastepnyWpis->setReadOnly(1);

    MainWindow::setFocusPolicy(Qt::StrongFocus);
    ui->obraz->setScaledContents(true);
    ui->obraz->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    mainApp->wyswietl(ui->poprzedniWpis, ui->aktualnyWpis, ui->nastepnyWpis, ui->obraz);
    mainApp->wczytajPoOtwarciu();
    wyswietlWpisy();

    connect(this,SIGNAL(zapisz_wspomnienie(QDateTime, QString, QColor, QFont, QString)),app,SLOT(zapisz_wspomnienie(QDateTime, QString, QColor, QFont, QString)));


}

MainWindow::~MainWindow()
{
    mainApp->zapiszPoZamknieciu();
    delete ui;
}


void MainWindow::on_dodawanieWpisow_clicked()
{
    m_okienko = new Edytuj(this);
    connect(m_okienko,SIGNAL(wyslij_wspomnienie(QDateTime, QString, QColor, QFont, QString)), this,SLOT(odbierz_wspomnienie(QDateTime, QString, QColor, QFont, QString)));
    m_okienko->exec();

    wyswietlWpisy();
    ui->usunWpis->setDisabled(0);
    delete m_okienko;
}


void MainWindow::odbierz_wspomnienie(QDateTime data, QString wpis, QColor kolor, QFont format, QString obraz)
{
   emit zapisz_wspomnienie(data, wpis, kolor, format, obraz);
}


void MainWindow::wyswietlWpisy()
{
    mainApp->wyswietl(ui->poprzedniWpis, ui->aktualnyWpis, ui->nastepnyWpis, ui->obraz);
}


void MainWindow::on_poprzednie_clicked()
{
    mainApp->doTylu();
    ui->usunWpis->setDisabled(0);
}


void MainWindow::on_nastepne_clicked()
{
    mainApp->doPrzodu();
    ui->usunWpis->setDisabled(0);
}


void MainWindow::on_usunWpis_clicked()
{
    mainApp->usunWpis();
    ui->usunWpis->setDisabled(1);
}


void MainWindow::on_zapiszKopie_clicked()
{
    mainApp->zapisz(QFileDialog::getSaveFileName(this, "Wskaz plik", "", "Plik tekstowy (*.txt)"));
}


void MainWindow::on_wczytajKopie_clicked()
{
    mainApp->wczytaj(QFileDialog::getOpenFileName(this, "Wskaz plik", "", "Plik tekstowy (*.txt)"));
    ui->usunWpis->setDisabled(0);
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int keyCode = event->key();
    switch(keyCode)
    {
    case Qt::Key_Up:
        ui->poprzednie->click();
        break;
    case Qt::Key_Down:
        ui->nastepne->click();
        break;
    }
}


void MainWindow::wheelEvent(QWheelEvent *event)
{
    QPoint p = event->angleDelta();
    if(p.y() == 120)
        ui->poprzednie->click();
    else
       ui->nastepne->click();
}


void MainWindow::on_cofnijZmiany_clicked()
{
    mainApp->wczytajPoOtwarciu();
    ui->usunWpis->setDisabled(0);
}

