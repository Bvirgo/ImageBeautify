#include "classicspecialeffectdialog.h"
#include <QVBoxLayout>
#include <QGroupBox>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QPushButton>

ClassicSpecialEffectDialog::ClassicSpecialEffectDialog(std::shared_ptr<QImage> img)
{
    setImage(img);
    imageLabel = new QLabel;
    imageLabel->setMaximumWidth(imageMaxWidth);
    imageLabel->setMaximumHeight(imageMaxHeight);
    update();

    QVBoxLayout *imageLayout = new QVBoxLayout;
    imageLayout->addWidget(imageLabel);
    imageLayout->setContentsMargins(10, 10, 10, 10);

    QGroupBox *imageGroup = new QGroupBox(tr("View Image"));
    imageGroup->setLayout(imageLayout);

    // special effects clickable qlabels/groupboxs
    ClickableQLabel *specialeffects1 = new ClickableQLabel(tr("锐化"));
    QGroupBox *segroupbox1 = new QGroupBox(tr("锐化"));
    QVBoxLayout *selayout1 = new QVBoxLayout;
    selayout1->addWidget(specialeffects1);
    segroupbox1->setLayout(selayout1);

    ClickableQLabel *specialeffects2 = new ClickableQLabel(tr("黑白"));
    QGroupBox *segroupbox2 = new QGroupBox(tr("黑白"));
    QVBoxLayout *selayout2 = new QVBoxLayout;
    selayout2->addWidget(specialeffects2);
    segroupbox2->setLayout(selayout2);

    ClickableQLabel *specialeffects3 = new ClickableQLabel(tr("去雾"));
    QGroupBox *segroupbox3 = new QGroupBox(tr("去雾"));
    QVBoxLayout *selayout3 = new QVBoxLayout;
    selayout3->addWidget(specialeffects3);
    segroupbox3->setLayout(selayout3);

    ClickableQLabel *specialeffects4 = new ClickableQLabel(tr("柔和"));
    QGroupBox *segroupbox4 = new QGroupBox(tr("柔和"));
    QVBoxLayout *selayout4 = new QVBoxLayout;
    selayout4->addWidget(specialeffects4);
    segroupbox4->setLayout(selayout4);

    ClickableQLabel *specialeffects5 = new ClickableQLabel(tr("均衡"));
    QGroupBox *segroupbox5 = new QGroupBox(tr("均衡"));
    QVBoxLayout *selayout5 = new QVBoxLayout;
    selayout5->addWidget(specialeffects5);
    segroupbox5->setLayout(selayout5);

    ClickableQLabel *specialeffects6 = new ClickableQLabel(tr("怀旧"));
    QGroupBox *segroupbox6 = new QGroupBox(tr("怀旧"));
    QVBoxLayout *selayout6 = new QVBoxLayout;
    selayout6->addWidget(specialeffects6);
    segroupbox6->setLayout(selayout6);

    ClickableQLabel *specialeffects7 = new ClickableQLabel(tr("连环画"));
    QGroupBox *segroupbox7 = new QGroupBox(tr("连环画"));
    QVBoxLayout *selayout7 = new QVBoxLayout;
    selayout7->addWidget(specialeffects7);
    segroupbox7->setLayout(selayout7);

    ClickableQLabel *specialeffects8 = new ClickableQLabel(tr("时光隧道"));
    QGroupBox *segroupbox8 = new QGroupBox(tr("时光隧道"));
    QVBoxLayout *selayout8 = new QVBoxLayout;
    selayout8->addWidget(specialeffects8);
    segroupbox8->setLayout(selayout8);

    ClickableQLabel *specialeffects9 = new ClickableQLabel(tr("经典lomo"));
    QGroupBox *segroupbox9 = new QGroupBox(tr("经典lomo"));
    QVBoxLayout *selayout9 = new QVBoxLayout;
    selayout9->addWidget(specialeffects9);
    segroupbox9->setLayout(selayout9);

    ClickableQLabel *specialeffects10 = new ClickableQLabel(tr("美白"));
    QGroupBox *segroupbox10 = new QGroupBox(tr("美白"));
    QVBoxLayout *selayout10 = new QVBoxLayout;
    selayout10->addWidget(specialeffects10);
    segroupbox10->setLayout(selayout10);

    ClickableQLabel *specialeffects11 = new ClickableQLabel(tr("美颜"));
    QGroupBox *segroupbox11 = new QGroupBox(tr("美颜"));
    QVBoxLayout *selayout11 = new QVBoxLayout;
    selayout11->addWidget(specialeffects11);
    segroupbox11->setLayout(selayout11);

    ClickableQLabel *specialeffects12 = new ClickableQLabel(tr("粉红佳人"));
    QGroupBox *segroupbox12 = new QGroupBox(tr("粉红佳人"));
    QVBoxLayout *selayout12 = new QVBoxLayout;
    selayout12->addWidget(specialeffects12);
    segroupbox12->setLayout(selayout12);

    // groupboxs layout
    QVBoxLayout *segroupboxLayout = new QVBoxLayout;
    segroupbox1->setMaximumSize(seGroupMinWidth,seGroupMinHeight);
    segroupbox2->setMaximumSize(seGroupMinWidth,seGroupMinHeight);
    segroupbox3->setMaximumSize(seGroupMinWidth,seGroupMinHeight);
    segroupbox4->setMaximumSize(seGroupMinWidth,seGroupMinHeight);
    segroupbox5->setMaximumSize(seGroupMinWidth,seGroupMinHeight);
    segroupbox6->setMaximumSize(seGroupMinWidth,seGroupMinHeight);
    segroupbox7->setMaximumSize(seGroupMinWidth,seGroupMinHeight);
    segroupbox8->setMaximumSize(seGroupMinWidth,seGroupMinHeight);
    segroupbox9->setMaximumSize(seGroupMinWidth,seGroupMinHeight);
    segroupbox10->setMaximumSize(seGroupMinWidth,seGroupMinHeight);
    segroupbox11->setMaximumSize(seGroupMinWidth,seGroupMinHeight);
    segroupbox12->setMaximumSize(seGroupMinWidth,seGroupMinHeight);

    segroupbox1->setMinimumSize(seGroupMinWidth,seGroupMinHeight);
    segroupbox2->setMinimumSize(seGroupMinWidth,seGroupMinHeight);
    segroupbox3->setMinimumSize(seGroupMinWidth,seGroupMinHeight);
    segroupbox4->setMinimumSize(seGroupMinWidth,seGroupMinHeight);
    segroupbox5->setMinimumSize(seGroupMinWidth,seGroupMinHeight);
    segroupbox6->setMinimumSize(seGroupMinWidth,seGroupMinHeight);
    segroupbox7->setMinimumSize(seGroupMinWidth,seGroupMinHeight);
    segroupbox8->setMinimumSize(seGroupMinWidth,seGroupMinHeight);
    segroupbox9->setMinimumSize(seGroupMinWidth,seGroupMinHeight);
    segroupbox10->setMinimumSize(seGroupMinWidth,seGroupMinHeight);
    segroupbox11->setMinimumSize(seGroupMinWidth,seGroupMinHeight);
    segroupbox12->setMinimumSize(seGroupMinWidth,seGroupMinHeight);

    segroupboxLayout->addWidget(segroupbox1);
    segroupboxLayout->addWidget(segroupbox2);
    segroupboxLayout->addWidget(segroupbox3);
    segroupboxLayout->addWidget(segroupbox4);
    segroupboxLayout->addWidget(segroupbox5);
    segroupboxLayout->addWidget(segroupbox6);
    segroupboxLayout->addWidget(segroupbox7);
    segroupboxLayout->addWidget(segroupbox8);
    segroupboxLayout->addWidget(segroupbox9);
    segroupboxLayout->addWidget(segroupbox10);
    segroupboxLayout->addWidget(segroupbox11);
    segroupboxLayout->addWidget(segroupbox12);

    // !! set icons !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    QImage icon1(":/classicEffects/Resource/classic_effect/sharpen.jpg");
    QImage icon2(":/classicEffects/Resource/classic_effect/colortoblack.jpg");
    QImage icon3(":/classicEffects/Resource/classic_effect/defog.jpg");
    QImage icon4(":/classicEffects/Resource/classic_effect/soft.jpg");
    QImage icon5(":/classicEffects/Resource/classic_effect/balance.jpg");
    QImage icon6(":/classicEffects/Resource/classic_effect/nostalgia.jpg");
    QImage icon7(":/classicEffects/Resource/classic_effect/BlackComic.jpg");
    QImage icon8(":/classicEffects/Resource/classic_effect/timetuunel.jpg");
    QImage icon9(":/classicEffects/Resource/classic_effect/classiclomo.jpg");
    QImage icon10(":/classicEffects/Resource/classic_effect/whiteFace.jpg");
    QImage icon11(":/classicEffects/Resource/classic_effect/beautifyFace.jpg");
    QImage icon12(":/classicEffects/Resource/classic_effect/pinkLady.jpg");

    specialeffects1->setPixmap(Icon2Pixmap(icon1));
    specialeffects2->setPixmap(Icon2Pixmap(icon2));
    specialeffects3->setPixmap(Icon2Pixmap(icon3));
    specialeffects4->setPixmap(Icon2Pixmap(icon4));
    specialeffects5->setPixmap(Icon2Pixmap(icon5));
    specialeffects6->setPixmap(Icon2Pixmap(icon6));
    specialeffects7->setPixmap(Icon2Pixmap(icon7));
    specialeffects8->setPixmap(Icon2Pixmap(icon8));
    specialeffects9->setPixmap(Icon2Pixmap(icon9));
    specialeffects10->setPixmap(Icon2Pixmap(icon10));
    specialeffects11->setPixmap(Icon2Pixmap(icon11));
    specialeffects12->setPixmap(Icon2Pixmap(icon12));

    // scroll area
    QGroupBox *scrollareagroup = new QGroupBox;
    QVBoxLayout *scrollarealayout = new QVBoxLayout;
    QWidget *scrollareawidget = new QWidget;
    scrollareawidget->setLayout(segroupboxLayout);
//    scrollareawidget->setMinimumWidth(90);
    QScrollArea *secialEffectsScrollArea = new QScrollArea;
    secialEffectsScrollArea->setMinimumSize(165,455);
    secialEffectsScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    secialEffectsScrollArea->setWidget(scrollareawidget);
    scrollarealayout->addWidget(secialEffectsScrollArea);
    scrollareagroup->setLayout(scrollarealayout);

    // alpha slider
    alphaSlider = new QSlider;
    QLabel *alphaLabel = new QLabel;
    alphaLabel->setText(tr("透明度: "));
    alphaValue = new QLabel;
    alphaValue->setText(tr("100"));
    alphaValue->setAlignment(Qt::AlignRight);

    QHBoxLayout *alphaLabelLayout = new QHBoxLayout;
    alphaLabelLayout->addWidget(alphaLabel);
    alphaLabelLayout->addWidget(alphaValue);

    alphaSlider = new QSlider(Qt::Horizontal);
    alphaSlider->setMinimum(0);
    alphaSlider->setMaximum(100);
    alphaSlider->setValue(100);

    QVBoxLayout *alphaLayout = new QVBoxLayout;
    alphaLayout->addLayout(alphaLabelLayout);
    alphaLayout->addWidget(alphaSlider);
    alphaLayout->setContentsMargins(10,10,10,10);

    QGroupBox *alphaGroup = new QGroupBox;
    alphaGroup->setLayout(alphaLayout);

    // button layout
    QPushButton *applyButton = new QPushButton(tr("Apply"));
    QPushButton *closeButton = new QPushButton(tr("Close"));

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addStretch(1);
    btnLayout->addWidget(applyButton);
    btnLayout->addWidget(closeButton);

    // right settings layout
    QVBoxLayout *settingLayout = new QVBoxLayout;
    settingLayout->addWidget(scrollareagroup);
    settingLayout->addWidget(alphaGroup);
    settingLayout->addStretch(1);
    settingLayout->addSpacing(12);
    settingLayout->addLayout(btnLayout);

    // main layout
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(imageGroup);
    mainLayout->addLayout(settingLayout);
    setLayout(mainLayout);

    connect(closeButton,SIGNAL(clicked()),this,SLOT(close()));
    connect(applyButton,SIGNAL(clicked()),this,SLOT(apply()));
    connect(specialeffects1,SIGNAL(clicked()),this,SLOT(handlespecialeffects1()));
    connect(specialeffects2,SIGNAL(clicked()),this,SLOT(handlespecialeffects2()));
    connect(specialeffects3,SIGNAL(clicked()),this,SLOT(handlespecialeffects3()));
    connect(specialeffects4,SIGNAL(clicked()),this,SLOT(handlespecialeffects4()));
    connect(specialeffects5,SIGNAL(clicked()),this,SLOT(handlespecialeffects5()));
    connect(specialeffects6,SIGNAL(clicked()),this,SLOT(handlespecialeffects6()));
    connect(specialeffects7,SIGNAL(clicked()),this,SLOT(handlespecialeffects7()));
    connect(specialeffects8,SIGNAL(clicked()),this,SLOT(handlespecialeffects8()));
    connect(specialeffects9,SIGNAL(clicked()),this,SLOT(handlespecialeffects9()));
    connect(specialeffects10,SIGNAL(clicked()),this,SLOT(handlespecialeffects10()));
    connect(specialeffects11,SIGNAL(clicked()),this,SLOT(handlespecialeffects11()));
    connect(specialeffects12,SIGNAL(clicked()),this,SLOT(handlespecialeffects12()));
    connect(alphaSlider,SIGNAL(sliderMoved(int)),this,SLOT(handlealphaslider(int)));
    connect(alphaSlider,SIGNAL(sliderReleased()),this,SLOT(handlealphaslider()));
}

