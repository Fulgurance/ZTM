#include "HelpBox.h"
#include "ZTM.h"

using ZTM::HelpOutButtonText;
using ZTM::HelpAssignmentButtonText;
using ZTM::HelpEnterButtonText;
using ZTM::HelpDatabaseButtonText;
using ZTM::HelpSettingsButtonText;
using ZTM::HelpPrintButtonText;

HelpBox::HelpBox(QWidget *parent) : QDialog(parent)
{
 initialize();
 create_group_boxs();
 create_buttons();
 create_labels();
 create_layouts();
 connect_buttons();
}

void HelpBox::initialize()
{
 setWindowTitle("Centre d'aide");
 setWindowIcon(QIcon(":Info.png"));
 setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
 setLayout(&layout);
 initialize_pointers();
}

void HelpBox::initialize_pointers()
{
 help_out_button_box = new HelpButtonBox(this,HelpOutButtonText);
 help_asssignment_button_box = new HelpButtonBox(this,HelpAssignmentButtonText);
 help_enter_button_box = new HelpButtonBox(this,HelpEnterButtonText);
 help_database_button_box = new HelpButtonBox(this,HelpDatabaseButtonText);
 help_print_button_box = new HelpButtonBox(this,HelpPrintButtonText);
 help_settings_button_box = new HelpButtonBox(this,HelpSettingsButtonText);
}

void HelpBox::create_help_box()
{
 help_box.setTitle("Fonctionnalités");
 help_box.setLayout(&help_box_layout);
}

void HelpBox::create_report_box()
{
 report_box.setTitle("Support technique");
 report_box.setLayout(&report_box_layout);
}

void HelpBox::create_group_boxs()
{
 create_help_box();
 create_report_box();
}

void HelpBox::create_help_label()
{
 help_label.setText("Cliquez sur le bouton dont vous souhaitez connaître ses fonctionnalités.");
}

void HelpBox::create_report_label()
{
 report_label.setText("Signaler un problème ou donner des suggestions sur le logiciel.");
}

void HelpBox::create_labels()
{
 create_help_label();
 create_report_label();
}

void HelpBox::create_out_button()
{
 out_button.setText("Sortir\nun\nTerritoire");
}

void HelpBox::create_reassignment_button()
{
 assignment_button.setText("Réassigner\nun\nTerritoire");
}

void HelpBox::create_enter_button()
{
 enter_button.setText("Rentrer\nun\nTerritoire");
}

void HelpBox::create_data_button()
{
 data_button.setFixedSize(34,22);
 data_button.setIcon(QIcon(":BaseDeDonnées.png"));
}

void HelpBox::create_settings_button()
{
 settings_button.setFixedSize(34,22);
 settings_button.setIcon(QIcon(":Paramètres.png"));
}

void HelpBox::create_print_button()
{
 print_button.setFixedSize(34,22);
 print_button.setIcon(QIcon(":Imprimer.png"));
}

void HelpBox::create_report_button()
{
 report_button.setText("Signaler");
}

void HelpBox::create_end_button()
{
 end_button.setText("Fermer");
 end_button.setToolTip("Quitter le centre d'aide");
}

void HelpBox::create_buttons()
{
 create_out_button();
 create_reassignment_button();
 create_enter_button();
 create_data_button();
 create_settings_button();
 create_print_button();
 create_report_button();
 create_end_button();
}

void HelpBox::create_help_layout()
{
 help_box_layout.addWidget(&help_label,0,0,1,6);
 help_box_layout.addWidget(&out_button,1,0);
 help_box_layout.addWidget(&assignment_button,1,1);
 help_box_layout.addWidget(&enter_button,1,2);
 help_box_layout.addWidget(&data_button,1,3);
 help_box_layout.addWidget(&print_button,1,4);
 help_box_layout.addWidget(&settings_button,1,5);
}

void HelpBox::create_report_layout()
{
 report_box_layout.addWidget(&report_label);
 report_box_layout.addWidget(&report_button);
}

void HelpBox::create_layout()
{
 layout.addWidget(&help_box,0,0,1,6);
 layout.addWidget(&report_box,1,0,1,6);
 layout.addWidget(&end_button,2,0,1,1);
}

void HelpBox::create_layouts()
{
 create_help_layout();
 create_report_layout();
 create_layout();
}

void HelpBox::connect_buttons()
{
 connect(&out_button,SIGNAL(clicked()),this,SLOT(open_help_out_button_box()));
 connect(&assignment_button,SIGNAL(clicked()),this,SLOT(open_help_assignment_button_box()));
 connect(&enter_button,SIGNAL(clicked()),this,SLOT(open_help_enter_button_box()));
 connect(&data_button,SIGNAL(clicked()),this,SLOT(open_help_database_button_box()));
 connect(&print_button,SIGNAL(clicked()),this,SLOT(open_help_print_button_box()));
 connect(&settings_button,SIGNAL(clicked()),this,SLOT(open_help_settings_button_box()));
 connect(&end_button,SIGNAL(clicked()),this,SLOT(accept()));
}

void HelpBox::open_help_out_button_box()
{
 help_out_button_box->exec();
}

void HelpBox::open_help_assignment_button_box()
{
 help_asssignment_button_box->exec();
}

void HelpBox::open_help_enter_button_box()
{
 help_enter_button_box->exec();
}

void HelpBox::open_help_database_button_box()
{
 help_database_button_box->exec();
}

void HelpBox::open_help_print_button_box()
{
 help_print_button_box->exec();
}

void HelpBox::open_help_settings_button_box()
{
 help_settings_button_box->exec();
}
