#include "easyfg.h"


void MainWindow::SaveAscii(QString filename, int **Array)
{
    QFile file;
    file.setFileName(filename);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream(&file);


    for(int i=0; i<dataheight; i++){
        for(int j=0; j<datawidth; j++){
            stream << Array[j][i];
            if(j<datawidth-1)
                stream<<",";
        }
        if(i<dataheight-1)
            stream<<"\n";
    }

    file.close();
}
