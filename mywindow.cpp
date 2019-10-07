#include "mywindow.h"
void read(QVector<std::pair<QChar, std::pair<size_t, size_t>>>&);



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
    read(chars);
    emit Sig(cipher());
}

void read(QVector<std::pair<QChar, std::pair<size_t, size_t>>> &chars){
    QVector<QString> strings;
    QFile stih("D:/Games/qtprojects/BookCipherLab3/stih.txt");
    if(stih.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&stih);
        QString temp;
        while(!in.atEnd()){
            temp = in.readLine();
            strings.push_back(temp);
        }
    }
    for(auto &str : strings){
        for(size_t ind = 0; ind < str.size();){
            if(ispunct(str.at(ind).toLatin1()) || isspace(str.at(ind).toLatin1()))
                str.remove(ind,1);
            else
                ++ind;
        }

    }

    QFile write("D:/Games/qtprojects/BookCipherLab3/out.txt");
    if(write.open(QIODevice::WriteOnly)){
        QTextStream out(&write);
        for(const auto &i : strings)
          out << i << endl;
    }

    for(size_t str = 0; str != strings.size(); ++str)
        for(size_t col = 0; col != strings.at(str).size(); ++col){
            QChar temp = strings.at(str).at(col);
            chars.push_back({temp,{str, col}});
        }

    QFile cipher("D:/Games/qtprojects/BookCipherLab3/cipher.txt");
    if(cipher.open(QIODevice::WriteOnly)){
        QTextStream out(&cipher);
        for(const auto &i : chars)
            out << i.first << ";" << i.second.first << '/' << i.second.second << ' ';
    }
}

QString MyWindow::cipher(){
    QString string(line->text()), out;
    for(auto &ch : string){
        auto it = std::find_if(chars.begin(), chars.end(),
                        [ch](std::pair<QChar, std::pair<size_t, size_t>> &it)->bool{
                        if(ch == it.first) return true;});
        if(it != chars.end())
            out.append(QString::number(it->second.first) + '/' + QString::number(it->second.second) + ',');
    }
    return out;
}

Interface::Interface(QWidget *parent):QDialog(parent){
    text = new QTextEdit;
    write = new QPushButton("Write");
    QVBoxLayout *main = new QVBoxLayout;
    main->addWidget(text);
    main->addWidget(write);
    setLayout(main);
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