QPixmap ClassicSpecialEffectDialog::Icon2Pixmap(QImage icon){
    QPixmap sepix = QPixmap::fromImage(icon);
    qreal h = sepix.height();
    qreal w = sepix.width();
    float rate = 0.7;
    if(sepix.height() > sepix.width())
        sepix = sepix.scaled(rate*seGroupMinHeight*w/h,rate*seGroupMinHeight,Qt::KeepAspectRatio);
    else sepix = sepix.scaled(rate*seGroupMinWidth,rate*seGroupMinWidth*h/w,Qt::KeepAspectRatio);
    return sepix;
}

void ClassicSpecialEffectDialog::setImage(std::shared_ptr<QImage> img){
    image = img;
}

void ClassicSpecialEffectDialog::sendData(bool apply){
    JsonParameters json;
    int value = 100;
    alphaSlider->setValue(value);
    alphaValue->setText(QString::number(value));
    json.insert("apply",std::make_shared<BoolParameters>(apply));
    json.insert("type",std::make_shared<EnumEffectsParameters>(effectsType));
    json.insert("alpha",std::make_shared<IntParameters>(value));
    emit sendApplySpecialEffect(std::make_shared<JsonParameters>(json));
}

void ClassicSpecialEffectDialog::apply(){
    sendData(true);
    close();
}

