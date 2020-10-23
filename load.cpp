#include "easyfg.h"


void MainWindow::LoadAscii(QString filename, int **Array, int *width, int *height)
{
    QFile file;
    file.setFileName(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream(&file);

    QString str;
    QTextStream stream1;
    QString separator = ",";
    //bool lineNumberInFirstColumn = true;
    char c;
    *width = 0;
    *height = 0;

    while(!stream.atEnd()){
        str = stream.readLine();
        if(*height==0){
            if(str.count(",") == 0){
                if(str.count(" ") != 0)
                    separator = " ";
                else
                    separator = "\t";
            }
            *width = str.count(separator)+1;
            if(str.lastIndexOf(separator) == str.length()-1)
                *width = *width-1;
        }
        stream1.setString(&str);
        for(int i=0; i<*width; i++)
            stream1 >> Array[i][*height] >> c;
        //if(Array[0][*height] != *height+1)
            //lineNumberInFirstColumn = false;
        *height += 1;
    }

    file.close();

    /*if(lineNumberInFirstColumn) // Andor ascii file has line numbering that need to be removed
    {
	*width = *width-1;
	for(int i=0; i<*width; i++)
	    for(int j=0; j<*height; j++)
		Array[i][j] = Array[i+1][j];
    }*/
}


//Andor .sif (doesn't work for all cameras; use tiff instead)
void MainWindow::LoadSif(QString filename, int **Array, int *width, int *height)
{
    int n_lines_before_data;
    int version[4];
    int i, j;
    QString str;
    QStringList list;

    *width = 0;
    *height = 0;

    // Sif file
    QFile file(filename);
    file.open(QIODevice::ReadOnly);

    // Streams for reading file header (text) and data
    QTextStream tstream(&file);
    QDataStream dstream(&file);
    dstream.setFloatingPointPrecision(QDataStream::SinglePrecision); // sif data are 32 bit float
    dstream.setByteOrder(QDataStream::LittleEndian);

    // check if correct sif file
    if(tstream.readLine() != "Andor Technology Multi-Channel File"){
        file.close();
        return;
    }

    tstream.readLine(); // skip line

    // read version info
    str = tstream.readLine();
    list = str.split(" ");
    version[0] = list.at(54).toInt();
    version[1] = list.at(55).toInt();
    version[2] = list.at(56).toInt();
    version[3] = list.at(57).toInt();

    // define data offset
    if(version[0]==0) // French group cameras
        n_lines_before_data=24;
    if(version[0]==4){
        if(version[1]==9) // from OpenSIFkai
            n_lines_before_data = 27;
        if(version[1]==11) // Imperial College camera
            n_lines_before_data = 31;
        if(version[1]==13 || version[1]==15) // from OpenSIFkai
            n_lines_before_data = 31;
    }

    for(i=0; i<=n_lines_before_data-6; i++)
        tstream.readLine(); // skip line

    // read width & height info
    str = tstream.readLine();
    list = str.split(" ");
    int left = list.at(1).toInt();
    int top = list.at(2).toInt();
    int right = list.at(3).toInt();
    int bottom = list.at(4).toInt();
    *width = right-left+1;
    *height = top-bottom+1;

    // go to begginning of the file
    file.seek(0);

    // skip headerer lines
    qint8 i8 = 0;
    for(i=0; i<n_lines_before_data; i++){
        dstream >> i8;
        while(i8 != 10) // end line simbol
            dstream >> i8;
    }

    // read data
    float tmp;
    for(j=0; j<*height; j++) {
        for(i=0; i<*width; i++){
            dstream >> tmp;
            Array[i][*height-1-j] = (int)tmp;
        }
    }

    file.close();
}


void MainWindow::LoadTiff(QString filename, int **Array, int *width, int *height)
{
    *width = 0;
    *height = 0;

    //check if tiff is supported (list all supported file formats)
    //QList<QByteArray> list = QImageReader::supportedImageFormats();
    //QMessageBox().information(this, "Supported formats", list.join(","));

    QFile f(filename);
    if(!f.open(QIODevice::ReadOnly)){
        QMessageBox().warning(this, "easyFG", "Cannot open file");
        return;
    }
    QByteArray ar(f.size(), ' ');
    f.read(ar.data(), ar.size());
    f.close();

    QImage img;
    img.loadFromData(ar);
    if (img.isNull()){
        QMessageBox().warning(this, "easyFG", "File load error");
        return;
    }

    //QMessageBox().information(this, "Image format", QString::number(img.format()));
    if(img.format()!=QImage::Format_Grayscale8 && img.format()!=QImage::Format_Grayscale16)
    {
        QMessageBox().warning(this, "easyFG", "Unsupported TIFF file format");
        return;
    }

    // read data

    *width = img.width();
    *height = img.height();

    uchar* line;
    int i, j;
    for(j=0; j<*height; j++)
    {
        line = img.scanLine(j);
        for(i=0; i<*width; i++)
        {
            if(img.format()==QImage::Format_Grayscale8) // 8-bit greyscale
                Array[i][j] = ((uint8_t*)line)[i];
            else //16-bit greyscale
                Array[i][j] = ((uint16_t*)line)[i];
        }
    }
}

// Pyrocam III .RAW file
void MainWindow::LoadRaw(QString filename, int **Array, int *width, int *height)
{
    int i, j;

    *width = 124;
    *height = 124;

    // Raw file
    QFile file(filename);
    file.open(QIODevice::ReadOnly);

    // Stream for reading  data
    QDataStream dstream(&file);
    dstream.setByteOrder(QDataStream::LittleEndian);

    // go to begginning of the data
    file.seek(16704);

    // read data
    int16_t tmp;
    for(j=0; j<*height; j++)
    {
        for(i=0; i<*width; i++)
        {
            dstream >> tmp;
            Array[i][j] = (int)tmp;
        }
    }

    file.close();
}


// Pyrocam IV .bgData file
void MainWindow::LoadBgdata(QString filename, int **Array, int *width, int *height)
{
    int i, j;
    *width = 0;
    *height = 0;
    hid_t file;
    int32_t *data;

    file = H5Fopen(filename.toUtf8(), H5F_ACC_RDONLY, H5P_DEFAULT);

    // read width and height
    H5LTread_dataset_int(file, "/BG_DATA/1/RAWFRAME/WIDTH", width);
    H5LTread_dataset_int(file, "/BG_DATA/1/RAWFRAME/HEIGHT", height);

    data = (int32_t*)malloc(sizeof(int32_t) * (*width) * (*height));

    // read dataset
    H5LTread_dataset_int(file,"/BG_DATA/1/DATA",data);

    for(j=0; j<*height; j++)
    {
        for(i=0; i<*width; i++)
            Array[i][j] = data[i+(*width)*j] >> 16; // shift 16 bit to the right
    }

    // from Ophir website:
    // Regarding the .bgData image file decription; the input camera native source may be 8, 10, 12, 14, or 16 bits per pixel.
    // BeamGage employs a normalized (signed 32-bit) fixed point format for storing pixel values in HDF5 data files. The
    // acquired and processed camera pixel data is converted to a 32-bit signed value and stored. The most significant bit of the
    // camera's native data is shifted to the bit position just behind the sign bit (assuming bit positions 0 [lsb] -31 [msb] this would
    // be position 30). The empty bits below the native format are then available for additional precision and will be utilized via
    // frame averaging, background subtraction, or other image processing activities.

    free(data);

    /* close file */
    H5Fclose(file);
}


void MainWindow::LoadData(QString path)
{
    QFileInfo file(path);

    if(!file.exists())
        return;

    int tmp;

    datafile = path;
    if(file.suffix().toLower()=="asc" || file.suffix().toLower()=="csv"){ // ASCII
        LoadAscii(datafile, DataArray, &datawidth, &dataheight);
        dataloaded = true;
    }
    if(file.suffix().toLower()=="sif"){ // Andor sif
        LoadSif(datafile, DataArray, &datawidth, &dataheight);
        dataloaded = true;
    }
    if(file.suffix().toLower()=="tiff" || file.suffix().toLower()=="tif"){ // TIFF
        LoadTiff(datafile, DataArray, &datawidth, &dataheight);
        dataloaded = true;
    }
    if(file.suffix().toLower()=="raw"){ // Pyrocam III
        LoadRaw(datafile, DataArray, &datawidth, &dataheight);
        dataloaded = true;
    } 
    if(file.suffix().toLower()=="bgdata"){ // Pyrocam IV
        LoadBgdata(datafile, DataArray, &datawidth, &dataheight);
        dataloaded = true;
    }
    if(!dataloaded)
        return;

    datamin = 1e9;
    datamax = -1e9;
    //dataaverage = 0;
    for(int i=0; i<datawidth; i++){
        for(int j=0; j<dataheight; j++){
            tmp = DataArray[i][j];
            if(tmp<datamin)
                datamin=tmp;
            if(tmp>datamax)
                datamax = tmp;
	    //dataaverage += DataArray[i][j];
        }
    }
    //dataaverage /= datawidth*dataheight;

    if(referenceComboBox->currentIndex() == 3) // "Show reference"
        referenceComboBox->setCurrentIndex(0); // switch to "OFF"

    if(refloaded && referenceComboBox->currentIndex()>0)
        CalculateCorrectedArray();

    UpdateCursors();
    UpdateScale();
    UpdateImage();
    RedoAnalysis();
    UpdateVisibility();
    UpdateScene();
    UpdateStatus();
}


void MainWindow::LoadRef(QString path)
{
    QFileInfo file(path);

    if(!file.exists())
        return;

    reffile = path;

    if(file.suffix().toLower()=="asc"){ // ASCII file
        LoadAscii(reffile, RefArray, &refwidth, &refheight);
        refloaded = true;
    }
    if(file.suffix().toLower()=="sif"){ // Andor sif
        LoadSif(reffile, RefArray, &refwidth, &refheight);
        refloaded = true;
    }
    if(file.suffix().toLower()=="tiff" || file.suffix().toLower()=="tif"){ // TIFF
        LoadTiff(reffile, RefArray, &refwidth, &refheight);
        refloaded = true;
    }
    if(file.suffix().toLower()=="raw"){ // Pyrocam III
        LoadRaw(reffile, RefArray, &refwidth, &refheight);
        refloaded = true;
    }
    if(file.suffix().toLower()=="bgdata"){ // Pyrocam IV
        LoadBgdata(reffile, RefArray, &refwidth, &refheight);
        refloaded = true;
    }
    if(!refloaded)
        return;

    refaverage = 0;
    for(int i=0; i<refwidth; i++)
        for(int j=0; j<refheight; j++)
            refaverage += RefArray[i][j];
    refaverage /= refwidth*refheight;

    if(dataloaded && referenceComboBox->currentIndex()>0){
        CalculateCorrectedArray();
        UpdateImage();
        UpdateScale();
        RedoAnalysis();
        UpdateScene();
        UpdateStatus();
    }

    UpdateVisibility();
}
