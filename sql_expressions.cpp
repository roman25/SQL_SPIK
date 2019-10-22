#include "sql_expressions.h"

QString SQLQueries::GetBinText()
{
    QString l_bintext = "";

    for (int i = 0; i < 256; i++)
    {
        l_bintext = l_bintext + "[Bin" + QString::number(i) + "][int], ";
    }
    return l_bintext;
}