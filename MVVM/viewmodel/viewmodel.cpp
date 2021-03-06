#include "viewmodel.h"
#include "sinks/viewmodelsink.h"
#include "commands/openfilecommand.h"
#include "../common/util.h"
#include <QDebug>
#include <QIODevice>

ViewModel::ViewModel()
    : image(new QImage())
    , subimage(new QImage())
    , undoEnabled(new bool(false))
    , redoEnabled(new bool(false))
    , isBinary(new bool(false))
    , isGray(new bool(false))
    , undoMsg(new QString())
    , redoMsg(new QString())
{
    viewModelSink = std::make_shared<ViewModelSink>(this);

    openfilecommand = std::make_shared<OpenFileCommand>(this);
    savefilecommand = std::make_shared<SaveFileCommand>(this);
    opensubfilecommand = std::make_shared<OpenSubFileCommand>(this);
    opensubdialogcommand = std::make_shared<OpenSubDialogCommand>(this);
    undocommand = std::make_shared<UndoCommand>(this);
    redocommand = std::make_shared<RedoCommand>(this);

    filtercommand = std::make_shared<FilterCommand>(this);
    edgedetectioncommand = std::make_shared<EdgeDetectionCommand>(this);
    houghcircledetectioncommand = std::make_shared<HoughCircleDetectionCommand>(this);
    channelcommand = std::make_shared<ChannelCommand>(this);
    grayscaletransfercommand = std::make_shared<GrayScaleTransferCommand>(this);
    otsucommand = std::make_shared<OtsuCommand>(this);
    houghlinedetectioncommand = std::make_shared<HoughLineDetectionCommand>(this);
    dualthresholdcommand = std::make_shared<DualThresholdCommand>(this);
    huesaturalightcommand = std::make_shared<HueSaturaLightCommand>(this);

    curvecommand = std::make_shared<CurveCommand>(this);
    levelcommand = std::make_shared<LevelCommand>(this);
    clipcommand = std::make_shared<ClipCommand>(this);
    scalecommand = std::make_shared<ScaleCommand>(this);
    histogramcommand = std::make_shared<HistogramCommand>(this);
    algebraiccommand = std::make_shared<AlgebraicCommand>(this);
    binarymorphologycommand = std::make_shared<BinaryMorphologyCommand>(this);
    graymorphologycommand = std::make_shared<GrayMorphologyCommand>(this);

    arteffectscommand = std::make_shared<ArtEffectsCommand>(this);
    classiceffectscommand = std::make_shared<ClassicEffectsCommand>(this);
}

void ViewModel::bindModel(std::shared_ptr<Model> model){
    this->model = model;
    model->AddPropertyNotification(std::static_pointer_cast<IPropertyNotification>(viewModelSink));
}

void ViewModel::execOpenFileCommand(const QString &path){
    model->open_file(path);
}

void ViewModel::execSaveFileCommand(const QString &path){
    model->save_file(path);
}

void ViewModel::execOpenSubFileCommand(const QString &path){
    model->open_sub_file(path);
}

void ViewModel::execOpenSubDialogCommand(){
    model->main2sub();
}

void ViewModel::execUndoCommand(){
    model->undo();
}

void ViewModel::execRedoCommand(){
    model->redo();
}

