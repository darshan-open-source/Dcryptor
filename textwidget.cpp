#include "textwidget.h"
#include"CryptoUtil.h"

textwidget::textwidget(QWidget *parent) : QWidget(parent)
{
  OSSL_PROVIDER_load(NULL, "legacy");
  OSSL_PROVIDER_load(NULL, "default");

    main_layout = new QVBoxLayout();


    t = new QTextEdit(this);
    t->setPlaceholderText("Enter Text Here");
    t->setStyleSheet("QTextEdit { background-color: white; border: 1px solid #a8a8a8; padding: 5px; border-radius: 5px;}");

    dowork = new QPushButton("Encrypt",this);

    dowork->setStyleSheet("QPushButton{height:25px;}QPushButton:hover{background-color:#007bff;border-radius:4px;color:white;border-style: inset;}");

    pbar = new QProgressBar(this);
    pbar->setFormat("Nothing");
    pbar->setRange(0,0);
    pbar->setValue(0);
    pbar->setStyleSheet("text-align:center");

    out = new QTextBrowser(this);
    out->setStyleSheet("  background-color: white; border: 1px solid #a8a8a8; padding: 5px; border-radius: 5px;");

    gb = new QGroupBox("save to file",this);
    last_layout= new QHBoxLayout();

    bin = new QRadioButton("binary",gb);
    base64encoded = new QRadioButton("Base64",gb);

    save = new QPushButton("Save",this);
    save->setStyleSheet("QPushButton{height:25px;}QPushButton:hover{background-color:#007bff;border-radius:4px;color:white;border-style: inset;}");


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
        pbar->setRange(0, 100);

        createthread(xbp);
    }


}

void textwidget::text_is_ready(std::string s)
{
    pbar->setRange(0,0);

    QString sx(s.c_str());

if(sx.length()!=0){
    out->setText(sx);
}
else {
    out->setText("operation not does not work");
}


    dowork->setEnabled(true);
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
