#include "DatabaseEditorBox.h"
#include "ZTM.h"
#include "WarningMessageBox.h"
#include <QFile>

using ZTM::territories_list;
using ZTM::permissions_list;

DatabaseEditorBox::DatabaseEditorBox(QWidget *parent) : QDialog(parent)
{
 initialize();
 create_buttons();
 create_list_boxs();
 create_layouts();
 create_group_boxs();
 create_tabs();
 connect_buttons();
}

void DatabaseEditorBox::initialize()
{
 setWindowTitle("Base de données");
 setWindowIcon(QIcon(":BaseDeDonnées.png"));
 setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
 setLayout(&layout);
 initialize_pointers();
}

void DatabaseEditorBox::initialize_pointers()
{
 new_territory_box = new AddTerritoryBox(this);
 new_people_box = new AddPermissionBox(this);
 territory_summary_box = new TerritorySummaryBox(this);
 permission_summary_box = new PermissionSummaryBox(this);
 territory_edit_box = new EditTerritoryBox(this);
 edit_permission_box = new EditPermissionBox(this);
}

void DatabaseEditorBox::create_add_territory_button()
{
 add_territory_button.setText("Ajouter");
 add_territory_button.setToolTip("Ajouter un nouveau territoire");
}

void DatabaseEditorBox::create_delete_territory_button()
{
 delete_territory_button.setText("Supprimer");
 delete_territory_button.setToolTip("Supprimer les territoires sélectionnés");
}

void DatabaseEditorBox::create_edit_territory_button()
{
 edit_territory_button.setText("Modifier");
 edit_territory_button.setToolTip("Modifier les territoires sélectionnés");
}

void DatabaseEditorBox::create_detail_territory_button()
{
 detail_territory_button.setText("Détails");
 detail_territory_button.setToolTip("Afficher les détails des territoires sélectionnés");
}

void DatabaseEditorBox::create_add_people_button()
{
 add_people_button.setText("Ajouter");
 add_people_button.setToolTip("Ajouter une nouvelle autorisation");
}

void DatabaseEditorBox::create_delete_people_button()
{
 delete_people_button.setText("Supprimer");
 delete_people_button.setToolTip("Supprimer les autorisations sélectionnées");
}

void DatabaseEditorBox::create_edit_people_button()
{
 edit_people_button.setText("Modifier");
 edit_people_button.setToolTip("Modifier les autorisations sélectionnées");
}

void DatabaseEditorBox::create_detail_people_button()
{
 detail_people_button.setText("Détails");
 detail_people_button.setToolTip("Afficher les détails des autorisations sélectionnées");
}

void DatabaseEditorBox::create_end_button()
{
 end_button.setText("Terminer");
 end_button.setToolTip("Mettre fin à l'édition de la base de données");
}

void DatabaseEditorBox::create_buttons()
{
 create_add_territory_button();
 create_delete_territory_button();
 create_edit_territory_button();
 create_detail_territory_button();
 create_add_people_button();
 create_delete_people_button();
 create_edit_people_button();
 create_detail_people_button();
 create_end_button();
}

void DatabaseEditorBox::create_territory_list_box()
{
 territory_list_box.setModel(&territory_modele);
 territory_list_box.setEditTriggers(QAbstractItemView::NoEditTriggers);
 territory_list_box.setSelectionMode(QAbstractItemView::ExtendedSelection);
}

void DatabaseEditorBox::create_people_list_box()
{
 people_list_box.setModel(&people_modele);
 people_list_box.setEditTriggers(QAbstractItemView::NoEditTriggers);
 people_list_box.setSelectionMode(QAbstractItemView::ExtendedSelection);
}

void DatabaseEditorBox::create_list_boxs()
{
 create_territory_list_box();
 create_people_list_box();
}

void DatabaseEditorBox::create_territory_layout()
{
 territory_layout.addWidget(&territory_list_box,0,0,1,2);
 territory_layout.addWidget(&add_territory_button,1,0,1,1);
 territory_layout.addWidget(&delete_territory_button,1,1,1,1);
 territory_layout.addWidget(&edit_territory_button,2,0,1,1);
 territory_layout.addWidget(&detail_territory_button,2,1,1,1);
}

void DatabaseEditorBox::create_people_layout()
{
 people_layout.addWidget(&people_list_box,0,0,1,2);
 people_layout.addWidget(&add_people_button,1,0,1,1);
 people_layout.addWidget(&delete_people_button,1,1,1,1);
 people_layout.addWidget(&edit_people_button,2,0,1,1);
 people_layout.addWidget(&detail_people_button,2,1,1,1);
}

void DatabaseEditorBox::create_territory_tab_layout()
{
 territory_tab_layout.addWidget(&territory_box);
}

void DatabaseEditorBox::create_people_tab_layout()
{
 people_tab_layout.addWidget(&people_box);
}

void DatabaseEditorBox::create_layout()
{
 layout.addWidget(&tabs,0,0,1,4);
 layout.addWidget(&end_button,1,3,1,1);
}

void DatabaseEditorBox::create_layouts()
{
 create_territory_layout();
 create_people_layout();
 create_territory_tab_layout();
 create_people_tab_layout();
 create_layout();
}

void DatabaseEditorBox::create_territory_box()
{
 territory_box.setTitle("Liste des territoires existants");
 territory_box.setLayout(&territory_layout);
}

