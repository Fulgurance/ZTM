#ifndef HELPBOX_H
#define HELPBOX_H

#include <QDialog>
#include <QLabel>
#include <QGroupBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGridLayout>
#include "HelpButtonBox.h"

class HelpBox : public QDialog
{
Q_OBJECT
public:
    HelpBox(QWidget *parent);
public slots:
    void open_help_out_button_box();
    void open_help_assignment_button_box();
    void open_help_enter_button_box();
    void open_help_database_button_box();
    void open_help_settings_button_box();
    void open_help_print_button_box();
private:
    QLabel help_label;
    QLabel report_label;
    QPushButton out_button;
    QPushButton assignment_button;
    QPushButton enter_button;
    QPushButton data_button;
    QPushButton settings_button;
    QPushButton print_button;
    QPushButton report_button;
    QPushButton end_button;
    QGroupBox help_box;
    QGroupBox report_box;
    QGridLayout help_box_layout;
    QHBoxLayout report_box_layout;
    QGridLayout layout;
    HelpButtonBox *help_out_button_box;
    HelpButtonBox *help_asssignment_button_box;
    HelpButtonBox *help_enter_button_box;
    HelpButtonBox *help_database_button_box;
    HelpButtonBox *help_print_button_box;
    HelpButtonBox *help_settings_button_box;
    void initialize();
    void initialize_pointers();
    void create_out_button();
    void create_reassignment_button();
    void create_enter_button();
    void create_data_button();
    void create_settings_button();
    void create_print_button();
    void create_report_button();
    void create_end_button();
    void create_buttons();
    void create_help_box();
    void create_report_box();
    void create_group_boxs();
    void create_help_label();
    void create_report_label();
    void create_labels();
    void create_help_layout();
    void create_report_layout();
    void create_layout();
    void create_layouts();
    void connect_buttons();
};
#endif
