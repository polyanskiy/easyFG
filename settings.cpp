#include "easyfg.h"


void MainWindow::SaveSession()
{
    QSettings settings("ATF", "easyFG");

    settings.setValue("datafile", datafile);
    settings.setValue("reffile", reffile);
    settings.setValue("savefile", savefile);
    settings.setValue("scale", scaleComboBox->currentIndex());
    settings.setValue("offset", offsetSpinBox->value());
    settings.setValue("cutoff", cutoffSpinBox->value());
    settings.setValue("reference", referenceComboBox->currentIndex());
    settings.setValue("pseudocolor", pseudocolorCheckBox->checkState());
    settings.setValue("inverted", invertedCheckBox->checkState());
    settings.setValue("zoom", zoom);
    settings.setValue("x_shift", xshiftSpinBox->value());
    settings.setValue("y_shift", yshiftSpinBox->value());
    settings.setValue("X", XCheckBox->checkState());
    settings.setValue("X_from", X1SpinBox->value());
    settings.setValue("X_to", X2SpinBox->value());
    settings.setValue("Y", YCheckBox->checkState());
    settings.setValue("Y_from", Y1SpinBox->value());
    settings.setValue("Y_to", Y2SpinBox->value());
    settings.setValue("D", DCheckBox->checkState());
    // window geometry
    if(!flag_fullscreen) // otherwise geometry is already saved
        settings.setValue("window_geometry", saveGeometry());
}


void MainWindow::RestoreSession()
{
    QSettings settings("ATF", "easyFG");

    datafile = settings.value("datafile", QString()).toString(); // from last session

    // Process command line
    QStringList arg = qApp->arguments( );
    /*if( arg.count()>1 && QFile::exists(arg.last()) )
        datafile = arg.last(); // from command line*/
    if( arg.count()>1 ){
        QString str = arg.at(1);
        for(int i=2; i<arg.count(); i++)
            str += " " + arg.at(i);
        if( QFile::exists(str) )
            datafile = str;
    }

    /*if(arg.count()>1){
	QMessageBox mb(QMessageBox::NoIcon, "arguments", arg.at(1));
	mb.exec();
    }*/

    // Saved settings
    restoreGeometry(settings.value("window_geometry").toByteArray());
    reffile = settings.value("reffile", QString()).toString();
    savefile = settings.value("savefile", QString()).toString();
    scaleComboBox->setCurrentIndex(settings.value("scale", 0).toInt());
    offsetSpinBox->setValue(settings.value("offset", 0).toFloat());
    cutoffSpinBox->setValue(settings.value("cutoff", 0).toInt());
    referenceComboBox->setCurrentIndex(settings.value("reference", 0).toInt());
    pseudocolorCheckBox->setCheckState((Qt::CheckState)settings.value("pseudocolor", 0).toInt());
    invertedCheckBox->setCheckState((Qt::CheckState)settings.value("inverted", 0).toInt());
    zoom = settings.value("zoom", 0).toInt();
    xshiftSpinBox->setValue(settings.value("x_shift", 0).toInt());
    yshiftSpinBox->setValue(settings.value("y_shift", 0).toInt());
    XCheckBox->setCheckState((Qt::CheckState)settings.value("X", 0).toInt());
    X1SpinBox->setValue(settings.value("X_from", 0).toInt());
    X2SpinBox->setValue(settings.value("X_to", MAX_HEIGHT-1).toInt());
    YCheckBox->setCheckState((Qt::CheckState)settings.value("Y", 0).toInt());
    Y1SpinBox->setValue(settings.value("Y_from", 0).toInt());
    Y2SpinBox->setValue(settings.value("Y_to", MAX_WIDTH-1).toInt());
    DCheckBox->setCheckState((Qt::CheckState)settings.value("D", 0).toInt());
}