void DatabaseEditorBox::create_people_box()
{
 people_box.setTitle("Liste des autorisations existantes");
 people_box.setLayout(&people_layout);
}

void DatabaseEditorBox::create_group_boxs()
{
 create_territory_box();
 create_people_box();
}

void DatabaseEditorBox::create_tabs()
{
 territory_tab.setLayout(&territory_tab_layout);
 people_tab.setLayout(&people_tab_layout);
 tabs.addTab(&territory_tab,"Territoires");
 tabs.addTab(&people_tab,"Autorisations");
}

void DatabaseEditorBox::connect_buttons()
{
 connect(&add_territory_button,SIGNAL(clicked()),this,SLOT(open_new_territory_box()));
 connect(&add_people_button,SIGNAL(clicked()),this,SLOT(open_new_people_box()));
 connect(&delete_territory_button,SIGNAL(clicked()),this,SLOT(delete_territory()));
 connect(&delete_people_button,SIGNAL(clicked()),this,SLOT(delete_permission()));
 connect(&edit_territory_button,SIGNAL(clicked()),this,SLOT(open_territory_edit_box()));
 connect(&edit_people_button,SIGNAL(clicked()),this,SLOT(open_people_edit_box()));
 connect(&detail_territory_button,SIGNAL(clicked()),this,SLOT(open_territory_detail_box()));
 connect(&detail_people_button,SIGNAL(clicked()),this,SLOT(open_people_detail_box()));
 connect(&end_button,SIGNAL(clicked()),this,SLOT(close()));
}

void DatabaseEditorBox::load_database()
{
 territory_modele.setStringList(territories_list());
 people_modele.setStringList(permissions_list());
}

void DatabaseEditorBox::open_new_territory_box()
{
 if (new_territory_box->exec())
 {
  territory_modele.setStringList(territories_list());
 }
}

void DatabaseEditorBox::open_new_people_box()
{
 if (new_people_box->exec())
 {
  people_modele.setStringList(permissions_list());
 }
}

void DatabaseEditorBox::delete_territory()
{
 QModelIndexList selection_list = territory_list_box.selectionModel()->selectedIndexes();
 for (int i = 0; i < selection_list.size(); i++)
 {
  QString id = selection_list[i].data().toString();
  id.resize(id.indexOf(" - "));
  QString path = "Territoires/"+id;
  QFile file(path+".ztm");
  file.remove();
  if(QFileInfo::exists(path+"-Recto.png"))
  {
   QFile file(path+"-Recto.png");
   file.remove();
  }
  if(QFileInfo::exists(path+"-Recto.jpeg"))
  {
   QFile file(path+"-Recto.jpeg");
   file.remove();
  }
  if(QFileInfo::exists(path+"-Recto.jpg"))
  {
   QFile file(path+"-Recto.jpg");
   file.remove();
  }
  if(QFileInfo::exists(path+"-Verso.png"))
  {
   QFile file(path+"-Verso.png");
   file.remove();
  }
  if(QFileInfo::exists(path+"-Verso.jpeg"))
  {
   QFile file(path+"-Verso.jpeg");
   file.remove();
  }
  if(QFileInfo::exists(path+"-Verso.jpg"))
  {
   QFile file(path+"-Verso.jpg");
   file.remove();
  }
 }
 territory_modele.setStringList(territories_list());
}

void DatabaseEditorBox::delete_permission()
{
 QModelIndexList selection_list = people_list_box.selectionModel()->selectedIndexes();
 for (int i = 0; i < selection_list.size(); i++)
 {
  QString id = selection_list[i].data().toString();
  id.resize(id.indexOf(" - "));
  QString path = "Autorisations/"+id+".ztm";
  QFile file(path);
  file.remove();
 }
 people_modele.setStringList(permissions_list());
}

void DatabaseEditorBox::open_territory_edit_box()
{
 QModelIndexList selection_list = territory_list_box.selectionModel()->selectedIndexes();
 for (int i = 0; i < selection_list.size(); i++)
 {
  QString id = selection_list[i].data().toString();
  id.resize(id.indexOf(" - "));
  territory_edit_box->set_territory_id(id.toInt());
  territory_edit_box->exec();
 }
 territory_modele.setStringList(territories_list());
}

void DatabaseEditorBox::open_people_edit_box()
{
 QModelIndexList selection_list = people_list_box.selectionModel()->selectedIndexes();
 for (int i = 0; i < selection_list.size(); i++)
 {
  QString id = selection_list[i].data().toString();
  id.resize(id.indexOf(" - "));
  edit_permission_box->set_permission_id(id.toInt());
  edit_permission_box->exec();
 }
 people_modele.setStringList(permissions_list());
}

void DatabaseEditorBox::open_territory_detail_box()
{
 QModelIndexList selection_list = territory_list_box.selectionModel()->selectedIndexes();
 for (int i = 0; i < selection_list.size(); i++)
 {
  QString id = selection_list[i].data().toString();
  id.resize(id.indexOf(" - "));
  territory_summary_box->set_territory_id(id.toInt());
  territory_summary_box->exec();
 }
}

void DatabaseEditorBox::open_people_detail_box()
{
 QModelIndexList selection_list = people_list_box.selectionModel()->selectedIndexes();
 for (int i = 0; i < selection_list.size(); i++)
 {
  QString id = selection_list[i].data().toString();
  id.resize(id.indexOf(" - "));
  permission_summary_box->set_permission_id(id.toInt());
  permission_summary_box->exec();
 }
}
