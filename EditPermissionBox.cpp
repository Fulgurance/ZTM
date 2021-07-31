#include "EditPermissionBox.h"
#include "WarningMessageBox.h"
#include "Permission.h"
#include "ZTM.h"
#include <QFileInfo>
#include <QTextStream>

using ZTM::load_permission_data;

EditPermissionBox::EditPermissionBox(QWidget *parent) : QDialog(parent)
{
 initialize();
 create_labels();
 create_buttons();
 create_layouts();
 create_group_box();
 connect_buttons();
}

void EditPermissionBox::initialize()
{
 setWindowTitle("Editer une autorisation");
 setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
 setLayout(&layout);
}

void EditPermissionBox::create_id_label()
{
 id_label.setText("Numéro:");
}

void EditPermissionBox::create_name_label()
{
 name_label.setText("Nom:");
}

void EditPermissionBox::create_mail_label()
{
 mail_label.setText("Adresse mail:");
}

void EditPermissionBox::create_labels()
{
 create_id_label();
 create_name_label();
 create_mail_label();
}

void EditPermissionBox::create_id_button()
{
 id_button.setToolTip("Numéro de l'autorisation modifiée");
 id_button.setAccelerated(true);
 id_button.setMinimum(1);
 id_button.setMaximum(150);
}

void EditPermissionBox::create_name_button()
{
 name_button.setToolTip("Nom de l'autorisation modifiée");
}

void EditPermissionBox::create_mail_button()
{
 mail_button.setToolTip("Adresse mail de l'autorisation modifiée");
}

void EditPermissionBox::create_validate_button()
{
 validate_button.setText("Valider");
 validate_button.setToolTip("Enregistrer les modifications sur cette autorisation");
}

void EditPermissionBox::create_cancel_button()
{
 cancel_button.setText("Annuler");
 cancel_button.setToolTip("Annuler les modifications sur cette autorisation");
}

void EditPermissionBox::create_buttons()
{
 create_id_button();
 create_name_button();
 create_mail_button();
 create_validate_button();
 create_cancel_button();
}

void EditPermissionBox::create_box_layout()
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

void EditPermissionBox::create_layout()
{
 layout.addWidget(&box);
}

void EditPermissionBox::create_layouts()
{
 create_layout();
 create_box_layout();
}

void EditPermissionBox::create_group_box()
{
 box.setTitle("Modifier une autorisation");
 box.setLayout(&box_layout);
}

void EditPermissionBox::set_permission_id(int id)
{
 permission_id = id;
 Permission data = load_permission_data(id);
 box.setTitle("Modifier l'autorisation n°"+QString::number(id)+" de "+data.name());
 id_button.setValue(id);
 name_button.setText(data.name());
 mail_button.setText(data.mail());
}

void EditPermissionBox::connect_buttons()
{
 QObject::connect(&validate_button, SIGNAL(clicked()),this,SLOT(validate()));
 QObject::connect(&cancel_button, SIGNAL(clicked()),this,SLOT(reject()));
}

void EditPermissionBox::validate()
{
 QString filepath = "Autorisations/"+QString::number(permission_id)+".ztm";
 QString edit_filepath = "Autorisations/"+QString::number(id_button.value())+".ztm";
 Permission data = load_permission_data(permission_id);
 QFile edit_file(edit_filepath);
 QFile file(filepath);
 if (id_button.value() != data.id() && QFileInfo::exists(edit_filepath))
 {
  WarningMessageBox warning("Modification invalide","Attention, ce numéro d'autorisation existe déjà.");
  warning.exec();
 }
 else
 {
  if (edit_file.open(QIODevice::WriteOnly))
  {
   if (id_button.value() != data.id())
   {
    file.remove();
   }
   QDataStream flux(&edit_file);
   data.set_id(id_button.value());
   data.set_name(name_button.text());
   data.set_mail(mail_button.text());
   flux << data;
   edit_file.close();
  }
  accept();
 }
}
