#include "mywindow.h"
void read();


MyWindow::MyWindow(QWidget *parent) : QDialog(parent)
{
    label = new QLabel("Текст");
    line = new QLineEdit;
    okey = new QPushButton("Okey");

    okey->setEnabled(false);

    QHBoxLayout *leftcenter = new QHBoxLayout;
    leftcenter->addWidget(label);
    leftcenter->addWidget(line);

    QVBoxLayout *right = new QVBoxLayout;
    right->addWidget(okey);

    QHBoxLayout *main = new QHBoxLayout;
    main->addLayout(leftcenter);
    main->addLayout(right);

    setLayout(main);

    connect(line, SIGNAL(textChanged(QString)), this, SLOT(okEnable(QString)));
    connect(okey, SIGNAL(clicked()), this, SLOT(okPressed()));

}

void MyWindow::okEnable(QString str){
    okey->setEnabled(!str.isEmpty());
}
void MyWindow::okPressed(){
    read();
}
void read(){
    QVector<QString> strings;
    QFile stih("D:/Games/qtprojects/BookCipherLab3/stih.txt");
    if(stih.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&stih);
        while(!in.atEnd()){
            strings.push_back(in.readLine());
        }
    }

    QVector<QVector<QString>> words;
    for(auto &i : strings){
        QTextStream in(&i);
        QString temp;
        QVector<QString> tempVec;
        for(size_t i = 0; i != 5; ++i)
            while(!in.atEnd()){
                in >> temp;
                tempVec.push_back(temp);
            }
        words.push_back(tempVec);
    }
    QFile("")
    for(const auto &i : words){
       for(const auto &j : i)
           qDebug() << j << " // ";
    }
}

void Interface::Message(QString str){
    text->setText(str);
    text->setReadOnly(true);
    this->show();
}

void Interface::writePressed(){
    QMessageBox *msg = new QMessageBox;
    QFile write("I:/VANIA GAMES/Qt/fileout.txt");
    if(write.open(QIODevice::WriteOnly)){
        write.write(text->toPlainText().toUtf8());
        msg->setText("Successful write");
        msg->show();
        write.close();
    }
}

