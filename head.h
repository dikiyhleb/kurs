#ifndef HEAD_H
#define HEAD_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>

class Head : public QWidget
{
    Q_OBJECT

public:
    Head(QWidget *parent = nullptr);
    ~Head();

private slots:
    void calculateBMI();

private:
    QLineEdit *heightInput;
    QLineEdit *weightInput;
    QLabel *resultLabel;
    QLabel *statusIndicator;

    double calculateBMIValue(double weight, double height);
    QString getBMIStatus(double bmi);
    void saveResultsToFile(double bmi);
};

#endif // HEAD_H