void ClassicSpecialEffectDialog::handlespecialeffects1(){
    effectsType = SHARPEN;
    sendData(false);
}
void ClassicSpecialEffectDialog::handlespecialeffects2(){
    effectsType = COLORTOBLACK;
    sendData(false);
}
void ClassicSpecialEffectDialog::handlespecialeffects3(){
    effectsType = DEFOG;
    sendData(false);
}
void ClassicSpecialEffectDialog::handlespecialeffects4(){
    effectsType = SOFT;
    sendData(false);
}
void ClassicSpecialEffectDialog::handlespecialeffects5(){
    effectsType = BALANCE;
    sendData(false);
}
void ClassicSpecialEffectDialog::handlespecialeffects6(){
    effectsType = NOSTALGIA;
    sendData(false);
}
void ClassicSpecialEffectDialog::handlespecialeffects7(){
    effectsType = BLACKCOMIC;
    sendData(false);
}
void ClassicSpecialEffectDialog::handlespecialeffects8(){
    effectsType = TIMETUUNEL;
    sendData(false);
}
void ClassicSpecialEffectDialog::handlespecialeffects9(){
    effectsType = CLASSICLOMO;
    sendData(false);
}
void ClassicSpecialEffectDialog::handlespecialeffects10(){
    effectsType = WHITEFACE;
    sendData(false);
}
void ClassicSpecialEffectDialog::handlespecialeffects11(){
    effectsType = BEAUTIFYFACE;
    sendData(false);
}
void ClassicSpecialEffectDialog::handlespecialeffects12(){
    effectsType = PINKLADY;
    sendData(false);
}

