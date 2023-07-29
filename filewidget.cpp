#include "filewidget.h"
#include"common2.h"
filewidget::filewidget(QWidget *parent) : QWidget(parent)
{

    main_layout = new QVBoxLayout();
    first_layout = new QHBoxLayout();
    second_layout = new QHBoxLayout();
    third_layout = new QHBoxLayout();
    forth_layout = new QHBoxLayout();
    fifth_layout = new QHBoxLayout();
    sixth_layout = new QHBoxLayout();
    layout = new QHBoxLayout();

    label = new  QLabel("Select Algorithm   ",this);
    label2 = new QLabel("Select Cipher Mode",this);
    label3 = new QLabel("Select Bit          ",this);
    label4 = new QLabel("Key                      ",this);
    label5 = new QLabel("Eigen Vector Iv",this);
    selectfile = new QLabel("Select File ");
    save_file_label = new QLabel("save file to",this);
    tosave = new QLineEdit(this);
    tosave->setPlaceholderText("save file");

    savebtn = new QToolButton(this);
    savebtn->setIcon(QIcon(":/img/save.png"));

    algorithm = new QComboBox(this);
    cmode = new QComboBox(this);
    bitcombobox = new QComboBox(this);


    algorithm->addItems(algolist23);
    cmode->addItems(aesmode3);
    bitcombobox->addItems(bits3);


    key = new QLineEdit(this);
    iv = new QLineEdit(this);

    keylen = new QLabel("0",this);
    ivlen = new QLabel("0",this);


    key->setPlaceholderText("Enter key here");
    iv->setPlaceholderText("Enter Eigon vector here");


    frame = new QFrame(this);
    r1 = new QRadioButton("Encrypt");
    r2 = new QRadioButton("Decrypt");
    frame->setLayout(sixth_layout);
    r1->setChecked(true);

    QFrame *abd = new QFrame(this);
    file = new QRadioButton("File",this);
    folder = new QRadioButton("Folder",this);
     file->setChecked(true);
    file_folder = new QHBoxLayout();
    abd->setLayout(file_folder);
    file_folder->addWidget(file);
    file_folder->addWidget(folder);

    dowork = new QPushButton("do",this);
    pbar = new QProgressBar(this);
    pbar->setRange(0,100);
  //  pbar->setValue(0);
    pbar->setStyleSheet("text-align:center");



    last_layout= new QHBoxLayout();
    last_layout->addWidget(save_file_label);
    last_layout->addWidget(tosave);
    last_layout->addWidget(savebtn);
    //bin->setChecked(true);
    select = new QToolButton(this);
    select->setIcon(QIcon(":/img/open.jpeg"));
    toopen = new QLineEdit(this);
    toopen->setPlaceholderText("open file");


    first_layout->addWidget(label);
    first_layout->addWidget(algorithm);
    second_layout->addWidget(label2);
    second_layout->addWidget(cmode);
    third_layout->addWidget(label3);
    third_layout->addWidget(bitcombobox);
    forth_layout->addWidget(label4);
    forth_layout->addWidget(key);
    forth_layout->addWidget(keylen);
    fifth_layout->addWidget(label5);
    fifth_layout->addWidget(iv);
    fifth_layout->addWidget(ivlen);
    sixth_layout->addWidget(r1);
    sixth_layout->addWidget(r2);

    layout->addWidget(selectfile);
    layout->addWidget(toopen);
    layout->addWidget(select);

    main_layout->addLayout(first_layout);
    main_layout->addLayout(second_layout);
    main_layout->addLayout(third_layout);
    main_layout->addLayout(forth_layout);
    main_layout->addLayout(fifth_layout);
    main_layout->addWidget(frame);
    main_layout->addWidget(abd);
    main_layout->addLayout(layout);
    main_layout->addLayout(last_layout);
    main_layout->addWidget(dowork);

    main_layout->addWidget(pbar);

    setLayout(main_layout);
    connector();
}
void filewidget::algochanged(int i )
{
    switch (i) {
    case 0:
        cmode->clear();
        cmode->addItems(aesmode3);
        bitcombobox->setDisabled(false);
        bitcombobox->clear();
        bitcombobox->addItems(bits3);
        break;
    case 1:
        cmode->clear();
        cmode->addItems(ariamode3);
        bitcombobox->setDisabled(false);
        bitcombobox->clear();
        bitcombobox->addItems(bits3);
        break;
    case 2:
        cmode->clear();
        cmode->addItems(bfmode_cast5_idea3);
        bitcombobox->clear();
        bitcombobox->addItem("unusable");
        bitcombobox->setDisabled(true);

        break;
    case 3:
        cmode->clear();
        cmode->addItems(cameliamode3);
        bitcombobox->clear();
        bitcombobox->setDisabled(false);
        bitcombobox->addItems(bits3);
        break;
    case 4:
        cmode->clear();
        cmode->addItems(bfmode_cast5_idea3);
        bitcombobox->clear();
        bitcombobox->addItem("unusable");
        bitcombobox->setDisabled(true);
        break;
    case 5:
        cmode->clear();
        cmode->addItems(desmode3);
        bitcombobox->clear();
        bitcombobox->addItem("unusable");
        bitcombobox->setDisabled(true);
        break;
    case 6:
        //    triple des not implemented
        //        cmode->clear();
        //        cmode->addItems(aria);
        //        bitcombobox->clear();
        //        bitcombobox->addItems(bits);
        break;
    case 7:
        cmode->clear();
        cmode->addItems(bfmode_cast5_idea3);
        bitcombobox->clear();
        bitcombobox->addItem("unusable");
        bitcombobox->setDisabled(true);
        break;
    case 8:
        cmode->clear();
        cmode->addItems(rc23);
        bitcombobox->clear();
        bitcombobox->addItem("unusable");
        bitcombobox->setDisabled(true);
        break;

    case 9:
        cmode->clear();
        cmode->addItems(rc43);
        bitcombobox->clear();
        bitcombobox->addItem("unusable");
        bitcombobox->setDisabled(true);
        break;
    case 10:
        cmode->clear();
        cmode->addItems(rc53);
        bitcombobox->clear();
        bitcombobox->addItem("unusable");
        bitcombobox->setDisabled(true);
        break;
    case 11:
        cmode->clear();
        cmode->addItems(sm43);
        bitcombobox->clear();
        bitcombobox->addItem("unusable");
        bitcombobox->setDisabled(true);
        break;

    }
}
void filewidget::modechanged(int i)
{
    if(cmode->currentText()=="ecb"){iv->setDisabled(true);
        iv->clear();
        ivlen->setText("0");

    }
    else{ iv->setEnabled(true);

        //        ivlen->setText(QString::fromStdString(std::to_string(ivlen->text().lengt));

    }
}

