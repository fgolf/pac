#!/bin/bash

./create_data_resubmit.sh >& data.log &
./create_mc_resubmit.sh >& mc.log &
