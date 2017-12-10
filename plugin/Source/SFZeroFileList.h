/*
  ==============================================================================

    SFZeroFileList.h
    Created: 27 Nov 2017 8:38:23pm
    Author:  malcolm

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
namespace sfzero
{
  
  class SFZeroFileList : public FileTreeComponent
  {
  public:
    SFZeroFileList(DirectoryContentsList& listToShow);
    ~SFZeroFileList();
    
    void paint(Graphics &g) override;
  protected:
  };
}
