#include "EnterTerritoryBox.h"
#include "WarningMessageBox.h"
#include "ZTM.h"
#include <QFile>

using ZTM::out_territories_list;
using ZTM::load_territory_data;
using ZTM::load_permission_data;

EnterTerritoryBox::EnterTerritoryBox(QWidget *parent) : QDialog(parent)
{
 initialize();
 create_labels();
 create_buttons();
 create_layouts();
 create_group_box();
 connect_buttons();
}

void EnterTerritoryBox::initialize()
{
 setWindowTitle("Mettre fin à une sortie");
 setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
 setLayout(&layout);
}

void EnterTerritoryBox::create_id_label()
{
 id_label.setText("Numéro:");
}

void EnterTerritoryBox::create_date_label()
{
 date_label.setText("Date de rentrée:");
}

void EnterTerritoryBox::create_note_label()
{
 note_label.setText("Note:");
}

void EnterTerritoryBox::create_labels()
{
 create_id_label();
 create_date_label();
 create_note_label();
}

void EnterTerritoryBox::create_id_button()
{
 id_button.addItem("(Vide)");
 id_button.setToolTip("Numéro du territoire à rentrer");
}

void EnterTerritoryBox::create_date_button()
{
 date_button.setDateTime(QDateTime::currentDateTime());
 date_button.setToolTip("Date et heure de la rentrée du territoire");
}

void EnterTerritoryBox::create_note_button()
{
 note_text.setToolTip("Ajouter un commentaire à propos de cette rentrée");
}

void EnterTerritoryBox::create_validate_button()
{
 validate_button.setText("Valider");
 validate_button.setToolTip("Enregistrer ce territoire comme rentré");
}

void EnterTerritoryBox::create_cancel_button()
{
 cancel_button.setText("Annuler");
 cancel_button.setToolTip("Annuler la rentrée de ce territoire");
}

void EnterTerritoryBox::create_buttons()
{
 create_id_button();
 create_date_button();
 create_note_button();
 create_validate_button();
 create_cancel_button();
}

void EnterTerritoryBox::create_box_layout()
{
 box_layout.addWidget(&id_label,0,0,1,1);
 box_layout.addWidget(&date_label,1,0,1,1);
 box_layout.addWidget(&note_label,2,0,1,1);
 box_layout.addWidget(&id_button,0,1,1,3);
 box_layout.addWidget(&date_button,1,1,1,3);
 box_layout.addWidget(&note_text,3,0,1,4);
 box_layout.addWidget(&validate_button,4,0,1,2);
 box_layout.addWidget(&cancel_button,4,2,1,2);
}

void EnterTerritoryBox::create_layout()
{
 layout.addWidget(&box);
}

void EnterTerritoryBox::create_layouts()
{
 create_box_layout();
 create_layout();
}

void EnterTerritoryBox::create_group_box()
{
 box.setTitle("Rentrer un territoire");
 box.setLayout(&box_layout);
}

void EnterTerritoryBox::connect_buttons()
{
 QObject::connect(&validate_button, SIGNAL(clicked()),this,SLOT(validate()));
 QObject::connect(&cancel_button, SIGNAL(clicked()),this,SLOT(reject()));
}

void EnterTerritoryBox::load_database()
{
 date_button.setDateTime(QDateTime::currentDateTime());
 id_button.clear();
 QStringList territories("(Vide)");
 territories.append(out_territories_list());
 id_button.addItems(territories);
}

void EnterTerritoryBox::validate()
{
 QString id = id_button.currentText();
 id.resize(id.indexOf(" - "));
 Territory territory = load_territory_data(id.toInt());
 Permission permission = load_permission_data(territory.holder_id());
 if (id_button.currentIndex() == 0 || date_button.dateTime() < territory.last_out_date() || date_button.dateTime() < territory.last_change_assignment_date())
 {
  if (id_button.currentIndex() == 0)
  {
   WarningMessageBox warning("Rentrée invalide","Attention, aucun territoire n'a été sélectionné.");
   warning.exec();
  }
  if (date_button.dateTime() < territory.last_out_date() || date_button.dateTime() < territory.last_change_assignment_date())
  {
   WarningMessageBox warning("Rentrée invalide","Attention, le territoire est rentré à une date antérieure.");
   warning.exec();
  }
 }
 else
 {
  QString territory_path = "Territoires/"+QString::number(territory.id())+".ztm";
  QFile territory_file(territory_path);

  QString permission_path = "Autorisations/"+QString::number(permission.id())+".ztm";
  QFile permission_file(permission_path);

  territory.add_event(TerritoryEvent(ZTM::EnterType,date_button.dateTime(),note_text.toPlainText(),territory.holder_id()));
  permission.remove_territory(territory.id());

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
