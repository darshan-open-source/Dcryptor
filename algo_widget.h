#pragma once
#include <qwidget.h>
#include"Algorithms_list.h"


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
class algo_widget :
    public QWidget
{
    Q_OBJECT
public:
    explicit algo_widget(QWidget* parent = nullptr);

    QString getAlgorithm();
    QString getBit();
    QString getMode();
    QString getKey();
    QString getIv();
    void setIvDisabled(bool);
    bool isIVEnabled();
    bool isBitCombooxDisabled();

    void highlightIV(bool);
    void highlightkey(bool);
  
    

    QLabel* keylen, * ivlen;
    QLabel* label, * label2, * label3, * label4, * label5;
    QComboBox* algorithm, * cmode, * bitcombobox;
    QLineEdit* key, * iv;
    QHBoxLayout* first_layout, * second_layout, * third_layout, * forth_layout, * fifth_layout, * sixth_layout, * last_layout;
    QFrame* frame;
    QRadioButton* r1, * r2;


    void addAllAlgorithms();
    void addBitsAndModes(QString s);
    void attachConnect();


public slots:
    void algochanged(int i);
    void modechanged(int i);
    void keychanged2(const QString&);
    void ivchanged2(const QString&);
    
};

