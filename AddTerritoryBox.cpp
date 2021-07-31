#include "AddTerritoryBox.h"
#include "WarningMessageBox.h"
#include "Territory.h"
#include <QFileInfo>
#include <QDataStream>

AddTerritoryBox::AddTerritoryBox(QWidget *parent) : QDialog(parent)
{
 initialize();
 create_labels();
 create_buttons();
 create_layouts();
 create_group_box();
 connect_buttons();
}

void AddTerritoryBox::initialize()
{
 setWindowTitle("Ajouter un territoire");
 setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
 setLayout(&layout);
}

void AddTerritoryBox::create_group_box()
{
 box.setTitle("Créer un nouveau territoire");
 box.setLayout(&box_layout);
}

void AddTerritoryBox::create_id_label()
{
 id_label.setText("Numéro:");
}

void AddTerritoryBox::create_name_label()
{
 name_label.setText("Nom:");
}

void AddTerritoryBox::create_pictures_label()
{
 pictures_label.setText("Images du territoire");
}

void AddTerritoryBox::create_first_file_label()
{
 first_file_label.setText("(Aucun)");
 first_file_label.setStyleSheet("QLabel { color: grey }");
}

void AddTerritoryBox::create_second_file_label()
{
 second_file_label.setText("(Aucun)");
 second_file_label.setStyleSheet("QLabel { color: grey }");
}

void AddTerritoryBox::create_labels()
{
 create_id_label();
 create_name_label();
 create_pictures_label();
 create_first_file_label();
 create_second_file_label();
}

void AddTerritoryBox::create_id_button()
{
 id_button.setToolTip("Numéro du nouveau territoire");
 id_button.setAccelerated(true);
 id_button.setValue(1);
 id_button.setMinimum(1);
 id_button.setMaximum(150);
}

void AddTerritoryBox::create_name_button()
{
 name_button.setToolTip("Nom du nouveau territoire");
}

void AddTerritoryBox::create_first_check_button()
{
 first_check_button.setText("Scan recto :");
 first_check_button.setStyleSheet("QCheckBox { color: grey }");
}

void AddTerritoryBox::create_second_check_button()
{
 second_check_button.setText("Scan verso :");
 second_check_button.setStyleSheet("QCheckBox { color: grey }");
}

void AddTerritoryBox::create_first_import_button()
{
 first_import_button.setText("Importer");
 first_import_button.setStyleSheet("QPushButton { color: grey }");
 first_import_button.setToolTip("Importer le scan de la partie recto du territoire");
 first_import_button.setDisabled(true);
}

void AddTerritoryBox::create_second_import_button()
{
 second_import_button.setText("Importer");
 second_import_button.setStyleSheet("QPushButton { color: grey }");
 second_import_button.setToolTip("Importer le scan de la partie verso du territoire");
 second_import_button.setDisabled(true);
}

void AddTerritoryBox::create_validate_button()
{
 validate_button.setText("Créer");
 validate_button.setToolTip("Enregistrer ce nouveau territoire");
}

void AddTerritoryBox::create_cancel_button()
{
 cancel_button.setText("Annuler");
 cancel_button.setToolTip("Annuler la création de ce territoire");
}

void AddTerritoryBox::create_buttons()
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

void AddTerritoryBox::create_box_layout()
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

void AddTerritoryBox::create_layout()
{
 layout.addWidget(&box);
}

void AddTerritoryBox::create_layouts()
{
 create_box_layout();
 create_layout();
}

void AddTerritoryBox::connect_buttons()
{
 QObject::connect(&first_check_button, SIGNAL(stateChanged(int)),this,SLOT(first_check(int)));
 QObject::connect(&second_check_button, SIGNAL(stateChanged(int)),this,SLOT(second_check(int)));
 QObject::connect(&first_import_button, SIGNAL(clicked()),this,SLOT(first_import()));
 QObject::connect(&second_import_button, SIGNAL(clicked()),this,SLOT(second_import()));
 QObject::connect(&validate_button, SIGNAL(clicked()),this,SLOT(validate()));
 QObject::connect(&cancel_button, SIGNAL(clicked()),this,SLOT(reject()));
}

void AddTerritoryBox::first_check(int state)
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

void AddTerritoryBox::second_check(int state)
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

void AddTerritoryBox::first_import()
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

void AddTerritoryBox::second_import()
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

void AddTerritoryBox::validate()
{ 
 QString filepath = "Territoires/"+QString::number(id_button.value())+".ztm";
 if (QFileInfo::exists(filepath) || name_button.text().isEmpty())
 {
  if(QFileInfo::exists(filepath))
  {
   WarningMessageBox warning("Territoire invalide","Attention, ce numéro de territoire existe déjà.");
   warning.exec();
  }
  if(name_button.text().isEmpty())
  {
   WarningMessageBox warning("Territoire invalide","Attention, aucun nom de territoire n'a été saisi.");
   warning.exec();
  }
 }
 else
 {
  QFile file(filepath);
  if (file.open(QIODevice::WriteOnly))
  {
   QDataStream flux(&file);
   if(first_check_button.isChecked() && first_file_label.text() != "(Aucun)")
   {
    QFile::copy(first_file_label.text(), "Territoires/"+QString::number(id_button.value())+"-Recto."+QFileInfo(first_file_label.text()).completeSuffix());
   }
   if(second_check_button.isChecked() && second_file_label.text() != "(Aucun)")
   {
    QFile::copy(second_file_label.text(), "Territoires/"+QString::number(id_button.value())+"-Verso."+QFileInfo(second_file_label.text()).completeSuffix());
   }
   Territory territory(id_button.value(),name_button.text());
   flux << territory;
   file.close();
  }
  accept();
 }
}
