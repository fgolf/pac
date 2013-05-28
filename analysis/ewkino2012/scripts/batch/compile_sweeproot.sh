#!/bin/bash

g++ sweepRoot.C -o sweepRoot `root-config --cflags --libs` -lGenVector -lEG
