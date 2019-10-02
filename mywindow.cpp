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
    QFile stih("C:/Users/Ivan Che/Documents/qtProjects/BookCipherLab3/stih.txt");
    if(stih.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&stih);
        QString temp;
        while(!in.atEnd()){
            temp = in.readLine();
            strings.push_back(temp);
        }
    }
    for(auto &str : strings){
        for(size_t ind = 0; ind < str.size(); ++ind){
            if(ispunct(str.at(ind).toLatin1()) || isspace(str.at(ind).toLatin1()))
                str.remove(ind,1);
        }

    }

    QFile write("C:/Users/Ivan Che/Documents/qtProjects/BookCipherLab3/out.txt");
    if(write.open(QIODevice::WriteOnly)){
        QTextStream out(&write);
        for(const auto &i : strings)
          out << i << endl;
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

