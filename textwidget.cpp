#include "textwidget.h"

#include"base64.h"
#include"common.h"
#include<openssl/provider.h>
textwidget::textwidget(QWidget *parent) : QWidget(parent)
{
  OSSL_PROVIDER_load(NULL, "legacy");
  OSSL_PROVIDER_load(NULL, "default");

    main_layout = new QVBoxLayout();
    first_layout = new QHBoxLayout();
    second_layout = new QHBoxLayout();
    third_layout = new QHBoxLayout();
    forth_layout = new QHBoxLayout();
    fifth_layout = new QHBoxLayout();
    sixth_layout = new QHBoxLayout();


    label = new  QLabel("Select Algorithm   ",this);
    label2 = new QLabel("Select Cipher Mode",this);
    label3 = new QLabel("Select Bit          ",this);
    label4 = new QLabel("Key                   ",this);
    label5 = new QLabel("Eigen Vector Iv ",this);

    algorithm = new QComboBox(this);
    cmode = new QComboBox(this);
    bitcombobox = new QComboBox(this);


    algorithm->addItems(algolist2);
    cmode->addItems(aesmode);
    bitcombobox->addItems(bits);


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
    t = new QTextEdit(this);
    t->setPlaceholderText("Enter Text Here");

    dowork = new QPushButton("do",this);
    pbar = new QProgressBar(this);
    pbar->setRange(0,100);
    pbar->setStyleSheet("text-align:center");
   //
//  pbar->setFormat("dddd");
    out = new QTextBrowser(this);
    gb = new QGroupBox("save to file",this);
    last_layout= new QHBoxLayout();

    bin = new QRadioButton("binary",gb);
    base64encoded = new QRadioButton("Base64",gb);
    //bin->setChecked(true);

    save = new QPushButton("save",this);

    last_layout->addWidget(bin);
    last_layout->addWidget(base64encoded);
    last_layout->addWidget(save);
    gb->setLayout(last_layout);

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



    main_layout->addLayout(first_layout);
    main_layout->addLayout(second_layout);
    main_layout->addLayout(third_layout);
    main_layout->addLayout(forth_layout);
    main_layout->addLayout(fifth_layout);
    main_layout->addWidget(frame);
    main_layout->addWidget(t);
    main_layout->addWidget(dowork);
    main_layout->addWidget(pbar);

    main_layout->addWidget(out);
    main_layout->addWidget(gb);

    setLayout(main_layout);
    connector();
}

void textwidget::connector()
{
    connect(algorithm,SIGNAL(currentIndexChanged(int)),this,SLOT(algochanged(int)));
    connect(cmode,SIGNAL(currentIndexChanged(int)),this,SLOT(modechanged(int)));
    connect(dowork,SIGNAL(clicked()),this,SLOT(do_pressed()));
    connect(this,SIGNAL(textready(std::string)),this,SLOT(text_is_ready(std::string)));
    connect(iv,SIGNAL(textChanged(const QString&)),this,SLOT(ivchanged2(const QString&)));
    connect(key,SIGNAL(textChanged(const QString&)),this,SLOT(keychanged2(const QString&)));
    connect(this,SIGNAL(progresschanged(int)),this,SLOT(update_progress(int)));
    connect(save,SIGNAL(clicked()),this,SLOT(saveclicked()));

}

void textwidget::createthread()
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
        qInfo()<<s.toStdString().c_str();
        xbp= EVP_get_cipherbyname(s.toStdString().c_str());
    }
    if(xbp != 0){

        std::thread tmxx(threadcall,this,xbp,t->toPlainText(),key->text(),iv->text(),(int)r1->isChecked());
        tmxx.detach();
    }
}

void textwidget::do_ui(char *x, int y)
{
    qInfo()<<"ddd";

//    emit textready();
}

