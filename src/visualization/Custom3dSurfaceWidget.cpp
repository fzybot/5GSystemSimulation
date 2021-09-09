#include <QtDataVisualization/Q3DSurface>
#include <QtWidgets>
#include "Custom3dSurfaceWidget.h"

Custom3dSurfaceWidget::Custom3dSurfaceWidget(QWidget *parent)
    : QWidget(parent)
{
    QtDataVisualization::Q3DSurface *graph = new QtDataVisualization::Q3DSurface();
    QWidget *container = QWidget::createWindowContainer(graph);
    //container->setMinimumSize(800, 600);
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    container->setFocusPolicy(Qt::StrongFocus);
    surface_ = new Custom3dSurface(graph);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    QVBoxLayout *heatmapLayout = new QVBoxLayout;
    heatmapLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(container);
    mainLayout->addLayout(heatmapLayout);

    QGroupBox *viewGroupBox = new QGroupBox(QStringLiteral("View"));

    QFont font = QFont("Century Gothic", 14);
    font.setBold(true);

    QCheckBox *checkboxHeight = new QCheckBox("Height");
    checkboxHeight->setChecked(true);
    checkboxHeight->setFont(font);

    QRadioButton *heightButton = new QRadioButton("Heightmap");
    heightButton->setChecked(true);
    heightButton->setFont(font);

    QRadioButton *cityButton = new QRadioButton("City picture");
    cityButton->setChecked(false);
    cityButton->setFont(font);

    QRadioButton *heatmapButton = new QRadioButton("Heatmap");
    heatmapButton->setChecked(false);
    heatmapButton->setFont(font);

    QVBoxLayout *viewVLayout = new QVBoxLayout;
    viewVLayout->addWidget(checkboxHeight);
    viewVLayout->addWidget(heightButton);
    viewVLayout->addWidget(cityButton);
    viewVLayout->addWidget(heatmapButton);
    viewGroupBox->setLayout(viewVLayout);

    QGroupBox *calculationGroupBox = new QGroupBox(QStringLiteral("Calculation"));

    QPushButton *calculationButton = new QPushButton("Re-CALCULATE");
    calculationButton->setFont(font);

    QVBoxLayout *calculationVLayout = new QVBoxLayout;
    calculationVLayout->addWidget(calculationButton);
    calculationGroupBox->setLayout(calculationVLayout);

    QGroupBox *gradientGroupBox = new QGroupBox(QStringLiteral("Gradient"));

    int height = 400;
    int width = 100;
    int border = 10;
    QLinearGradient gr(0, 0, 1, height - 2 * border);
    gr.setColorAt(1.0f, Qt::black);
    gr.setColorAt(0.8f, Qt::darkGreen);
    gr.setColorAt(0.6f, Qt::green);
    gr.setColorAt(0.4f, Qt::yellow);
    gr.setColorAt(0.2f, Qt::red);
    gr.setColorAt(0.0f, Qt::darkRed);

    QPixmap pm(width, height);
    pm.fill(Qt::transparent);
    QPainter pmp(&pm);
    pmp.setBrush(QBrush(gr));
    pmp.setPen(Qt::NoPen);
    pmp.drawRect(border, border, 35, height - 2 * border);
    pmp.setPen(Qt::black);
    int step = (height - 2 * border) / 5;
    for (int i = 0; i < 6; i++) {
        int yPos = i * step + border;
        pmp.drawLine(border, yPos, 55, yPos);
        pmp.drawText(60, yPos + 2, QString("%1 m").arg(550 - (i * 110)));
    }

    QLabel *label = new QLabel();
    label->setPixmap(pm);

    QVBoxLayout *colorMapVBox = new QVBoxLayout;
    colorMapVBox->addWidget(label);
    gradientGroupBox->setLayout(colorMapVBox);

    heatmapLayout->addWidget(viewGroupBox);
    heatmapLayout->addWidget(calculationGroupBox);
    heatmapLayout->addWidget(gradientGroupBox);

    connect(checkboxHeight, &QCheckBox::stateChanged,
                        surface_, &Custom3dSurface::toggleCheckBoxItem);
    connect(heightButton, &QRadioButton::clicked,
                        surface_, &Custom3dSurface::toggleRadioButtonItem);
    connect(cityButton, &QRadioButton::clicked,
                        surface_, &Custom3dSurface::toggleRadioButtonItem);
    connect(heatmapButton, &QRadioButton::clicked,
                        surface_, &Custom3dSurface::toggleRadioButtonItem);
    connect(calculationButton, &QPushButton::pressed,
                surface_, &Custom3dSurface::calculateModel);

    setLayout(mainLayout);
}