void ViewModel::execFilterCommand(std::shared_ptr<JsonParameters> json){
    // model filter
    int type = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["type"])->getvalue();
    int col = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["col"])->getvalue();
    int row = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["row"])->getvalue();
    int x = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["x"])->getvalue();
    int y = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["y"])->getvalue();
    QString desc = "Filter: Type: ";
    switch (type) {
    case 0:
        desc += "mean filter, Kernel: (Size: (";
        desc += QString::number(col) + ", " + QString::number(row) + "), Anchor: (";
        desc += QString::number(x) + ", " + QString::number(y) + "))";
        model->commit(desc);
        model->meanFilter(col,row,x,y);
        break;
    case 1:
        desc += "median filter, Kernel: (Size: (";
        desc += QString::number(col) + ", " + QString::number(row) + "), Anchor: (";
        desc += QString::number(x) + ", " + QString::number(y) + "))";
        model->commit(desc);
        model->medianFilter(col,row,x,y);
        break;
    case 2:
        double sigma = std::static_pointer_cast<DoubleParameters,ParametersBase>((*json)["sigma"])->getvalue();
        desc += "median filter, Kernel: (Size: (";
        desc += QString::number(col) + ", " + QString::number(row) + "), Anchor: (";
        desc += QString::number(x) + ", " + QString::number(y) + "), ";
        desc += "Sigma: " + QString::number(sigma) + ")";
        model->commit(desc);
        model->gaussianFilter(col,row,x,y,sigma);
        break;
    }
}

void ViewModel::execEdgeDetectionCommand(std::shared_ptr<JsonParameters> json){
    // model edge detection
    int type = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["type"])->getvalue();
    QString desc = "Edge Detection: Type:";
    if(type == 2){
        int lo = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["lo"])->getvalue();
        int hi = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["hi"])->getvalue();
        desc += "canny, ";
        desc += "Low Threshold: " + QString::number(lo) + ", ";
        desc += "High Threshold: " + QString::number(hi);
        model->commit(desc);
        model->cannyEdgeDetection(lo,hi);
    } else {
        int threshold = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["threshold"])->getvalue();
        if(type == 0){
            desc += "sobel, Threshold: " + QString::number(threshold);
            model->commit(desc);
            model->sobelEdgeDetection(threshold);
        } else {
            desc += "laplacian, Threshold: " + QString(threshold);
            model->commit(desc);
            model->laplacianEdgeDetection(threshold);
        }
    }
}

void ViewModel::execHoughCircleDetectionCommand(std::shared_ptr<JsonParameters>json){
    QString desc = "Hough Transformation: Detect Circle: ";
    int lo = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["lo"])->getvalue();
    int hi = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["hi"])->getvalue();
    desc += "Radius: from " + QString::number(lo) + " to " + QString::number(hi);
    model->commit(desc);
    model->houghCircleDetect(lo,hi);
}

void ViewModel::execChannelCommand(std::shared_ptr<EnumCommandParameters> type){
    switch (type->getvalue()) {
    case RED_CHANNEL:
        //model
        model->commit("Channel Separation: Red");
        model->getSingleChannel(RED);
        break;
    case GREEN_CHANNEL:
        model->commit("Channel Separation: Green");
        model->getSingleChannel(GREEN);
        break;
    case BLUE_CHANNEL:
        model->commit("Channel Separation: Blue");
        model->getSingleChannel(BLUE);
        break;
    default:
        break;
    }
}

void ViewModel::execHoughLineDetectionCommand(){
    qDebug()<<"execHoughLineDetectionCommand()";
    //    qDebug()<<"bug here";
    //    model->houghLineDetect();
}

void ViewModel::execOtsuCommand(){
    model->commit("Image Binarization: OTSU");
    model->otsu();
}

void ViewModel::execGrayScaleTransferCommand(){
    model->commit("Gray-Scale Transfer");
    model->grayScale();
}

void ViewModel::execDualThresholdCommand(std::shared_ptr<JsonParameters> json){
    bool apply = std::static_pointer_cast<BoolParameters,ParametersBase>((*json)["apply"])->getvalue();
    int lo = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["low"])->getvalue();
    int hi = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["high"])->getvalue();
    model->dualThreshold(lo,hi);
    if(apply){
        QString desc = "Image Binarization: DualThreshold: (low threshold: ";
        desc += QString::number(lo) + ", ";
        desc += "high threshold: " + QString::number(hi) + ")";
        model->commit(desc);
        model->sub2main();
    }
}

