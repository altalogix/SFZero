/*
  ==============================================================================

    SFZeroFileBrowserLookAndFeel.h
    Created: 28 Nov 2017 7:47:28pm
    Author:  malcolm

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
namespace sfzero
{
  
  class SFZeroFileBrowserLookAndFeel : public LookAndFeel_V4
  {
  public:
    SFZeroFileBrowserLookAndFeel();
    ~SFZeroFileBrowserLookAndFeel();
    void drawFileBrowserRow (Graphics&, int width, int height,
                             const File& file, const String& filename, Image* icon,
                             const String& fileSizeDescription, const String& fileTimeDescription,
                             bool isDirectory, bool isItemSelected, int itemIndex,
                             DirectoryContentsDisplayComponent&) override;
  };
}
