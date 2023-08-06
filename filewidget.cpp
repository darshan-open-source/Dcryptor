#include "filewidget.h"
#include"CryptoUtil.h"

filewidget::filewidget(QWidget* parent) : QWidget(parent)
{

	main_layout = new QVBoxLayout();

	layout = new QHBoxLayout();

	algo_widgetx = new algo_widget(this);

	selectfile = new QLabel("Select File ");
	save_file_label = new QLabel("save file to", this);
	tosave = new QLineEdit(this);
	tosave->setPlaceholderText("save file");
	tosave->setStyleSheet("QLineEdit { background-color: white; border: 1px solid #a8a8a8; padding: 5px; border-radius: 5px;}");

	savebtn = new QToolButton(this);
	savebtn->setIcon(QIcon(":/img/save.png"));
	savebtn->setStyleSheet("padding:6px");




	QFrame* abd = new QFrame(this);
	file = new QRadioButton("File", this);
	folder = new QRadioButton("Folder", this);
	file->setChecked(true);
	file_folder = new QHBoxLayout();
	abd->setLayout(file_folder);
	file_folder->addWidget(file);
	file_folder->addWidget(folder);

	dowork = new QPushButton("Encrypt", this);
	dowork->setStyleSheet("QPushButton{height:25px;}QPushButton:hover{background-color:#007bff;border-radius:4px;color:white;border-style: inset;}");

	pbar = new QProgressBar(this);
	pbar->setRange(0, 0);
	pbar->setValue(0);
	pbar->setFormat("Nothing");
	pbar->setStyleSheet("text-align:center");



	last_layout = new QHBoxLayout();
	last_layout->addWidget(save_file_label);
	last_layout->addWidget(tosave);
	last_layout->addWidget(savebtn);
	//bin->setChecked(true);
	select = new QToolButton(this);
	select->setIcon(QIcon(":/img/open.jpeg"));
	select->setStyleSheet("padding:6px");

	toopen = new QLineEdit(this);
	toopen->setPlaceholderText("open file");
	toopen->setStyleSheet("QLineEdit { background-color: white; border: 1px solid #a8a8a8; padding: 5px; border-radius: 5px;}");



	layout->addWidget(selectfile);
	layout->addWidget(toopen);
	layout->addWidget(select);

	main_layout->addWidget(algo_widgetx);
	main_layout->addWidget(abd);
	main_layout->addLayout(layout);
	main_layout->addLayout(last_layout);
	main_layout->addWidget(dowork);

	main_layout->addWidget(pbar);

	setLayout(main_layout);
	connector();
}


void filewidget::openclicked()
{
	f = new QFileDialog(this);
	if (file->isChecked()) {
		f->setAcceptMode(QFileDialog::AcceptMode::AcceptOpen);
	}
	else {
		f->setFileMode(QFileDialog::Directory);
	}
	f->exec();

	if (f->selectedFiles().length() != 0)toopen->setText(f->selectedFiles().at(0));
}

void filewidget::saveclicked()
{
	QFileDialog* fd = new QFileDialog(this);
	if (file->isChecked()) {
		fd->setAcceptMode(QFileDialog::AcceptSave);

		//    fd->setAcceptMode(QFileDialog::AcceptMode::AcceptOpen);
	}
	else {
		fd->setFileMode(QFileDialog::Directory);
	}
	fd->exec();
	if (fd->selectedFiles().length() != 0)tosave->setText(fd->selectedFiles().at(0));
}
void filewidget::connector()
{
	connect(select, SIGNAL(clicked()), this, SLOT(openclicked()));
	connect(savebtn, SIGNAL(clicked()), this, SLOT(saveclicked()));

	connect(dowork, SIGNAL(clicked()), this, SLOT(do_pressed()));
	connect(this, SIGNAL(ready(int)), this, SLOT(fileready(int)));
	connect(this, SIGNAL(progresschanged(int, int)), this, SLOT(update_progress(int, int)));
	connect(algo_widgetx, SIGNAL(encryptDecryptRadioButtonChanged(bool)), this, SLOT(encryptDecryptButtionChanged(bool)));

}
int filewidget::do_pressed()
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

		xbp = (const EVP_CIPHER*)EVP_get_cipherbyname(s.toStdString().c_str());

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


	if (!std::filesystem::exists(toopen->text().toStdString()))
	{
		QMessageBox::information(this, "info", "File is not found");

		return 0;
	}

	if (tosave->text().length() == 0)
	{

		QMessageBox::critical(this, "info", "Please Select output destination ");

		return 0;
	}
	if (std::filesystem::exists(std::filesystem::path(tosave->text().toStdString())))
	{
		std::filesystem::create_directory(tosave->text().toStdString());
	}





	if (f->selectedFiles().length() != 0) {

		createthread(xbp);
	}

}

