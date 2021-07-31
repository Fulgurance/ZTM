#include "EditTerritoryBox.h"
#include "WarningMessageBox.h"
#include "Territory.h"
#include "ZTM.h"
#include <QFileInfo>
#include <QDataStream>
#include <QFileDialog>

using ZTM::load_territory_data;

EditTerritoryBox::EditTerritoryBox(QWidget *parent) : QDialog(parent)
{
 initialize();
 create_labels();
 create_buttons();
 create_layouts();
 create_group_box();
 connect_buttons();
}

void EditTerritoryBox::initialize()
{
 setWindowTitle("Editer un territoire");
 setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
 setLayout(&layout);
}

void EditTerritoryBox::create_group_box()
{
 box.setLayout(&box_layout);
}

void EditTerritoryBox::create_id_label()
{
 id_label.setText("Numéro:");
}

void EditTerritoryBox::create_name_label()
{
 name_label.setText("Nom:");
}

void EditTerritoryBox::create_pictures_label()
{
 pictures_label.setText("Images du territoire");
}

void EditTerritoryBox::create_first_file_label()
{
 first_file_label.setStyleSheet("QLabel { color: grey }");
}

void EditTerritoryBox::create_second_file_label()
{
 second_file_label.setStyleSheet("QLabel { color: grey }");
}

void EditTerritoryBox::create_labels()
{
 create_id_label();
 create_name_label();
 create_pictures_label();
 create_first_file_label();
 create_second_file_label();
}

void EditTerritoryBox::create_id_button()
{
 id_button.setToolTip("Numéro du territoire modifié");
 id_button.setAccelerated(true);
 id_button.setMinimum(1);
 id_button.setMaximum(150);
}

void EditTerritoryBox::create_name_button()
{
 name_button.setToolTip("Nom du territoire modifié");
}

void EditTerritoryBox::create_first_check_button()
{
 first_check_button.setText("Scan recto :");
 first_check_button.setStyleSheet("QCheckBox { color: grey }");
}

void EditTerritoryBox::create_second_check_button()
{
 second_check_button.setText("Scan verso :");
 second_check_button.setStyleSheet("QCheckBox { color: grey }");
}

void EditTerritoryBox::create_first_import_button()
{
 first_import_button.setText("Importer");
 first_import_button.setStyleSheet("QPushButton { color: grey }");
 first_import_button.setToolTip("Importer le scan de la partie recto du territoire");
 first_import_button.setDisabled(true);
}

void EditTerritoryBox::create_second_import_button()
{
 second_import_button.setText("Importer");
 second_import_button.setStyleSheet("QPushButton { color: grey }");
 second_import_button.setToolTip("Importer le scan de la partie verso du territoire");
 second_import_button.setDisabled(true);
}

void EditTerritoryBox::create_validate_button()
{
 validate_button.setText("Valider");
 validate_button.setToolTip("Enregistrer les modifications sur ce territoire");
}

void EditTerritoryBox::create_cancel_button()
{
 cancel_button.setText("Annuler");
 cancel_button.setToolTip("Annuler les modifications sur ce territoire");
}

void EditTerritoryBox::create_buttons()
{
 create_id_button();
 create_name_button();
 create_first_check_button();
 create_second_check_button();
 create_first_import_button();
 create_second_import_button();
 create_validate_button();
 create_cancel_button();
}

void EditTerritoryBox::create_box_layout()
{
 box_layout.addWidget(&id_label,0,0,1,1);
 box_layout.addWidget(&name_label,1,0,1,1);
 box_layout.addWidget(&id_button,0,1,1,1);
 box_layout.addWidget(&pictures_label,2,0,1,1);
 box_layout.addWidget(&first_file_label,3,1,1,1);
 box_layout.addWidget(&second_file_label,4,1,1,1);
 box_layout.addWidget(&name_button,1,1,1,1);
 box_layout.addWidget(&first_check_button,3,0,1,1);
 box_layout.addWidget(&second_check_button,4,0,1,1);
 box_layout.addWidget(&first_import_button,3,2,1,1);
 box_layout.addWidget(&second_import_button,4,2,1,1);
 box_layout.addWidget(&validate_button,5,0,1,1);
 box_layout.addWidget(&cancel_button,5,1,1,1);
}

