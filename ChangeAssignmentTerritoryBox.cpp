#include "ChangeAssignmentTerritoryBox.h"
#include "WarningMessageBox.h"
#include "ZTM.h"
#include <QFile>

using ZTM::permissions_list;
using ZTM::out_territories_list;
using ZTM::load_territory_data;
using ZTM::load_permission_data;

ChangeAssignmentTerritoryBox::ChangeAssignmentTerritoryBox(QWidget *parent) : QDialog(parent)
{
 initialize();
 create_labels();
 create_buttons();
 create_layouts();
 create_group_box();
 connect_buttons();
}

void ChangeAssignmentTerritoryBox::initialize()
{
 setWindowTitle("Modifier une sortie");
 setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
 setLayout(&layout);
}

void ChangeAssignmentTerritoryBox::create_id_label()
{
 id_label.setText("Numéro:");
}

void ChangeAssignmentTerritoryBox::create_date_label()
{
 date_label.setText("Date de réassignation:");
}

void ChangeAssignmentTerritoryBox::create_name_label()
{
 name_label.setText("Personne:");
}

void ChangeAssignmentTerritoryBox::create_note_label()
{
 note_label.setText("Note:");
}

void ChangeAssignmentTerritoryBox::create_labels()
{
 create_id_label();
 create_date_label();
 create_name_label();
 create_note_label();
}

void ChangeAssignmentTerritoryBox::create_id_button()
{
 id_button.setToolTip("Numéro du territoire à réassigner");
}

void ChangeAssignmentTerritoryBox::create_date_button()
{
 date_button.setDateTime(QDateTime::currentDateTime());
 date_button.setToolTip("Date et heure de la réassignation du territoire");
}

void ChangeAssignmentTerritoryBox::create_name_button()
{
 name_button.addItems(permissions_list());
 name_button.setToolTip("Nom de la personne à qui le territoire est réassigné");
}

void ChangeAssignmentTerritoryBox::create_note_text()
{
 note_text.setToolTip("Ajouter un commentaire à propos de cette réassignation");
}

void ChangeAssignmentTerritoryBox::create_validate_button()
{
 validate_button.setText("Valider");
 validate_button.setToolTip("Enregistrer ce territoire comme réassigné");
}

void ChangeAssignmentTerritoryBox::create_cancel_button()
{
 cancel_button.setText("Annuler");
 cancel_button.setToolTip("Annuler la réassignation de ce territoire");
}

void ChangeAssignmentTerritoryBox::create_buttons()
{
 create_id_button();
 create_date_button();
 create_name_button();
 create_note_text();
 create_validate_button();
 create_cancel_button();
}

void ChangeAssignmentTerritoryBox::create_box_layout()
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

void ChangeAssignmentTerritoryBox::create_layout()
{
 layout.addWidget(&box);
}

void ChangeAssignmentTerritoryBox::create_layouts()
{
 create_box_layout();
 create_layout();
}

void ChangeAssignmentTerritoryBox::create_group_box()
{
 box.setTitle("Réassigner un territoire");
 box.setLayout(&box_layout);
}

void ChangeAssignmentTerritoryBox::connect_buttons()
{
 QObject::connect(&validate_button, SIGNAL(clicked()),this,SLOT(validate()));
 QObject::connect(&cancel_button, SIGNAL(clicked()),this,SLOT(reject()));
}

void ChangeAssignmentTerritoryBox::load_database()
{
 date_button.setDateTime(QDateTime::currentDateTime());
 id_button.clear();
 name_button.clear();
 QStringList territories("(Vide)");
 QStringList permissions("(Vide)");
 territories.append(out_territories_list());
 permissions.append(permissions_list());
 id_button.addItems(territories);
 name_button.addItems(permissions);
}

void ChangeAssignmentTerritoryBox::validate()
{
 QString id = id_button.currentText();
 id.resize(id.indexOf(" - "));
 QString holder = name_button.currentText();
 holder.resize(holder.indexOf(" - "));
 Territory territory = load_territory_data(id.toInt());
 Permission old_permission = load_permission_data(territory.holder_id());
 Permission permission = load_permission_data(holder.toInt());
 if (id_button.currentIndex() == 0 || name_button.currentIndex() == 0 || name_button.currentText() == (load_permission_data(territory.holder_id()).list_name()) || date_button.dateTime() < territory.last_out_date() || date_button.dateTime() < territory.last_change_assignment_date())
 {
  if (id_button.currentIndex() == 0)
  {
   WarningMessageBox warning("Réassignation invalide","Attention, aucun territoire n'a été sélectionné.");
   warning.exec();
  }
  if (name_button.currentIndex() == 0)
  {
   WarningMessageBox warning("Réassignation invalide","Attention, aucune personne n'a été sélectionné.");
   warning.exec();
  }
  if (name_button.currentText() == (load_permission_data(territory.holder_id()).list_name()))
  {
   WarningMessageBox warning("Réassignation invalide","Attention, le territoire est réassigné à la même personne.");
   warning.exec();
  }
  if (date_button.dateTime() < territory.last_out_date() || date_button.dateTime() < territory.last_change_assignment_date())
  {
   WarningMessageBox warning("Réassignation invalide","Attention, le territoire est réassigné à une date antérieure.");
   warning.exec();
  }
 }
 else
 {
  QString territory_path = "Territoires/"+QString::number(territory.id())+".ztm";
  QFile territory_file(territory_path);

  QString old_permission_path = "Autorisations/"+QString::number(territory.holder_id())+".ztm";
  QFile old_permission_file(old_permission_path);

  QString new_permission_path = "Autorisations/"+QString::number(permission.id())+".ztm";
  QFile new_permission_file(new_permission_path);


  territory.add_event(TerritoryEvent(ZTM::ChangeAssignmentType,date_button.dateTime(),note_text.toPlainText(),permission.id()));
  old_permission.remove_territory(territory.id());
  permission.add_territory(territory.id());

  territory_file.remove();
  old_permission_file.remove();
  new_permission_file.remove();

  if (territory_file.open(QIODevice::WriteOnly))
  {
   QDataStream flux(&territory_file);
   flux << territory;
   territory_file.close();
  }

  if (old_permission_file.open(QIODevice::WriteOnly))
  {
   QDataStream flux(&old_permission_file);
   flux << old_permission;
   old_permission_file.close();
  }

  if (new_permission_file.open(QIODevice::WriteOnly))
  {
   QDataStream flux(&new_permission_file);
   flux << permission;
   new_permission_file.close();
  }

  accept();
 }
}
