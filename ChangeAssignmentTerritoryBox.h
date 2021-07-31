#ifndef CHANGEASSIGNMENTTERRITORYBOX_H
#define CHANGEASSIGNMENTTERRITORYBOX_H

#include <QDialog>
#include <QGroupBox>
#include <QLabel>
#include <QComboBox>
#include <QDateTimeEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QGridLayout>

class ChangeAssignmentTerritoryBox : public QDialog
{
Q_OBJECT
public:
    ChangeAssignmentTerritoryBox(QWidget *parent);
    void load_database();
public slots:
    void validate();
private:
    QGroupBox box;
    QLabel id_label;
    QLabel date_label;
    QLabel name_label;
    QLabel note_label;
    QComboBox id_button;
    QDateTimeEdit date_button;
    QComboBox name_button;
    QTextEdit note_text;
    QPushButton validate_button;
    QPushButton cancel_button;
    QGridLayout box_layout;
    QGridLayout layout;
    void initialize();
    void create_id_label();
    void create_date_label();
    void create_name_label();
    void create_note_label();
    void create_labels();
    void create_id_button();
    void create_date_button();
    void create_name_button();
    void create_note_text();
    void create_validate_button();
    void create_cancel_button();
    void create_buttons();
    void create_box_layout();
    void create_layout();
    void create_layouts();
    void create_group_box();
    void connect_buttons();
};

#endif
