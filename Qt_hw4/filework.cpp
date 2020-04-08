#include "filework.h"


fileWork::fileWork()
{

}

bool fileWork::openFile(QString s, bool forRead)
{
    int index = s.indexOf(".txt");
    QFile file(s);
    if (file.open(QFile::ReadOnly | QFile::ExistingOnly))
    {
        if (index != -1 && s.length() - 4 == index) // если текстовый файл
                                                    // (выполняются 2
                                                    // условия)
        {
            QTextStream stream(&file);
            emit returnOpenedText(stream.readAll());
        }
        else
        {
            QDataStream stream(&file);
            QByteArray withAuthor = QString("GB_Qt_Auth1").toUtf8();
            QByteArray withoutAuthor = QString("GB_Qt_Auth0").toUtf8();
            char mH[15];
            stream.readRawData(mH, withAuthor.length());
            if (memcmp(mH, withAuthor.data(), withAuthor.length()) &
                    memcmp(mH, withoutAuthor.data(), withoutAuthor.length()))    // если не совпадает
                                                                                 // хотябы один из заголовков, то открытие
                                                                                 // недопустимо, так как
                                                                                 // формат у файла другой
            {
                file.close();
                return false;
            }
            if (!memcmp(mH, withAuthor.data(), withAuthor.length())) { // если заголовок с автором, то считываем автора
                uint amount = 0;
                stream.readRawData(reinterpret_cast<char*>(&amount), sizeof amount);
                withAuthor.resize(amount);
                stream.readRawData(withAuthor.data(), amount);
                emit returnAuthor(withAuthor.data());
            }
            uint amount = 0;
            stream.readRawData(reinterpret_cast<char*>(&amount), sizeof amount);
            withoutAuthor.resize(amount);
            stream.readRawData(withoutAuthor.data(), amount);
            QString usedS = tr(withoutAuthor.data());
            QString str = "";
            uint pos = 0;
            uint mm = 1;
            for (;!stream.atEnd();) { // atEnd() true конец файла
                char ch;
                stream.readRawData(&ch, 1);
                bool bl = (ch & 0x80) ? false : true;
                int rValue = (ch & 0x7F);
                pos += mm * rValue;
                mm *= 128;
                if (bl)
                {
                    mm = 1;
                    str += usedS.at(pos);
                    pos = 0;
                }
            }
            emit returnOpenedText(str);
        }
    }
    file.seek(0);
    auto pp = file.readAll();
    file.close();
    return true;
}

bool fileWork::saveFile(QString s, QString textToSave, QString authorStr)
{
    int index = s.indexOf(".txt"); // определяем, есть ли в названии
                                   // строка ".txt"
    QFile file(s);
    if (file.open(QFile::WriteOnly))
    {
        if (index != -1)           // если текстовый файл (выполняются
            // 2 условия)
        {
            QTextStream stream(&file);
            stream <<  textToSave;
        }
        else {
            QDataStream stream(&file);
            if (authorStr == 0) {
                QByteArray b = QString("GB_Qt_Auth0").toUtf8();
                stream.writeRawData(b.data(), b.length());
            } else { // если автор есть, то после записи Magichead, записываем число символов в строке автора и самого автора
                QByteArray b = QString("GB_Qt_Auth1").toUtf8();
                QByteArray author = QString(authorStr).toUtf8();
                stream.writeRawData(b.data(), b.length());
                uint amount = author.length();
                stream.writeRawData(reinterpret_cast<char*>(&amount), sizeof amount);
                stream.writeRawData(author.data(), amount);
            }
            QHash<QChar, int>symbamount;
            symbamount.clear();
            QString str = textToSave;
            int amount = str.length();
            QString usedS = "";
            for (int i = 0; i < amount; ++i) {
                QChar ch = str.at(i);
                int index = usedS.indexOf(ch);
                if (index == -1)
                {
                    symbamount[ch] = 0;
                    usedS += ch;
                }
                else{
                    symbamount[ch]++;
                }
            }
            //********************************
            for (int i = 0; i < amount; ++i) {
                QChar chi = usedS[i];
                for (int j = i + 1; j < amount; ++j) {
                    QChar chj = usedS[j];
                    if (symbamount[chi] < symbamount[chj])
                    {
                        usedS[i] = chj;
                        usedS[j] = chi;
                        chi = chj;
                    }
                }
            }
            symbamount.clear();
            //**********************************************
            QByteArray b = usedS.toUtf8();
            amount = b.length();
            stream.writeRawData(reinterpret_cast<char*>(&amount), sizeof amount);
            stream.writeRawData(b.data(), amount);
            //***********************************************
            amount = str.length();
            for (int i = 0; i < amount; i++) {
                int index = usedS.indexOf(str.at(i));
                for (bool w = true; w;) {
                    char wr = index % 128;
                    index /= 128;
                    if (index) {
                        wr |= 0x80;
                        stream.writeRawData(&wr, 1); // старший бит
                        // сообщает, что
                        // значение состоит
                        // еще из 1 байта
                    }
                    else {
                        stream.writeRawData(&wr, 1);
                        w = false;
                    }
                }
            }

        }
        file.close();
        return true;
    }else {
        return false;
    }



}

