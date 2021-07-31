#include "WarningMessageBox.h"

WarningMessageBox::WarningMessageBox(QString title,QString text) : QMessageBox()
{
 initialize(title,text);
}

void WarningMessageBox::initialize(QString title,QString text)
{
 setWindowTitle(title);
 setWindowFlags(Qt::WindowCloseButtonHint | Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
 setText(text);
 setIcon(QMessageBox::Warning);
}
