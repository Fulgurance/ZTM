#include "AddPermissionBox.h"
#include "WarningMessageBox.h"
#include "Permission.h"
#include <QFileInfo>
#include <QTextStream>

AddPermissionBox::AddPermissionBox(QWidget *parent) : QDialog(parent)
{
 initialize();
 create_labels();
 create_buttons();
 create_layouts();
 create_group_box();
 connect_buttons();
}

void AddPermissionBox::initialize()
{
 setWindowTitle("Ajouter une autorisation");
 setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
 setLayout(&layout);
}

void AddPermissionBox::create_id_label()
{
 id_label.setText("Numéro:");
}

void AddPermissionBox::create_name_label()
{
 name_label.setText("Nom:");
}

void AddPermissionBox::create_mail_label()
{
 mail_label.setText("Adresse mail:");
}

void AddPermissionBox::create_labels()
{
 create_id_label();
 create_name_label();
 create_mail_label();
}

void AddPermissionBox::create_id_button()
{
 id_button.setToolTip("Numéro d'identification de la nouvelle autorisation");
 id_button.setAccelerated(true);
 id_button.setValue(1);
 id_button.setMinimum(1);
 id_button.setMaximum(150);
}

void AddPermissionBox::create_name_button()
{
 name_button.setToolTip("Nom de la personne autorisée");
}

void AddPermissionBox::create_mail_button()
{
 mail_button.setToolTip("Adresse mail de la personne autorisée");
}

void AddPermissionBox::create_validate_button()
{
 validate_button.setText("Créer");
 validate_button.setToolTip("Enregistrer cette nouvelle autorisation");
}

void AddPermissionBox::create_cancel_button()
{
 cancel_button.setText("Annuler");
 cancel_button.setToolTip("Annuler la création de cette autorisation");
}

void AddPermissionBox::create_buttons()
{
 create_id_button();
 create_name_button();
 create_mail_button();
 create_validate_button();
 create_cancel_button();
}

void AddPermissionBox::create_box_layout()
{
 box_layout.addWidget(&id_label,0,0,1,1);
 box_layout.addWidget(&name_label,1,0,1,1);
 box_layout.addWidget(&mail_label,2,0,1,1);
 box_layout.addWidget(&id_button,0,1,1,1);
 box_layout.addWidget(&name_button,1,1,1,1);
 box_layout.addWidget(&mail_button,2,1,1,1);
 box_layout.addWidget(&validate_button,3,0,1,1);
 box_layout.addWidget(&cancel_button,3,1,1,1);
}

void AddPermissionBox::create_layout()
{
 layout.addWidget(&box);
}

void AddPermissionBox::create_layouts()
{
 create_layout();
 create_box_layout();
}

void AddPermissionBox::create_group_box()
{
 box.setTitle("Créer une autorisation");
 box.setLayout(&box_layout);
}

void AddPermissionBox::connect_buttons()
{
 QObject::connect(&validate_button, SIGNAL(clicked()),this,SLOT(validate()));
 QObject::connect(&cancel_button, SIGNAL(clicked()),this,SLOT(reject()));
}

void AddPermissionBox::validate()
{
 QString filepath = "Autorisations/"+QString::number(id_button.value())+".ztm";
 if(QFileInfo::exists(filepath) || name_button.text().isEmpty() || mail_button.text().isEmpty())
 {
  if (QFileInfo::exists(filepath))
  {
  WarningMessageBox warning("Autorisation invalide","Attention, ce numéro d'autorisation existe déjà");
  warning.exec();
  }
  if (name_button.text().isEmpty())
  {
  WarningMessageBox warning("Autorisation invalide","Attention, le nom de la personne autorisée n'a pas été saisi.");
  warning.exec();
  }
  if (mail_button.text().isEmpty())
  {
  WarningMessageBox warning("Autorisation invalide","Attention, l'adresse mail n'a pas été saisie.");
  warning.exec();
  }
 }
 else
 {
  QFile file(filepath);
  if (file.open(QIODevice::WriteOnly))
  {
   QDataStream flux(&file);
   Permission permission(id_button.value(),name_button.text(),mail_button.text());
   flux << permission;
   file.close();
  }
  accept();
 }
}
