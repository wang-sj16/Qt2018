#ifndef TEMPCONVERTER_H
#define TEMPCONVERTER_H

#include <QWidget>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDial>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QWidget>

namespace Ui {
class TempConverter;
}

class TempConverter : public QWidget
{
    Q_OBJECT

public:
    explicit TempConverter(QWidget *parent = 0);
    void setUi(QWidget *TempConverter);

    QGroupBox *groupBox;
    QLCDNumber *cLcd;
    QDial *cDial;
    QGroupBox *groupBox_2;
    QLCDNumber *fLcd;
    QDial *fDial;

    //int tempCelsius() const;
    int tempFahrenheit() const;

public slots:
    void setTempCelsius(int);
    void setTempFahrenheit(int);
signals:
    void tempCelsiusChanged(int);
    void tempFahrenheitChanged(int);

private:
    int m_tempCelsius=0;
    int m_tempFahrenheit;
};

#endif // TEMPCONVERTER_H
