#include "HelpButtonBox.h"
#include "ZTM.h"
#include <QMessageBox>

using ZTM::HelpOutButtonText;
using ZTM::HelpAssignmentButtonText;
using ZTM::HelpEnterButtonText;
using ZTM::HelpDatabaseButtonText;
using ZTM::HelpSettingsButtonText;
using ZTM::HelpPrintButtonText;

HelpButtonBox::HelpButtonBox(QWidget *parent, int type) : QDialog(parent)
{
 help_type = type;
 initialize();
 create_text();
 create_button();
 create_layout();
 connect_button();
}

void HelpButtonBox::initialize()
{
 switch(help_type)
 {
  case HelpOutButtonText:
   setWindowTitle("Aide pour sortir un territoire");
   break;
  case HelpAssignmentButtonText:
   setWindowTitle("Aide pour réassigner un territoire");
   break;
  case HelpEnterButtonText:
   setWindowTitle("Aide pour rentrer un territoire");
   break;
  case HelpDatabaseButtonText:
   setWindowTitle("Aide pour l'édition de la base de données");
   break;
  case HelpSettingsButtonText:
   setWindowTitle("Aide pour la configuration des paramètres");
   break;
  case HelpPrintButtonText:
   setWindowTitle("Aide pour imprimer");
   break;
 }
 setWindowIcon(QIcon(":Info.png"));
 setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
 setLayout(&layout);
}

