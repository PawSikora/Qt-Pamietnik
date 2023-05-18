#include "edytuj.h"
#include "ui_edytuj.h"

Edytuj::Edytuj(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Edytuj)
{
    ui->setupUi(this);

    ui->dataWpisu->setDisplayFormat("HH:mm dd-MM-yyyy");
    ui->dataWpisu->setDateTime(QDateTime::currentDateTime());

    ui->formatTekstu->addItems({"Normalny", "Pogrubiony", "Kursywa"});
    ui->kolorTekstu->addItems({"Czarny", "Czerwony", "Zielony", "Niebieski", "Cyjan"});
    QFont fontfixer; //do naprawy czcionki startowej
    ui->edytowanieWpisu->setFont(fontfixer);

    ui->obraz->setScaledContents(true);
    ui->obraz->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
}

Edytuj::~Edytuj()
{
    delete ui;
}

void Edytuj::on_formatTekstu_currentIndexChanged(int index)
{
    QFont format = ui->edytowanieWpisu->toPlainText();
    switch(index)
    {
        case 0:
            format.setBold(0);
            format.setItalic(0);
            ui->edytowanieWpisu->setFont(format);
        break;

        case 1:
            format.setBold(1);
            format.setItalic(0);
            ui->edytowanieWpisu->setFont(format);
        break;

        case 2:
            format.setBold(0);
            format.setItalic(1);
            ui->edytowanieWpisu->setFont(format);
        break;
    }
}


void Edytuj::on_kolorTekstu_currentIndexChanged(int index)
{
    QVector<QColor> kolory = {"black", "red", "green", "blue", "cyan"};
    QString temp = ui->edytowanieWpisu->toPlainText();
    ui->edytowanieWpisu->setTextColor(kolory[index]);
    ui->edytowanieWpisu->setText(temp);
}


void Edytuj::on_dodajObraz_clicked()
{
    obraz = QFileDialog::getOpenFileName(this, "Open Image File", "","Images (*.png *.bmp *.jpg)");
    if(!obraz.isEmpty())
    {
        QImage img(obraz);
        QSize rozdz = ui->obraz->size();
        ui->obraz->setPixmap(QPixmap::fromImage(img.scaled(rozdz)));
    }
}


void Edytuj::on_usunObraz_clicked()
{
    ui->obraz->setText("Brak zdjecia");
    obraz = "";
}


void Edytuj::on_buttonBox_accepted()
{
    emit wyslij_wspomnienie(ui->dataWpisu->dateTime(), ui->edytowanieWpisu->toPlainText(), ui->edytowanieWpisu->textColor(), ui->edytowanieWpisu->font(), obraz);
}

