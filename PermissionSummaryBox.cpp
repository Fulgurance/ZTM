#include "PermissionSummaryBox.h"
#include "Permission.h"
#include "LogEvent.h"
#include "ZTM.h"

using ZTM::load_permission_data;
using ZTM::load_territory_data;

PermissionSummaryBox::PermissionSummaryBox(QWidget *parent) : QDialog(parent)
{
 initialize();
 create_group_box();
 create_summary_text();
 create_button();
 create_layouts();
 connect_button();
}

void PermissionSummaryBox::initialize()
{
 setWindowTitle("Détail");
 setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
 setLayout(&layout);
}

void PermissionSummaryBox::create_group_box()
{
 box.setLayout(&box_layout);
}

void PermissionSummaryBox::create_summary_text()
{
 summary_text.setReadOnly(true);
}

void PermissionSummaryBox::create_button()
{
 close_button.setText("Terminer");
 close_button.setToolTip("Fermer les détails de cette autorisation");
}

void PermissionSummaryBox::create_box_layout()
{
 box_layout.addWidget(&summary_text);
}

void PermissionSummaryBox::create_layout()
{
 layout.addWidget(&box,0,0,1,5);
 layout.addWidget(&close_button,1,4,1,1);
}

void PermissionSummaryBox::create_layouts()
{
 create_box_layout();
 create_layout();
}

void PermissionSummaryBox::set_permission_id(int id)
{
 summary_text.clear();
 permission_id = id;
 box.setTitle("Autorisation n°"+QString::number(id));
 Permission data = load_permission_data(id);
 QString summary;
 summary.append("<font color=\"#009fff\"><u><i><b>Informations</b></i></u></font><br>");
 summary.append("<b>-Nom: <font color=\"#0000ff\">"+data.name()+"</font></b><br>");
 summary.append("<b>-Adresse E-Mail:</b> "+data.mail()+"<br>");
 summary.append("<b>-Territoires possédés:</b><br>");
 if(!data.holded_territories().isEmpty())
 {
  for (int i = 0; i < data.holded_territories().size(); i++)
  {
   summary.append(load_territory_data(data.holded_territories()[i]).list_name()+"<br>");
  }
 }
 else
 {
  summary.append("<i>Aucun</i><br>");
 }
 summary_text.setHtml(summary);
}

void PermissionSummaryBox::connect_button()
{
 QObject::connect(&close_button,SIGNAL(clicked()),this,SLOT(accept()));
}