void HelpButtonBox::create_text()
{
 switch(help_type)
 {
  case HelpOutButtonText:
   text.setText("La fenêtre permettant la sortie d'un territoire se compose de <font color=\"#0000ff\"><b>4 champs principaux</font></b>:<br><br>"
                "<br><img src=:ChampNuméro.png><br>"
                "<font color=\"#0000ff\"><b>Le numéro</font></b><br>"
                "Ce champ vous permet de sélectionner le territoire à sortir. Pour cela, il vous suffit de cliquer sur la fenêtre<br>"
                "déroulante et de sélectionner le territoire voulu. Si la fenêtre est vide ou que le territoire voulu ne figure pas dedant,<br>"
                "veuillez vérifier que le territoire n'est pas déjà sorti ou tout simplement inexistant dans la base de données.<br><br>"
                "<br><img src=:ChampDate.png><br>"
                "<font color=\"#0000ff\"><b>La date</font></b><br>"
                "Ce champ vous permet de sélectionner la date et l'heure de la sortie du territoire.Vous pouvez l'éditer via le clavier<br>"
                "ou bien en cliquant sur les flèches. Par défaut, la date et l'heure sont celles du moment où la fenêtre est ouverte.<br><br>"
                "<br><img src=:ChampPersonne.png><br>"
                "<font color=\"#0000ff\"><b>La personne</font></b><br>"
                "Ce champ vous permet de sélectionner la personne sortant le territoire. Pour cela, il vous suffit de cliquer sur la fenêtre<br>"
                "déroulante et de sélectionner la personne voulue. Si la fenêtre est vide ou que la personne voulue ne figure pas dedant,<br>"
                "veuillez vérifier que la personne n'est tout simplement pas inexistante dans la base de données.<br><br>"
                "<br><img src=:ChampNote.png><br>"
                "<font color=\"#0000ff\"><b>La note</font></b><br>"
                "Ce champ facultatif vous permet tout simplement de saisir une note à propos de la sortie effectuée."
              );
   break;
  case HelpAssignmentButtonText:
   text.setText("La fenêtre permettant la réassignation d'un territoire se compose de <font color=\"#0000ff\"><b>4 champs principaux</font></b>:<br><br>"
                "<br><img src=:ChampNuméro.png><br>"
                "<font color=\"#0000ff\"><b>Le numéro</font></b><br>"
                "Ce champ vous permet de sélectionner le territoire à réassigner. Pour cela, il vous suffit de cliquer sur la fenêtre<br>"
                "déroulante et de sélectionner le territoire voulu. Si la fenêtre est vide ou que le territoire voulu ne figure pas dedant,<br>"
                "veuillez vérifier que le territoire soit déjà sorti, qu'il ne soit pas rentré ou tout simplement inexistant dans la base de données.<br><br>"
                "<br><img src=:ChampDate.png><br>"
                "<font color=\"#0000ff\"><b>La date</font></b><br>"
                "Ce champ vous permet de sélectionner la date et l'heure de la réassignation du territoire.Vous pouvez l'éditer via le clavier<br>"
                "ou bien en cliquant sur les flèches. Par défaut, la date et l'heure sont celles du moment où la fenêtre est ouverte.<br><br>"
                "<br><img src=:ChampPersonne.png><br>"
                "<font color=\"#0000ff\"><b>La personne</font></b><br>"
                "Ce champ vous permet de sélectionner la personne à qui le territoire est réassigné. Pour cela, il vous suffit de cliquer sur la fenêtre<br>"
                "déroulante et de sélectionner la personne voulue. Si la fenêtre est vide ou que la personne voulue ne figure pas dedant,<br>"
                "veuillez vérifier que la personne n'est tout simplement pas inexistante dans la base de données.<br><br>"
                "<br><img src=:ChampNote.png><br>"
                "<font color=\"#0000ff\"><b>La note</font></b><br>"
                "Ce champ facultatif vous permet tout simplement de saisir une note à propos de la sortie effectuée."
              );
   break;
  case HelpEnterButtonText:
   text.setText("La fenêtre permettant la rentrée d'un territoire se compose de <font color=\"#0000ff\"><b>3 champs principaux</font></b>:<br><br>"
                "<br><img src=:ChampNuméro.png><br>"
                "<font color=\"#0000ff\"><b>Le numéro</font></b><br>"
                "Ce champ vous permet de sélectionner le territoire à rentrer. Pour cela, il vous suffit de cliquer sur la fenêtre<br>"
                "déroulante et de sélectionner le territoire voulu. Si la fenêtre est vide ou que le territoire voulu ne figure pas dedant,<br>"
                "veuillez vérifier que le territoire n'est pas déjà rentré ou tout simplement inexistant dans la base de données.<br><br>"
                "<br><img src=:ChampDate.png><br>"
                "<font color=\"#0000ff\"><b>La date</font></b><br>"
                "Ce champ vous permet de sélectionner la date et l'heure de la rentrée du territoire.Vous pouvez l'éditer via le clavier<br>"
                "ou bien en cliquant sur les flèches. Par défaut, la date et l'heure sont celles du moment où la fenêtre est ouverte.<br><br>"
                "<br><img src=:ChampNote.png><br>"
                "<font color=\"#0000ff\"><b>La note</font></b><br>"
                "Ce champ facultatif vous permet tout simplement de saisir une note à propos de la rentrée effectuée."
              );
   break;
  case HelpDatabaseButtonText:
   text.setText("La fenêtre permettant la gestion de la base de données se compose de <font color=\"#0000ff\"><b>3 champs principaux</font></b>:<br><br>"
                "<br><img src=:ChampOnglets.png><br>"
                "<font color=\"#0000ff\"><b>Les onglets</font></b><br>"
                "Ce champ comporte 2 onglets, ceux-ci vous permettent de sélectionner la base de données que vous souhaitez éditer.<br>"
                "Pour cela, cliquez sur l'onglet désiré. Le premier onglet permet d'éditer la base de données qui regroupent les territoires,<br>"
                "le second permet d'éditer la base de données qui regroupent la liste des personnes autorisées à emprunter un territoire.<br><br>"
                "<br><img src=:ChampListe.png><br>"
                "<font color=\"#0000ff\"><b>La liste</font></b><br>"
                "Ce champ contient la liste des données contenues dans la base de données de l'onglet sélectionné.<br><br>"
                "<br><img src=:ChampBoutonsGestion.png><br>"
                "<font color=\"#0000ff\"><b>Les boutons de gestion</font></b><br>"
                "Ce champ comporte 4 boutons principaux:<br>"
                "-Le bouton <b>Ajouter</b> permet d'ajouter une donnée supplémentaire dans la base de données de l'onglet courant.<br>"
                "-Le bouton <b>Supprimer</b> permet d'effacer une donnée de la base de donnée de l'onglet courant.<br>"
                "<i>En sélectionnant plusieurs données ensembles avant d'appuyer sur le bouton, il est possible de faire une suppression multiple.</i><br>"
                "-Le bouton <b>Modifier</b> permet d'éditer une donnée de la base de donnée de l'onglet courant.<br>"
                "<i>En sélectionnant plusieurs données ensembles avant d'appuyer sur le bouton, il est possible de faire une édition multiple.</i><br>"
                "-Le bouton <b>Détails</b> permet d'avoir des renseignements supplémentaires sur une donnée de la base de donnée de l'onglet courant.<br>"
                "<i>En sélectionnant plusieurs données ensembles avant d'appuyer sur le bouton, il est possible d'afficher les détails de plusieurs données d'affilés.</i>"
              );
   break;
  case HelpSettingsButtonText:
   text.setText("La fenêtre permettant la configuration des paramètres se compose de <font color=\"#0000ff\"><b>4 champs principaux</font></b>:<br><br>"
                "<br><img src=:ChampLangue.png><br>"
                "<font color=\"#0000ff\"><b>La langue</font></b><br>"
                "Ce champ permet de choisir la langue des interfaces du logiciel. Par défaut, elle est en français.<br>"
                "Pour le moment, ce paramètre n'est pas modifiable car c'est la seule langue disponible.<br><br>"
                "<br><img src=:ChampCongrégation.png><br>"
                "<font color=\"#0000ff\"><b>La congrégation</font></b><br>"
                "Ce champ permet de saisir le nom de la congrégation.<br><br>"
                "<br><img src=:ChampDuréeSortie.png><br>"
                "<font color=\"#0000ff\"><b>La durée de sortie</font></b><br>"
                "Ce champ permet de saisir la durée maximale de sortie d'un territoire en nombres de mois.<br>"
                "Par défaut, cette durée est fixée à 4 mois<br><br>"
                "<br><img src=:ChampDuréeConservation.png><br>"
                "<font color=\"#0000ff\"><b>La durée de conservation</font></b><br>"
                "Ce champ permet de saisir la durée maximale de conservation de l'historique des territoires en nombres d'années.<br>"
                "Par défaut, cette durée est fixée à 1 an. Au delà de cette durée, l'historique est effacé.<br><br>"
              );
   break;
  case HelpPrintButtonText:
   text.setText("La fenêtre permettant d'imprimer se compose de <font color=\"#0000ff\"><b>2 champs principaux</font></b>:<br><br>"
                "<br><img src=:ChampDateDébut.png><br>"
                "<font color=\"#0000ff\"><b>La date de début</font></b><br>"
                "Ce champ permet de définir à partir de quelle date vous souhaiter imprimer l'historique de l'ensemble des<br>"
                "territoires de la base de données. Vous pouvez l'éditer via le clavier ou bien en cliquant sur les flèches.<br>"
                "La date doit être strictement inférieure ou égale à la date de fin. Par défaut, la date et l'heure sont<br>"
                "celles du moment où la fenêtre est ouverte.<br><br>"
                "<br><img src=:ChampDateFin.png><br>"
                "<font color=\"#0000ff\"><b>La date de fin</font></b><br>"
                "Ce champ permet de définir jusqu'à quelle date vous souhaiter imprimer l'historique de l'ensemble des<br>"
                "territoires de la base de données. Vous pouvez l'éditer via le clavier ou bien en cliquant sur les flèches.<br>"
                "La date doit être strictement supérieure ou égale à la date de début. Par défaut, la date et l'heure sont<br>"
                "celles du moment où la fenêtre est ouverte.<br><br>"
              );
   break;
 }
}

void HelpButtonBox::create_button()
{
 switch(help_type)
 {
  case HelpOutButtonText:
   end_button.setToolTip("Quitter l'aide pour la sortie d'un territoire");
   break;
  case HelpAssignmentButtonText:
   end_button.setToolTip("Quitter l'aide pour le réassignement d'un territoire");
   break;
  case HelpEnterButtonText:
   end_button.setToolTip("Quitter l'aide pour la rentrée d'un territoire");
   break;
  case HelpDatabaseButtonText:
   end_button.setToolTip("Quitter l'aide pour l'édition de la base de données");
   break;
  case HelpSettingsButtonText:
   end_button.setToolTip("Quitter l'aide pour la configuration des paramètres");
   break;
  case HelpPrintButtonText:
   end_button.setToolTip("Quitter l'aide pour imprimer");
   break;
 }
 end_button.setText("Fermer");
}

void HelpButtonBox::create_layout()
{
 layout.addWidget(&text,0,0,1,5);
 layout.addWidget(&end_button,1,4,1,1);
}

void HelpButtonBox::connect_button()
{
 QObject::connect(&end_button, SIGNAL(clicked()),this,SLOT(accept()));
}
