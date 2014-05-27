#ifndef QIRRLICHTWIDGET_H
#define QIRRLICHTWIDGET_H

#include <qwidget.h>
#include <irrlicht.h>
#include <qfont.h>

class QPaintEvent;

class QIrrlichtWidget : public QWidget
{
    Q_OBJECT

public:
    irr::IrrlichtDevice* getIrrlichtDevice();

    void setDriverType( irr::video::E_DRIVER_TYPE driver );

    QIrrlichtWidget( QWidget *parent=0 );
    ~QIrrlichtWidget();

    void init();

public slots:
    void autoUpdateIrrlicht( irr::IrrlichtDevice* device );

signals:
    void updateIrrlicht( irr::IrrlichtDevice* device );

protected:
    irr::video::E_DRIVER_TYPE driverType;

    virtual void paintEvent( QPaintEvent* event );

    void sendKeyEventToIrrlicht( QKeyEvent* event, bool pressedDown );
    virtual void keyPressEvent( QKeyEvent* event );
    virtual void keyReleaseEvent( QKeyEvent* event );

    void sendMouseEventToIrrlicht( QMouseEvent* event, bool pressedDown );
    virtual void mousePressEvent( QMouseEvent* event );
    virtual void mouseReleaseEvent( QMouseEvent* event );
    virtual void wheelEvent( QWheelEvent* event );

    virtual void timerEvent( QTimerEvent* event );

    virtual void resizeEvent( QResizeEvent* event );


private:
    irr::IrrlichtDevice* device;
};

#endif // QIRRLICHTWIDGET_H
