/*
  ZynAddSubFX - a software synthesizer

  Fl_Osc_ListView.H - OSC Based List View
  Copyright (C) 2016 Mark McCurry

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.
*/
#pragma once
#include <string>
#include <vector>
#include "Fl_Osc_Widget.H"
#include <FL/Fl_Browser.H>
#include "Osc_SimpleListModel.h"

class Fl_Osc_ListView:public Fl_Browser, Fl_Osc_Widget
{
    public:
        Fl_Osc_ListView(int x,int y, int w, int h, const char *label=0);
        virtual ~Fl_Osc_ListView(void);
        
        void init(const char *path_);
        void doUpdate(Osc_SimpleListModel::list_t l);
        void update(void);

        void insert(std::string s, int offset);
        void append(std::string s);
        void doMove(int i, int j);
        void doRemove(int offset);
    private:
        void sendUpdate() const;
        std::string path;
        Osc_SimpleListModel *data;
};
