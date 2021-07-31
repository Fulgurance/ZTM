#ifndef ADDTERRITORYBOX_H
#define ADDTERRITORYBOX_H

#include <QDialog>
#include <QGroupBox>
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QGridLayout>
#include <QFileDialog>

class AddTerritoryBox : public QDialog
{
Q_OBJECT
public:
    AddTerritoryBox(QWidget *parent);
public slots:
    void first_check(int state);
    void second_check(int state);
    void first_import();
    void second_import();
    void validate();
private:
    QGroupBox box;
    QLabel id_label;
    QLabel name_label;
    QLabel pictures_label;
    QLabel first_file_label;
    QLabel second_file_label;
    QSpinBox id_button;
    QLineEdit name_button;
    QCheckBox first_check_button;
    QCheckBox second_check_button;
    QPushButton first_import_button;
    QPushButton second_import_button;
    QPushButton validate_button;
    QPushButton cancel_button;
    QGridLayout box_layout;
    QGridLayout layout;
    void initialize();
    void create_id_label();
    void create_name_label();
    void create_pictures_label();
    void create_first_file_label();
    void create_second_file_label();
    void create_labels();
    void create_id_button();
    void create_name_button();
    void create_first_check_button();
    void create_second_check_button();
    void create_first_import_button();
    void create_second_import_button();
    void create_validate_button();
    void create_cancel_button();
    void create_buttons();
    void create_box_layout();
    void create_layout();
    void create_layouts();
    void create_group_box();
    void connect_buttons();
};

#endif // ADDTERRITORYBOX_H
