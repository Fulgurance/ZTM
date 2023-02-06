#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QFrame>
#include <QLineEdit>
#include <QToolButton>

#include "MainWindow.h"

class LoginWindow : public QWidget
{
    Q_OBJECT
public:
    explicit LoginWindow();
private:
    QGridLayout *main_layout;
    QLabel      *title;
    QFrame      *separator;
    QLabel      *login_picture;
    QLineEdit   *login_text;
    QLabel      *password_picture;
    QLineEdit   *password_text;
    QToolButton *connect_button;
    QToolButton *leave_button;
    MainWindow  *main_window;
    void initialize();
    void initialize_pointers();
    void create_layouts();
    void connect_slots();
    void create_main_layout();
    void create_interface();
    void create_title();
    void create_separator();
    void create_login_picture();
    void create_login_text();
    void create_password_picture();
    void create_password_text();
    void create_connect_button();
    void create_leave_button();
private slots:
    void login();
};

#endif // LOGINWINDOW_H
