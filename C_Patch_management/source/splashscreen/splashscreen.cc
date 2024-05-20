#include "splashscreen.hpp"

#include <QPainter>

SplashScreen::SplashScreen(const QPixmap& pixmap) : QSplashScreen(pixmap) {
}

SplashScreen::~SplashScreen() = default;

void SplashScreen::drawContents(QPainter* painter) {
	painter->setFont(QFont("Helvetica", 12, QFont::Bold));
	QSplashScreen::drawContents(painter);
}