void ViewModel::execHueSaturaLightCommand(std::shared_ptr<JsonParameters> json){
    bool apply = std::static_pointer_cast<BoolParameters,ParametersBase>((*json)["apply"])->getvalue();
    bool hue = std::static_pointer_cast<BoolParameters,ParametersBase>((*json)["hue"])->getvalue();
    bool saturation = std::static_pointer_cast<BoolParameters,ParametersBase>((*json)["saturation"])->getvalue();
    bool lightness = std::static_pointer_cast<BoolParameters,ParametersBase>((*json)["lightness"])->getvalue();
    QVector<int> hueValues = std::static_pointer_cast<QVectorParameters<int>,ParametersBase>((*json)["hueValues"])->getvalue();
    int saturationValue = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["saturationValue"])->getvalue();
    int lightnessValue = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["lightnessValue"])->getvalue();

    if(hue)model->adjustHue(hueValues);
    if(saturation)model->adjustSaturation(saturationValue);
    if(lightness)model->adjustLightness(lightnessValue);
    if(apply){
        QString desc = "HSL Adjust: ";
        desc += "Hue: (";
        desc += "whole image: " + QString::number(hueValues[0]) + ", ";
        desc += "red: " + QString::number(hueValues[1]) + ", ";
        desc += "yellow: " + QString::number(hueValues[2]) + ", ";
        desc += "green: " + QString::number(hueValues[3]) + ", ";
        desc += "cyan: " + QString::number(hueValues[4]) + ", ";
        desc += "blue: " + QString::number(hueValues[5]) + ", ";
        desc += "magenta: " + QString::number(hueValues[6]) + "), ";
        desc += "Saturation: " + QString::number(saturationValue) + ", ";
        desc += "Lightness: " + QString::number(lightnessValue);
        model->commit(desc);
        model->sub2main();
    }
}

void ViewModel::execCurveCommand(std::shared_ptr<JsonParameters> json)
{
    bool apply = std::static_pointer_cast<BoolParameters,ParametersBase>((*json)["apply"])->getvalue();
    QString type = std::static_pointer_cast<QStringParameters,ParametersBase>((*json)["type"])->getvalue();
    double a = std::static_pointer_cast<DoubleParameters,ParametersBase>((*json)["a"])->getvalue();
    double b = std::static_pointer_cast<DoubleParameters,ParametersBase>((*json)["b"])->getvalue();
    QPoint p1 = std::static_pointer_cast<QPointParameters,ParametersBase>((*json)["p1"])->getvalue();
    QPoint p2 = std::static_pointer_cast<QPointParameters,ParametersBase>((*json)["p2"])->getvalue();
    if(type == "Linear")model->linearContrastAdjust(p1.x(),p1.y(),p2.x(),p2.y());
    if(type == "Piecewice Linear")model->pieceLinContrastAdjust(p1.x(),p1.y(),p2.x(),p2.y());
    if(type == "Logarithm")model->logContrastAdjust(a,b);
    if(type == "Exponential")model->expContrastAdjust(a,b);
    if(apply){
        QString desc = "Adjust Contrast Curve: Curve Type: " + type;
        model->commit(desc);
        model->sub2main();
    }
}

void ViewModel::execLevelCommand(std::shared_ptr<JsonParameters> json)
{
    bool apply = std::static_pointer_cast<BoolParameters,ParametersBase>((*json)["apply"])->getvalue();
    ColorLevelData data = std::static_pointer_cast<ColorLevelDataParameters,ParametersBase>((*json)["data"])->getvalue();

    model->colorLevel(&data);
    if(apply){
        model->commit("Color Level Adjust");
        model->sub2main();
    }
}