void EditTerritoryBox::create_layout()
{
 layout.addWidget(&box);
}

void EditTerritoryBox::create_layouts()
{
 create_box_layout();
 create_layout();
}

void EditTerritoryBox::set_territory_id(int id)
{
 territory_id = id;
 Territory data = load_territory_data(id);
 box.setTitle("Modifier le territoire n°"+QString::number(id)+" à "+data.name());
 id_button.setValue(id);
 name_button.setText(data.name());
 QString first_picture_path = "Territoires/"+QString::number(id)+"-Recto";
 QString second_picture_path = "Territoires/"+QString::number(id)+"-Verso";
 if(QFileInfo::exists(first_picture_path+".png"))
 {
  first_file_label.setText(first_picture_path+".png");
 }
 else if(QFileInfo::exists(first_picture_path+".jpeg"))
 {
  first_file_label.setText(first_picture_path+".jpeg");
 }
 else if(QFileInfo::exists(first_picture_path+".jpg"))
 {
  first_file_label.setText(first_picture_path+".jpg");
 }
 else
 {
  first_file_label.setText("(Aucun)");
 }
 if(QFileInfo::exists(second_picture_path+".png"))
 {
  second_file_label.setText(second_picture_path+".png");
 }
 else if(QFileInfo::exists(second_picture_path+".jpeg"))
 {
  second_file_label.setText(second_picture_path+".jpeg");
 }
 else if(QFileInfo::exists(second_picture_path+".jpg"))
 {
  second_file_label.setText(second_picture_path+".jpg");
 }
 else
 {
  second_file_label.setText("(Aucun)");
 }
}

void EditTerritoryBox::connect_buttons()
{
 QObject::connect(&first_check_button, SIGNAL(stateChanged(int)),this,SLOT(first_check(int)));
 QObject::connect(&second_check_button, SIGNAL(stateChanged(int)),this,SLOT(second_check(int)));
 QObject::connect(&first_import_button, SIGNAL(clicked()),this,SLOT(first_import()));
 QObject::connect(&second_import_button, SIGNAL(clicked()),this,SLOT(second_import()));
 QObject::connect(&validate_button, SIGNAL(clicked()),this,SLOT(validate()));
 QObject::connect(&cancel_button, SIGNAL(clicked()),this,SLOT(reject()));
}

void EditTerritoryBox::first_check(int state)
{
 if (state==Qt::Checked)
 {
  first_file_label.setStyleSheet("QLabel { color: black }");
  first_check_button.setStyleSheet("QCheckBox { color: black }");
  first_import_button.setStyleSheet("QPushButton { color: black }");
  first_import_button.setDisabled(false);
 }
 else
 {
  first_file_label.setStyleSheet("QLabel { color: grey }");
  first_check_button.setStyleSheet("QCheckBox { color: grey }");
  first_import_button.setStyleSheet("QPushButton { color: grey }");
  first_import_button.setDisabled(true);
 }
}

void EditTerritoryBox::second_check(int state)
{
 if (state==Qt::Checked)
 {
  second_file_label.setStyleSheet("QLabel { color: black }");
  second_check_button.setStyleSheet("QCheckBox { color: black }");
  second_import_button.setStyleSheet("QPushButton { color: black }");
  second_import_button.setDisabled(false);
 }
 else
 {
  second_file_label.setStyleSheet("QLabel { color: grey }");
  second_check_button.setStyleSheet("QCheckBox { color: grey }");
  second_import_button.setStyleSheet("QPushButton { color: grey }");
  second_import_button.setDisabled(true);
 }
}

void EditTerritoryBox::first_import()
{
 QString selected_file;
 QFileDialog import_window(this);
 import_window.setWindowTitle("Importer");
 import_window.setFileMode(QFileDialog::ExistingFile);
 import_window.setNameFilter(tr("Fichiers images (*.png *.jpeg *.jpg);; Tous les fichiers (*.*)"));
 import_window.setViewMode(QFileDialog::List);
 import_window.setAcceptMode(QFileDialog::AcceptOpen);
 import_window.setLabelText(QFileDialog::LookIn, "Regardez dans :");
 import_window.setLabelText(QFileDialog::FileName, "Nom de fichier :");
 import_window.setLabelText(QFileDialog::FileType, "Type de fichiers :");
 import_window.setLabelText(QFileDialog::Accept, "Importer");
 import_window.setLabelText(QFileDialog::Reject, "Annuler");
 if(import_window.exec())
 {
  if (!import_window.selectedFiles().empty())
  {
   selected_file = import_window.selectedFiles()[0];
   first_file_label.setText(selected_file);
  }
 }
}

