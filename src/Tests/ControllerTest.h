/*
  ZynAddSubFX - a software synthesizer

  ControllerTest.h - CxxTest for Params/Controller
  Copyright (C) 2009-2011 Mark McCurry
  Author: Mark McCurry

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.
*/
#include <cxxtest/TestSuite.h>
#include <iostream>
#include "../Params/Controller.h"
#include "../globals.h"
#include "../Misc/Time.h"

SYNTH_T *synth;

class ControllerTest:public CxxTest::TestSuite
{
    public:
        void setUp() {
            synth   = new SYNTH_T;
            AbsTime time(*synth);
            testCtl = new Controller(*synth, &time);
        }

        void tearDown() {
            delete testCtl;
            delete synth;
        }


        void testPortamentoRange() {
            //Initialize portamento
            testCtl->setportamento(127);
            testCtl->portamento.time = 127;
            testCtl->initportamento(40.0f, 400.0f, false);
            //Bounds Check
            while(testCtl->portamento.used) {
                TS_ASSERT((0.0f <= testCtl->portamento.x)
                          && (testCtl->portamento.x <= 1.0f));
                TS_ASSERT((0.1f <= testCtl->portamento.freqrap)
                          && (testCtl->portamento.freqrap <= 1.0f));
                testCtl->updateportamento();
            }
            TS_ASSERT((0.0f <= testCtl->portamento.x)
                      && (testCtl->portamento.x <= 1.0f));
            TS_ASSERT((0.1f <= testCtl->portamento.freqrap)
                      && (testCtl->portamento.freqrap <= 1.0f));
        }

        void testPortamentoValue() {
            testCtl->setportamento(127);
            testCtl->portamento.time = 127;
            testCtl->initportamento(40.0f, 400.0f, false);
            int i;
            for(i = 0; i < 10; ++i)
                testCtl->updateportamento();
            //Assert that the numbers are the same as they were at release
            TS_ASSERT_DELTA(testCtl->portamento.x, 0.0290249f, 0.000001f)
            TS_ASSERT_DELTA(testCtl->portamento.freqrap, 0.126122f, 0.000001f)
        }

    private:
        Controller *testCtl;
};
