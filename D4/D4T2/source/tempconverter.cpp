#include "tempconverter.h"
//#include "ui_tempconverter.h"
#include<QGroupBox>
TempConverter::TempConverter(QWidget *parent) :
    QWidget(parent)
{
    setUi(this);
    m_tempFahrenheit=m_tempCelsius*(9.0/5.0)+32;
    cLcd->display(m_tempCelsius);
    fLcd->display(tempFahrenheit());
    cDial->setValue(m_tempCelsius);
    fDial->setValue(tempFahrenheit());

    connect(cDial,SIGNAL(valueChanged(int)),this,SLOT(setTempCelsius(int)));
    connect(cDial,SIGNAL(valueChanged(int)),cLcd,SLOT(display(int)));
    connect(this,SIGNAL(tempCelsiusChanged(int)),cDial,SLOT(setValue(int)));

    connect(fDial,SIGNAL(valueChanged(int)),this,SLOT(setTempFahrenheit(int)));
    connect(fDial,SIGNAL(valueChanged(int)),fLcd,SLOT(display(int)));
    connect(this,SIGNAL(tempFahrenheitChanged(int)),fDial,SLOT(setValue(int)));
}

void TempConverter::setUi(QWidget *TempConverter)             //用于布置UI界面
{
    if (TempConverter->objectName().isEmpty())
        TempConverter->setObjectName(QStringLiteral("TempConverter"));
    TempConverter->resize(399, 274);

    groupBox = new QGroupBox(TempConverter);
    groupBox->setObjectName(QStringLiteral("groupBox"));
    groupBox->setGeometry(QRect(20, 40, 171, 201));

    cLcd = new QLCDNumber(groupBox);
    cLcd->setObjectName(QStringLiteral("lcdNumber"));
    cLcd->setGeometry(QRect(20, 160, 131, 23));

    cDial = new QDial(groupBox);
    cDial->setObjectName(QStringLiteral("dial"));
    cDial->setGeometry(QRect(30, 50, 111, 91));
    cDial->setMaximum(200);

    groupBox_2 = new QGroupBox(TempConverter);
    groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
    groupBox_2->setGeometry(QRect(210, 40, 171, 201));

    fLcd = new QLCDNumber(groupBox_2);
    fLcd->setObjectName(QStringLiteral("lcdNumber_2"));
    fLcd->setGeometry(QRect(20, 160, 131, 23));

    fDial = new QDial(groupBox_2);
    fDial->setObjectName(QStringLiteral("dial_2"));
    fDial->setGeometry(QRect(30, 50, 111, 91));
    fDial->setMaximum(200);

    TempConverter->setWindowTitle(QApplication::translate("TempConverter", "TempConverter", Q_NULLPTR));
    groupBox->setTitle(QApplication::translate("TempConverter", "Celsius", Q_NULLPTR));
    groupBox_2->setTitle(QApplication::translate("TempConverter", "Fahrenheit", Q_NULLPTR));

    QMetaObject::connectSlotsByName(TempConverter);
}


void TempConverter::setTempFahrenheit(int tempFahrenheit)
{
    if(m_tempFahrenheit == tempFahrenheit)
        return;
    m_tempFahrenheit=tempFahrenheit;
    m_tempCelsius = (5.0/9.0)*(tempFahrenheit-32);
    setTempCelsius(m_tempCelsius);
    emit tempCelsiusChanged(m_tempCelsius);
    emit tempFahrenheitChanged(m_tempFahrenheit);
}

void TempConverter::setTempCelsius(int tempCelsius)
{
    if(m_tempCelsius == tempCelsius)
        return;
    m_tempCelsius = tempCelsius;
    m_tempFahrenheit=tempCelsius*(9.0/5.0)+32;
    emit tempCelsiusChanged(m_tempCelsius);
    emit tempFahrenheitChanged(m_tempFahrenheit);
}

int TempConverter::tempFahrenheit() const
{
    return (m_tempCelsius*(9.0/5.0)+32);
}

