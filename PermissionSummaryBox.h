#ifndef PERMISSIONSUMMARYBOX_H
#define PERMISSIONSUMMARYBOX_H

#include <QDialog>
#include <QGroupBox>
#include <QTextEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGridLayout>

class PermissionSummaryBox : public QDialog
{
Q_OBJECT
public:
    PermissionSummaryBox(QWidget *parent);
    void set_permission_id(int id);
private:
    int permission_id;
    QGroupBox box;
    QTextEdit summary_text;
    QPushButton close_button;
    QHBoxLayout box_layout;
    QGridLayout layout;
    void initialize();
    void create_group_box();
    void create_summary_text();
    void create_button();
    void create_box_layout();
    void create_layout();
    void create_layouts();
    void connect_button();
};

#endif // PERMISSIONSUMMARYBOX_H
