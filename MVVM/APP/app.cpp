#include <QApplication>
#include "app.h"

ImageBeautifyApp::ImageBeautifyApp()
    : view(new MainView)
    , model(new Model)
    , viewmodel(new ViewModel)
{
    viewmodel->bindModel(model);

    view->setImage(viewmodel->getImage());
    view->setSubImage(viewmodel->getSubImage());
    view->setUndoEnabled(viewmodel->getUndoEnabled());
    view->setRedoEnabled(viewmodel->getRedoEnabled());
    view->setUndoMsg(viewmodel->getUndoMsg());
    view->setRedoMsg(viewmodel->getRedoMsg());
    view->setIsBinary(viewmodel->getIsBinary());
    view->setIsGray(viewmodel->getIsGray());

    view->setOpenFileCommand(viewmodel->getOpenFileCommand());
    view->setSaveFileCommand(viewmodel->getSaveFileCommand());
    view->setOpenSubFileCommand(viewmodel->getOpenSubFileCommand());
    view->setOpenSubDialogCommand(viewmodel->getOpenSubDialogCommand());
    view->setRedoCommand(viewmodel->getRedoCommand());
    view->setUndoCommand(viewmodel->getUndoCommand());

    view->setFilterCommand(viewmodel->getFilterCommand());
    view->setEdgeDetectionCommand(viewmodel->getEdgeDetectionCommand());
    view->setHoughCircleDetectionCommand(viewmodel->getHoughCircleDetectionCommand());
    view->setChannelCommand(viewmodel->getChannelCommand());
    view->setOtsuCommand(viewmodel->getOtsuCommand());
    view->setGrayScaleTransferCommand(viewmodel->getGrayScaleTransferCommand());
    view->setHoughLineDetectionCommand(viewmodel->getHoughLineDetectionCommand());
    view->setDualThresholdCommand(viewmodel->getDualThresholdCommand());
    view->setHueSaturaLightCommand(viewmodel->getHueSaturaLightCommand());

    view->setCurveCommand(viewmodel->getCurveCommand()); 
    view->setLevelCommand(viewmodel->getLevelCommand());
    view->setClipCommand(viewmodel->getClipCommand());
    view->setScaleCommand(viewmodel->getScaleCommand());
    view->setHistogramCommand(viewmodel->getHistogramCommand());
    view->setAlgebraicCommand(viewmodel->getAlgebraicCommand());
    view->setBinaryMorphologyCommand(viewmodel->getBinaryMorphologyCommand());
    view->setGrayMorphologyCommand(viewmodel->getGrayMorphologyCommand());

    view->setArtEffectsCommand(viewmodel->getArtEffectsCommand());
    view->setClassicEffectsCommand(viewmodel->getClassicEffectsCommand());

    viewmodel->AddPropertyNotification(view->getMainViewSink());
    viewmodel->AddCommandNotification(view->getMainCommandSink());
}

void ImageBeautifyApp::run(){
    view->show();
}
