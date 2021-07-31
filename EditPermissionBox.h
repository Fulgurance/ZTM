#ifndef EDITPERMISSIONBOX_H
#define EDITPERMISSIONBOX_H

#include <QDialog>
#include <QGroupBox>
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

class EditPermissionBox : public QDialog
{
Q_OBJECT
public:
    EditPermissionBox(QWidget *parent);
    void set_permission_id(int id);
public slots:
    void validate();
private:
    int permission_id;
    QGroupBox box;
    QLabel id_label;
    QLabel name_label;
    QLabel mail_label;
    QSpinBox id_button;
    QLineEdit name_button;
    QLineEdit mail_button;
    QPushButton validate_button;
    QPushButton cancel_button;
    QGridLayout box_layout;
    QGridLayout layout;
    void initialize();
    void create_id_label();
    void create_name_label();
    void create_mail_label();
    void create_labels();
    void create_id_button();
    void create_name_button();
    void create_mail_button();
    void create_validate_button();
    void create_cancel_button();
    void create_buttons();
    void create_box_layout();
    void create_layout();
    void create_layouts();
    void create_group_box();
    void connect_buttons();
};

#endif // EDITPERMISSIONBOX_H
