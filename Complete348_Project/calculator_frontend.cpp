void Calculator::equalClicked() {
    // 1. Get the string from the UI
    QString input = display->text();
    
    // 2. Pass it to the backend (converting QString to std::string)
    try {
        double result = m_evaluator.calculate(input.toStdString());
        
        // 3. Update the UI with the result
        display->setText(QString::number(result));
    } catch (const std::exception& e) {
        // Handle errors (like division by zero) using your backend error handler
        display->setText("Error");
    }
}