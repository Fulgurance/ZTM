#include "LoginWindow.h"

LoginWindow::LoginWindow()
{
    initialize();
    create_interface();
    create_layouts();
    connect_slots();
}

void LoginWindow::initialize()
{
    setWindowTitle("Connexion");
    setWindowIcon(QIcon("Pictures/LoginWindow.png"));
    setWindowFlags(Qt::WindowCloseButtonHint);
    setStyleSheet("background-color: #ffffff; color: #000000");
    initialize_pointers();
    setLayout(main_layout);
}

void LoginWindow::initialize_pointers()
{
    main_layout = new QGridLayout;
    title = new QLabel;
    separator = new QFrame;
    login_picture = new QLabel;
    login_text = new QLineEdit;
    password_picture = new QLabel;
    password_text = new QLineEdit;
    connect_button = new QToolButton;
    leave_button = new QToolButton;
    main_window = new MainWindow;
}

void LoginWindow::create_layouts()
{
    create_main_layout();
}

void LoginWindow::create_interface()
{
    create_title();
    create_separator();
    create_login_picture();
    create_login_text();
    create_password_picture();
    create_password_text();
    create_connect_button();
    create_leave_button();
}

void LoginWindow::connect_slots()
{
    connect(connect_button,SIGNAL(clicked()),this,SLOT(login()));
    connect(leave_button,SIGNAL(clicked()),this,SLOT(close()));
}

void LoginWindow::create_main_layout()
{
    main_layout->setMargin(50);
    main_layout->setSizeConstraint(QLayout::SetFixedSize);
    main_layout->addWidget(title,0,0,3,9);
    main_layout->addWidget(separator,3,0,1,9);
    main_layout->addWidget(login_picture,4,0,2,2);
    main_layout->addWidget(login_text,4,2,2,7);
    main_layout->addWidget(password_picture,6,0,2,2);
    main_layout->addWidget(password_text,6,2,2,7);
    main_layout->addWidget(connect_button,8,3,2,3);
    main_layout->addWidget(leave_button,8,6,2,3);
}

void LoginWindow::create_title()
{
    title->setStyleSheet("font-weight: bold;");
    title->setText("Connexion");
}

void LoginWindow::create_separator()
{
    separator->setFrameShape(QFrame::HLine);
    separator->setStyleSheet("background-color: #000000");
}

void LoginWindow::create_login_picture()
{
    login_picture->setPixmap(QPixmap("Pictures/Login.png"));
}

void LoginWindow::create_login_text()
{
    login_text->setPlaceholderText("Nom d'utilisateur");
    login_text->setToolTip("Champ de saisie du compte utilisateur");
}

void LoginWindow::create_password_picture()
{
    password_picture->setPixmap(QPixmap("Pictures/Password.png"));
}

void LoginWindow::create_password_text()
{
    password_text->setPlaceholderText("Mot de passe");
    password_text->setToolTip("Champ de saisie du mot de passe");
    password_text->setEchoMode(QLineEdit::Password);
}

void LoginWindow::create_connect_button()
{
    connect_button->setStyleSheet("background-color: #2244ff; color: #ffffff");
    connect_button->setText("Connexion");
    connect_button->setToolTip("Se connecter avec le nom d'utilisateur et mot de passe spécifiés");
    connect_button->setSizePolicy(QSizePolicy::Expanding , QSizePolicy::Fixed);
}

void LoginWindow::create_leave_button()
{
    leave_button->setStyleSheet("background-color: #ff5555; color: #ffffff");
    leave_button->setText("Quitter");
    leave_button->setToolTip("Quitter le logiciel");
    leave_button->setSizePolicy(QSizePolicy::Expanding , QSizePolicy::Fixed);
}

void LoginWindow::login()
{
    main_window->showMaximized();
    main_window->load_log();
    main_window->showMaximized();
    close();
}
