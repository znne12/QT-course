#include "insertspecialchar.h"


insertSpecialChar::insertSpecialChar()
{

}
insertSpecialChar::~insertSpecialChar()
{

}

QString insertSpecialChar::replaceSpecSyms(QString in, bool *addSpecSym){
    for(auto now : listOfReplacements){
        do{
            if (in.contains(now.first)) {in.replace(now.first, now.second); *addSpecSym = true;}
        }while(in.contains(now.first));
    }
    return in;
}
