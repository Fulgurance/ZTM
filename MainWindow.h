#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGroupBox>
#include <QPushButton>
#include <QTextEdit>
#include <QGridLayout>
#include "AddOutTerritoryBox.h"
#include "ChangeAssignmentTerritoryBox.h"
#include "EnterTerritoryBox.h"
#include "DatabaseEditorBox.h"
#include "PrintBox.h"
#include "SettingsBox.h"
#include "HelpBox.h"

class MainWindow : public QWidget
{
Q_OBJECT
public:
    MainWindow();
    void load_log();
public slots:
    void open_out_territory_box();
    void open_change_territory_box();
    void open_enter_territory_box();
    void open_database_editor_box();
    void open_print_box();
    void open_settings_box();
    void open_info_box();
private:
    QGroupBox buttons_box;
    QGroupBox log_box;
    QPushButton out_button;
    QPushButton change_button;
    QPushButton enter_button;
    QPushButton data_button;
    QPushButton print_button;
    QPushButton settings_button;
    QPushButton info_button;
    QString log;
    QTextEdit list_box;
    QHBoxLayout buttons_layout;
    QGridLayout log_layout;
    QGridLayout layout;
    AddOutTerritoryBox *out_territory_box;
    ChangeAssignmentTerritoryBox *change_territory_box;
    EnterTerritoryBox *enter_territory_box;
    DatabaseEditorBox *database_editor_box;
    PrintBox *print_box;
    SettingsBox *settings_box;
    HelpBox *help_box;
    void initialize();
    void initialize_pointers();
    void create_out_button();
    void create_change_button();
    void create_enter_button();
    void create_data_button();
    void create_print_button();
    void create_settings_button();
    void create_info_button();
    void create_buttons();
    void create_list_box();
    void create_buttons_layout();
    void create_log_layout();
    void create_layout();
    void create_layouts();
    void create_buttons_box();
    void create_log_box();
    void create_group_boxs();
    void connect_buttons();
};

#endif
