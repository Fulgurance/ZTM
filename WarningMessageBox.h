#ifndef WARNINGMESSAGEBOX_H
#define WARNINGMESSAGEBOX_H

#include <QMessageBox>

class WarningMessageBox : public QMessageBox
{
public:
    WarningMessageBox();
    WarningMessageBox(QString title,QString text);
private:
    void initialize(QString title,QString text);
};

#endif // WARNINGMESSAGEBOX_H
