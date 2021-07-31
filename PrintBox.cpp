#include "PrintBox.h"
#include "WarningMessageBox.h"
#include "ZTM.h"
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QTextEdit>

using ZTM::print_period_list;

PrintBox::PrintBox(QWidget *parent) : QDialog(parent)
{
 initialize();
 create_labels();
 create_buttons();
 create_layouts();
 create_group_box();
 connect_buttons();
}

void PrintBox::initialize()
{
 setWindowTitle("Imprimer");
 setWindowIcon(QIcon(":Imprimer.png"));
 setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
 setLayout(&layout);
}

void PrintBox::create_first_date_label()
{
 first_date_label.setText("Date de début:");
}

void PrintBox::create_second_date_label()
{
 second_date_label.setText("Date de fin:");
}

void PrintBox::create_labels()
{
 create_first_date_label();
 create_second_date_label();
}

void PrintBox::create_first_date_button()
{
 first_date_button.setDate(QDate::currentDate());
 first_date_button.setToolTip("Date de début de la période à imprimer");
}

void PrintBox::create_second_date_button()
{
 second_date_button.setDate(QDate::currentDate());
 second_date_button.setToolTip("Date de fin de la période à imprimer");
}

void PrintBox::create_validate_button()
{
 validate_button.setText("Valider");
 validate_button.setToolTip("Valider la période à imprimer");
}

void PrintBox::create_cancel_button()
{
 cancel_button.setText("Annuler");
 cancel_button.setToolTip("Annuler l'impression");
}

void PrintBox::create_buttons()
{
 create_first_date_button();
 create_second_date_button();
 create_validate_button();
 create_cancel_button();
}

void PrintBox::create_box_layout()
{
 box_layout.addWidget(&first_date_label,0,0,1,3);
 box_layout.addWidget(&second_date_label,1,0,1,3);
 box_layout.addWidget(&first_date_button,0,3,1,3);
 box_layout.addWidget(&second_date_button,1,3,1,3);
 box_layout.addWidget(&validate_button,3,0,1,3);
 box_layout.addWidget(&cancel_button,3,3,1,3);
}

void PrintBox::create_layout()
{
 layout.addWidget(&box);
}

void PrintBox::create_layouts()
{
 create_box_layout();
 create_layout();
}

void PrintBox::create_group_box()
{
 box.setTitle("Sélectionner la période à imprimer");
 box.setLayout(&box_layout);
}

void PrintBox::connect_buttons()
{
 QObject::connect(&validate_button, SIGNAL(clicked()),this,SLOT(open_print_box()));
 QObject::connect(&cancel_button, SIGNAL(clicked()),this,SLOT(reject()));
}

void PrintBox::open_print_box()
{
 if (first_date_button.date() > second_date_button.date() || first_date_button.date() == second_date_button.date())
 {
  if (first_date_button.date() > second_date_button.date())
  {
   WarningMessageBox warning("Date invalide","Attention, la date de début est supérieure à la date de fin.");
   warning.exec();
  }
  if (first_date_button.date() == second_date_button.date())
  {
   WarningMessageBox warning("Date invalide","Attention, les deux dates sont équivalentes.");
   warning.exec();
  }
 }
 else
 {
  print_period(first_date_button.date(), second_date_button.date());
 }
}

void PrintBox::print_period(QDate first_date, QDate second_date)
{
 QPrinter printer;
 QPrintDialog print_box(&printer);
 if (print_box.exec())
 {
  QTextEdit page;
  page.setHtml(print_period_list(first_date,second_date));
  page.print(&printer);
  accept();
 }
}
