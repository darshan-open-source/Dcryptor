#include "multiple.h"

multiple::multiple(QWidget *parent) : QWidget(parent)
{
mainlayout= new QVBoxLayout();
algo_layout = new QHBoxLayout();
mode_layout = new QHBoxLayout();
bit_layout = new QHBoxLayout();
new_layout = new QHBoxLayout();

algo_label = new QLabel("select algorithm",this);
mode_label = new QLabel("select mode",this);
bit_label = new QLabel("select bit",this);
new_label = new QLabel("Add new Row",this);



algorithm = new QComboBox(this);
cmode = new QComboBox(this);
bitcombobox = new QComboBox(this);

dowork = new QPushButton("do",this);
new_btn = new QToolButton(this);
new_btn->setIcon(QIcon(":/img/plus.jpeg"));
new_btn->setStyleSheet("border:none");

algo_layout->addWidget(algo_label);
algo_layout->addWidget(algorithm);
mode_layout->addWidget(mode_label);
mode_layout->addWidget(cmode);
bit_layout->addWidget(bit_label);
bit_layout->addWidget(bitcombobox);
new_layout->addWidget(new_label);
new_layout->addWidget(new_btn);

mainlayout->addLayout(algo_layout);
mainlayout->addLayout(mode_layout);
mainlayout->addLayout(bit_layout);

tabel = new QTableWidget(this);

tabel->setColumnCount(3);
tabel->setHorizontalHeaderLabels({"open file","save file","progress"});
tabel->insertRow(0);






mainlayout->addLayout(new_layout);
mainlayout->addWidget(tabel);
mainlayout->addWidget(dowork);

setLayout(mainlayout);
}
