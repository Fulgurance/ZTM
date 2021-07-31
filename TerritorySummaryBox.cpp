#include "TerritorySummaryBox.h"
#include "Territory.h"
#include "LogEvent.h"
#include "ZTM.h"

using ZTM::load_territory_data;
using ZTM::date_string;

TerritorySummaryBox::TerritorySummaryBox(QWidget *parent) : QDialog(parent)
{
 initialize();
 initialize_pointers();
 create_group_box();
 create_summary_text();
 create_buttons();
 create_layouts();
 connect_buttons();
}

void TerritorySummaryBox::initialize()
{
 setWindowTitle("Détail");
 setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
 setLayout(&layout);
}

void TerritorySummaryBox::initialize_pointers()
{
 territory_show_box = new TerritoryShowBox(this);
}

void TerritorySummaryBox::create_group_box()
{
 box.setLayout(&box_layout);
}

void TerritorySummaryBox::create_summary_text()
{
 summary_text.setReadOnly(true);
}

void TerritorySummaryBox::create_show_button()
{
 show_button.setText("Aperçu");
 show_button.setToolTip("Afficher l'aperçu du territoire");
}

void TerritorySummaryBox::create_close_button()
{
 close_button.setText("Fermer");
 close_button.setToolTip("Fermer les détails de ce territoire");
}

void TerritorySummaryBox::create_buttons()
{
 create_show_button();
 create_close_button();
}

void TerritorySummaryBox::create_box_layout()
{
 box_layout.addWidget(&summary_text);
}

void TerritorySummaryBox::create_layout()
{
 layout.addWidget(&box,0,0,1,5);
 layout.addWidget(&show_button,4,0,1,2);
 layout.addWidget(&close_button,4,4,1,1);
}

void TerritorySummaryBox::create_layouts()
{
 create_box_layout();
 create_layout();
}

void TerritorySummaryBox::set_territory_id(int id)
{
 summary_text.clear();
 territory_show_box->set_territory_id(id);
 box.setTitle("Territoire n°"+QString::number(id));
 Territory data = load_territory_data(id);
 QString summary;
 QString available;
 QString last_out;
 QString last_change_assignment;
 QString last_enter;
 if (data.last_out_date().isNull())
 {
  last_out = "Aucune";
 }
 else
 {
  last_out = "Le "+date_string(data.last_out_date().date())+" à "+data.last_out_date().time().toString();
 }
 if (data.last_change_assignment_date().isNull())
 {
  last_change_assignment = "Aucun";
 }
 else
 {
  last_change_assignment = "Le "+date_string(data.last_change_assignment_date().date())+" à "+data.last_change_assignment_date().time().toString();
 }
 if (data.last_enter_date().isNull())
 {
  last_enter = "Aucune";
 }
 else
 {
  last_enter = "Le "+date_string(data.last_enter_date().date())+" à "+data.last_enter_date().time().toString();
 }
 if (data.available())
 {
  available = "<font color=\"#00dd00\"><b>Oui</b></font>";
 }
 else
 {
  available = "<font color=\"#ff0000\"><b>Non</b></font>";
 }
 summary.append("<font color=\"#009fff\"><u><i><b>Informations</b></i></u></font><br>");
 summary.append("<b>-Lieu: <font color=\"#0000ff\">"+data.name()+"</font></b><br>");
 summary.append("<b>-Dernière sortie:</b> "+last_out+"<br>");
 summary.append("<b>-Dernier réassignement:</b> "+last_change_assignment+"<br>");
 summary.append("<b>-Dernière rentrée:</b> "+last_enter+"<br>");
 summary.append("<b>-Disponible:</b> "+available+"<br><br>");
 if (!data.events().isEmpty())
 {
  summary.append("<font color=\"#df0080\"><u><i><b>Historique</b></i></u></font><br>");
  foreach(TerritoryEvent event, data.events())
  {
   summary.append(event.list_name());
  }
 }
 summary_text.setHtml(summary);
}

void TerritorySummaryBox::connect_buttons()
{
 QObject::connect(&close_button,SIGNAL(clicked()),this,SLOT(accept()));
 QObject::connect(&show_button,SIGNAL(clicked()),this,SLOT(open_territory_show_box()));
}

void TerritorySummaryBox::open_territory_show_box()
{
 territory_show_box->exec();
}
