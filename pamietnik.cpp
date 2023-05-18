#include "pamietnik.h"

Pamietnik::Pamietnik(){}

Pamietnik::Pamietnik(QDateTime data, QString wpis, QColor kolor, QFont format, QString obraz)
{
    setData(data);
    setTekst(wpis);
    setFormat(format);
    setKolor(kolor);
    setObraz(obraz);
}

void Pamietnik::setData(QDateTime data)
{
    data_wpisu = data;
}

void Pamietnik::setTekst(QString wpis)
{
    tekst_wpisu = wpis;
}

void Pamietnik::setFormat(QFont format)
{
    format_wpisu = format;
}

void Pamietnik::setKolor(QColor kolor)
{
    kolor_wpisu = kolor;
}

void Pamietnik::setObraz(QString obraz)
{
    obraz_wpisu = obraz;
}

QString Pamietnik::getData()
{
    return data_wpisu.toString("HH:mm dd-MM-yyyy");
}

QString Pamietnik::getTekst()
{
    return tekst_wpisu;
}

QFont Pamietnik::getFormat()
{
    return format_wpisu;
}

QColor Pamietnik::getKolor()
{
    return kolor_wpisu;
}

QString Pamietnik::getObraz()
{
    return obraz_wpisu;
}

QString Pamietnik::doZapisu()
{
    QString data, tekst, format, kolor, obraz;
    data = this->data_wpisu.toString("HH:mm dd-MM-yyyy");
    tekst = this->tekst_wpisu;
    format = this->format_wpisu.toString();
    kolor = this->kolor_wpisu.name();
    obraz = this->obraz_wpisu;
    return "/d" + data + "d/" + " " + "/t" + tekst + "t/" + " " + "/f" + format + "f/" + " " + "/k" + kolor + "k/" + "/o" + obraz + "o/" + "\n";
}

QVector<Pamietnik> Pamietnik::sortuj_Wspomnienia(QVector<Pamietnik> zbior)
{
    std::sort(zbior.begin(), zbior.end());
    return zbior;
}

void Pamietnik::zapisz_DoPliku(QVector<Pamietnik> zbior, QString nazwa_pliku)
{
    QFile plik;
    plik.setFileName(nazwa_pliku);

    if(plik.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream outStream(&plik);
        for (auto iter = zbior.begin(); iter < zbior.end(); iter++)
        {
            outStream << iter->doZapisu();
            qInfo() << "Zapisano";
        }
        plik.close();
    }
}

Pamietnik Pamietnik::wpisZPliku(std::string dane)
{
    Pamietnik wpis_temp;
    int pocz, kon, dlug;

    //Data
    pocz = dane.find("/d");
    kon = dane.find("d/");
    dlug = kon - pocz;
    wpis_temp.setData(QDateTime::fromString(QString::fromStdString(dane.substr(pocz+2,dlug-2)),"HH:mm dd-MM-yyyy"));

    //Tekst
    pocz = dane.find("/t");
    kon = dane.find("t/");
    dlug = kon - pocz;
    wpis_temp.setTekst(QString::fromStdString(dane.substr(pocz+2,dlug-2)));

    //Format
    QFont font;
    pocz = dane.find("/f");
    kon = dane.find("f/");
    dlug = kon - pocz;
    font.fromString(QString::fromStdString(dane.substr(pocz+2, dlug-2)));
    wpis_temp.setFormat(font);

    //Kolor
    pocz = dane.find("/k");
    kon = dane.find("k/");
    dlug = kon - pocz;
    wpis_temp.setKolor(QColor(QString::fromStdString(dane.substr(pocz+2, dlug-2))));

    //Obraz
    pocz = dane.find("/o");
    kon = dane.find("o/");
    dlug = kon - pocz;
    wpis_temp.setObraz(QString::fromStdString(dane.substr(pocz+2, dlug-2)));

    return wpis_temp;
}

QVector<Pamietnik> Pamietnik::wczytaj_ZPliku(QVector<Pamietnik> zbior, QString nazwa_pliku)
{
    QFile plik;
    plik.setFileName(nazwa_pliku);

    zbior.clear();

    if(plik.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream inStream(&plik);
        while(!inStream.atEnd())
        {
            QString line = inStream.readLine();
            zbior.push_front(wpisZPliku(line.toStdString()));
            qInfo() << "Wczytano";
        }
        plik.close();
    }
    return zbior;
}
