#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <vector>
#include <QLabel>
#include <QPixmap>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <ctime>
#include <cstdlib>

using namespace std;

// ==============================================
// COLOR DEFINITIONS (User Custom Hex Codes)
// ==============================================
const QColor COL_ALLOC = QColor(45, 45, 45);
const QColor COL_NEED  = QColor(0xD4, 0xAF, 0x37); // orange
const QColor COL_AVAIL = QColor("#FF007F"); // pink
const QColor COL_ERROR = QColor(150, 0, 0);  // red
const QColor COL_MAX   = QColor("#f4e008ff");
// Red (Error)

// ==============================================
// CONSTRUCTOR
// ==============================================
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 1. THEME STYLING
    this->setStyleSheet("QMainWindow { background-color: #1e1e1e; }"
                        "QLabel { color: #e0e0e0; font-weight: bold; font-size: 14px; }"
                        "QLineEdit { background-color: #333; color: white; border: 1px solid #555; padding: 8px; border-radius: 4px; }"
                        "QTableWidget { background-color: #2d2d2d; color: white; gridline-color: #444; border: 1px solid #444; font-size: 14px; }"
                        "QHeaderView::section { background-color: #333; color: white; padding: 6px; border: 1px solid #222; font-weight: bold; }"
                        "QPushButton { background-color: #007acc; color: white; border-radius: 5px; padding: 12px; font-weight: bold; font-size: 14px; }"
                        "QPushButton:hover { background-color: #0099ff; }"
                        "QPushButton#Reset { background-color: #d32f2f; }"
                        "QTextEdit { background-color: #121212; color: #00ff00; font-family: Consolas; font-size: 14px; border: 1px solid #555; }");

    // 2. INITIALIZE TABLES & COMPONENTS
    tableAvailable = new QTableWidget(this);
    tableAvailable->setRowCount(1);
    tableAvailable->setFixedHeight(75);
    // Available Table text color logic handled in styling or items
    tableAvailable->setStyleSheet("background-color: #222; color: white; font-weight: bold; font-size: 16px;");

    // Gantt Chart Container
    ganttContainer = new QWidget(this);
    ganttContainer->setFixedHeight(60);
    ganttContainer->setStyleSheet("background-color: #252525; border-radius: 5px; border: 1px solid #444;");
    ganttLayout = new QHBoxLayout(ganttContainer);
    ganttLayout->setContentsMargins(10, 5, 10, 5);
    ganttLayout->setAlignment(Qt::AlignLeft);

    // Logo
    QLabel *logoLabel = new QLabel(this);
    QPixmap pixmap("logo.png");
    if(!pixmap.isNull()){
        logoLabel->setPixmap(pixmap.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        logoLabel->setAlignment(Qt::AlignCenter);
    } else {
        logoLabel->setText("OS SIMULATOR - BANKER'S ALGORITHM");
        logoLabel->setAlignment(Qt::AlignCenter);
        logoLabel->setStyleSheet("font-size: 20px; color: cyan; letter-spacing: 1px; margin-bottom: 10px;");
    }
    //Logo end

    // 3. LAYOUT DESIGN
    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(25);

    // --- LEFT SIDEBAR (Fixed Width) ---
    QWidget *leftPanel = new QWidget();
    leftPanel->setFixedWidth(320);
    QVBoxLayout *leftLayout = new QVBoxLayout(leftPanel);
    leftLayout->setContentsMargins(0, 0, 0, 0);

    QGroupBox *inputGroup = new QGroupBox("Configuration");
    inputGroup->setStyleSheet("QGroupBox { color: white; border: 1px solid #555; padding-top: 20px; font-weight: bold; }");
    QVBoxLayout *inputLayout = new QVBoxLayout(inputGroup);
    inputLayout->setSpacing(15);

    inputLayout->addWidget(ui->labelResources);
    inputLayout->addWidget(ui->lineResources);
    inputLayout->addWidget(ui->labelProcesses);
    inputLayout->addWidget(ui->lineProcesses);
    inputLayout->addSpacing(10);
    inputLayout->addWidget(ui->btnCreateTables);
    if(ui->btnAutoFill) inputLayout->addWidget(ui->btnAutoFill);
    inputLayout->addWidget(ui->btnCheckSafe);
    inputLayout->addWidget(ui->Reset);
    inputLayout->addStretch();

    leftLayout->addWidget(inputGroup);
    leftLayout->addStretch();

    // --- RIGHT VISUALIZATION PANEL ---
    QVBoxLayout *rightLayout = new QVBoxLayout();
    rightLayout->setSpacing(10);

    rightLayout->addWidget(logoLabel);

    // Clean Label (No colors mentioned in text)
    rightLayout->addWidget(new QLabel("📊 Safe Sequence Visualization (Gantt Chart):"));
    rightLayout->addWidget(ganttContainer);

    rightLayout->addWidget(new QLabel("🔥 Available Resources:"));
    rightLayout->addWidget(tableAvailable);

    ui->textOutput->setFixedHeight(60);   // 👈 height reduced (was too big)
    ui->textOutput->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->textOutput->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    rightLayout->addWidget(ui->textOutput);


    // Tables Layout
    rightLayout->addWidget(new QLabel("Allocation Table:"));
    ui->tableAllocation->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    rightLayout->addWidget(ui->tableAllocation);

    QHBoxLayout *bottomTables = new QHBoxLayout();

    QVBoxLayout *maxLayout = new QVBoxLayout();
    maxLayout->addWidget(new QLabel("Max Table:"));
    ui->tableMax->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    maxLayout->addWidget(ui->tableMax);

    QVBoxLayout *needLayout = new QVBoxLayout();
    needLayout->addWidget(new QLabel("Need Table:"));
    ui->tableNeed->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    needLayout->addWidget(ui->tableNeed);

    bottomTables->addLayout(maxLayout);
    bottomTables->addLayout(needLayout);
    rightLayout->addLayout(bottomTables);

    mainLayout->addWidget(leftPanel);
    mainLayout->addLayout(rightLayout);

    setCentralWidget(centralWidget);
    srand(time(0));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ==============================================
//  HELPER: CLEAR GANTT CHART
// ==============================================
void MainWindow::clearGanttChart() {
    QLayoutItem *child;
    while ((child = ganttLayout->takeAt(0)) != nullptr) {
        if(child->widget()) delete child->widget();
        delete child;
    }
}

// ==============================================
// HELPER: COLOR ROW
// ==============================================
void MainWindow::colorRow(QTableWidget* table, int row, QColor color) {
    for(int j = 0; j < table->columnCount(); j++) {
        if(table->item(row, j))
            table->item(row, j)->setBackground(color);
    }
}

// ==============================================
// HELPER: VALIDATE INPUT
// ==============================================
bool MainWindow::validateInput(QTableWidget* table, int row, int col) {
    if(table->item(row, col) == nullptr) return false;

    QString text = table->item(row, col)->text();
    bool ok;
    int val = text.toInt(&ok);

    if(text.isEmpty() || !ok || val < 0) {
        table->item(row, col)->setBackground(COL_ERROR);
        return false;
    }

    // Reset to specific color if valid
    if(table == tableAvailable)
        table->item(row, col)->setBackground(COL_AVAIL);
    else if(table == ui->tableMax)
        table->item(row, col)->setBackground(COL_MAX);
    else if(table == ui->tableNeed)
        table->item(row, col)->setBackground(COL_NEED);
    else
        table->item(row, col)->setBackground(COL_ALLOC);

    return true;
}

// ==============================================
// 1. CREATE TABLES (WITH COLORS)
// ==============================================
void MainWindow::on_btnCreateTables_clicked()
{
    int resources = ui->lineResources->text().toInt();
    int processes = ui->lineProcesses->text().toInt();

    if (resources <= 0 || processes <= 0) {
        QMessageBox::warning(this, "Invalid Input", "Enter valid number of resources and processes!");
        return;
    }

    // 1. Setup Allocation
    ui->tableAllocation->setRowCount(processes);
    ui->tableAllocation->setColumnCount(resources);

    // 2. Setup Max
    ui->tableMax->setRowCount(processes);
    ui->tableMax->setColumnCount(resources);

    // 3. Setup Need
    ui->tableNeed->setRowCount(processes);
    ui->tableNeed->setColumnCount(resources);

    QStringList hHeaders;
    for(int i=0; i<resources; i++) hHeaders << "R" + QString::number(i);
    QStringList vHeaders;
    for(int i=0; i<processes; i++) vHeaders << "P" + QString::number(i);

    // Common Settings
    QTableWidget* tables[] = {ui->tableAllocation, ui->tableMax, ui->tableNeed};
    for(auto table : tables) {
        table->setVerticalHeaderLabels(vHeaders);
        table->setHorizontalHeaderLabels(hHeaders);
        table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        table->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }

    // Fill with Colors
    for(int i=0; i<processes; i++) {
        for(int j=0; j<resources; j++) {
            // Allocation -> Grey
            ui->tableAllocation->setItem(i, j, new QTableWidgetItem("0"));
            ui->tableAllocation->item(i, j)->setTextAlignment(Qt::AlignCenter);
            ui->tableAllocation->item(i, j)->setBackground(COL_ALLOC);

            // Max -> Purple
            ui->tableMax->setItem(i, j, new QTableWidgetItem("0"));
            ui->tableMax->item(i, j)->setTextAlignment(Qt::AlignCenter);
            ui->tableMax->item(i, j)->setBackground(COL_MAX);

            // Need -> Orange
            ui->tableNeed->setItem(i, j, new QTableWidgetItem("0"));
            ui->tableNeed->item(i, j)->setTextAlignment(Qt::AlignCenter);
            ui->tableNeed->item(i, j)->setBackground(COL_NEED);
        }
    }

    // Setup Available -> Pink
    tableAvailable->setColumnCount(resources);
    tableAvailable->setHorizontalHeaderLabels(hHeaders);
    tableAvailable->setVerticalHeaderLabels(QStringList() << "Avail");
    tableAvailable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    for(int j=0; j<resources; j++) {
        tableAvailable->setItem(0, j, new QTableWidgetItem("0"));
        tableAvailable->item(0, j)->setTextAlignment(Qt::AlignCenter);
        tableAvailable->item(0, j)->setBackground(COL_AVAIL);
    }

    clearGanttChart();
    // CLEAN MESSAGE
    ui->textOutput->setText("✅ Tables Created.");
}

// ==============================================
// 2. AUTO FILL (PRESERVE COLORS)
// ==============================================
void MainWindow::on_btnAutoFill_clicked()
{
    int rows = ui->tableAllocation->rowCount();
    int cols = ui->tableAllocation->columnCount();

    if(rows == 0) {
        QMessageBox::warning(this, "Error", "Create Tables first!");
        return;
    }

    for(int i=0; i<rows; i++) {
        for(int j=0; j<cols; j++) {
            int rMax = (rand() % 9) + 1;
            int rAlloc = rand() % (rMax + 1);

            ui->tableAllocation->item(i, j)->setText(QString::number(rAlloc));
            ui->tableMax->item(i, j)->setText(QString::number(rMax));
            ui->tableNeed->item(i, j)->setText(QString::number(rMax - rAlloc));

            // Ensure Colors are preserved
            ui->tableAllocation->item(i, j)->setBackground(COL_ALLOC);
            ui->tableMax->item(i, j)->setBackground(COL_MAX);
            ui->tableNeed->item(i, j)->setBackground(COL_NEED);
        }
    }

    for(int j=0; j<cols; j++) {
        tableAvailable->item(0, j)->setText(QString::number((rand()%5)+2));
        tableAvailable->item(0, j)->setBackground(COL_AVAIL);
    }

    clearGanttChart();
    ui->textOutput->setText("🎲 Random Data Filled!");
}

// ==============================================
// 3. RESET
// ==============================================
void MainWindow::on_Reset_clicked()
{
    ui->lineResources->clear();
    ui->lineProcesses->clear();

    QTableWidget* tables[] = {ui->tableAllocation, ui->tableMax, ui->tableNeed, tableAvailable};
    for(auto t : tables) {
        t->clear();
        t->setRowCount(0);
        t->setColumnCount(0);
    }
    tableAvailable->setRowCount(1);
    clearGanttChart();

    ui->textOutput->clear();
    ui->textOutput->setText("🔄 System Reset.");
}

// ==============================================
// 4. CHECK SAFE
// ==============================================
void MainWindow::on_btnCheckSafe_clicked()
{
    ui->textOutput->clear();
    clearGanttChart();

    int processes = ui->tableAllocation->rowCount();
    int resources = ui->tableAllocation->columnCount();

    if (processes == 0) {
        QMessageBox::warning(this, "Error", "Create Tables first!");
        return;
    }

    vector<vector<int>> alloc(processes, vector<int>(resources));
    vector<vector<int>> maxm(processes, vector<int>(resources));
    vector<vector<int>> need(processes, vector<int>(resources));
    vector<int> available(resources);
    vector<bool> finished(processes, false);
    vector<int> safeSeq;

    // VALIDATION & READ
    for (int i = 0; i < processes; i++) {
        // Reset Allocation Color
        colorRow(ui->tableAllocation, i, COL_ALLOC);

        for (int j = 0; j < resources; j++) {
            if (!validateInput(ui->tableAllocation, i, j) || !validateInput(ui->tableMax, i, j)) {
                QMessageBox::critical(this, "Error", "Invalid data!");
                return;
            }
            alloc[i][j] = ui->tableAllocation->item(i, j)->text().toInt();
            maxm[i][j] = ui->tableMax->item(i, j)->text().toInt();
            need[i][j] = maxm[i][j] - alloc[i][j];

            if(need[i][j] < 0) {
                ui->textOutput->setText("❌ Error: Allocated > Max!");
                return;
            }
            ui->tableNeed->setItem(i, j, new QTableWidgetItem(QString::number(need[i][j])));
            ui->tableNeed->item(i, j)->setTextAlignment(Qt::AlignCenter);
            // Keep Need Orange
            ui->tableNeed->item(i, j)->setBackground(COL_NEED);
        }
    }

    for (int j = 0; j < resources; j++) {
        if (!validateInput(tableAvailable, 0, j)) return;
        available[j] = tableAvailable->item(0, j)->text().toInt();
    }

    // ALGORITHM
    int count = 0;
    while (count < processes) {
        bool found = false;

        for (int p = 0; p < processes; p++) {
            if (!finished[p]) {
                bool canRun = true;
                for (int j = 0; j < resources; j++) {
                    if (need[p][j] > available[j]) {
                        canRun = false;
                        break;
                    }
                }

                if (canRun) {
                    for (int j = 0; j < resources; j++) {
                        available[j] += alloc[p][j];
                    }
                    safeSeq.push_back(p);
                    finished[p] = true;
                    found = true;
                    count++;
                }
            }
        }

        if (!found) {
            ui->textOutput->setText("❌ DEADLOCK DETECTED! System is Unsafe.");
            QLabel *unsafeLbl = new QLabel("⛔ UNSAFE STATE");
            unsafeLbl->setStyleSheet("background-color: red; color: white; padding: 5px; font-weight: bold;");
            ganttLayout->addWidget(unsafeLbl);
            return;
        }
    }

    // UPDATE UI
    for(int j=0; j<resources; j++) {
        tableAvailable->item(0, j)->setText(QString::number(available[j]));
    }

    // Highlight Safe Rows (Green) in Allocation
    for(int s : safeSeq) colorRow(ui->tableAllocation, s, QColor(0, 100, 0));

    // DRAW GANTT
    for(int s : safeSeq) {
        QLabel *procLbl = new QLabel(" P" + QString::number(s) + " ");
        procLbl->setStyleSheet("background-color: #008000; color: white; font-weight: bold; border: 1px solid white; padding: 8px; border-radius: 4px;");
        procLbl->setAlignment(Qt::AlignCenter);
        ganttLayout->addWidget(procLbl);

        if(s != safeSeq.back()) {
            QLabel *arrow = new QLabel("➡");
            arrow->setStyleSheet("color: white; font-weight: bold;");
            ganttLayout->addWidget(arrow);
        }
    }

    ganttLayout->addStretch();

    QString result = "✔ System is SAFE. Sequence generated above.";
    ui->textOutput->setText(result);
}
