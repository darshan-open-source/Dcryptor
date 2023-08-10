#include "MyLineEdit.h"

MyLineEdit::MyLineEdit(bool key,QWidget* parent):QLineEdit(parent)
{
	iskey = key;

	algo = parent->findChild<QComboBox*>("algo");
	bit = parent->findChild<QComboBox*>("bit");
	cmode = parent->findChild<QComboBox*>("cmode");

}

void MyLineEdit::keyPressEvent(QKeyEvent* keyevent)
{
	QKeyCombination c = keyevent->keyCombination();
	if (c.toCombined() == (Qt::Key::Key_R | Qt::KeyboardModifier::ControlModifier))
	{

		const  EVP_CIPHER* xbp;
		QString s;
		if (bit->isEnabled())
		{
			s.append(algo->currentText());
			s.append("-");
			s.append(bit->currentText());
			s.append("-");
			s.append(cmode->currentText());

			xbp = (const EVP_CIPHER*)EVP_get_cipherbyname(s.toStdString().c_str());
		
		}
		else {
			if (strcmp(algo->currentText().toStdString().c_str(), "Blowfish") == 0)
				s.append("bf");

			else s.append(algo->currentText());
			s.append("-");
			s.append(cmode->currentText());

	
			xbp = EVP_get_cipherbyname(s.toStdString().c_str());
		}

		this->clear();

		if (iskey)
		{
			int key_len = EVP_CIPHER_get_key_length(xbp);
           
			unsigned char* m = (unsigned char*)malloc(key_len+1);
			RAND_priv_bytes(m, key_len);
			QString s;
			for (size_t i = 0; i < key_len; i++)
			{
				const int minAsciiValue = 32; // Lowest printable ASCII character
				const int maxAsciiValue = 126; // Highest printable ASCII character
				s.append(QChar(  (minAsciiValue + (m[i] % (maxAsciiValue - minAsciiValue + 1)))));
			}
			free(m);


			this->setText(s);

		}
		else
		{
			int iv_len = EVP_CIPHER_get_iv_length(xbp);
			unsigned char* m = (unsigned char*)malloc(iv_len + 1);
			RAND_priv_bytes(m, iv_len);
			QString s;
			for (size_t i = 0; i < iv_len; i++)
			{
				const int minAsciiValue = 32; // Lowest printable ASCII character
				const int maxAsciiValue = 126; // Highest printable ASCII character
				s.append(QChar((minAsciiValue + (m[i] % (maxAsciiValue - minAsciiValue + 1)))));
			}
			free(m);
			this->setText(s);

		}

	}
	QLineEdit::keyPressEvent(keyevent);

}
