#include "mywindow.h"
#include "random.h"
void read(QVector<QString>&);


MyWindow::MyWindow(QWidget *parent) : QDialog(parent)
{
    mode = new QComboBox;
    label = new QLabel("Текст");
    line = new QLineEdit;
    okey = new QPushButton("Okey");
    read_but = new QPushButton("Read");

    okey->setEnabled(false);
    mode->addItem("Зашифрувати");
    mode->addItem("Розшифрувати");

    QHBoxLayout *leftcenter = new QHBoxLayout;
    leftcenter->addWidget(label);
    leftcenter->addWidget(line);

    QVBoxLayout *left = new QVBoxLayout;
    left->addWidget(mode);
    left->addLayout(leftcenter);

    QVBoxLayout *right = new QVBoxLayout;
    right->addWidget(okey);
    right->addWidget(read_but);

    QHBoxLayout *main = new QHBoxLayout;
    main->addLayout(left);
    main->addLayout(right);

    setLayout(main);
    read_insert_map();

    connect(line, SIGNAL(textChanged(QString)), this, SLOT(okEnable(QString)));
    connect(okey, SIGNAL(clicked()), this, SLOT(okPressed()));
    connect(read_but, SIGNAL(clicked()), this, SLOT(readPressed()));
}

void MyWindow::okEnable(QString str){
    okey->setEnabled(!str.isEmpty());
}
void MyWindow::okPressed(){
    if(mode->currentIndex() == 0)
        emit Sig(cipher());
    else if(mode->currentIndex() == 1)
        emit Sig(decryption());
}
void MyWindow::readPressed(){
    read_insert_map();
}

QString MyWindow::cipher(){
    QString string(line->text()), out;
    for(const auto &ch : string){
        if(chars.contains(ch)){ //If char is in map
            const auto &vec = chars[ch]; //Get vector with this key
            const auto &par = vec.at(Random::get(0, vec.size()-1)); //Get random pair
            out.append(QString::number(par.first) + '/' + QString::number(par.second) + ',');
        }
        else
            out += ch;
    }
    return out;
}

QString MyWindow::decryption(){
    read(strings_stih);
    QString encr_string(line->text());

    int first_beg(0), first_end(0), second_beg(0), second_end(0);
    QRegularExpression reg("\\d{1,2}/\\d{1,2},") ;
    first_beg = encr_string.indexOf(reg);
    while(first_beg != -1){
        first_end = encr_string.indexOf('/',first_beg);
        second_beg = first_end + 1;
        second_end = encr_string.indexOf(',', second_beg);

        QStringRef int1(&encr_string, first_beg, first_end-first_beg);
        QStringRef int2(&encr_string, second_beg, second_end-second_beg);
        qDebug() << int1 << ' ' << int2;
        int str = int1.toInt();
        int col = int2.toInt();
        QChar ch = strings_stih.at(str).at(col);

        encr_string.replace(first_beg, second_end - first_beg + 1, ch);
        first_beg = encr_string.indexOf(reg, first_beg);
    }
    return encr_string;
}

void MyWindow::read_insert_map(){
    read(strings_stih);

    QFile write("I:/VANIA GAMES/Qt/l3/out.txt");
    if(write.open(QIODevice::WriteOnly)){
        QTextStream out(&write);
        for(const auto &i : strings_stih)
          out << i << endl;
    }

    for(size_t str = 0; str != strings_stih.size(); ++str)
        for(size_t col = 0; col != strings_stih.at(str).size(); ++col){
            chars[strings_stih.at(str).at(col)].push_back({str,col});
        }

    write.close();
}

void read(QVector<QString> &strings_stih){
    QFile stih("I:/VANIA GAMES/Qt/l3/stih.txt");
    if(stih.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&stih);
        QString temp;
        while(!in.atEnd()){
            temp = in.readLine();
            strings_stih.push_back(temp);
        }
    }
   for(auto &string : strings_stih){
        string.remove(QRegularExpression("[\\s,.:?!-]"));
    }
    stih.close();
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
    QFile write("I:/VANIA GAMES/Qt/l3/fileout.txt");
    if(write.open(QIODevice::WriteOnly)){
        write.write(text->toPlainText().toUtf8());
        msg->setText("Successful write");
        msg->show();
        write.close();
    }
}

