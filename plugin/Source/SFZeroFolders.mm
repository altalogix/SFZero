#include "SFZeroFolders.h"
#include "Foundation/NSFileManager.h"
#include "Foundation/NSString.h"

sfzero::SFZeroFolders::SFZeroFolders(){
};

sfzero::SFZeroFolders::~SFZeroFolders(){
}

 File sfzero::SFZeroFolders::GetGroupFolder(){
  NSFileManager* fm = [NSFileManager defaultManager];
  NSURL *containerURL = [fm containerURLForSecurityApplicationGroupIdentifier:@"group.com.vsamp.SFZero"];
  String tmp = ([containerURL.relativeString UTF8String]);
  File startDir(tmp.substring(7));
  return(startDir);
}