void filewidget::openclicked()
{
    f  = new QFileDialog(this);
    if(file->isChecked()){
    f->setAcceptMode(QFileDialog::AcceptMode::AcceptOpen);
    }
    else {
        f->setFileMode(QFileDialog::Directory);
    }
    f->exec();

      if(f->selectedFiles().length() !=0)toopen->setText(f->selectedFiles().at(0));
}

void filewidget::saveclicked()
{
    QFileDialog *fd = new QFileDialog(this);
    //fd->setAcceptMode(QFileDialog::AcceptSave);
    if(file->isChecked()){
    fd->setAcceptMode(QFileDialog::AcceptMode::AcceptOpen);
    }
    else {
        fd->setFileMode(QFileDialog::Directory);
    }
    fd->exec();
    if(fd->selectedFiles().length() !=0)tosave->setText(fd->selectedFiles().at(0));
}
void filewidget::connector()
{
    connect(select,SIGNAL(clicked()),this,SLOT(openclicked()));
    connect(savebtn,SIGNAL(clicked()),this,SLOT(saveclicked()));
    connect(algorithm,SIGNAL(currentIndexChanged(int)),this,SLOT(algochanged(int)));
    connect(cmode,SIGNAL(currentIndexChanged(int)),this,SLOT(modechanged(int)));
    connect(dowork,SIGNAL(clicked()),this,SLOT(do_pressed()));
    connect(this,SIGNAL(ready(int)),this,SLOT(fileready(int)));
    connect(iv,SIGNAL(textChanged(const QString&)),this,SLOT(ivchanged2(const QString&)));
    connect(key,SIGNAL(textChanged(const QString&)),this,SLOT(keychanged2(const QString&)));
    connect(this,SIGNAL(progresschanged(int,int)),this,SLOT(update_progress(int,int)));

}
int filewidget::do_pressed()
{
    if(!std::filesystem::exists(toopen->text().toStdString()))
    {
        QMessageBox::information(this,"info","File is not found");

        return 0;
    }
        if(key->text().length()==0){
        key->setStyleSheet("border:1px solid red");
    }
    else{
        key->setStyleSheet("");
    }

    if(iv->isEnabled() && iv->text().length()==0){
        iv->setStyleSheet("border:1px solid red");
    }
    else{
        iv->setStyleSheet("");
    }
    if(bitcombobox->isEnabled()){

        int x = bitcombobox->currentText().toInt();
        if(x==128){
            if(key->text().length() != 16) {  key->setStyleSheet("border:1px solid red"); return 0;}
            else   key->setStyleSheet("");
        }
        else if(x==192){
            if(key->text().length() != 24) {  key->setStyleSheet("border:1px solid red"); return 0;}
            else   key->setStyleSheet("");
        }
        else if(x==256){
            if(key->text().length() != 32) {  key->setStyleSheet("border:1px solid red"); return 0;}
            else   key->setStyleSheet("");
        }
    }
    if(iv->isEnabled()){
        if(iv->text().length()!=16){
            iv->setStyleSheet("border:1px solid red"); return 0;
        }
        else
            iv->setStyleSheet("");
    }

    if(key->text().length() !=0 && f->selectedFiles().length() !=0 && iv->isEnabled() && iv->text().length() !=0 ){

        createthread();
    }
    if(key->text().length() !=0 &&  f->selectedFiles().length() !=0  && !iv->isEnabled() ){

        createthread();
    }

}

