#ifndef INSERTSPECIALCHAR_H
#define INSERTSPECIALCHAR_H
#include <QString>
#include <QVector>

class insertSpecialChar
{
public:
    insertSpecialChar();
    ~insertSpecialChar();
    QString replaceSpecSyms(QString in, bool *addSpecSym);
private:
    QVector<std::pair<QString, QString>> listOfReplacements =   // список замещаемых спец символов
    {{"#@cr", "©"}, {"#@tm", "®"}, {"#@permille", "‰"}, {"#@eur", "€"}, {"#@rub", "₽"}};
};

#endif // INSERTSPECIALCHAR_H
