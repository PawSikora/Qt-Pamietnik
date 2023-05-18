#include "program.h"

Program::Program(QObject *parent) : QObject(parent)
{}


void Program::zapisz_wspomnienie(QDateTime data, QString wpis, QColor kolor, QFont format, QString obraz)
{
    Pamietnik nowy_Wpis(data, wpis, kolor, format, obraz);
    bool czy_nadpisany = false;
    for(auto iter = zbior_wpisow.begin(); iter != zbior_wpisow.end(); iter++)
    {
        if(iter->getData() == nowy_Wpis.getData())
        {
            iter->setTekst(nowy_Wpis.getTekst());
            iter->setKolor(nowy_Wpis.getKolor());
            iter->setFormat(nowy_Wpis.getFormat());
            iter->setObraz(nowy_Wpis.getObraz());
            czy_nadpisany = true;
        }
    }
    if(!czy_nadpisany)
        zbior_wpisow.push_front(nowy_Wpis);

    zbior_wpisow = nowy_Wpis.sortuj_Wspomnienia(zbior_wpisow);
    iter_przewijania = zbior_wpisow.end() - 1;
}

void Program::wyswietl(QTextEdit *poprzedni, QTextEdit *aktualny, QTextEdit *nastepny, QLabel *obraz_wyswietlany)
{
    poprzedniWpis = poprzedni;
    aktualnyWpis = aktualny;
    nastepnyWpis = nastepny;
    obraz = obraz_wyswietlany;

    if(zbior_wpisow.isEmpty())
    {
        poprzedniWpis->setText("Brak starszych wspomnien");
        aktualnyWpis->setText("Brak aktualnych wspomnien");
        nastepnyWpis->setText("Brak nowszych wpomnien");
    }
    else
    {
        //Aktualny wpis
        if(iter_przewijania > zbior_wpisow.begin() || iter_przewijania < zbior_wpisow.end())
        {
            ustawienieWyswietlacza(aktualnyWpis, iter_przewijania);
            if(!iter_przewijania->getObraz().isEmpty())
            {
                QSize rozdz = obraz->size();
                obraz->setPixmap(QPixmap::fromImage(QImage(iter_przewijania->getObraz()).scaled(rozdz)));
            }
            else
                obraz->setText("Brak zdjecia");
        }
        else
            aktualnyWpis->setText((zbior_wpisow.end()-1)->getTekst());

        //Nastepny wpis
        if((iter_przewijania + 1) < zbior_wpisow.end())
            ustawienieWyswietlacza(nastepnyWpis, iter_przewijania+1);
        else
        {
          resetWyswietlacza(nastepnyWpis);
          nastepnyWpis->setText("Brak nowszych wspomnien");
        }

        //Poprzedni wpis
        if((iter_przewijania - 1) >= zbior_wpisow.begin())
            ustawienieWyswietlacza(poprzedniWpis, iter_przewijania-1);
        else
        {
          resetWyswietlacza(poprzedniWpis);
          poprzedniWpis->setText("Brak starszych wspomnien");
        }
    }
}

void Program::doTylu()
{
    if(!zbior_wpisow.isEmpty())
    {
        if(iter_przewijania > zbior_wpisow.begin())
            iter_przewijania--;
    }
    wyswietl(poprzedniWpis, aktualnyWpis, nastepnyWpis, obraz);
}

void Program::doPrzodu()
{
    if(!zbior_wpisow.isEmpty())
    {
       if(iter_przewijania < zbior_wpisow.end() - 1)
           iter_przewijania++;
    }
    wyswietl(poprzedniWpis, aktualnyWpis, nastepnyWpis, obraz);
}

void Program::usunWpis()
{
    for(int i = 0; i < zbior_wpisow.size(); i++)
    {
        if(zbior_wpisow[i].getData() == iter_przewijania->getData())
        {
            zbior_wpisow.removeAt(i);
            resetWyswietlacza(aktualnyWpis);
            aktualnyWpis->setText("WPIS USUNIETY");
            obraz->setText("Brak zdjecia");
            if(iter_przewijania > zbior_wpisow.begin())
                iter_przewijania--;
            else
                iter_przewijania = zbior_wpisow.begin();
        }
    }
}

void Program::ustawienieWyswietlacza(QTextEdit *wyswietlacz, QVector<Pamietnik>::iterator iter)
{
    wyswietlacz->setText("<b>" + (iter)->getData() + "</b>");
    wyswietlacz->setTextColor((iter)->getKolor());
    wyswietlacz->setCurrentFont((iter)->getFormat());
    wyswietlacz->append((iter)->getTekst());
}

void Program::resetWyswietlacza(QTextEdit *wyswietlacz)
{
    QFont reset; //Reset fonta
    reset.setBold(0);
    reset.setItalic(0);
    wyswietlacz->setTextColor("black");
    wyswietlacz->setCurrentFont(reset);
}

void Program::zapisz(QString nazwaPliku)
{
    Pamietnik zapis;
    zapis.zapisz_DoPliku(zbior_wpisow, nazwaPliku);
}

void Program::wczytaj(QString nazwaPliku)
{
    Pamietnik wczyta;
    if(!nazwaPliku.isEmpty())
        zbior_wpisow = wczyta.wczytaj_ZPliku(zbior_wpisow, nazwaPliku);
    else
        zbior_wpisow = wczyta.wczytaj_ZPliku(zbior_wpisow, domyslny_plik);
    if(!zbior_wpisow.isEmpty())
    {
        zbior_wpisow = wczyta.sortuj_Wspomnienia(zbior_wpisow);
        iter_przewijania = zbior_wpisow.end() - 1;
        wyswietl(poprzedniWpis, aktualnyWpis, nastepnyWpis, obraz);
    }
}

void Program::zapiszPoZamknieciu()
{
    zapisz(domyslny_plik);
}

void Program::wczytajPoOtwarciu()
{
    wczytaj(domyslny_plik);
    auto najblizsze = std::lower_bound(zbior_wpisow.begin(), zbior_wpisow.end(), QDateTime::currentDateTime());
    if(najblizsze != zbior_wpisow.end())
    {
      iter_przewijania = najblizsze;
      iter_przewijania--;
    }
    wyswietl(poprzedniWpis, aktualnyWpis, nastepnyWpis, obraz);
}
