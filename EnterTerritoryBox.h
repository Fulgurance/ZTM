#ifndef ENTERTERRITORYBOX_H
#define ENTERTERRITORYBOX_H

#include <QDialog>
#include <QGroupBox>
#include <QLabel>
#include <QComboBox>
#include <QDateTimeEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QGridLayout>

class EnterTerritoryBox : public QDialog
{
Q_OBJECT
public:
    EnterTerritoryBox(QWidget *parent);
    void load_database();
public slots:
    void validate();
private:
    QGroupBox box;
    QLabel id_label;
    QLabel date_label;
    QLabel note_label;
    QComboBox id_button;
    QDateTimeEdit date_button;
    QTextEdit note_text;
    QPushButton validate_button;
    QPushButton cancel_button;
    QGridLayout box_layout;
    QGridLayout layout;
    void initialize();
    void create_id_label();
    void create_date_label();
    void create_note_label();
    void create_labels();
    void create_id_button();
    void create_date_button();
    void create_note_button();
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
