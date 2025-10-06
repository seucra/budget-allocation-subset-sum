// src/main_gui.cpp
#include <QApplication>
#include "GUI/MainWindow.h" // Include our custom main window

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Create and show an instance of our MainWindow class
    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
