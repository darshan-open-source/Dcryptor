#pragma once
#include<qlineedit.h>
#include<qkeysequence.h>
#include<qevent.h>
#include<qcombobox.h>
#include<openssl/evp.h>
#include <openssl/rand.h>

class MyLineEdit :
    public QLineEdit
{
public:
    MyLineEdit(bool isKey, QWidget* parent = nullptr);
protected:
    void keyPressEvent(QKeyEvent*);
private:
    QComboBox* algo, * bit, * cmode;
    bool iskey;
};

