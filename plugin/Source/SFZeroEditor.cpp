#include "SFZeroEditor.h"
#include "SFZeroAudioProcessor.h"
#include "SFZeroFolders.h"

sfzero::SFZeroEditor::SFZeroEditor(SFZeroAudioProcessor *ownerFilter) : SFZeroEditorBase(ownerFilter){
  addAndMakeVisible(&viewport);
  viewport.setScrollBarsShown(true, true);
  viewport.setViewedComponent(&infoLabel, false);
  infoLabel.setFont(labelFont);
  infoLabel.setJustificationType(Justification::topLeft);
  infoLabel.addClickListener(this);
  setSize(500, 300);
}

sfzero::SFZeroEditor::~SFZeroEditor(){
}

void sfzero::SFZeroEditor::paint(Graphics &g){
  g.fillAll(Colours::white);
}

void sfzero::SFZeroEditor::resized(){
  int marginedWidth = getWidth() - 2 * hMargin;

  fileLabel.setBounds(hMargin, vMargin, marginedWidth, labelHeight);
  pathLabel.setBounds(hMargin, vMargin + labelHeight, marginedWidth, labelHeight);
  int infoTop = vMargin + 2 * labelHeight;
  int keyboardTop = getHeight() - keyboardHeight - vMargin;
  int infoLabelHeight = keyboardTop - infoTop - 4;
  viewport.setBounds(hMargin, infoTop, marginedWidth, infoLabelHeight);
  infoLabel.setBounds(0, 0, marginedWidth, infoLabelHeight * 10);
  midiKeyboard.setBounds(hMargin, keyboardTop, marginedWidth, keyboardHeight);
}
