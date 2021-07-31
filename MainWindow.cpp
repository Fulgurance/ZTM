#include "MainWindow.h"
#include "ZTM.h"

using ZTM::log_list;

MainWindow::MainWindow() : QWidget()
{
 initialize();
 create_buttons();
 create_list_box();
 create_layouts();
 create_group_boxs();
 connect_buttons();
}

void MainWindow::initialize()
{
 setWindowTitle("ZTM");
 setWindowIcon(QIcon(":Icone.png"));
 setWindowFlags(Qt::WindowMinimizeButtonHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
 setLayout(&layout);
 initialize_pointers();
}

void MainWindow::initialize_pointers()
{
 out_territory_box = new AddOutTerritoryBox(this);
 change_territory_box = new ChangeAssignmentTerritoryBox(this);
 enter_territory_box = new EnterTerritoryBox(this);
 database_editor_box = new DatabaseEditorBox(this);
 print_box = new PrintBox(this);
 settings_box = new SettingsBox(this);
 help_box = new HelpBox(this);
}

void MainWindow::create_out_button()
{
 out_button.setText("Sortir\nun\nTerritoire");
 out_button.setToolTip("Créer une sortie de territoire pour l'assigner à un frère ou une soeur");
}

void MainWindow::create_change_button()
{
 change_button.setText("Réassigner\nun\nTerritoire");
 change_button.setToolTip("Réassigner un territoire sortie à un autre frère ou une autre soeur");
}

void MainWindow::create_enter_button()
{
 enter_button.setText("Rentrer\nun\nTerritoire");
 enter_button.setToolTip("Mettre fin à l'assignation d'un territoire d'un frère ou d'une soeur");
}

void MainWindow::create_data_button()
{
 data_button.setFixedSize(34,22);
 data_button.setIcon(QIcon(":BaseDeDonnées.png"));
 data_button.setToolTip("Editer la base de données");
}

void MainWindow::create_print_button()
{
 print_button.setFixedSize(34,22);
 print_button.setIcon(QIcon(":Imprimer.png"));
 print_button.setToolTip("Imprimer l'historique des territoires");
}

void MainWindow::create_settings_button()
{
 settings_button.setFixedSize(34,22);
 settings_button.setIcon(QIcon(":Paramètres.png"));
 settings_button.setToolTip("Paramètres d'utilisation du logiciel");
}

void MainWindow::create_info_button()
{
 info_button.setFixedSize(34,22);
 info_button.setIcon(QIcon(":Info.png"));
 info_button.setToolTip("Centre d'aide du logiciel");
}

void MainWindow::create_buttons()
{
 create_out_button();
 create_change_button();
 create_enter_button();
 create_data_button();
 create_print_button();
 create_settings_button();
 create_info_button();
}

void MainWindow::create_list_box()
{
 list_box.setReadOnly(true);
}

void MainWindow::create_buttons_layout()
{
 buttons_layout.addWidget(&out_button);
 buttons_layout.addWidget(&change_button);
 buttons_layout.addWidget(&enter_button);
}

void MainWindow::create_log_layout()
{
 log_layout.addWidget(&list_box);
}

void MainWindow::create_layout()
{
 layout.addWidget(&buttons_box);
 layout.addWidget(&log_box,1,0,1,6);
 layout.addWidget(&data_button,2,0,1,1);
 layout.addWidget(&print_button,2,3,1,1);
 layout.addWidget(&settings_button,2,4,1,1);
 layout.addWidget(&info_button,2,5,1,1);
 layout.setRowStretch(0,0);
}

void MainWindow::create_layouts()
{
 create_buttons_layout();
 create_log_layout();
 create_layout();
}

void MainWindow::create_buttons_box()
{
 buttons_box.setParent(this);
 buttons_box.setTitle("Gestion");
 buttons_box.setLayout(&buttons_layout);
}

void MainWindow::create_log_box()
{
 log_box.setParent(this);
 log_box.setTitle("Journal");
 log_box.setLayout(&log_layout);
}

void MainWindow::create_group_boxs()
{
 create_buttons_box();
 create_log_box();
}

void MainWindow::connect_buttons()
{
 connect(&out_button,SIGNAL(clicked()),this,SLOT(open_out_territory_box()));
 connect(&change_button,SIGNAL(clicked()),this,SLOT(open_change_territory_box()));
 connect(&enter_button,SIGNAL(clicked()),this,SLOT(open_enter_territory_box()));
 connect(&data_button,SIGNAL(clicked()),this,SLOT(open_database_editor_box()));
 connect(&print_button,SIGNAL(clicked()),this,SLOT(open_print_box()));
 connect(&settings_button,SIGNAL(clicked()),this,SLOT(open_settings_box()));
 connect(&info_button,SIGNAL(clicked()),this,SLOT(open_info_box()));
}

void MainWindow::load_log()
{
 log.clear();
 if (log_list().isEmpty())
 {
  log.append("Aucun journal d'historique disponible");
 }
 else
 {
  log.append(log_list());
 }
 list_box.setHtml(log);
}

void MainWindow::open_out_territory_box()
{
 out_territory_box->load_database();
 out_territory_box->exec();
 load_log();
}

void MainWindow::open_change_territory_box()
{
 change_territory_box->load_database();
 change_territory_box->exec();
 load_log();
}

void MainWindow::open_enter_territory_box()
{
 enter_territory_box->load_database();
 enter_territory_box->exec();
 load_log();
}

void MainWindow::open_database_editor_box()
{
 database_editor_box->load_database();
 database_editor_box->exec();
 load_log();
}

void MainWindow::open_print_box()
{
 print_box->exec();
}

void MainWindow::open_settings_box()
{
 settings_box->load_database();
 settings_box->exec();
}

void MainWindow::open_info_box()
{
 help_box->exec();
}