void ViewModel::execClipCommand(std::shared_ptr<JsonParameters> json)
{
    QString desc = "Clip: ";
    int left = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["left"])->getvalue();
    int right = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["right"])->getvalue();
    int top = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["top"])->getvalue();
    int bottom = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["bottom"])->getvalue();
    desc += "X: from " + QString::number(left) + " to " + QString::number(right) + ", ";
    desc += "Y: from " + QString::number(top) + " to " + QString::number(bottom);
    model->commit(desc);
    model->clip(left,right,top,bottom);
}

void ViewModel::execScaleCommand(std::shared_ptr<JsonParameters> json)
{
    QString desc = "Scale/Rotation: Algorithms: ";

    int type = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["algo"])->getvalue();
    int scale = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["scale"])->getvalue();
    int rotation = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["rotation"])->getvalue();

    if(type == 0){
        desc += "nearnest interpolation, ";
        desc += "Scale: " + QString::number(scale) + ", ";
        desc += "Rotation: " + QString::number(rotation);
        model->commit(desc);
        model->nearnestInterpolation(scale, rotation);
    } else {
        desc += "bilinear interpolation, ";
        desc += "Scale: " + QString::number(scale) + ", ";
        desc += "Rotation: " + QString::number(rotation);
        model->commit(desc);
        model->nearnestInterpolation(scale, rotation);
    }
}

void ViewModel::execHistogramCommand(std::shared_ptr<VectorParameters<int> > histo)
{
    model->commit("Histogram Equalization");
    model->histogramEqualization(&(histo->getvalue())[0]);
}

void ViewModel::execAlgebraicCommand(std::shared_ptr<JsonParameters> json)
{
    QString operationDesc;
    enum commandsType type = std::static_pointer_cast<EnumCommandParameters,ParametersBase>((*json)["type"])->getvalue();
    bool dft = std::static_pointer_cast<BoolParameters,ParametersBase>((*json)["default"])->getvalue();
    double param1 = std::static_pointer_cast<DoubleParameters,ParametersBase>((*json)["param1"])->getvalue();
    double param2 = std::static_pointer_cast<DoubleParameters,ParametersBase>((*json)["param2"])->getvalue();
    switch (type) {
    case ALGEBRAIC_ADD:
        if(dft){
            operationDesc = "image1 + image2";
            model->commit("Algebraic Operation: " + operationDesc);
            model->imageAdd(1,1);
        }
        else{
            operationDesc = QIODevice::tr("%1*image1 + %2*image2").arg(param1).arg(param2);
            model->commit("Algebraic Operation: " + operationDesc);
            model->imageAdd(param1,param2);
        }
        break;
    case ALGEBRAIC_SUBTRACT:
        if(dft){
            operationDesc = "image1 - image2";
            model->commit("Algebraic Operation: " + operationDesc);
            model->imageSubtract(1,1);
        }
        else{
            operationDesc = QIODevice::tr("%1*image1 - %2*image2").arg(param1).arg(param2);
            model->commit("Algebraic Operation: " + operationDesc);
            model->imageSubtract(param1,param2);
        }
        break;
    case ALGEBRAIC_MULTIPLY:
        operationDesc = "image1 * image2";
        model->commit("Algebraic Operation: " + operationDesc);
        model->imageMultiply();
        break;
    default:
        break;
    }
}