void EditTerritoryBox::second_import()
{
 QString selected_file;
 QFileDialog import_window(this);
 import_window.setWindowTitle("Importer");
 import_window.setFileMode(QFileDialog::ExistingFile);
 import_window.setNameFilter(tr("Fichiers images (*.png *.jpeg *.jpg);; Tous les fichiers (*.*)"));
 import_window.setViewMode(QFileDialog::List);
 import_window.setAcceptMode(QFileDialog::AcceptOpen);
 import_window.setLabelText(QFileDialog::LookIn, "Regardez dans :");
 import_window.setLabelText(QFileDialog::FileName, "Nom de fichier :");
 import_window.setLabelText(QFileDialog::FileType, "Type de fichiers :");
 import_window.setLabelText(QFileDialog::Accept, "Importer");
 import_window.setLabelText(QFileDialog::Reject, "Annuler");
 if(import_window.exec())
 {
  if (!import_window.selectedFiles().empty())
  {
   selected_file = import_window.selectedFiles()[0];
   second_file_label.setText(selected_file);
  }
 }
}

void EditTerritoryBox::validate()
{
 QString filepath = "Territoires/"+QString::number(territory_id)+".ztm";
 QString edit_filepath = "Territoires/"+QString::number(id_button.value())+".ztm";
 Territory data = load_territory_data(territory_id);
 QFile edit_file(edit_filepath);
 QFile file(filepath);
 QString remove_picture_id;
 if (id_button.value() != data.id() && QFileInfo::exists(edit_filepath))
 {
  WarningMessageBox warning("Modification invalide","Attention, ce numéro de territoire existe déjà.");
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
   if (first_check_button.isChecked() && first_file_label.text() != "(Aucun)")
   {
    if (QFileInfo::exists("Territoires/"+QString::number(data.id())+"-Recto.png"))
    {
     QFile first_picture("Territoires/"+QString::number(data.id())+"-Recto.png");
     first_picture.remove();
    }
    if (QFileInfo::exists("Territoires/"+QString::number(data.id())+"-Recto.jpeg"))
    {
     QFile first_picture("Territoires/"+QString::number(data.id())+"-Recto.jpeg");
     first_picture.remove();
    }
    if (QFileInfo::exists("Territoires/"+QString::number(data.id())+"-Recto.jpg"))
    {
     QFile first_picture("Territoires/"+QString::number(data.id())+"-Recto.jpg");
     first_picture.remove();
    }
    QFile::copy(first_file_label.text(), "Territoires/"+QString::number(id_button.value())+"-Recto."+QFileInfo(first_file_label.text()).completeSuffix());
   }
   if(second_check_button.isChecked() && second_file_label.text() != "(Aucun)")
   {
    if (QFileInfo::exists("Territoires/"+QString::number(data.id())+"-Verso.png"))
    {
     QFile second_picture("Territoires/"+QString::number(data.id())+"-Verso.png");
     second_picture.remove();
    }
    if (QFileInfo::exists("Territoires/"+QString::number(data.id())+"-Verso.jpeg"))
    {
     QFile second_picture("Territoires/"+QString::number(data.id())+"-Verso.jpeg");
     second_picture.remove();
    }
    if (QFileInfo::exists("Territoires/"+QString::number(data.id())+"-Verso.jpg"))
    {
     QFile second_picture("Territoires/"+QString::number(data.id())+"-Verso.jpg");
     second_picture.remove();
    }
    QFile::copy(second_file_label.text(), "Territoires/"+QString::number(id_button.value())+"-Verso."+QFileInfo(second_file_label.text()).completeSuffix());
   }
   QDataStream flux(&edit_file);
   data.set_id(id_button.value());
   data.set_name(name_button.text());
   flux << data;
   edit_file.close();
  }
 }
 accept();
}
