#ifndef TERRITORYSUMMARYBOX_H
#define TERRITORYSUMMARYBOX_H

#include <QDialog>
#include <QGroupBox>
#include <QTextEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGridLayout>
#include "TerritoryShowBox.h"

class TerritorySummaryBox : public QDialog
{
Q_OBJECT
public:
    TerritorySummaryBox(QWidget *parent);
    void set_territory_id(int id);
public slots:
    void open_territory_show_box();
private:
    QGroupBox box;
    QTextEdit summary_text;
    QPushButton show_button;
    QPushButton close_button;
    QHBoxLayout box_layout;
    QGridLayout layout;
    TerritoryShowBox *territory_show_box;
    void initialize();
    void initialize_pointers();
    void create_group_box();
    void create_summary_text();
    void create_show_button();
    void create_close_button();
    void create_buttons();
    void create_box_layout();
    void create_layout();
    void create_layouts();
    void connect_buttons();
};

#endif // TERRITORYSUMMARYBOX_H
