#include <QColor>

QColor HSLtoRGB(float h, float s, float l) {
    float c = (1 - fabs(2 * l - 1)) * s;
    float x = c * (1 - fabs(fmod(h / 60.0, 2) - 1));
    float m = l - c / 2;
    float r, g, b;
    if (h < 60) {
        r = c, g = x, b = 0;
    } else if (h < 120) {
        r = x, g = c, b = 0;
    } else if (h < 180) {
        r = 0, g = c, b = x;
    } else if (h < 240) {
        r = 0, g = x, b = c;
    } else if (h < 300) {
        r = x, g = 0, b = c;
    } else {
        r = c, g = 0, b = x;
    }
    return QColor::fromRgbF(r + m, g + m, b + m);
}

std::vector<float> hues = {0, 30, 60, 120, 180, 240, 300};

QList <QColor> generateColors(int count) {
    QList <QColor> colors;
    float saturation = 0.9;
    float lightness = 0.5;

    for (int i = 0; i < count; ++i) {
        float hue = hues[i % hues.size()] + (i / hues.size()) * 15;
        hue = fmod(hue, 360);
        QColor color = HSLtoRGB(hue, saturation, lightness);
        colors.append(color);
    }

    return colors;
}
