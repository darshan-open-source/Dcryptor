#include "textwidget.h"
#include<Algorithms_list.h>

#include"base64.h"
#include"common.h"
#include<algo_widget.h>
#include<openssl/provider.h>
textwidget::textwidget(QWidget *parent) : QWidget(parent)
{
  OSSL_PROVIDER_load(NULL, "legacy");
  OSSL_PROVIDER_load(NULL, "default");

    main_layout = new QVBoxLayout();


    t = new QTextEdit(this);
    t->setPlaceholderText("Enter Text Here");

    dowork = new QPushButton("Encrypt",this);
    pbar = new QProgressBar(this);
    pbar->setFormat("Nothing");
    pbar->setRange(0,100);
    pbar->setValue(0);
    pbar->setStyleSheet("text-align:center");

    out = new QTextBrowser(this);
    gb = new QGroupBox("save to file",this);
    last_layout= new QHBoxLayout();

    bin = new QRadioButton("binary",gb);
    base64encoded = new QRadioButton("Base64",gb);

    save = new QPushButton("save",this);

    last_layout->addWidget(bin);
    last_layout->addWidget(base64encoded);
    last_layout->addWidget(save);
    gb->setLayout(last_layout);

    algo_widgetx = new algo_widget(this);

    main_layout->addWidget(algo_widgetx);
    main_layout->addWidget(t);
    main_layout->addWidget(dowork);
    main_layout->addWidget(pbar);

    main_layout->addWidget(out);
    main_layout->addWidget(gb);

    setLayout(main_layout);
   connector();
}

void textwidget::addAllAlgorithms()
{

    for (std::map<std::string, algorithm_data>::iterator i = all_algorithms.begin(); i != all_algorithms.end(); i++)
    {
        algorithm->addItem(QString(i->first.c_str()));
    }
}

void textwidget::addBitsAndModes(QString s)
{
    algorithm_data a = all_algorithms[s.toStdString()];
    for (int i = 0; i < a["bits"].size(); i++) {
        // add bits
        bitcombobox->addItem(QString(a["bits"][i].c_str()));
    }


    for (int i = 0; i < a["modes"].size(); i++) {
        // add modes
        cmode->addItem(QString(a["modes"][i].c_str()));

    }
}

void textwidget::connector()
{
    
    connect(dowork,SIGNAL(clicked()),this,SLOT(do_pressed()));
    connect(this,SIGNAL(textready(std::string)),this,SLOT(text_is_ready(std::string)));
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
void textwidget::algochanged(int i)
{
    bitcombobox->clear();
    cmode->clear();
    addBitsAndModes(algorithm->currentText());
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
   if(algo_widgetx->isIVEnabled()){
       QString cmodetext = algo_widgetx->getMode();
       QString key_text = algo_widgetx->getKey();
       QString iv_text = algo_widgetx->getIv();

    if(  cmodetext == "gcm" || cmodetext == "ccm"){
        if(iv_text.length()!=8){

            //iv->setStyleSheet("border:1px solid red");

            return 0;
        }
    }else if(cmodetext == "cbc" || cmodetext == "cfb"|| cmodetext == "ctr"||cmodetext == "ofb"||cmodetext == "cfb8"||cmodetext == "cfb1"||cmodetext == "xts"){
        if(iv_text.length()!=16){
            //iv->setStyleSheet("border:1px solid red");

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

void textwidget::encryptDecryptButtionChanged()
{

    if (r1->isChecked())
    {
        dowork->setText("Encrypt");

    }
    else dowork->setText("Decrypt");
}
