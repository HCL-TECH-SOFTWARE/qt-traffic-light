/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/
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
