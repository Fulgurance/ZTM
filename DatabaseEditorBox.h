#ifndef DATABASEEDITORBOX_H
#define DATABASEEDITORBOX_H

#include <QDialog>
#include <QTabWidget>
#include <QGridLayout>
#include <QStringList>
#include <QStringListModel>
#include <QListView>
#include <QPushButton>
#include <QGroupBox>
#include "AddTerritoryBox.h"
#include "AddPermissionBox.h"
#include "TerritorySummaryBox.h"
#include "PermissionSummaryBox.h"
#include "EditTerritoryBox.h"
#include "EditPermissionBox.h"

class DatabaseEditorBox : public QDialog
{
Q_OBJECT
public:
    DatabaseEditorBox(QWidget *parent);
    void load_database();
public slots:
    void open_new_territory_box();
    void open_new_people_box();
    void delete_territory();
    void delete_permission();
    void open_territory_edit_box();
    void open_people_edit_box();
    void open_territory_detail_box();
    void open_people_detail_box();
private:
    QTabWidget tabs;
    QPushButton end_button;
    QWidget territory_tab;
    QWidget people_tab;
    QGridLayout territory_layout;
    QGridLayout people_layout;
    QStringListModel territory_modele;
    QListView territory_list_box;
    QPushButton add_territory_button;
    QPushButton delete_territory_button;
    QPushButton edit_territory_button;
    QPushButton detail_territory_button;
    QStringListModel people_modele;
    QListView people_list_box;
    QPushButton add_people_button;
    QPushButton delete_people_button;
    QPushButton edit_people_button;
    QPushButton detail_people_button;
    QGroupBox territory_box;
    QGroupBox people_box;
    QGridLayout territory_tab_layout;
    QGridLayout people_tab_layout;
    QGridLayout layout;
    AddTerritoryBox *new_territory_box;
    AddPermissionBox *new_people_box;
    TerritorySummaryBox *territory_summary_box;
    PermissionSummaryBox *permission_summary_box;
    EditTerritoryBox *territory_edit_box;
    EditPermissionBox *edit_permission_box;
    void initialize();
    void initialize_pointers();
    void create_add_territory_button();
    void create_delete_territory_button();
    void create_edit_territory_button();
    void create_detail_territory_button();
    void create_add_people_button();
    void create_delete_people_button();
    void create_edit_people_button();
    void create_detail_people_button();
    void create_end_button();
    void create_buttons();
    void create_territory_list_box();
    void create_people_list_box();
    void create_list_boxs();
    void create_territory_layout();
    void create_people_layout();
    void create_territory_tab_layout();
    void create_people_tab_layout();
    void create_layout();
    void create_layouts();
    void create_territory_box();
    void create_people_box();
    void create_group_boxs();
    void create_tabs();
    void connect_buttons();
};

#endif // DATABASEEDITORBOX_H
