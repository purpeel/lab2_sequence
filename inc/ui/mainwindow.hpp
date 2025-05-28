#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QMetaType>
#include <vector>
#include "Wrapper.hpp"
#include "ICollection.hpp"
#include "ArraySequence.hpp"
#include "ListSequence.hpp"

Q_DECLARE_METATYPE(SequenceTuple)

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
    void on_copyBtn_clicked();
    void on_concatBtn_clicked();
    void on_subSeqBtn_clicked();
private:
    Ui::MainWindow *ui;
    void addToList( ICollectionTuple<Sequence, int, double>& tuple );
    void updateUI();
    void showError( const std::exception &ex );
};

#endif // MAINWINDOW_H
