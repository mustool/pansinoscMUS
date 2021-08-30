/*

Copyright MUS 2020

This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.


*/


#include <lv2plugin.hpp>
#include <math.h>
#include <lv2lib00_MUS/mainMUS.h>

using namespace LV2;

class PanSinOscMUS : public Plugin<PanSinOscMUS> {
public:

  PanSinOscMUS(double rate)
    : Plugin<PanSinOscMUS>(9) {

      panosc = new WaveTableSine00(rate, 0, 0.0, 1.0, 0.0);

  }

  void run(uint32_t nframes) {

    float pan = *p(4);

    pan = pan < -1 ? -1 : pan;
    pan = pan > 1 ? 1 : pan;

    float rate = *p(5);

    rate = rate < 0 ? 0 : rate;
    rate = rate > 22 ? 22 : rate;

    float amt = *p(6);

    amt = amt < 0 ? 0 : amt;
    amt = amt > 1 ? 1 : amt;


    float mix = *p(7);

    mix = mix < 0 ? 0 : mix;
    mix = mix > 1 ? 1 : mix;

    float rmix = 1.0 - mix;

    float amp = *p(8);

    amp = amp < 0 ? 0 : amp;
    amp = amp > 1 ? 1 : amp;

    panosc->setFreq(rate);

    panosc->setMul(amt);


    for (uint32_t i = 0; i < nframes; ++i) {

      float left = p(0)[i];
      float right = p(1)[i];

      float osc = panosc->ar();
      osc += pan;
      osc += 1.0;
      osc *= 0.5;

      if(osc > 1.0) osc = 1.0;
      if(osc < 0.0) osc = 0.0;

      float leftpan = left;
      leftpan *= (1.0 - osc);
      float rightpan = right;
      rightpan *= osc;

      p(2)[i] = ((leftpan * mix) + (left * rmix)) * amp;
      p(3)[i] =  ((rightpan * mix) + (right * rmix)) * amp;

    }

  }

protected:
WaveTableSine00* panosc;


};

static int _ = PanSinOscMUS::register_class("http://musens.pluggar/lv2/lv2pftci/pansinoscMUS");
