#include "textwidget.h"
#include<Algorithms_list.h>

#include"base64.h"
#include"common.h"
#include<algo_widget.h>
#include<openssl/provider.h>
#include<qmessagebox.h>
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
    connect(algo_widgetx, SIGNAL(encryptDecryptRadioButtonChanged(bool)), this, SLOT(encryptDecryptButtionChanged(bool)));
}

void textwidget::createthread(const EVP_CIPHER* xbp)
{
    dowork->setDisabled(true);
   
    if(xbp != 0){

        std::thread tmxx(threadcall,this,xbp,t->toPlainText(),algo_widgetx->getKey(), algo_widgetx->getIv(), (int)algo_widgetx->isEncryptedChecked());
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
    EVP_CIPHER_free((EVP_CIPHER*)C);
}


int textwidget::do_pressed()
{
    algo_widgetx->highlightIV(false);
    algo_widgetx->highlightkey(false);


    
    QString s;
   const  EVP_CIPHER* xbp;
    if (!algo_widgetx->isBitCombooxDisabled())
    {
        s.append(algo_widgetx->getAlgorithm());
        s.append("-");
        s.append(algo_widgetx->getBit());
        s.append("-");
        s.append(algo_widgetx->getMode());

       xbp = (const EVP_CIPHER*) EVP_get_cipherbyname(s.toStdString().c_str());

    }
    else {
        if (strcmp(algo_widgetx->getAlgorithm().toStdString().c_str(), "Blowfish") == 0)
            s.append("bf");

        else s.append(algo_widgetx->getAlgorithm());
        s.append("-");
        s.append(algo_widgetx->getMode());
    
        qInfo() << s.toStdString().c_str();
        xbp = EVP_get_cipherbyname(s.toStdString().c_str());
    }


    int key_len = EVP_CIPHER_get_key_length(xbp);
    int iv_len = EVP_CIPHER_get_iv_length(xbp);

    if (algo_widgetx->getKey().length() != key_len)
    {
        algo_widgetx->highlightkey(true);
        return 0;
    }
    if (algo_widgetx->getIv().length() != iv_len)
    {
        algo_widgetx->highlightIV(true);


        return 0;
    }
  


  
   
    


    
    if(t->toPlainText().length() !=0 ){

        createthread(xbp);
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

void textwidget::encryptDecryptButtionChanged(bool val)
{

    if (val)
    {
        dowork->setText("Encrypt");

    }
    else dowork->setText("Decrypt");
}
