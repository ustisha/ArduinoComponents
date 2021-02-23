#include "../include/DisplayHandler.h"
#include <../include/DisplayView.h>

void DisplayHandler::addDisplayHandler(DisplayView *view) {
    displayView = view;
}

void DisplayHandler::render() {
    if (displayView != nullptr) {
        displayView->render();
    }
}
