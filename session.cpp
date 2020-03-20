#include "easyfg.h"


void MainWindow::SaveSession()
{
    QSettings settings("ATF", "easyFG");

    settings.setValue("datafile", datafile);
    settings.setValue("reffile", reffile);
    settings.setValue("savefile", savefile);

    settings.setValue("min", minSpinBox->value());
    settings.setValue("min_type", minComboBox->currentIndex());
    settings.setValue("max", maxSpinBox->value());
    settings.setValue("max_type", maxComboBox->currentIndex());
    settings.setValue("pseudocolor", pseudocolorCheckBox->checkState());
    settings.setValue("inverted", invertedCheckBox->checkState());
    settings.setValue("zoom", zoom);
    settings.setValue("H", HCheckBox->checkState());
    settings.setValue("H1", H1SpinBox->value());
    settings.setValue("H2", H2SpinBox->value());
    settings.setValue("V", VCheckBox->checkState());
    settings.setValue("V1", V1SpinBox->value());
    settings.setValue("V2", V2SpinBox->value());
    settings.setValue("cursorh1", cursorh1);
    settings.setValue("cursorh2", cursorh2);
    settings.setValue("cursorv1", cursorv1);
    settings.setValue("cursorv2", cursorv2);
    settings.setValue("X", XCheckBox->checkState());
    settings.setValue("Y", YCheckBox->checkState());
    settings.setValue("R", RCheckBox->checkState());
    settings.setValue("D", DCheckBox->checkState());
    settings.setValue("reference", referenceComboBox->currentIndex());
    settings.setValue("x_shift", xshiftSpinBox->value());
    settings.setValue("y_shift", yshiftSpinBox->value());
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

    restoreGeometry(settings.value("window_geometry").toByteArray());

    savefile = settings.value("savefile", QString()).toString();
    reffile = settings.value("reffile", QString()).toString();

    pseudocolorCheckBox->setCheckState((Qt::CheckState)settings.value("pseudocolor", 0).toInt());
    invertedCheckBox->setCheckState((Qt::CheckState)settings.value("inverted", 0).toInt());
    zoom = settings.value("zoom", 0).toInt();
    minSpinBox->setValue(settings.value("min", 0).toFloat());
    minComboBox->setCurrentIndex(settings.value("min_type", 0).toInt());
    maxSpinBox->setValue(settings.value("max", 0).toInt());
    maxComboBox->setCurrentIndex(settings.value("max_type", 0).toInt());
    HCheckBox->setCheckState((Qt::CheckState)settings.value("H", 0).toInt());
    H1SpinBox->setValue(settings.value("H1", 0).toInt());
    H2SpinBox->setValue(settings.value("H2", MAX_HEIGHT-1).toInt());
    VCheckBox->setCheckState((Qt::CheckState)settings.value("V", 0).toInt());
    V1SpinBox->setValue(settings.value("V1", 0).toInt());
    V2SpinBox->setValue(settings.value("V2", MAX_WIDTH-1).toInt());
    cursorh1 = settings.value("cursorh1", 0).toInt();
    cursorh2 = settings.value("cursorh2", MAX_HEIGHT-1).toInt();
    cursorv1 = settings.value("cursorv1", 0).toInt();
    cursorv2 = settings.value("cursorv2", MAX_WIDTH-1).toInt();
    XCheckBox->setCheckState((Qt::CheckState)settings.value("X", 0).toInt());
    YCheckBox->setCheckState((Qt::CheckState)settings.value("Y", 0).toInt());
    RCheckBox->setCheckState((Qt::CheckState)settings.value("R", 0).toInt());
    DCheckBox->setCheckState((Qt::CheckState)settings.value("D", 0).toInt());
    referenceComboBox->setCurrentIndex(settings.value("reference", 0).toInt());
    xshiftSpinBox->setValue(settings.value("x_shift", 0).toInt());
    yshiftSpinBox->setValue(settings.value("y_shift", 0).toInt());
}
