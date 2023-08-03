#ifndef TEXTWIDGET_H
#define TEXTWIDGET_H

#include <QWidget>

#include<QVBoxLayout>
#include<QHBoxLayout>
#include<qcombobox.h>
#include<QPushButton>
#include<QRadioButton>
#include<QGroupBox>
#include<qlineedit.h>
#include<qlabel.h>
#include<QTextEdit>
#include<QTextBrowser>
#include<qprogressbar.h>
#include<QFileDialog>
#include<QCheckBox>
#include<openssl/evp.h>
#include<thread>
#include<qtoolbutton.h>
#include"algo_widget.h"

class textwidget : public QWidget
{
    Q_OBJECT
public:
    explicit textwidget(QWidget *parent = nullptr);
    QVBoxLayout *main_layout;
    QHBoxLayout *first_layout,*second_layout,*third_layout,*forth_layout,*fifth_layout,*sixth_layout,*last_layout;
    QLabel *label,*label2,*label3,*label4,*label5;
    QComboBox *algorithm,*cmode,*bitcombobox;
    QLineEdit *key,*iv;
    QTextEdit *t;
    QRadioButton *r1,*r2,*bin,*base64encoded;
    QPushButton *dowork,*save;
    QTextBrowser *out;
    QFileDialog *diag;
    QProgressBar *pbar;
    algo_widget* algo_widgetx;

   QGroupBox *gb;
   int temp=0;
   QLabel *keylen,*ivlen;
QFrame *frame;
void addBitsAndModes(QString);
void addAllAlgorithms();

void connector();
void createthread(const EVP_CIPHER*);
void do_ui(char*,int);
static void threadcall(textwidget*,const EVP_CIPHER *C, QString text, QString key, QString iv, bool encrypt);
public slots:
void encryptDecryptButtionChanged(bool);

int do_pressed();
void text_is_ready(std::string);
void keychanged2(const QString &);
void ivchanged2(const QString &);
void update_progress(int);
void progress(int);
void saveclicked();
signals:
void textready(std::string);
void progresschanged(int);
};

#endif // TEXTWIDGET_H
