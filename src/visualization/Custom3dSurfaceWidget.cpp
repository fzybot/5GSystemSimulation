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

    gradientGroupBox_ = new QGroupBox(QStringLiteral("Gradient"));

    int height = 400;
    int width = 100;
    int border = 10;
    QLinearGradient gr(0, 0, 1, height - 2 * border);
    gr.setColorAt(1.0f, Qt::blue);
    gr.setColorAt(0.8f, Qt::cyan);
    gr.setColorAt(0.6f, Qt::green);
    gr.setColorAt(0.4f, Qt::yellow);
    gr.setColorAt(0.0f, Qt::red);

//blue,cyan,green,yellow,red
    QPixmap pm(width, height);
    pm.fill(Qt::transparent);
    QPainter pmp(&pm);
    pmp.setBrush(QBrush(gr));
    pmp.setPen(Qt::NoPen);
    pmp.drawRect(border, border, 35, height - 2 * border);
    pmp.setPen(Qt::black);
    int step = (height - 2 * border) / 10;
    for (int i = 0; i < 11; i++) {
        int yPos = i * step + border;
        pmp.drawLine(border, yPos, 55, yPos);
        pmp.drawText(60, yPos + 2, QString("%1 dBm").arg(-44 - (i * 10)));
    }

    label_ = new QLabel();
    label_->setPixmap(pm);

    QVBoxLayout *colorMapVBox = new QVBoxLayout;
    colorMapVBox->addWidget(label_);
    gradientGroupBox_->setLayout(colorMapVBox);

    heatmapLayout->addWidget(viewGroupBox);
    heatmapLayout->addWidget(calculationGroupBox);
    heatmapLayout->addWidget(gradientGroupBox_);

    connect(checkboxHeight, &QCheckBox::stateChanged,
                        surface_, &Custom3dSurface::toggleCheckBoxItem);

    //connect(checkboxHeight, &QCheckBox::stateChanged,
    //                    this, &Custom3dSurfaceWidget::changeGradient);

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

void Custom3dSurfaceWidget::changeGradient()
{
    qDebug() << "!SiGNAL!";
    int height = 400;
    int width = 100;
    int border = 10;
    QLinearGradient gr(0, 0, 1, height - 2 * border);
    gr.setColorAt(1.0f, Qt::black);
    gr.setColorAt(0.0f, Qt::white);

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
        pmp.drawText(60, yPos + 2, QString("-%1 m").arg(144 - (i * 10)));
    }

    QLayout* colorMapVBox = gradientGroupBox_->layout();

    label_->setPixmap(pm);

    colorMapVBox->addWidget(label_);

    gradientGroupBox_->setLayout(colorMapVBox);

}

