#pragma once
class QMenu;
class QWidget;
class QString;

class StyleSheetConfigModel
{
public:
	enum class StyleSheetType
    {
		DARK,
		LIGHT,
	};
	void setStyleType(StyleSheetType);
	void setGlobalStyleSheet(QWidget*);
	void setMenuStyle(QMenu*);
	StyleSheetType getStyleType() const;
private:
	static StyleSheetType sheet_type;
	QString getStyleSheetParentPath();
};

