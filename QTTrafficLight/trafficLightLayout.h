#ifndef TRAFFICLIGHTLAYOUT_H
#define TRAFFICLIGHTLAYOUT_H

#include <QWidget>
#include <QGridLayout>
#include <QPainter>

class LightWidget : public QWidget
{
    Q_PROPERTY(bool on READ isOn WRITE setOn)
public:
    explicit LightWidget(const QColor &color, QWidget *parent = nullptr)
        : QWidget(parent), m_color(color)
    {
    }
    virtual ~LightWidget(){}
    bool isOn() const { return m_on; }

    void setOn(bool on)
    {
        if (on == m_on)
            return;
        m_on = on;
        update();
    }

public slots:
    void turnOff() { setOn(false); }
    void turnOn() { setOn(true); }

protected:
    void paintEvent(QPaintEvent *) override
    {
        if (!m_on)
            return;
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setBrush(m_color);
        painter.drawEllipse(rect());
    }

private:
    QColor m_color;
    bool m_on = false;
};

class TrafficLightWidget : public QWidget
{
public:
    explicit TrafficLightWidget(QWidget *parent = nullptr) : QWidget(parent)
    {
        auto vbox = new QVBoxLayout(this);

        m_red = new LightWidget(Qt::red);
        vbox->addWidget(m_red);

        m_yellow = new LightWidget(Qt::yellow);
        vbox->addWidget(m_yellow);

        m_green = new LightWidget(Qt::green);
        vbox->addWidget(m_green);

        auto pal = palette();
        pal.setColor(QPalette::Window, Qt::black);
        setPalette(pal);
        setAutoFillBackground(true);
    }
    virtual ~TrafficLightWidget(){}
    LightWidget *redLight() const { return m_red; }
    LightWidget *yellowLight() const { return m_yellow; }
    LightWidget *greenLight() const { return m_green; }

private:
    LightWidget *m_red;
    LightWidget *m_yellow;
    LightWidget *m_green;
};

class TrafficLightLayout : public QWidget
{
public:
    explicit TrafficLightLayout(QWidget *parent = nullptr);
    virtual ~TrafficLightLayout(){}
    TrafficLightWidget* widget;

    QGridLayout*  getTrafficLightLayout()
    {
        QGridLayout  *glayout = new QGridLayout(this);

        widget = new TrafficLightWidget;
        glayout->addWidget(widget);
        glayout->setContentsMargins(QMargins());
        return glayout;
    }

    void turnOnRed()
    {
        LightWidget *light = widget->redLight();
        light->turnOn();
    }

    void turnOnYellow()
    {
        LightWidget *light = widget->yellowLight();
        light->turnOn();
    }

    void turnOnGreen()
    {
        LightWidget *light = widget->greenLight();
        light->turnOn();
    }

    void turnOffRed()
    {
        LightWidget *light = widget->redLight();
        light->turnOff();
    }

    void turnOffYellow()
    {
        LightWidget *light = widget->yellowLight();
        light->turnOff();
    }

    void turnOffGreen()
    {
        LightWidget *light = widget->greenLight();
        light->turnOff();
    }
};

#endif // TRAFFICLIGHTLAYOUT_H
