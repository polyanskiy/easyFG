#include "easyfg.h"


void MainWindow::CalculateCorrectedArray()
{
    if(!refloaded || referenceComboBox->currentIndex() == 0)
        return;

    int i, j;
    int x_shift = -xshiftSpinBox->value();
    int y_shift = -yshiftSpinBox->value();
    float val=0;
    correctedmin = 1e9;
    correctedmax = 0;

    for(i=0; i<datawidth; i++){
        for(j=0; j<dataheight; j++){
            if(i>=refwidth-x_shift || j>=refheight-y_shift || i<-x_shift || j<-y_shift)
                val = 0;
	    else{
		val = RefArray[i+x_shift][j+y_shift];

		switch(referenceComboBox->currentIndex()){
		    case 1: //substract
			val = DataArray[i][j] - val;
		    break;
		    case 2: //divide
			if(val != 0)
			    val = refaverage*DataArray[i][j]/val;
		    break;
		    //case 3: "show reference" - do nothing
		}
            }

            if(val < correctedmin)
                correctedmin = val;
            if(val > correctedmax)
                correctedmax = val;

            CorrectedArray[i][j] = floor(val+0.5);
        }
    }

    //UpdateRanges();
    UpdateScale();
}


void MainWindow::on_referenceButton_clicked()
{
    if(!QFile::exists(reffile))
        reffile = datafile;
    QFileDialog dialog(this, "Load reference file", reffile, "All supported (*.asc *.csv *.tiff *.tif *.sif *.raw);;ASCII (*.asc *.csv);;TIFF (*.tiff *.tif);;Andor SIF (*.sif);;Pyrocam RAW (*.raw)");
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    if(dialog.exec()){
        QStringList path = dialog.selectedFiles();
        LoadRef(path[0]);
    }
}


void MainWindow::on_currentButton_clicked()
{
    if(!QFile::exists(datafile))
        return;

    reffile = datafile;
    LoadRef(reffile);
}


void MainWindow::on_referenceComboBox_currentIndexChanged()
{
    if(dataloaded && refloaded)
    {
        if(referenceComboBox->currentIndex()>0) // reference ON
	    CalculateCorrectedArray();

        RedoAnalysis();
        UpdateScale();
        UpdateImage();
        UpdateScene();
        UpdateStatus();
    }
    UpdateVisibility();
}


void MainWindow::on_xshiftSpinBox_valueChanged()
{
    on_referenceComboBox_currentIndexChanged();
}


void MainWindow::on_yshiftSpinBox_valueChanged()
{
    on_referenceComboBox_currentIndexChanged();
}
