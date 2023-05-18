#ifndef PAMIETNIK_H
#define PAMIETNIK_H

#include <QDateTime>
#include <QImage>
#include <QFont>
#include <QFile>

class Pamietnik
{
private:
    QDateTime data_wpisu;
    QString tekst_wpisu;
    QFont format_wpisu;
    QColor kolor_wpisu;
    QString obraz_wpisu;

public:
    Pamietnik();
    Pamietnik(QDateTime data, QString wpis, QColor kolor, QFont format, QString obraz);
    ~Pamietnik() {};

    //Metody warstwy danych
    QVector<Pamietnik> sortuj_Wspomnienia(QVector<Pamietnik> zbior);
    void zapisz_DoPliku(QVector<Pamietnik> zbior, QString nazwa_pliku);
    QVector<Pamietnik> wczytaj_ZPliku(QVector<Pamietnik> zbior, QString nazwa_pliku);
    Pamietnik wpisZPliku(std::string dane);

    //Settery
    void setTekst(QString wpis);
    void setData(QDateTime data);
    void setFormat(QFont format);
    void setKolor(QColor kolor);
    void setObraz(QString obraz);

    //Gettery
    QString getTekst();
    QString getData();
    QFont getFormat();
    QColor getKolor();
    QString getObraz();
    QString doZapisu();


    //Operatory
    bool operator !=(Pamietnik rhs) const
    {
        return (this->data_wpisu != rhs.data_wpisu);
    }

    bool operator ==(Pamietnik rhs) const
    {
        return (this->data_wpisu == rhs.data_wpisu);
    }

    bool operator >(Pamietnik rhs) const
    {
        return (this->data_wpisu > rhs.data_wpisu);
    }

    bool operator <(Pamietnik rhs) const
    {
        return (this->data_wpisu < rhs.data_wpisu);
    }

    bool operator !=(QDateTime rhs) const
    {
        return (this->data_wpisu != rhs);
    }

    bool operator ==(QDateTime rhs) const
    {
        return (this->data_wpisu == rhs);
    }

    bool operator >(QDateTime rhs) const
    {
        return (this->data_wpisu > rhs);
    }

    bool operator <(QDateTime rhs) const
    {
        return (this->data_wpisu < rhs);
    }
};

#endif // PAMIETNIK_H
