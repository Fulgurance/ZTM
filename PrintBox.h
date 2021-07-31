#ifndef PRINTBOX_H
#define PRINTBOX_H

#include <QDialog>
#include <QDateEdit>
#include <QLabel>
#include <QGroupBox>
#include <QGridLayout>
#include <QPushButton>

class PrintBox : public QDialog
{
Q_OBJECT
public:
    PrintBox(QWidget *parent);
public slots:
    void open_print_box();
private:
    QLabel first_date_label;
    QLabel second_date_label;
    QDateEdit first_date_button;
    QDateEdit second_date_button;
    QPushButton validate_button;
    QPushButton cancel_button;
    QGridLayout box_layout;
    QGridLayout layout;
    QGroupBox box;
    void initialize();
    void create_first_date_label();
    void create_second_date_label();
    void create_labels();
    void create_first_date_button();
    void create_second_date_button();
    void create_validate_button();
    void create_cancel_button();
    void create_buttons();
    void create_box_layout();
    void create_layout();
    void create_layouts();
    void create_group_box();
    void connect_buttons();
    void print_period(QDate first_date, QDate second_date);
};

#endif // PRINTBOX_H
