#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QtWidgets>
#include <QFile>
#include <string>
#include <bitset>
#include <algorithm>

class MyWindow : public QDialog
{
    Q_OBJECT
public:
    MyWindow(QWidget *parent = nullptr);
private:
    QComboBox *mode;
    QLabel *label;
    QLineEdit *line;
    QPushButton *okey;
    QPushButton *read_but;
    QMap<QChar, QVector<std::pair<size_t, size_t>>> chars;
    QVector<QString> strings_stih;

private:
    void read_insert_map();
    QString cipher();
    QString decryption();
private slots:
    void okEnable(QString);
    void okPressed();
    void readPressed();
signals:
    void Sig(QString);

};

class Interface : public QDialog{
    Q_OBJECT
public:
    Interface(QWidget *parent = nullptr);
private:
    QTextEdit *text;
    QPushButton *write;
public slots:
    void Message(QString);
    void writePressed();

};

#endif // MYWINDOW_H
