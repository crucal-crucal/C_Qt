#pragma once

#include <QSplashScreen>

#ifdef SPLASHSCREEN_LIB
#define SPLASHSCREEN_EXPORT Q_DECL_EXPORT
#else
#define SPLASHSCREEN_EXPORT Q_DECL_IMPORT
#endif

class SPLASHSCREEN_EXPORT SplashScreen final : public QSplashScreen {
public:
	explicit SplashScreen(const QPixmap& pixmap = QPixmap());
	~SplashScreen() override;

protected:
	void drawContents(QPainter* painter) override;
};
