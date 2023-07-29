#ifndef FILEWIDGET_H
#define FILEWIDGET_H

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
#include<qmessagebox.h>
#include<sys/stat.h>
#include<qtoolbutton.h>
class filewidget : public QWidget
{
    Q_OBJECT
public:
    explicit filewidget(QWidget *parent = nullptr);
    QVBoxLayout *main_layout;
    QHBoxLayout *layout,*first_layout,*second_layout,*third_layout,*forth_layout,*fifth_layout,*sixth_layout,*last_layout,*file_folder;
    QLabel *label,*label2,*label3,*label4,*label5,*selectfile,*save_file_label;
    QComboBox *algorithm,*cmode,*bitcombobox;
    QLineEdit *key,*iv,*tosave,*toopen;
    QFileDialog *f;
    QRadioButton *r1,*r2,*file,*folder;
    QPushButton *dowork,*save;
    QToolButton *select;
    QTextBrowser *out;
    QFileDialog *diag;
    QProgressBar *pbar;
    QCheckBox *c;
    QGroupBox *gb;
    int temp=0;
    QToolButton *savebtn;
    QLabel *keylen,*ivlen;
    QFrame *frame;
    void connector();
    void createthread();
    void do_ui(int);
    static void threadcall(const EVP_CIPHER *C, QString plainfile,QString encryptfile, QString key, QString iv, bool encrypt,filewidget*);
    static void encryptFolder(const EVP_CIPHER *C, QString plainfile,QString encryptfile, QString key, QString iv, bool encrypt,filewidget*);

public slots:
    void algochanged(int i);
    void modechanged(int i);
    int do_pressed();
    void fileready(int);
    void keychanged2(const QString &);
    void ivchanged2(const QString &);
    void update_progress(int,int);
    void progress(int,int);
    void openclicked();

    void saveclicked();
signals:
    void ready(int);
    void progresschanged(int,int);
};


#endif // FILEWIDGET_H