void filewidget::fileready(int x)
{
	if (x == 1 && !folder->isChecked()) {
		dowork->setEnabled(1);
		QMessageBox::information(this, "info", "File Encrypted Successfully");
	}
	if (x == 2 && !folder->isChecked()) {
		dowork->setEnabled(1);
		QMessageBox::information(this, "info", "File Decrypted Successfully");


	}

	if (x == 1 && folder->isChecked()) {
		dowork->setEnabled(1);
		QMessageBox::information(this, "info", "Folder Encrypted Successfully");
	}
	if (x == 2 && folder->isChecked()) {
		dowork->setEnabled(1);
		QMessageBox::information(this, "info", "Folder Decrypted Successfully");


	}
}

void filewidget::createthread(const  EVP_CIPHER* xbp)
{
	dowork->setDisabled(true);

	if (xbp != 0) {
		QString s;
		if (tosave->text().length() == 0) {
			s = f->selectedFiles().at(0);
			s.append(".denc");
		}
		else s = tosave->text();
		if (file->isChecked()) {
			std::thread tmxx(threadcall, xbp, f->selectedFiles().at(0), s, algo_widgetx->getKey(), algo_widgetx->getIv(), algo_widgetx->isEncryptedChecked(), this);
			tmxx.detach();
		}
		else {
			std::thread tmxx(encryptFolder, xbp, f->selectedFiles().at(0), s, algo_widgetx->getKey(), algo_widgetx->getIv(), algo_widgetx->isEncryptedChecked(), this);
			tmxx.detach();
		}
	}
}

void filewidget::do_ui(int x)
{
	emit ready(x);
}
void filewidget::encryptFolder(const EVP_CIPHER* C, QString plain, QString enc, QString key, QString iv, bool encrypt, filewidget* t) {





	if (!std::filesystem::exists(plain.toStdString()))return;
	QDirIterator id(plain, QDirIterator::Subdirectories);
	while (id.hasNext())

	{

		std::filesystem::path px(id.next().toStdString());
		if (px.filename() == ".." || px.filename() == ".")
		{
			continue;
		}
		
		   std::string s = px.lexically_relative(plain.toStdString()).generic_string();
		   std::filesystem::path e(enc.toStdString());
		   std::filesystem::path full_path = e / s;
			if (std::filesystem::is_directory(px))
			{
				
			
				std::filesystem::create_directory(full_path);
				continue;
			}
		
		
		

	

	
		if (encrypt) {
			   Encrypt_File(C, key.toStdString().c_str(), iv.toStdString().c_str(),px.generic_string().c_str(), full_path.generic_string().c_str(), t);
		}
		else {

			Decrypt_File(C, key.toStdString().c_str(), iv.toStdString().c_str(),  px.generic_string().c_str(),full_path.generic_string().c_str(), t);


		}

	}
	if (encrypt)
	{
		t->do_ui(1);
	}
	else
	{
		t->do_ui(2);
	}
}

void filewidget::threadcall(const EVP_CIPHER* C, QString plain, QString enc, QString key, QString iv, bool encrypt, filewidget* t)
{

	if (encrypt == true) {
		Encrypt_File(C, key.toStdString().c_str(), iv.toStdString().c_str(), plain.toStdString().c_str(), enc.toStdString().c_str(), t);

		t->do_ui(1);

	}
	else {
		qInfo("decrypting file");
		Decrypt_File(C, key.toStdString().c_str(), iv.toStdString().c_str(), plain.toStdString().c_str(), enc.toStdString().c_str(), t);

		t->do_ui(2);

	}
}

void filewidget::update_progress(int x, int y)
{
	pbar->setValue(x);
	QString s;
	if (y == 1) {
		if (x == 100) s = "Encrypted ";
		else
			s = "Encrypting ";

		s.append(std::to_string(x).c_str());
		s.append("%");
		pbar->setFormat(s);
	}
	else {
		if (x == 100) s = "Decrypted ";
		else
			s = "Decrypting ";

		s.append(std::to_string(x).c_str());
		s.append("%");
		pbar->setFormat(s);
	}
}

void filewidget::progress(int x, int y)
{
	emit progresschanged(x, y);
}

void filewidget::encryptDecryptButtionChanged(bool val)
{

	if (val)
	{
		dowork->setText("Encrypt");

	}
	else dowork->setText("Decrypt");
}