void ClassicSpecialEffectDialog::handlealphaslider(int value){
    alphaValue->setText(QString::number(value));
    JsonParameters json;
    bool apply = false;
    enum EffectsType type = NOEFFECTS;
    json.insert("apply",std::make_shared<BoolParameters>(apply));
    json.insert("type",std::make_shared<EnumEffectsParameters>(type));
    json.insert("alpha",std::make_shared<IntParameters>(value));
    emit sendApplySpecialEffect(std::make_shared<JsonParameters>(json));
}

void ClassicSpecialEffectDialog::handlealphaslider(){
    int value = alphaSlider->value();
    alphaValue->setText(QString::number(value));
    JsonParameters json;
    bool apply = false;
    enum EffectsType type = NOEFFECTS;
    json.insert("apply",std::make_shared<BoolParameters>(apply));
    json.insert("type",std::make_shared<EnumEffectsParameters>(type));
    json.insert("alpha",std::make_shared<IntParameters>(value));
    emit sendApplySpecialEffect(std::make_shared<JsonParameters>(json));
}

void ClassicSpecialEffectDialog::update(){
    QPixmap pix = QPixmap::fromImage(*image);
    qreal h = pix.height();
    qreal w = pix.width();
    if(h > imageMaxHeight)
        pix = pix.scaled(imageMaxHeight*w/h,imageMaxHeight,Qt::KeepAspectRatio);
    if(w > imageMaxWidth)
        pix = pix.scaled(imageMaxWidth,imageMaxWidth*h/w,Qt::KeepAspectRatio);
    imageLabel->setPixmap(pix);
}
