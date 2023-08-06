#include "About_Decryptor.h"
// aboutpage.cpp
#include <QLabel>
#include <QVBoxLayout>
#include <QPixmap>
#include <QTextBrowser>

About_Decryptor::About_Decryptor(QWidget* parent) : QWidget(parent)
{
    // Main layout
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(20);

    // Application logo
    QLabel* logoLabel = new QLabel(this);
    QPixmap logoPixmap(":/img/icon.png"); // Replace with the path to your application logo
    logoLabel->setPixmap(logoPixmap.scaledToHeight(100, Qt::SmoothTransformation));
    logoLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(logoLabel);

    // Application name and version
    QLabel* titleLabel = new QLabel("Dcryptor", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold;");
    mainLayout->addWidget(titleLabel);

    QLabel* versionLabel = new QLabel("Version 1.0", this);
    versionLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(versionLabel);

    // Application description
    QTextBrowser* descriptionBrowser = new QTextBrowser(this);
    descriptionBrowser->setOpenExternalLinks(true);
    descriptionBrowser->setHtml(
        "<p style='font-size: 16px; text-align: center;'>"
        "Dcryptor is a free and open-source encryption tool written in C++ using Qt and OpenSSL. It offers a wide range of algorithms and cipher modes to encrypt and decrypt strings and files. It is cross-platform compatible and provides a user-friendly GUI for secure data protection. <br><br>"
        "For more information, visit our <a href='https://github.com/darshan-open-source/Dcryptor'>website</a>."
        "<br><br> Author : Darshan Sojitra"
        "</p>"
    );
    descriptionBrowser->setStyleSheet("background:transparent;border:none");
    mainLayout->addWidget(descriptionBrowser);

    //mainLayout->addStretch();



    setLayout(mainLayout);
}
