# SFZero, the Juce module version

This is a fork of the [forked SFZero of altalogix](https://github.com/altalogix/SFZero) from the [original SFZero by Steve Folta](https://github.com/stevefolta/SFZero), with the following changes:

* add OSX and iOS AUv3 with standalone
* added disk streaming for SFZ files

Please note that, in order to build, SFZero requires [Juce](http://www.juce.com).

Before building the sample plugin, it's necessary to

* for iOS under XCode, ensure AppExtension and STanalone are both given the same group ID. 

See altalogix repo for more info on building 
