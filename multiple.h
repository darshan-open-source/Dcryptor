#ifndef MULTIPLE_H
#define MULTIPLE_H

#include <QWidget>
#include<qtablewidget.h>
#include<qprogressbar.h>
#include<QComboBox>
#include<qpushbutton.h>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<qlabel.h>
#include<vector>
#include<qtoolbutton.h>
class multiple : public QWidget
{
    Q_OBJECT
public:
    explicit multiple(QWidget *parent = nullptr);

     QTableWidget *tabel;
     QVBoxLayout *mainlayout;
     QHBoxLayout *algo_layout,*mode_layout,*bit_layout,*new_layout;
     QComboBox *algorithm,*cmode,*bitcombobox;
     QLabel *algo_label,*mode_label,*bit_label,*new_label;
     QPushButton *dowork;
     int row;
     QToolButton *new_btn;
signals:

};

#endif // MULTIPLE_H
