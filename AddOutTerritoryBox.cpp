#include "AddOutTerritoryBox.h"
#include "WarningMessageBox.h"
#include "ZTM.h"
#include <QTextStream>
#include <QFile>

using ZTM::available_territories_list;
using ZTM::permissions_list;
using ZTM::load_territory_data;
using ZTM::load_permission_data;

AddOutTerritoryBox::AddOutTerritoryBox(QWidget *parent) : QDialog(parent)
{
 initialize();
 create_labels();
 create_buttons();
 create_layouts();
 create_group_box();
 connect_buttons();
}

void AddOutTerritoryBox::initialize()
{
 setWindowTitle("Nouvelle sortie");
 setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
 setLayout(&layout);
}

void AddOutTerritoryBox::create_id_label()
{
 id_label.setText("Numéro:");
}

void AddOutTerritoryBox::create_date_label()
{
 date_label.setText("Date:");
}

void AddOutTerritoryBox::create_name_label()
{
 name_label.setText("Personne:");
}

void AddOutTerritoryBox::create_note_label()
{
 note_label.setText("Note:");
}

void AddOutTerritoryBox::create_labels()
{
 create_id_label();
 create_date_label();
 create_name_label();
 create_note_label();
}

void AddOutTerritoryBox::create_id_button()
{
 id_button.setToolTip("Numéro du territoire à sortir");
}

void AddOutTerritoryBox::create_date_button()
{
 date_button.setDateTime(QDateTime::currentDateTime());
 date_button.setToolTip("Date et heure de sortie du territoire");
}

void AddOutTerritoryBox::create_name_button()
{
 name_button.setToolTip("Nom de la personne empruntant le territoire");
}

void AddOutTerritoryBox::create_note_button()
{
 note_text.setToolTip("Ajouter un commentaire à propos de cette sortie");
}

void AddOutTerritoryBox::create_validate_button()
{
 validate_button.setText("Valider");
 validate_button.setToolTip("Enregistrer ce territoire comme sorti");
}

void AddOutTerritoryBox::create_cancel_button()
{
 cancel_button.setText("Annuler");
 cancel_button.setToolTip("Annuler la sortie de ce territoire");
}

void AddOutTerritoryBox::create_buttons()
{
 create_id_button();
 create_date_button();
 create_name_button();
 create_note_button();
 create_validate_button();
 create_cancel_button();
}

void AddOutTerritoryBox::create_layout()
{
 layout.addWidget(&box);
}

void AddOutTerritoryBox::create_box_layout()
{
 box_layout.addWidget(&id_label,0,0,1,1);
 box_layout.addWidget(&date_label,1,0,1,1);
 box_layout.addWidget(&name_label,2,0,1,1);
 box_layout.addWidget(&note_label,3,0,1,1);
 box_layout.addWidget(&id_button,0,1,1,3);
 box_layout.addWidget(&date_button,1,1,1,3);
 box_layout.addWidget(&name_button,2,1,1,3);
 box_layout.addWidget(&note_text,4,0,1,4);
 box_layout.addWidget(&validate_button,5,0,1,2);
 box_layout.addWidget(&cancel_button,5,2,1,2);
}

void AddOutTerritoryBox::create_layouts()
{
 create_layout();
 create_box_layout();
}

void AddOutTerritoryBox::create_group_box()
{
 box.setTitle("Ajouter un territoire sorti");
 box.setLayout(&box_layout);
}

void AddOutTerritoryBox::connect_buttons()
{
 QObject::connect(&validate_button, SIGNAL(clicked()),this,SLOT(validate()));
 QObject::connect(&cancel_button, SIGNAL(clicked()),this,SLOT(reject()));
}

void AddOutTerritoryBox::load_database()
{
 date_button.setDateTime(QDateTime::currentDateTime());
 id_button.clear();
 name_button.clear();
 QStringList territories("(Vide)");
 QStringList permissions("(Vide)");
 territories.append(available_territories_list());
 permissions.append(permissions_list());
 id_button.addItems(territories);
 name_button.addItems(permissions);
}

void AddOutTerritoryBox::validate()
{
 QString id = id_button.currentText();
 id.resize(id.indexOf(" - "));
 QString holder = name_button.currentText();
 holder.resize(holder.indexOf(" - "));
 Territory territory = load_territory_data(id.toInt());
 Permission permission = load_permission_data(holder.toInt());
 if (id_button.currentIndex() == 0 || name_button.currentIndex() == 0)
 {
  if(id_button.currentIndex() == 0)
  {
   WarningMessageBox warning("Sortie invalide","Attention, aucun territoire n'a été sélectionné.");
   warning.exec();
  }
  if(name_button.currentIndex() == 0)
  {
   WarningMessageBox warning("Sortie invalide","Attention, aucune personne n'a été sélectionné.");
   warning.exec();
  }
 }
 else
 {
  territory.add_event(TerritoryEvent(ZTM::OutType,date_button.dateTime(),note_text.toPlainText(),permission.id()));
  permission.add_territory(territory.id());
  QString territory_path = "Territoires/"+QString::number(territory.id())+".ztm";
  QFile territory_file(territory_path);
  QString permission_path = "Autorisations/"+QString::number(permission.id())+".ztm";
  QFile permission_file(permission_path);
  territory_file.remove();
  permission_file.remove();
  if (territory_file.open(QIODevice::WriteOnly))
  {
   QDataStream flux(&territory_file);
   flux << territory;
   territory_file.close();
  }
  if (permission_file.open(QIODevice::WriteOnly))
  {
   QDataStream flux(&permission_file);
   flux << permission;
   permission_file.close();
  }
  accept();
 }
}
