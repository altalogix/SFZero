/*
  ==============================================================================

    SFZeroFileBrowserLookAndFeel.cpp
    Created: 28 Nov 2017 7:47:28pm
    Author:  malcolm

  ==============================================================================
*/

#include "SFZeroFileBrowserLookAndFeel.h"
sfzero::SFZeroFileBrowserLookAndFeel::SFZeroFileBrowserLookAndFeel(){
}

sfzero::SFZeroFileBrowserLookAndFeel::~SFZeroFileBrowserLookAndFeel(){
}

void sfzero::SFZeroFileBrowserLookAndFeel::drawFileBrowserRow (Graphics& g, int width, int height,
                                                               const File& file, const String& filename, Image* icon,
                                                               const String& fileSizeDescription,
                                                               const String& fileTimeDescription,
                                                               bool isDirectory, bool isItemSelected,
                                                               int itemIndex, DirectoryContentsDisplayComponent& dcc){
  LookAndFeel_V4::drawFileBrowserRow (g, width, height,
                                      file, filename, icon,
                                      "",
                                      "",
                                      isDirectory, isItemSelected,
                                      itemIndex, dcc);
}