void ViewModel::execBinaryMorphologyCommand(std::shared_ptr<JsonParameters> json)
{
    QString desc = "Binary Morphology: Operation: ";
    int size = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["size"])->getvalue();
    std::vector<int> elem = std::static_pointer_cast<VectorParameters<int>, ParametersBase>((*json)["elem"])->getvalue();

    int x = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["x"])->getvalue();
    int y = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["y"])->getvalue();

    int operation = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["operation"])->getvalue();
    switch (operation) 
    {
        case DILATION:
            desc += "Dilation, ";
            desc += QIODevice::tr("Structure Element Size: %1x%1, Anchor: (%2, %3)").arg(size).arg(x).arg(y);
            model->commit(desc);
            model->dilation(size, x, y, &elem[0]);
            break;
        case EROSION:
            desc += "Erosion, ";
            desc += QIODevice::tr("Structure Element Size: %1x%1, Anchor: (%2, %3)").arg(size).arg(x).arg(y);
            model->commit(desc);
            model->erosion(size, x, y, &elem[0]);
            break;
        case OPENING:
            desc += "Opening, ";
            desc += QIODevice::tr("Structure Element Size: %1x%1, Anchor: (%2, %3)").arg(size).arg(x).arg(y);
            model->commit(desc);
            model->opening(size, x, y, &elem[0]);
            break;
        case CLOSING:
            desc += "Closing, ";
            desc += QIODevice::tr("Structure Element Size: %1x%1, Anchor: (%2, %3)").arg(size).arg(x).arg(y);
            model->commit(desc);
            model->closing(size, x, y, &elem[0]);
            break;
        case SKELETONIZATION:
            desc += "Skeletonization, ";
            desc += QIODevice::tr("Structure Element Size: %1x%1, Anchor: (%2, %3)").arg(size).arg(x).arg(y);
            model->commit(desc);
            model->skeletonization(size, x, y, &elem[0]);
            break;
        case THINNING:
            desc += "Thinning";
            model->commit(desc);
            model->thinning();
            break;
        case THICKING:
            desc += "Thicking";
            model->commit(desc);
            model->thicking();
            break;
        case DISTANCE_TRANSFORM:
            desc += "Distance Transform";
            model->commit(desc);
            model->distanceTransform();
            break;
        case SKELETON_RECONSTRUCTION:
            desc += "Skeleton Reconstruction, ";
            desc += QIODevice::tr("Structure Element Size: %1x%1, Anchor: (%2, %3)").arg(size).arg(x).arg(y);
            model->commit(desc);
            model->skeletionReconstruct(size, x, y, &elem[0]);
            break;
        case RECONSTRUCTION:
            desc += "Reconstruction, ";
            desc += QIODevice::tr("Structure Element Size: %1x%1, Anchor: (%2, %3)").arg(size).arg(x).arg(y);
            model->commit(desc);
            model->binaryReconstruction(size, x, y, &elem[0]);
            break;
        default:
            break;
    }
}

void ViewModel::execGrayMorphologyCommand(std::shared_ptr<JsonParameters> json)
{
    QString desc = "Grayscale Morphology: Operation: ";
    int size = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["size"])->getvalue();
    std::vector<int> elem = std::static_pointer_cast<VectorParameters<int>, ParametersBase>((*json)["elem"])->getvalue();

    int x = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["x"])->getvalue();
    int y = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["y"])->getvalue();

    int operation = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["operation"])->getvalue();

    switch (operation) {
    case DILATION:
        desc += "Dilation, ";
        desc += QIODevice::tr("Structure Element Size: %1x%1, Anchor: (%2, %3)").arg(size).arg(x).arg(y);
        model->commit(desc);
        model->dilation(size, x, y, &elem[0]);
        break;
    case EROSION:
        desc += "Erosion, ";
        desc += QIODevice::tr("Structure Element Size: %1x%1, Anchor: (%2, %3)").arg(size).arg(x).arg(y);
        model->commit(desc);
        model->erosion(size, x, y, &elem[0]);
        break;
    case OPENING:
        desc += "Opening, ";
        desc += QIODevice::tr("Structure Element Size: %1x%1, Anchor: (%2, %3)").arg(size).arg(x).arg(y);
        model->commit(desc);
        model->opening(size, x, y, &elem[0]);
        break;
    case CLOSING:
        desc += "Closing, ";
        desc += QIODevice::tr("Structure Element Size: %1x%1, Anchor: (%2, %3)").arg(size).arg(x).arg(y);
        model->commit(desc);
        model->closing(size, x, y, &elem[0]);
        break;
    case OBR:
        desc += "Opening By Reconstruction, ";
        desc += QIODevice::tr("Structure Element Size: %1x%1, Anchor: (%2, %3)").arg(size).arg(x).arg(y);
        model->commit(desc);
        model->obr(size, x, y, &elem[0]);
        break;
    case CBR:
        desc += "Closing By Reconstruction, ";
        desc += QIODevice::tr("Structure Element Size: %1x%1, Anchor: (%2, %3)").arg(size).arg(x).arg(y);
        model->commit(desc);
        model->cbr(size, x, y, &elem[0]);
        break;
    case WATERSHED:
        desc += "Watershed";
        model->commit(desc);
        model->watershed();
        break;
    default:
        break;
    }
}

