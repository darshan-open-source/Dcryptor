#include "algo_widget.h"

algo_widget::algo_widget(QWidget* parent):QWidget(parent)
{

	QVBoxLayout* main_layout = new QVBoxLayout();


    main_layout = new QVBoxLayout();
    first_layout = new QHBoxLayout();
    second_layout = new QHBoxLayout();
    third_layout = new QHBoxLayout();
    forth_layout = new QHBoxLayout();
    fifth_layout = new QHBoxLayout();
    sixth_layout = new QHBoxLayout();


    label = new  QLabel("Select Algorithm   ", this);
    label2 = new QLabel("Select Cipher Mode", this);
    label3 = new QLabel("Select Bit          ", this);
    label4 = new QLabel("Key                   ", this);
    label5 = new QLabel("Eigen Vector Iv ", this);
   
    algorithm = new QComboBox(this);
    addAllAlgorithms();

    cmode = new QComboBox(this);
    bitcombobox = new QComboBox(this);


    key = new QLineEdit(this);
    iv = new QLineEdit(this);

    keylen = new QLabel("0", this);
    ivlen = new QLabel("0", this);


    key->setPlaceholderText("Enter key here");
    iv->setPlaceholderText("Enter Eigon vector here");


    
    r1 = new QRadioButton("Encrypt");
    r2 = new QRadioButton("Decrypt");
    r1->setChecked(true);

    frame = new QFrame(this);
    frame->setLayout(sixth_layout);
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



	setLayout(main_layout);
    attachConnect();

}

QString algo_widget::getAlgorithm()
{
    return algorithm->currentText();
}

QString algo_widget::getBit()
{
    return bitcombobox->currentText();
}

QString algo_widget::getMode()
{
    return cmode->currentText();
}

QString algo_widget::getKey()
{
    return key->text();
}

QString algo_widget::getIv()
{
    return  iv->text();
}

void algo_widget::setIvDisabled(bool value)
{
    iv->setDisabled(value);
}

bool algo_widget::isIVEnabled()
{
    return iv->isEnabled();
}


void algo_widget::addAllAlgorithms()
{

    for (std::map<std::string, algorithm_data>::iterator i = all_algorithms.begin(); i != all_algorithms.end(); i++)
    {
        algorithm->addItem(QString(i->first.c_str()));
    }
}

void algo_widget::addBitsAndModes(QString s)
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

void algo_widget::attachConnect()
{
    connect(algorithm, SIGNAL(currentIndexChanged(int)), this, SLOT(algochanged(int)));
    connect(cmode, SIGNAL(currentIndexChanged(int)), this, SLOT(modechanged(int)));
    
    connect(iv, SIGNAL(textChanged(const QString&)), this, SLOT(ivchanged2(const QString&)));
    connect(key, SIGNAL(textChanged(const QString&)), this, SLOT(keychanged2(const QString&)));
    connect(r1, SIGNAL(clicked()), this, SLOT(encryptDecryptButtionChanged()));
    connect(r2, SIGNAL(clicked()), this, SLOT(encryptDecryptButtionChanged()));

    // for inialize bit and modes in ui
    algorithm->currentIndexChanged(algorithm->currentIndex());
}



void algo_widget::keychanged2(const QString& text)
{
    keylen->setText(QString::fromStdString(std::to_string(text.length())));
}

void algo_widget::ivchanged2(const QString& text)
{
    if (iv->isEnabled()) {

        ivlen->setText(QString::fromStdString(std::to_string(text.length())));
    }
}

void algo_widget::algochanged(int i)
{
    bitcombobox->clear();
    cmode->clear();
    addBitsAndModes(algorithm->currentText());
}

void algo_widget::modechanged(int i)
{
    if (cmode->currentText() == "ecb") {
        iv->setDisabled(true);
        iv->clear();
        ivlen->setText("0");

    }
    else {
        iv->setEnabled(true);


    }
}

