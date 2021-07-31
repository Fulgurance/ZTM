#ifndef SETTINGSBOX_H
#define SETTINGSBOX_H

#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QGridLayout>

class SettingsBox : public QDialog
{
Q_OBJECT
public:
    SettingsBox(QWidget *parent);
    void load_database();
public slots:
    void validate();
private:
    QLabel language_label;
    QLabel congregation_label;
    QLabel territory_label;
    QLabel historic_label;
    QComboBox language_button;
    QLineEdit congregation_button;
    QSpinBox territory_button;
    QSpinBox historic_button;
    QPushButton validate_button;
    QPushButton cancel_button;
    QGridLayout layout;
    void initialize();
    void create_language_label();
    void create_congregation_label();
    void create_territory_label();
    void create_historic_label();
    void create_labels();
    void create_language_button();
    void create_congregation_button();
    void create_territory_button();
    void create_historic_button();
    void create_validate_button();
    void create_cancel_button();
    void create_buttons();
    void create_layout();
    void connect_buttons();
};

#endif // SETTINGSBOX_H
