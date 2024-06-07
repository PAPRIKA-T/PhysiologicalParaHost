#include "StyleSheetConfigModel.h"
#include <QMenu>
#include <QFile>
#include <QString>
#include <QDebug>
void StyleSheetConfigModel::setGlobalStyleSheet(QWidget* w)
{
    QFile file(getStyleSheetParentPath() + "DefaultStyle.qss");
    if (file.open(QFile::ReadOnly)) {
        QString stylesheet = QLatin1String(file.readAll());
        w->setStyleSheet(stylesheet);
        file.close();
    }
    else {
        qDebug() << "StyleSheetConfig::setGlobalStyleSheet: open file failed";
    }
}

void StyleSheetConfigModel::setMenuStyle(QMenu* menu)
{
    QFile file( getStyleSheetParentPath() + "MenuStyle.qss");
    if (file.open(QFile::ReadOnly)) {
        QString stylesheet = QLatin1String(file.readAll());
        menu->setStyleSheet(stylesheet);
        file.close();
    }
    else {
        qDebug() << "StyleSheetConfig::setMenuStyle: open file failed";
    }
}

StyleSheetConfigModel::StyleSheetType StyleSheetConfigModel::getStyleType() const
{
    return sheet_type;
}

QString StyleSheetConfigModel::getStyleSheetParentPath()
{
    QString p{};
    if(sheet_type == StyleSheetType::DARK)
		p = ":/PspahResource/QSS/Dark/";
	else if(sheet_type == StyleSheetType::LIGHT)
		p = ":/PspahResource/QSS/Light/";
	else
		qDebug() << "StyleSheetConfig::getStyleSheetParentPath: invalid type";
    return p;
}

void StyleSheetConfigModel::setStyleType(StyleSheetType t)
{
    sheet_type = t;
}
