#include <QFile>
#include <QDataStream>
#include "SettingsBox.h"
#include "WarningMessageBox.h"
#include "ZTM.h"

using ZTM::load_settings_data;

SettingsBox::SettingsBox(QWidget *parent) : QDialog(parent)
{
 initialize();
 create_labels();
 create_buttons();
 create_layout();
 connect_buttons();
}

void SettingsBox::initialize()
{
 setWindowTitle("Paramètres");
 setWindowIcon(QIcon(":Paramètres.png"));
 setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
 setLayout(&layout);
}

void SettingsBox::create_language_label()
{
 language_label.setText("Langue:");
}

void SettingsBox::create_congregation_label()
{
 congregation_label.setText("Assemblée locale:");
}

void SettingsBox::create_territory_label()
{
 territory_label.setText("Durée de sortie\nd'un territoire (en mois):");
}

void SettingsBox::create_historic_label()
{
 historic_label.setText("Durée de conservation\nde l'historique (en année):");
}

void SettingsBox::create_labels()
{
 create_language_label();
 create_congregation_label();
 create_territory_label();
 create_historic_label();
}

void SettingsBox::create_language_button()
{
 language_button.setToolTip("Langue de l'interface");
 language_button.setEnabled(false);
}

void SettingsBox::create_congregation_button()
{
 congregation_button.setToolTip("Nom de l'assemblée locale");
}

void SettingsBox::create_territory_button()
{
 territory_button.setToolTip("Nombre de mois durant lesquels un territoire peut-être sorti");
 territory_button.setAccelerated(true);
 territory_button.setValue(1);
 territory_button.setMinimum(1);
 territory_button.setMaximum(12);
}

void SettingsBox::create_historic_button()
{
 historic_button.setToolTip("Nombre d'années durant lesquelles l'historique des territoires est conservé");
 historic_button.setAccelerated(true);
 historic_button.setValue(1);
 historic_button.setMinimum(1);
 historic_button.setMaximum(5);
}

void SettingsBox::create_validate_button()
{
 validate_button.setText("Valider");
 validate_button.setToolTip("Valider la configuration des paramètres");
}

void SettingsBox::create_cancel_button()
{
 cancel_button.setText("Annuler");
 cancel_button.setToolTip("Annuler la configuration des paramètres");
}

void SettingsBox::create_buttons()
{
 create_language_button();
 create_congregation_button();
 create_territory_button();
 create_historic_button();
 create_validate_button();
 create_cancel_button();
}

void SettingsBox::create_layout()
{
 layout.addWidget(&language_label,0,0,1,1);
 layout.addWidget(&congregation_label,1,0,1,1);
 layout.addWidget(&territory_label,2,0,1,1);
 layout.addWidget(&historic_label,3,0,1,1);
 layout.addWidget(&language_button,0,1,1,1);
 layout.addWidget(&congregation_button,1,1,1,1);
 layout.addWidget(&territory_button,2,1,1,1);
 layout.addWidget(&historic_button,3,1,1,1);
 layout.addWidget(&validate_button,4,0,1,1);
 layout.addWidget(&cancel_button,4,1,1,1);
}

void SettingsBox::connect_buttons()
{
 QObject::connect(&validate_button, SIGNAL(clicked()),this,SLOT(validate()));
 QObject::connect(&cancel_button, SIGNAL(clicked()),this,SLOT(reject()));
}

void SettingsBox::load_database()
{
 Settings settings = load_settings_data();
 language_button.clear();
 language_button.addItem(settings.language());
 congregation_button.setText(settings.congregation());
 territory_button.setValue(settings.territory_duration());
 historic_button.setValue(settings.historic_duration());
}

void SettingsBox::validate()
{
 QString filepath = "Paramètres.ztm";
 if (congregation_button.text().isEmpty())
 {
  WarningMessageBox warning("Paramètres invalides","Attention, aucun nom d'assemblée locale n'a été saisi.");
  warning.exec();
 }
 else
 {
  QFile file(filepath);
  file.remove();
  if (file.open(QIODevice::WriteOnly))
  {
   QDataStream flux(&file);
   Settings settings(language_button.currentText(),congregation_button.text(),territory_button.value(),historic_button.value());
   flux << settings;
   file.close();
  }
  accept();
 }
}