void ViewModel::execArtEffectsCommand(std::shared_ptr<JsonParameters> json)
{
    enum EffectsType type = std::static_pointer_cast<EnumEffectsParameters,ParametersBase>((*json)["type"])->getvalue();
    bool apply = std::static_pointer_cast<BoolParameters,ParametersBase>((*json)["apply"])->getvalue();
    int alpha = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["alpha"])->getvalue();
    if(apply)
    {
        model->commit("Classic Effect");
        model->sub2main();
    }
    else
    switch (type) {
    case NOEFFECTS:
        model->mix_tmp_main(alpha);
        break;
    case EMBOSS:
        model->_emboss();
        break;
    case SCULPTURE:
        model->_sculpture();
        break;
    case DILATE:
        model->_dilate();
        break;
    case ERODE:
        model->_erode();
        break;
    case FROSTGLASS:
        model->_frostGlass();
        break;
    case SKETCH:
        model->_sketch();
        break;
    case OILPAINT:
        model->_oilPaint();
        break;
    case WOODCUT:
        model->_woodCut();
        break;
    case INVERTED:
        model->_inverted();
        break;
    case MEMORY:
        model->_memory();
        break;
    case FREEZING:
        model->_freezing();
        break;
    case CASTING:
        model->_casting();
        break;
    case COMICSTRIP:
        model->_comicStrip();
        break;
    default:
        break;
    }
}

void ViewModel::execClassicEffectsCommand(std::shared_ptr<JsonParameters> json){
    enum EffectsType type = std::static_pointer_cast<EnumEffectsParameters,ParametersBase>((*json)["type"])->getvalue();
    bool apply = std::static_pointer_cast<BoolParameters,ParametersBase>((*json)["apply"])->getvalue();
    int alpha = std::static_pointer_cast<IntParameters,ParametersBase>((*json)["alpha"])->getvalue();
    if(apply)
    {
        model->commit("Classic Effect");
        model->sub2main();
    }
    else
    switch (type) {
    case NOEFFECTS:
        model->mix_tmp_main(alpha);
        break;
    case SHARPEN:
        model->_sharpen();
        break;
    case COLORTOBLACK:
        model->_colortoblack();
        break;
    case DEFOG:
        model->_defog();
        break;
    case SOFT:
        model->_soft();
        break;
    case BALANCE:
        model->_balance();
        break;
    case NOSTALGIA:
        model->_nostalgia();
        break;
    case BLACKCOMIC:
        model->_BlackComic();
        break;
    case TIMETUUNEL:
        model->_timetuunel();
        break;
    case CLASSICLOMO:
        model->_classiclomo();
        break;
    case WHITEFACE:
        model->_whiteFace();
        break;
    case BEAUTIFYFACE:
        model->_beautifyFace();
        break;
    case PINKLADY:
        model->_pinkLady();
        break;
    default:
        break;
    }
}

std::shared_ptr<ICommandBase> ViewModel::getOpenFileCommand(){
    return openfilecommand;
}

std::shared_ptr<ICommandBase> ViewModel::getSaveFileCommand(){
    return savefilecommand;
}

std::shared_ptr<ICommandBase> ViewModel::getOpenSubFileCommand(){
    return opensubfilecommand;
}

