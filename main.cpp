#include <QApplication>
#include "GUI/PspahMainWindow.h"
#include "model/StyleSheetConfigModel.h"
#include "GUI/PspahChartView.h"
StyleSheetConfigModel::StyleSheetType StyleSheetConfigModel::sheet_type =
StyleSheetConfigModel::StyleSheetType::LIGHT;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PspahMainWindow w;
    qDebug() << "Main Thread:" << w.thread();
    StyleSheetConfigModel* style_model = new StyleSheetConfigModel();
    style_model->setGlobalStyleSheet(&w);
    w.show();
    return a.exec();
}
