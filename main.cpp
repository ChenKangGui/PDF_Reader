#include "MainViewer.h"
#include <QApplication>

/*
class Mainwindow : public QMainWindow
{
  Q_OBJECT
public:
    Mainwindow(QMainWindow *parent=0)
    {
        resize(900, 100);
    }
    ~Mainwindow()
    {

    }

};
*/







int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    MainViewer mainViewer;
    mainViewer.show();


	return a.exec();
}
