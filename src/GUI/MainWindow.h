// src/GUI/MainWindow.h
#pragma once

#include <QMainWindow>
#include "DataModel/DataSet.h"     // <-- Make sure this is included
#include "DataModel/SolverResult.h"  // <-- Make sure this is included

// (Forward declarations are unchanged)
class QTextEdit;
class QLineEdit;
class QComboBox;
class QPushButton;
class QTextBrowser;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSolveClicked();
    void onSaveClicked(); // <-- ADD THIS NEW SLOT

private:
    void displayResult(const SolverResult& result);

    // --- Add Member variables to store the last run ---
    DataSet m_lastData;
    SolverResult m_lastResult;
    std::string m_lastAlgorithm;
    // --------------------------------------------------

    // (UI Widgets are unchanged)
    QTextEdit* m_numbersInput;
    QLineEdit* m_targetInput;
    QComboBox* m_algorithmSelector;
    QPushButton* m_solveButton;
    QTextBrowser* m_resultsDisplay;
    QPushButton* m_saveButton;
};