std::shared_ptr<ICommandBase> ViewModel::getOpenSubDialogCommand(){
    return opensubdialogcommand;
}

std::shared_ptr<ICommandBase> ViewModel::getUndoCommand(){
    return undocommand;
}

std::shared_ptr<ICommandBase> ViewModel::getRedoCommand(){
    return redocommand;
}

std::shared_ptr<ICommandBase> ViewModel::getFilterCommand(){
    return filtercommand;
}

std::shared_ptr<ICommandBase> ViewModel::getEdgeDetectionCommand(){
    return edgedetectioncommand;
}

std::shared_ptr<ICommandBase> ViewModel::getHoughCircleDetectionCommand(){
    return houghcircledetectioncommand;
}

std::shared_ptr<ICommandBase> ViewModel::getChannelCommand(){
    return channelcommand;
}

std::shared_ptr<ICommandBase> ViewModel::getOtsuCommand(){
    return otsucommand;
}

std::shared_ptr<ICommandBase> ViewModel::getHoughLineDetectionCommand(){
    return houghlinedetectioncommand;
}

std::shared_ptr<ICommandBase> ViewModel::getGrayScaleTransferCommand(){
    return grayscaletransfercommand;
}

std::shared_ptr<ICommandBase> ViewModel::getDualThresholdCommand(){
    return dualthresholdcommand;
}

std::shared_ptr<ICommandBase> ViewModel::getHueSaturaLightCommand(){
    return huesaturalightcommand;
}

std::shared_ptr<QImage> ViewModel::getImage(){
    return image;
}

std::shared_ptr<QImage> ViewModel::getSubImage(){
    return subimage;
}

std::shared_ptr<bool> ViewModel::getUndoEnabled(){
    return undoEnabled;
}
std::shared_ptr<bool> ViewModel::getRedoEnabled(){
    return redoEnabled;
}
std::shared_ptr<QString> ViewModel::getUndoMsg(){
    return undoMsg;
}
std::shared_ptr<QString> ViewModel::getRedoMsg(){
    return redoMsg;
}

std::shared_ptr<bool> ViewModel::getIsBinary(){
    return isBinary;
}
std::shared_ptr<bool> ViewModel::getIsGray(){
    return isGray;
}

std::shared_ptr<ICommandBase> ViewModel::getCurveCommand()
{
    return curvecommand;
}

std::shared_ptr<ICommandBase> ViewModel::getLevelCommand()
{
    return levelcommand;
}

std::shared_ptr<ICommandBase> ViewModel::getClipCommand()
{
    return clipcommand;
}

std::shared_ptr<ICommandBase> ViewModel::getScaleCommand()
{
    return scalecommand;
}

std::shared_ptr<ICommandBase> ViewModel::getHistogramCommand()
{
    return histogramcommand;
}

std::shared_ptr<ICommandBase> ViewModel::getAlgebraicCommand()
{
    return algebraiccommand;
}

std::shared_ptr<ICommandBase> ViewModel::getBinaryMorphologyCommand()
{
   return binarymorphologycommand;
}

std::shared_ptr<ICommandBase> ViewModel::getGrayMorphologyCommand()
{
   return graymorphologycommand;
}

std::shared_ptr<ICommandBase> ViewModel::getArtEffectsCommand()
{
    return arteffectscommand;
}

std::shared_ptr<ICommandBase> ViewModel::getClassicEffectsCommand()
{
    return classiceffectscommand;
}

void ViewModel::setImageFromModel(){
    *image = model->getMain();
    *isBinary = model->isBinaryImage();
    *isGray = model->isGrayImage();
}

void ViewModel::setSubImageFromModel(){
    *subimage = model->getSub();
}

void ViewModel::updateLogManagerFromModel(){
    *undoEnabled = model->undoEnabled();
    *redoEnabled = model->redoEnabled();
    *undoMsg = model->getUndoMsg();
    *redoMsg = model->getRedoMsg();
}
