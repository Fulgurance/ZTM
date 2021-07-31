#include <QGraphicsScene>
#include <QPixmap>
#include <QFileInfo>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QTextEdit>
#include "TerritoryShowBox.h"

TerritoryShowBox::TerritoryShowBox(QWidget *parent) : QDialog(parent)
{
 initialize();
 initialize_pointers();
 create_buttons();
 create_layouts();
 create_group_boxs();
 create_tabs();
 connect_buttons();
}

TerritoryShowBox::~TerritoryShowBox()
{
 delete first_path;
 delete second_path;
 delete first_view;
 delete second_view;
}

void TerritoryShowBox::initialize()
{
 setWindowTitle("Aperçu");
 setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
 setLayout(&layout);
}

void TerritoryShowBox::initialize_pointers()
{
 first_path = new QString;
 second_path = new QString;
 first_scene = new QGraphicsScene(this);
 second_scene = new QGraphicsScene(this);
 first_view = new QGraphicsView(first_scene);
 second_view = new QGraphicsView(second_scene);
}

void TerritoryShowBox::create_first_print_button()
{
 first_print_button.setText("Imprimer");
 first_print_button.setToolTip("Imprimer la face recto du territoire");
}

void TerritoryShowBox::create_second_print_button()
{
 second_print_button.setText("Imprimer");
 second_print_button.setToolTip("Imprimer la face verso du territoire");
}

void TerritoryShowBox::create_end_button()
{
 end_button.setText("Fermer");
 end_button.setToolTip("Fermer l'aperçu du territoire");
}

void TerritoryShowBox::create_buttons()
{
 create_first_print_button();
 create_second_print_button();
 create_end_button();
}

void TerritoryShowBox::create_first_picture_layout()
{
 first_picture_layout.addWidget(first_view,0,0,1,2);
 first_picture_layout.addWidget(&first_print_button,4,0,1,2);
}

void TerritoryShowBox::create_second_picture_layout()
{
 second_picture_layout.addWidget(second_view,0,0,1,2);
 second_picture_layout.addWidget(&second_print_button,4,0,1,2);
}

void TerritoryShowBox::create_first_picture_tab_layout()
{
 first_picture_tab_layout.addWidget(&first_picture_box);
}

void TerritoryShowBox::create_second_picture_tab_layout()
{
 second_picture_tab_layout.addWidget(&second_picture_box);
}

void TerritoryShowBox::create_layout()
{
 layout.addWidget(&tabs,0,0,1,4);
 layout.addWidget(&end_button,1,3,1,1);
}

void TerritoryShowBox::create_layouts()
{
 create_first_picture_layout();
 create_second_picture_layout();
 create_first_picture_tab_layout();
 create_second_picture_tab_layout();
 create_layout();
}

void TerritoryShowBox::create_first_picture_box()
{
 first_picture_box.setTitle("Aperçu du territoire face recto");
 first_picture_box.setLayout(&first_picture_layout);
}

void TerritoryShowBox::create_second_picture_box()
{
 second_picture_box.setTitle("Aperçu du territoire face verso");
 second_picture_box.setLayout(&second_picture_layout);
}

void TerritoryShowBox::create_group_boxs()
{
 create_first_picture_box();
 create_second_picture_box();
}

void TerritoryShowBox::create_tabs()
{
 first_picture_tab.setLayout(&first_picture_tab_layout);
 second_picture_tab.setLayout(&second_picture_tab_layout);
 tabs.addTab(&first_picture_tab,"Recto");
 tabs.addTab(&second_picture_tab,"Verso");
}

void TerritoryShowBox::connect_buttons()
{
 connect(&first_print_button,SIGNAL(clicked()),this,SLOT(print_first_picture()));
 connect(&second_print_button,SIGNAL(clicked()),this,SLOT(print_second_picture()));
 connect(&end_button,SIGNAL(clicked()),this,SLOT(close()));
}

void TerritoryShowBox::set_territory_id(int id)
{
 QString first_picture_path = "Territoires/"+QString::number(id)+"-Recto";
 QString second_picture_path = "Territoires/"+QString::number(id)+"-Verso";
 first_scene->clear();
 second_scene->clear();
 if(QFileInfo::exists(first_picture_path+".png"))
 {
  *first_path = first_picture_path+".png";
  first_scene->addPixmap(QPixmap(*first_path));
 }
 else if(QFileInfo::exists(first_picture_path+".jpeg"))
 {
  *first_path = first_picture_path+".jpeg";
  first_scene->addPixmap(QPixmap(*first_path));
 }
 else if(QFileInfo::exists(first_picture_path+".jpg"))
 {
  *first_path = first_picture_path+".jpg";
  first_scene->addPixmap(QPixmap(*first_path));
 }
 else
 {
  *first_path = "";
  first_scene->addText("Aucun image trouvée");
  first_print_button.setEnabled(false);
 }
 if(QFileInfo::exists(second_picture_path+".png"))
 {
  *second_path = second_picture_path+".png";
  second_scene->addPixmap(QPixmap(*second_path));
 }
 else if(QFileInfo::exists(second_picture_path+".jpeg"))
 {
  *second_path = second_picture_path+".jpeg";
  second_scene->addPixmap(QPixmap(*second_path));
 }
 else if(QFileInfo::exists(second_picture_path+".jpg"))
 {
  *second_path = second_picture_path+".jpg";
  second_scene->addPixmap(QPixmap(*second_path));
 }
 else
 {
  *second_path = "";
  second_scene->addText("Aucun image trouvée");
  second_print_button.setEnabled(false);
 }
 first_view->show();
 second_view->show();
}

void TerritoryShowBox::print_first_picture()
{
 QPrinter printer;
 QPrintDialog print_box(&printer);
 if (print_box.exec())
 {
  QTextEdit page;
  page.setHtml("<img src="+*first_path+">");
  page.print(&printer);
 }
}

void TerritoryShowBox::print_second_picture()
{
 QPrinter printer;
 QPrintDialog print_box(&printer);
 if (print_box.exec())
 {
  QTextEdit page;
  page.setHtml("<img src="+*second_path+">");
  page.print(&printer);
 }
}
