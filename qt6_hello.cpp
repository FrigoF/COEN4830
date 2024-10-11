// qt6_hello.cpp - Qt6 Hello World
// Marquette University
// Fred J. Frigo
// 10-Oct-2024
//
// To build: 
//     $ qmake6 -project
//     $ echo “QT += gui widgets” >> qt6_hello.pro
//     $ qmake6 qt6_hello.pro
//     $ make
//     $ ./qt6_hello
//
// See: https://vitux.com/compiling-your-first-qt-program-in-ubuntu/
//
// For Ubuntu 24.04 it is necessary to install these packages:
//   build_essential qtcreator qt6-base qt6-base-doc qt6-base-doc-html 
//   qt6-base-examples libclang-dev
//

#include <QApplication>
#include <QLabel>
#include <QWidget>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QLabel hello("<center>Hello world!</center>");
    hello.setWindowTitle("Hello World QT");
    hello.resize(400,400);
    hello.show();
    return app.exec();
}
