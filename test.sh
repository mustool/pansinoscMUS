#!/bin/bash

jalv.gtk -c "amp=0,5" http://musens.pluggar/lv2/lv2pftci/pansinoscMUS &

sleep 0.1

jalv.gtk -c "amp=0,5" http://musens.pluggar/lv2/lv2pftci/sinwtMUS &


sleep 1

jack_connect "sinwtMUS MUS:out1" "pansinoscMUS MUS:in1" &

jack_connect "sinwtMUS MUS:out2" "pansinoscMUS MUS:in2" &

sleep 1

jack_connect "pansinoscMUS MUS:out1" "system:playback_1" &

jack_connect "pansinoscMUS MUS:out2" "system:playback_2" &
