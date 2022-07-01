#!/bin/bash
#source runscript.sh
rm -rf *.d *.so *.pcm
rm -rf AnalysisOutputs.root
rm -rf AnalysisOutputs.txt
root -l Run.C 

