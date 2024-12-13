#include "head.h"
#include <QFile>
#include <QTextStream>
#include <QVBoxLayout>
#include <QPalette>

Head::Head(QWidget *parent) : QWidget(parent)
{
    heightInput = new QLineEdit(this);
    weightInput = new QLineEdit(this);
    QPushButton *calculateButton = new QPushButton("Расчитать индекс массы тела", this);
    resultLabel = new QLabel(this);
    statusIndicator = new QLabel(this);

    connect(calculateButton, &QPushButton::clicked, this, &Head::calculateBMI);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Рост (m):", this));
    layout->addWidget(heightInput);
    layout->addWidget(new QLabel("Вес (kg):", this));
    layout->addWidget(weightInput);
    layout->addWidget(calculateButton);
    layout->addWidget(resultLabel);
    layout->addWidget(statusIndicator);
    setLayout(layout);
}

Head::~Head() {}

void Head::calculateBMI()
{
    bool heightOk, weightOk;
    double height = heightInput->text().toDouble(&heightOk);
    double weight = weightInput->text().toDouble(&weightOk);

    if (heightOk && weightOk && height > 0) {
        double bmi = calculateBMIValue(weight, height);
        QString status = getBMIStatus(bmi);
        resultLabel->setText("Ваш ИМТ: " + QString::number(bmi) + " (" + status + ")");
        saveResultsToFile(bmi);

        if (status == "Недостаточный вес" || status == "Избыточный вес" || status == "Ожирение") {
            statusIndicator->setStyleSheet("background-color: red; color: white;");
        } else {
            statusIndicator->setStyleSheet("background-color: green; color: white;");
        }

        statusIndicator->setText("Статус: " + status);
    } else {
        resultLabel->setText("Неверные значения веса или роста. Введите действительное значение роста и веса!");
        statusIndicator->clear(); // Очищаем индикатор статуса
    }
}

double Head::calculateBMIValue(double weight, double height)
{
    return weight / ((height/100) * (height/100));
}

QString Head::getBMIStatus(double bmi)
{
    if (bmi < 18.5)
        return "Недостаточный вес";
    else if (bmi < 24.9)
        return "Нормальный вес";
    else if (bmi < 29.9)
        return "Избыточный вес";
    else
        return "Ожирение";
}

void Head::saveResultsToFile(double bmi)
{
    QFile file("BMI_results.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << "BMI: " << QString::number(bmi) << "\n";
        file.close();
    }
}
