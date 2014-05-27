#include "QIrrlichtWidget.h"
#include <irrlicht.h>
#include <line2d.h>
#include <qpalette.h>
#include <QKeyEvent>
#include <QMouseEvent>
#include <qpainter.h>
#include <iostream>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

QIrrlichtWidget::QIrrlichtWidget( QWidget *parent )
    : QWidget(parent)
{
    // Wait for the init() call
    device = 0;

    // Default to Open GL
   driverType = irr::video::EDT_DIRECT3D9;
}

QIrrlichtWidget::~QIrrlichtWidget()
{
    if ( device != 0 )
    {
        device->closeDevice();
        device->run();
        device->drop();
    }
}

void QIrrlichtWidget::init()
{
    // Don't initialize more than once!
    if ( device != 0 ) return;

    irr::SIrrlichtCreationParameters params;

    params.DriverType = driverType;
    params.WindowId = (void*)winId();
    params.WindowSize.Width = width();
    params.WindowSize.Height = height();

    device = irr::createDeviceEx( params );

    // Irrlicht will clear the canvas for us, so tell Qt not to do it
    setAttribute( Qt::WA_OpaquePaintEvent );

    connect( this, SIGNAL(updateIrrlicht(irr::IrrlichtDevice*)),
             this, SLOT(autoUpdateIrrlicht(irr::IrrlichtDevice*)) );
    startTimer(0);
}


irr::IrrlichtDevice* QIrrlichtWidget::getIrrlichtDevice()
{
    return device;
}

void QIrrlichtWidget::paintEvent( QPaintEvent* event )
{
    if ( device != 0 )
    {
        emit updateIrrlicht( device );
    }
}

void QIrrlichtWidget::timerEvent( QTimerEvent* event )
{
    if ( device != 0 )
    {
        emit updateIrrlicht( device );
    }
    event->accept();
}


void QIrrlichtWidget::resizeEvent( QResizeEvent* event )
{
    if ( device != 0 )
    {
        irr::core::dimension2d<u32> size;
        size.Width = event->size().width();
        size.Height = event->size().height();
        device->getVideoDriver()->OnResize( size );

        irr::scene::ICameraSceneNode *cam = device->getSceneManager()->getActiveCamera();
        if ( cam != 0 )
        {
            cam->setAspectRatio( (float) size.Height / size.Width );
        }
    }
    QWidget::resizeEvent(event);
}

void QIrrlichtWidget::autoUpdateIrrlicht( irr::IrrlichtDevice* device )
{
    device->getTimer()->tick();

    irr::video::SColor color (0,0,0,0);

    device->getVideoDriver()->beginScene( true, true, color );

    device->getSceneManager()->drawAll();
    device->getGUIEnvironment()->drawAll();

    device->getVideoDriver()->endScene();
}

struct SIrrlichtKey
{
    irr::EKEY_CODE code;
    wchar_t ch;
};

SIrrlichtKey convertToIrrlichtKey( int key )
{
    SIrrlichtKey irrKey;
    irrKey.code = (irr::EKEY_CODE)(0);
    irrKey.ch = (wchar_t)(0);

    // Letters A..Z and numbers 0..9 are mapped directly
    if ( (key >= Qt::Key_A && key <= Qt::Key_Z) || (key >= Qt::Key_0 && key <= Qt::Key_9) )
    {
        irrKey.code = (irr::EKEY_CODE)( key );
        irrKey.ch = (wchar_t)( key );
    }
    else

    // Dang, map keys individually
    switch( key )
    {
    case Qt::Key_Up:
        irrKey.code = irr::KEY_UP;
        break;

    case Qt::Key_Down:
        irrKey.code = irr::KEY_DOWN;
        break;

    case Qt::Key_Left:
        irrKey.code = irr::KEY_LEFT;
        break;

    case Qt::Key_Right:
        irrKey.code = irr::KEY_RIGHT;
        break;
    }
    return irrKey;
}

void QIrrlichtWidget::sendKeyEventToIrrlicht( QKeyEvent* event, bool pressedDown )
{
    irr::SEvent irrEvent;

    irrEvent.EventType = irr::EET_KEY_INPUT_EVENT;

    SIrrlichtKey irrKey = convertToIrrlichtKey( event->key() );

    if ( irrKey.code == 0 ) return; // Could not find a match for this key

    irrEvent.KeyInput.Key = irrKey.code;
    irrEvent.KeyInput.Control = ((event->modifiers() & Qt::ControlModifier) != 0);
    irrEvent.KeyInput.Shift = ((event->modifiers() & Qt::ShiftModifier) != 0);
    irrEvent.KeyInput.Char = irrKey.ch;
    irrEvent.KeyInput.PressedDown = pressedDown;

    device->postEventFromUser( irrEvent );
}

void QIrrlichtWidget::keyPressEvent( QKeyEvent* event )
{
    if ( device != 0 )
    {
        sendKeyEventToIrrlicht( event, true );
    }
    event->ignore();
}

void QIrrlichtWidget::keyReleaseEvent( QKeyEvent* event )
{
    if ( device != 0 )
    {
        sendKeyEventToIrrlicht( event, false );
    }
    event->ignore();
}

void QIrrlichtWidget::sendMouseEventToIrrlicht( QMouseEvent* event, bool pressedDown )
{
    irr::SEvent irrEvent;

    irrEvent.EventType = irr::EET_MOUSE_INPUT_EVENT;

    switch ( event->button() )
    {
    case Qt::LeftButton:
        irrEvent.MouseInput.Event = pressedDown? irr::EMIE_LMOUSE_PRESSED_DOWN:irr::EMIE_LMOUSE_LEFT_UP;
        break;

    case Qt::MidButton:
        irrEvent.MouseInput.Event = pressedDown? irr::EMIE_MMOUSE_PRESSED_DOWN:irr::EMIE_MMOUSE_LEFT_UP;
        break;

    case Qt::RightButton:
        irrEvent.MouseInput.Event = pressedDown? irr::EMIE_RMOUSE_PRESSED_DOWN:irr::EMIE_RMOUSE_LEFT_UP;
        break;

    default:
        return; // Cannot handle this mouse event
    }

    irrEvent.MouseInput.X = event->x();
    irrEvent.MouseInput.Y = event->y();
    irrEvent.MouseInput.Wheel = 0.0f; // Zero is better than undefined

    device->postEventFromUser( irrEvent );
}

void QIrrlichtWidget::mousePressEvent( QMouseEvent* event )
{
    if ( device != 0 )
    {
        sendMouseEventToIrrlicht( event, true );
    }
    event->ignore();
}

void QIrrlichtWidget::mouseReleaseEvent( QMouseEvent* event )
{
    if ( device != 0 )
    {
        sendMouseEventToIrrlicht( event, false );
    }
    event->ignore();
}

void QIrrlichtWidget::wheelEvent( QWheelEvent* event )
{
    if ( device != 0 && event->orientation() == Qt::Vertical )
    {
        irr::SEvent irrEvent;

        irrEvent.EventType = irr::EET_MOUSE_INPUT_EVENT;

        irrEvent.MouseInput.Event = irr::EMIE_MOUSE_WHEEL;
        irrEvent.MouseInput.X = 0; // We don't know these,
        irrEvent.MouseInput.Y = 0; // but better zero them instead of letting them be undefined
        irrEvent.MouseInput.Wheel = event->delta() / 120.0f;

        device->postEventFromUser( irrEvent );
    }
    event->ignore();
}
