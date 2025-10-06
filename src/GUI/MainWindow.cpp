// src/GUI/MainWindow.cpp
#include "MainWindow.h"
#include "AlgorithmSelector/SolverFactory.h"
#include <vector>
#include <string>
#include <sstream>
#include <cstdio> // For popen

// --- Make sure to include the JSON header ---
#include "include/json.hpp"

// (Include all the Qt headers as before)
#include <QTextEdit>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QTextBrowser>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QWidget>
#include <QLabel>
#include <QGroupBox>
#include <QMessageBox>

// (parseGuiNumbers helper function is unchanged)
std::vector<int> parseGuiNumbers(const QString& text) {
    std::vector<int> numbers;
    std::string stdStr = text.toStdString();
    std::stringstream ss(stdStr);
    std::string item;
    while (std::getline(ss, item, ',')) {
        try {
            item.erase(0, item.find_first_not_of(" \t\n\r"));
            item.erase(item.find_last_not_of(" \t\n\r") + 1);
            if (!item.empty()) {
                numbers.push_back(std::stoi(item));
            }
        } catch (...) { /* Ignore invalid numbers */ }
    }
    return numbers;
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // (Widget creation and layout code is unchanged)
    m_numbersInput = new QTextEdit;
    m_numbersInput->setPlaceholderText("Enter comma-separated numbers, e.g., 1,2,3,4,5");
    m_targetInput = new QLineEdit;
    m_targetInput->setPlaceholderText("Enter target sum");
    m_algorithmSelector = new QComboBox;
    m_algorithmSelector->addItems({"backtrack", "dp"});
    m_solveButton = new QPushButton("SOLVE");
    m_resultsDisplay = new QTextBrowser;
    m_saveButton = new QPushButton("Save to Database");
    m_saveButton->setEnabled(false);
    QFormLayout* inputLayout = new QFormLayout;
    inputLayout->addRow(new QLabel("Numbers:"), m_numbersInput);
    inputLayout->addRow(new QLabel("Target:"), m_targetInput);
    QGroupBox* inputGroup = new QGroupBox("Input");
    inputGroup->setLayout(inputLayout);
    QVBoxLayout* dbLayout = new QVBoxLayout;
    dbLayout->addWidget(m_saveButton);
    QGroupBox* dbGroup = new QGroupBox("Database");
    dbGroup->setLayout(dbLayout);
    QVBoxLayout* leftLayout = new QVBoxLayout;
    leftLayout->addWidget(inputGroup);
    leftLayout->addWidget(dbGroup);
    QFormLayout* controlsLayout = new QFormLayout;
    controlsLayout->addRow(new QLabel("Algorithm:"), m_algorithmSelector);
    QGroupBox* controlsGroup = new QGroupBox("Controls");
    controlsGroup->setLayout(controlsLayout);
    QVBoxLayout* rightLayout = new QVBoxLayout;
    rightLayout->addWidget(controlsGroup);
    rightLayout->addWidget(m_solveButton);
    rightLayout->addWidget(m_resultsDisplay);
    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout, 1);
    mainLayout->addLayout(rightLayout, 2);
    QWidget* centralWidget = new QWidget;
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
    setWindowTitle("Subset Sum Solver");
    setMinimumSize(800, 600);

    // --- Connect Signals and Slots ---
    connect(m_solveButton, &QPushButton::clicked, this, &MainWindow::onSolveClicked);
    connect(m_saveButton, &QPushButton::clicked, this, &MainWindow::onSaveClicked); // <-- CONNECT THE SAVE BUTTON
}

MainWindow::~MainWindow() {}

void MainWindow::onSolveClicked()
{
    DataSet data;
    data.numbers = parseGuiNumbers(m_numbersInput->toPlainText());
    
    bool ok;
    data.target_sum = m_targetInput->text().toInt(&ok);
    if (!ok || m_targetInput->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a valid integer for the target sum.");
        return;
    }

    std::string algo_type = m_algorithmSelector->currentText().toStdString();
    
    try {
        auto solver = SolverFactory::createSolver(algo_type);
        SolverResult result = solver->solve(data, false); 
        displayResult(result);
        
        // Store the result if a solution exists
        if (result.solution_exists) {
            m_lastData = data;
            m_lastResult = result;
            m_lastAlgorithm = algo_type;
        }
        m_saveButton->setEnabled(result.solution_exists);

    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Solver Error", e.what());
    }
}

// --- NEW SLOT IMPLEMENTATION ---
void MainWindow::onSaveClicked()
{
    m_saveButton->setEnabled(false); // Prevent double-clicks
    m_saveButton->setText("Saving...");

    nlohmann::json j;
    j["algorithm"] = m_lastAlgorithm;
    j["dataset"]["numbers"] = m_lastData.numbers;
    j["dataset"]["target_sum"] = m_lastData.target_sum;
    j["result"]["solution_found"] = m_lastResult.solution_exists;
    j["result"]["execution_time_ms"] = m_lastResult.execution_time.count();
    j["result"]["subsets"] = m_lastResult.subsets;

    // The Python script is in the root, one level up from the `build` dir
    std::string command = "python3 ../db_handler.py";
    FILE* pipe = popen(command.c_str(), "w");
    if (!pipe) {
        QMessageBox::critical(this, "Execution Error", "Failed to open pipe to Python script.");
        m_saveButton->setText("Save to Database");
        m_saveButton->setEnabled(true);
        return;
    }
    
    fprintf(pipe, "%s\n", j.dump(4).c_str());
    pclose(pipe);

    m_saveButton->setText("Save to Database");
    QMessageBox::information(this, "Success", "Result saved to the database.");
}


void MainWindow::displayResult(const SolverResult& result)
{
    QString html;
    html += "<h3>Solver Results</h3>";
    html += QString("<b>Execution Time:</b> %1 ms<br>").arg(result.execution_time.count());
    
    if (result.solution_exists) {
        html += QString("<b>Solutions Found:</b> %1<br><br>").arg(result.subsets.size());
        int count = 1;
        for (const auto& subset : result.subsets) {
            QString subsetStr;
            for (size_t i = 0; i < subset.size(); ++i) {
                subsetStr += QString::number(subset[i]);
                if (i < subset.size() - 1) {
                    subsetStr += ", ";
                }
            }
            html += QString("<b>Subset %1:</b> { %2 }<br>").arg(count++).arg(subsetStr);
        }
    } else {
        html += "<br><b>Solution Found:</b> No";
    }
    m_resultsDisplay->setHtml(html);
}
