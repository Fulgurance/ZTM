#ifndef TERRITORYSHOWBOX_H
#define TERRITORYSHOWBOX_H

#include <QDialog>
#include <QTabWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QGraphicsView>
#include <QGroupBox>

class TerritoryShowBox : public QDialog
{
 Q_OBJECT
public:
    TerritoryShowBox(QWidget *parent);
    ~TerritoryShowBox();
    void set_territory_id(int id);
public slots:
    void print_first_picture();
    void print_second_picture();
private:
    QString *first_path;
    QString *second_path;
    QTabWidget tabs;
    QGraphicsScene *first_scene;
    QGraphicsScene *second_scene;
    QGraphicsView *first_view;
    QGraphicsView *second_view;
    QPushButton first_print_button;
    QPushButton second_print_button;
    QPushButton end_button;
    QWidget first_picture_tab;
    QWidget second_picture_tab;
    QGridLayout first_picture_layout;
    QGridLayout second_picture_layout;
    QGroupBox first_picture_box;
    QGroupBox second_picture_box;
    QGridLayout first_picture_tab_layout;
    QGridLayout second_picture_tab_layout;
    QGridLayout layout;
    void initialize();
    void initialize_pointers();
    void create_first_print_button();
    void create_second_print_button();
    void create_end_button();
    void create_buttons();
    void create_first_picture_layout();
    void create_second_picture_layout();
    void create_first_picture_tab_layout();
    void create_second_picture_tab_layout();
    void create_layout();
    void create_layouts();
    void create_first_picture_box();
    void create_second_picture_box();
    void create_group_boxs();
    void create_tabs();
    void connect_buttons();
};

#endif
