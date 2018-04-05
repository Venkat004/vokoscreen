#include "QvkDbus.h"
#include "vokoscreenqvkdbus_adaptor.h"

QvkDbus::QvkDbus( Ui_screencast value )
{
    myUi = value;
    
    new GuiAdaptor( this );
    QDBusConnection dbusConnection = QDBusConnection::sessionBus();
    dbusConnection.registerObject("/gui", this);
    dbusConnection.registerService("org.vokoscreen.screencast");
}


QvkDbus::~QvkDbus()
{  
}


QString QvkDbus::showAllMethode()
{
    QStringList functions;
    for (int n = 0; n < staticMetaObject.methodCount(); n++) {
        functions.append(QString::fromLocal8Bit(staticMetaObject.method(n).name()));

        int index = functions.indexOf("destroyed");
        functions.removeAt( index );

        index = functions.indexOf("objectNameChanged");
        functions.removeAt( index );

        index = functions.indexOf("deleteLater");
        functions.removeAt( index );

        index = functions.indexOf("_q_reregisterTimers");
        functions.removeAt( index );

        index = functions.indexOf("vokoscreenFinishLoaded");
        functions.removeAt( index );
    }

    qDebug() << "[vokoscreen] ---Begin DBus method--- ";
    QString string = functions.join( " " );
    qDebug().noquote() << "[vokoscreen] methods:" << string;
    qDebug() << "[vokoscreen] ---End DBus method--- ";
    qDebug(" ");

    return string;
}


void QvkDbus::vokoscreenFinishLoaded()
{
    vokoscreenLoaded = 0;
    showAllMethode();
}


int QvkDbus::isVokoscreenLoaded()
{
  return vokoscreenLoaded;
}


int QvkDbus::startrecord()
{
   if ( myUi.recordButton->isEnabled() == true )
   {
     myUi.recordButton->click();
     return 0;
   }
   else
   {
     return 1;
   }
}


int QvkDbus::stoprecord()
{
   if ( myUi.StopButton->isEnabled() == true )
   {
     myUi.StopButton->click();
     return 0;
   }
   else
   {
     return 1;
   }
}


int QvkDbus::setFullScreen()
{
    if ( ( myUi.FullScreenRadioButton->isEnabled() == true ) and ( myUi.FullScreenRadioButton->isChecked() == false ) )
    {
      myUi.FullScreenRadioButton->click();
      return 0;
    }
    else
    {
      return 1;
    }
}


int QvkDbus::setWindow()
{
   if ( ( myUi.WindowRadioButton->isEnabled() == true ) and ( myUi.WindowRadioButton->isChecked() == false ) )
   {
     myUi.WindowRadioButton->click();
     return 0;
   }
   else
   {
     return 1;
   }
}



int QvkDbus::setArea()
{
   if ( ( myUi.AreaRadioButton->isEnabled() == true ) and ( myUi.AreaRadioButton->isChecked() == false ) )
   {
     myUi.AreaRadioButton->click();
     return 0;
   }
   else
   {
     return 1;
   }
}


int QvkDbus::setAreaReset()
{
   if ( myUi.areaResetButton->isEnabled() == true )
   {
      myUi.areaResetButton->click();
      return 0;
   }
   else
   {
      return 1;
   }
}


int QvkDbus::setAudioOn()
{
   if ( ( myUi.AudioOnOffCheckbox->isEnabled() == true ) ) //and ( myUi.AudioOnOffCheckbox->checkState() == Qt::Unchecked ) )
   {
       myUi.AudioOnOffCheckbox->setCheckState(Qt::Unchecked);
       myUi.AudioOnOffCheckbox->click();
       return 0;
   }
   else
   {
       return 1;
   }
}


int QvkDbus::setAudioOff()
{
   if ( ( myUi.AudioOnOffCheckbox->isEnabled() == true ) ) //and ( myUi.AudioOnOffCheckbox->checkState() == Qt::Checked ) )
   {
       myUi.AudioOnOffCheckbox->setCheckState(Qt::Checked);
       myUi.AudioOnOffCheckbox->click();
       return 0;
   }
   else
   {
       return 1;
   }
}


int QvkDbus::setWebcamOn()
{
    if ( myUi.webcamCheckBox->checkState() == Qt::Unchecked )
    {
        myUi.webcamCheckBox->click();
        return 0;
    }
    else
    {
        return 1;
    }
}


int QvkDbus::setWebcamOff()
{
    if ( myUi.webcamCheckBox->checkState() == Qt::Checked  )
    {
        myUi.webcamCheckBox->click();
        return 0;
    }
    else
    {
        return 1;
    }
}


int QvkDbus::setCountDown( int value )
{
    myUi.CountdownSpinBox->setValue( value );
    return 0;
}


int QvkDbus::setTab( int value )
{
    if ( value < myUi.tabWidget->count() )
    {
      myUi.tabWidget->setCurrentIndex( value );
      return 0;
    }
    else
    {
      return 1;
    }
}


void QvkDbus::quit()
{
    emit close();
}