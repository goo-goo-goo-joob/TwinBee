#pragma once
#include <QCoreApplication>
#include <QSettings>
#include <QString>
#include <QTextStream>
#include <QMap>
#include <QFile>
using namespace std;

class Initialization
{
    QString _path;
    QMap<QString, QString> map;
    Initialization(){}
    ~Initialization(){}
public:
    static Initialization& Instance()
    {
        static Initialization i;
        return i;
    }
    int Sett(QString key, const int & val = 0){
        if (map.find(key) == map.end()){
            return  val;
        }
        return map.value(key).toInt();
    }
    void Save(const QString &section,
              const QString &variable, int value){
        QSettings sett(_path, QSettings::IniFormat);
        QFile file(_path);
        if ((file.open(QIODevice::ReadWrite)))
        {
            QString line;
            QString comment;
            bool flag = false;
            QTextStream stream( &file );
            do {
                line = file.readLine();
                if (line.contains(section, Qt::CaseSensitive)
                        && !line.isEmpty() && line[0] != ';')
                {
                    stream << line;
                    line = file.readLine();
                    while(!line.isEmpty() && line != "\n" && line[0] != ';'){
                        if (line.contains(variable,
                                          Qt::CaseSensitive)
                                && !line.isEmpty()
                                && line[0] != ';')
                        {
                            flag = true;
                            line = variable + "="
                                    + QString::number(value)
                                    + '\n';
                        }
                        stream << line;
                        line = file.readLine();
                    }
                    if (!flag){
                        flag = true;
                        line = variable + "="
                                + QString::number(value)
                                + "\n\n";
                    }
                }
                stream << line;
            } while (!line.isEmpty());
            if (!flag){
                stream << "\n\n[" + section + "]" + '\n';
                stream << variable + "="
                          + QString::number(value) + "\n";
            }
            file.resize(0);
            file.close();
        }
    }
    QString Parse(QString &str, QString &sec){
        //ignore comments
        if (str[0] == ';')
            return "";
        //init section
        if (str[0] == '['){
            int i = 1;
            sec="";
            while (str[i] != ']'){
                sec.append(str[i]);
                i++;
            }
            sec.append('/');
            return sec;
        }
        //init variable
        int i = 0;
        QString key="";
        while(str[i] != 0 && str[i] != '='){
            if (str[i] == ' ')
                i++;
            else{
                key.append(str[i]);
                i++;
            }
        }
        QString val="";
        i++;
        while(str[i] != 0 && str[i] != ';'){
            if (str[i] == ' ')
                i++;
            else{
                val.append(str[i]);
                i++;
            }
        }
        if(val.length())
            map.insert(sec + key, val);
        return sec;
    }
    void Init(QString p)
    {
        _path = QCoreApplication:: applicationDirPath();
        _path.append("/" + p);
        QSettings sett(_path, QSettings::IniFormat);
        QFile file(_path);
        if ((file.open(QIODevice::ReadOnly)))
        {
            QString str, sec;
            while(!file.atEnd())
            {
                str = file.readLine();
                sec = Parse(str, sec);
            }
            file.close();
        }
    }
};