void filewidget::fileready(int x)
{
    if(x==1){
        dowork->setEnabled(1);
        QMessageBox::information(this,"info","File Encrypted Successfully");
    }
    if(x==2){
        dowork->setEnabled(1);
        QMessageBox::information(this,"info","File Decrypted Successfully");


    }
}

void filewidget::createthread()
{
    dowork->setDisabled(true);
    QString AL = algorithm->currentText();
    QString mode = cmode->currentText();
    const EVP_CIPHER *xbp;
    QString s;
    if(bitcombobox->isEnabled())
    {
        s.append(AL);
        s.append("-");
        s.append(bitcombobox->currentText());
        s.append("-");
        s.append(mode);
        xbp= EVP_get_cipherbyname(s.toStdString().c_str());
    }
    else{
        if(strcmp(algorithm->currentText().toStdString().c_str(),"Blowfish")==0)
            s.append("bf");

        else s.append(AL);
        s.append("-");
        s.append(mode);
        xbp= EVP_get_cipherbyname(s.toStdString().c_str());
    }
    if(xbp != 0){
        QString s;
        if(tosave->text().length()==0){
            s = f->selectedFiles().at(0);
            s.append(".denc");
        }else s= tosave->text();
        if(file->isChecked()){
        std::thread tmxx(threadcall,xbp,f->selectedFiles().at(0),s,key->text(),iv->text(),(int)r1->isChecked(),this);
        tmxx.detach();}
        else{
            std::thread tmxx(encryptFolder,xbp,f->selectedFiles().at(0),s,key->text(),iv->text(),(int)r1->isChecked(),this);
            tmxx.detach();
        }
    }
}

void filewidget::do_ui(int x)
{
    emit ready(x);
}
void filewidget::encryptFolder(const EVP_CIPHER *C,QString plain,QString enc,QString key,QString iv,bool encrypt,filewidget* t){
    if(!std::filesystem::exists(plain.toStdString()))return;

    for (auto const& dir_entry : std::filesystem::directory_iterator{plain.toStdString()})
       {
           if(dir_entry.is_regular_file()){
               std::string s = enc.toStdString();
               std::filesystem::path pathx(s);
               pathx /= dir_entry.path().filename().string();

               if(encrypt){
                   Encrypt_File(C,key.toStdString().c_str(),iv.toStdString().c_str(),dir_entry.path().string().c_str(),pathx.string().c_str(),t);
                   t->do_ui(1);
               }
               else{
                   qInfo() << "decrypt is called";
                   Decrypt_File(C,key.toStdString().c_str(),iv.toStdString().c_str(),dir_entry.path().string().c_str(),pathx.string().c_str(),t);
                   t->do_ui(2);

               }
           }
       }
}

void filewidget::threadcall(const EVP_CIPHER *C,QString plain,QString enc,QString key,QString iv,bool encrypt,filewidget* t)
{

    if(encrypt==true){
        Encrypt_File(C,key.toStdString().c_str(),iv.toStdString().c_str(),plain.toStdString().c_str(),enc.toStdString().c_str(),t);

        t->do_ui(1);
//        emit t->textready(coded,len);

    }
    else{
        qInfo("decrypting file");
        Decrypt_File(C,key.toStdString().c_str(),iv.toStdString().c_str(),plain.toStdString().c_str(),enc.toStdString().c_str(),t);

        t->do_ui(2);

    }
}

void filewidget::keychanged2(const QString & text)
{
    keylen->setText(QString::fromStdString(std::to_string(text.length())));
}

void filewidget::ivchanged2(const QString & text)
{
    if(iv->isEnabled()){

        ivlen->setText(QString::fromStdString(std::to_string(text.length())));
    }
}

void filewidget::update_progress(int x,int y)
{
    pbar->setValue(x);
    QString s;
    if(y==1){
        if(x==100) s = "Encrypted ";
        else
         s = "Encrypting ";

        s.append(std::to_string(x).c_str());
        s.append("%");
        pbar->setFormat(s);
    }
    else{
        if(x==100) s = "Decrypted ";
        else
         s = "Decrypting ";

        s.append(std::to_string(x).c_str());
        s.append("%");
        pbar->setFormat(s);
    }
}

void filewidget::progress(int x,int y)
{
    emit progresschanged(x,y);
}
