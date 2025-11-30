#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QHBoxLayout> // Needed for Gantt

QT_BEGIN_NAMESPACE
namespace Ui {
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
    void on_btnCreateTables_clicked();
    void on_btnCheckSafe_clicked();
    void on_Reset_clicked();
    void on_btnAutoFill_clicked();

private:
    Ui::MainWindow *ui;

    // UI Components created in Code
    QTableWidget *tableAvailable;
    QHBoxLayout *ganttLayout;     // Layout for Visual Gantt Chart
    QWidget *ganttContainer;      // Container for the chart

    // Helper functions
    void colorRow(QTableWidget* table, int row, QColor color);
    bool validateInput(QTableWidget* table, int row, int col);
    void clearGanttChart();       // Helper to clear old chart
};

#endif // MAINWINDOW_H
