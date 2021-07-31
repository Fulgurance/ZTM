#ifndef HELPBUTTONBOX_H
#define HELPBUTTONBOX_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>

class HelpButtonBox : public QDialog
{
public:
    HelpButtonBox(QWidget *parent, int type);
private:
    int help_type;
    QLabel text;
    QPushButton end_button;
    QGridLayout layout;
    void initialize();
    void create_text();
    void create_button();
    void create_layout();
    void connect_button();
};

#endif