void textwidget::threadcall(textwidget* t,const EVP_CIPHER *C,QString text,QString key,QString iv,bool encrypt)
{
    qInfo("thread called");

    char bu[5055];
    char coded[50000];
    if(encrypt==true){
        qInfo("e called");
        int leng =   Encrypt_Data(C,(char*)key.toStdString().c_str(),(char*)iv.toStdString().c_str(),(char*)text.toStdString().c_str(),text.length(),bu,t);

        int len = Base64_Encode(bu,leng,coded);
        qInfo(coded);
//        t->do_ui(coded,len);
        emit t->textready(std::string(coded,len));

    }
    else{
        qInfo("decryption called");
        int len = Base64_Decode((char*)text.toStdString().c_str(),text.length(),coded);
        int xpp =   Decrypt_Data(C,(char*)key.toStdString().c_str(),(char*)iv.toStdString().c_str(),coded,len,bu);

        emit t->textready(std::string(bu,xpp));


    }
}
void textwidget::algochanged(int i )
{
    switch (i) {
    case 0:
        cmode->clear();
        cmode->addItems(aesmode);
        bitcombobox->setDisabled(false);
        bitcombobox->clear();
        bitcombobox->addItems(bits);
        break;
    case 1:
        cmode->clear();
        cmode->addItems(ariamode);
        bitcombobox->setDisabled(false);
        bitcombobox->clear();
        bitcombobox->addItems(bits);
        break;
    case 2:
        cmode->clear();
        cmode->addItems(bfmode_cast5_idea);
        bitcombobox->clear();
        bitcombobox->addItem("unusable");
        bitcombobox->setDisabled(true);

        break;
    case 3:
        cmode->clear();
        cmode->addItems(cameliamode);
        bitcombobox->clear();
        bitcombobox->setDisabled(false);
        bitcombobox->addItems(bits);
        break;
    case 4:
        cmode->clear();
        cmode->addItems(bfmode_cast5_idea);
        bitcombobox->clear();
        bitcombobox->addItem("unusable");
        bitcombobox->setDisabled(true);
        break;
    case 5:
        cmode->clear();
        cmode->addItems(desmode);
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
        cmode->addItems(bfmode_cast5_idea);
        bitcombobox->clear();
        bitcombobox->addItem("unusable");
        bitcombobox->setDisabled(true);
        break;
    case 8:
        cmode->clear();
        cmode->addItems(rc2);
        bitcombobox->clear();
        bitcombobox->addItem("unusable");
        bitcombobox->setDisabled(true);
        break;

    case 9:
        cmode->clear();
        cmode->addItems(rc4);
        bitcombobox->clear();
        bitcombobox->addItem("unusable");
        bitcombobox->setDisabled(true);
        break;
    case 10:
        cmode->clear();
        cmode->addItems(rc5);
        bitcombobox->clear();
        bitcombobox->addItem("unusable");
        bitcombobox->setDisabled(true);
        break;
    case 11:
        cmode->clear();
        cmode->addItems(sm4);
        bitcombobox->clear();
        bitcombobox->addItem("unusable");
        bitcombobox->setDisabled(true);
        break;

    }
}

void textwidget::modechanged(int i)
{
    if(cmode->currentText()=="ecb"){iv->setDisabled(true);
        iv->clear();
        ivlen->setText("0");

    }
    else{ iv->setEnabled(true);

//        ivlen->setText(QString::fromStdString(std::to_string(ivlen->text().lengt));

    }
}

int textwidget::do_pressed()
{
   if(iv->isEnabled()){
    if(  cmode->currentText() == "gcm" || cmode->currentText() == "ccm"){
        if(iv->text().length()!=8){

            iv->setStyleSheet("border:1px solid red");

            return 0;
        }
    }else if(cmode->currentText() == "cbc" || cmode->currentText() == "cfb"|| cmode->currentText() == "ctr"||cmode->currentText() == "ofb"||cmode->currentText() == "cfb8"||cmode->currentText() == "cfb1"||cmode->currentText() == "xts"){
        if(iv->text().length()!=16){
            iv->setStyleSheet("border:1px solid red");

            return 0;
        }
    }
   }
    iv->setStyleSheet("");

    if(key->text().length()==0){
        key->setStyleSheet("border:1px solid red");
    }
    else{
        key->setStyleSheet("");
    }
    if(t->toPlainText().length()==0){
        t->setStyleSheet("border:1px solid red");
    }
    else{
        t->setStyleSheet("");
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

    qInfo() <<"j" <<key->text().length();
    if(key->text().length() !=0 && t->toPlainText().length() !=0 && iv->isEnabled() && iv->text().length() !=0 ){

        createthread();
    }
    if(key->text().length() !=0 && t->toPlainText().length() !=0 && !iv->isEnabled() ){

        createthread();
    }

}

void textwidget::text_is_ready(std::string s)
{
    QString sx(s.c_str());

if(sx.length()!=0){
    out->setText(sx);
}
else {
    out->setText("operation not does not work");
}
//    if(strlen(x)==0 && temp==0){
//        do_pressed();
//        temp++;
//    }
//    else if(strlen(x)==0 && temp!=0){
//        out->setText("Data can't be decrypted");
//    }
//    else{
//        out->setText(s);}

    dowork->setEnabled(true);
}

void textwidget::keychanged2(const QString & text)
{
    keylen->setText(QString::fromStdString(std::to_string(text.length())));
}

void textwidget::ivchanged2(const QString & text)
{
    if(iv->isEnabled()){

        ivlen->setText(QString::fromStdString(std::to_string(text.length())));
    }
}

void textwidget::update_progress(int x)
{
    pbar->setValue(x);
}

void textwidget::progress(int x)
{
    emit progresschanged(x);
}
void textwidget::saveclicked(){
    if(out->toPlainText().length()==0){
        return;
    }

    QFileDialog *fd = new QFileDialog(this);
    fd->setAcceptMode(QFileDialog::AcceptMode::AcceptSave);


        if(bin->isChecked()){
          char *x =(char*) malloc(out->toPlainText().length()+1);
            Base64_Decode(out->toPlainText().toStdString().c_str(),out->toPlainText().length(),x);
            QByteArray b(x);
            fd->saveFileContent(b);
            free(x);
        }
        else if(base64encoded->isChecked()){
            QByteArray  b(out->toPlainText().toStdString().c_str());
            fd->saveFileContent(b);
        }

}
