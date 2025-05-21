#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <vector>
#include "Sequence.hpp"
#include "SequenceWrap.hpp"


QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_createBtn_clicked();
    void on_deleteBtn_clicked();
    void on_appendBtn_clicked();
    void on_prependBtn_clicked();
    void on_removeAtBtn_clicked();
    void on_setAtBtn_clicked();
    void on_insertAtBtn_clicked();
    void on_swapBtn_clicked();
    void on_varType_currentIndexChanged(int index);
    void on_containerType_currentIndexChanged(int index);
private:
    Ui::MainWindow *ui;
    std::vector<ICollection> sequences;
    void updateUI();
    void showError( const QString& message );
    enum class ContainerType
    {
        LinkedList,
        Array
    };
    enum class VarType
    {
        Int,
        Double
    };
};

#endif // MAINWINDOW_H
