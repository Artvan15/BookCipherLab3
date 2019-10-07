#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QtWidgets>
#include <QFile>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>

class MyWindow : public QDialog
{
    Q_OBJECT
public:
    MyWindow(QWidget *parent = nullptr);
private:
    QLabel *label;
    QLineEdit *line;
    QPushButton *okey;
    QVector<std::pair<QChar, std::pair<size_t, size_t>>> chars;

private:
    QString cipher();
private slots:
    void okEnable(QString);
    void okPressed();
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
